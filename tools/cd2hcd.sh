#!/bin/bash
# Backup an PC Engine CDROM2 game into an hcd archive.
# Copyright 2012-2014, Alexander von Gluck IV for HuExpress
# Released under the terms of the MIT license

# DO NOT USE THIS TOOL FOR PIRACY!
# Archives are for personal use only unless you have
# written permission of the title publisher.

function checkTools() {
	echo -n "Checking for required tools... "
	for var in "$@"; do
		echo -n "$var "
		which $var &> /dev/null
		if [ $? -ne 0 ]; then
			echo "Error!"
			echo "$var isn't available! Please install first"
			exit 1
		fi
	done
	echo "OK!"
}

echo "========================================"
echo "HuExpress PCengine CD archival utility"
echo "Revision 0.3"
echo "========================================"
echo ""
echo "Do not distrubute personal game backups!"
echo ""

CDROM=${1}
TEMP="/tmp/cd2hcd"
CSVDB="./pcecd.csv"

if [ $# -ne 1 ]; then
	echo "Usage: $0 <cdrom>"
	echo
	exit 1
fi

if [ ! -b ${CDROM} ]; then
	echo "warning: ${CDROM} is not a block device!"
else
	echo "Using block device ${CDROM}"
fi

if [ $(mount | grep ${CDROM} | wc -l) -gt 0 ]; then
	echo "error: ${CDROM} looks to be mounted, please unmount and retry!"
	exit 1
fi

rm -rf ${TEMP}
mkdir -p ${TEMP}
if [ ! -d ${TEMP} ]; then
	# Exists, but not a directory. error
	echo "${TEMP} isn't a directory!"
	exit 1
fi

if [ -f /usr/share/huexpress/pcecd.csv ]; then
    CSVDB="/usr/share/huexpress/pcecd.csv";
fi

if [ ! -f ${CSVDB} ]; then
	echo "Unable to find pcecd.csv in /usr/share/huexpress or ."
	exit 1
fi

# Check for required tools...
checkTools cdrdao toc2cue bchunk oggenc grep wc zip

read -p "What is the ID of this game? " -e givenID

gameID=$(grep "${givenID}" ${CSVDB} | head -1 | cut -d"," -f1)
gameName="unknown"
gameDeveloper="unknown"
gameRelease="unknown"
gameCountry="unknown"
gameMedia="CDROM2"
if [ $(echo ${gameID} | wc -c) -le 2 ]; then
	echo "Warning: ${gameCountry} id ${gameID} is not known to me. Metadata is unknown"
else
	gameName=$(grep "${gameID}" ${CSVDB} | head -1 | cut -d"," -f2)
	gameDeveloper=$(grep "${gameID}" ${CSVDB} | head -1 | cut -d"," -f3)
	gameRelease=$(grep "${gameID}" ${CSVDB} | head -1 | cut -d"," -f4)
	gameCountry=$(grep "${gameID}" ${CSVDB} | head -1 | cut -d"," -f5)
	gameMedia=$(grep "${gameID}" ${CSVDB} | head -1 | cut -d"," -f6)
	echo "Found game name \"${gameName}\" (${gameCountry}) in local database."
fi

cd ${TEMP}
# Rip CD
echo "Examining ${gameMedia} game information..."
lastTrack=$(cdrdao disk-info --device ${CDROM} 2>/dev/null | grep "Last Track" | cut -d":" -f2 | tr -d ' ')
echo "Ripping ${gameMedia} image..."
cdrdao read-cd -v 0 --read-raw --device ${CDROM} --datafile ${gameID}.bin ${gameID}.toc &> /tmp/cd2hcd.log
if [ $? -gt 0 ]; then
	echo "cdrdao error. Please see /tmp/cd2hcd.log for details"
	exit 1
fi
echo "Converting TOC to CUE..."
toc2cue ${gameID}.toc ${gameID}.cue &>> /tmp/cd2hcd.log
# Break out tracks
echo "Breaking apart disc tracks..."
bchunk -w -s ${gameID}.bin ${gameID}.cue Track &>> /tmp/cd2hcd.log
rm ${gameID}.bin ${gameID}.toc

hcdFile=${gameID}.hcd

# Generate a basic hcd
echo "Generating hcd metadata and encoding wav tracks..."
echo "[main]" > ${hcdFile}
echo "id=${gameID}" >> ${hcdFile}
echo "media=${gameMedia}" >> ${hcdFile}
echo "country=${gameCountry}" >> ${hcdFile}
echo "title=${gameName}" >> ${hcdFile}
echo "developer=${gameDeveloper}" >> ${hcdFile}
echo "release=${gameRelease}" >> ${hcdFile}
echo "price=unknown" >> ${hcdFile}
echo "genere=unknown" >> ${hcdFile}
echo "first_track=1" >> ${hcdFile}
echo "last_track=${lastTrack}" >> ${hcdFile}
echo "minimum_bios=1" >> ${hcdFile}
echo "" >> ${hcdFile}

track=1
for i in $(find . -name "*.wav" -or -name "*.ugh" -or -name "*.iso" | sort); do
        filename=$(echo $i | cut -d \/ -f 2)
        extension=$(echo $filename | cut -d . -f 2)
        basename=$(echo $filename | cut -d . -f 1)
        echo "[track${track}]" >> ${hcdFile}
        case $extension in
		"wav")
			echo "Track ${track}: Converting wav to ogg..."
			echo "type=AUDIO" >> ${hcdFile}
			oggenc -l "${gameID}" -N ${track} ${filename} &> /dev/null
			rm ${filename}
			filename="${basename}.ogg"
			extension="ogg"
			;;
		"ogg" | "mp3")
			echo "Track ${track}: $extension track."
			echo "type=AUDIO" >> ${hcdFile}
			;;
		"ugh")
			echo "Track ${track}: Code track."
			echo "type=CODE" >> ${hcdFile}
			mv "${filename}" "${basename}.iso"
			filename="${basename}.iso"
			extension="iso"
			;;
		"iso")
			echo "Track ${track}: Code track."
			echo "type=CODE" >> ${hcdFile}
			;;
		*)
			echo "Track ${track}: Warning: Unknown track!"
			echo "type=UNKNOWN" >> ${hcdFile}
			;;
        esac
        echo "filename=${filename}" >> ${hcdFile}
        track=$[track+1];
done;

FILEOUT="${gameName} - ${gameID}.zip"

zip -9 "$FILEOUT" *
cd -

mv "${TEMP}/${FILEOUT}" .
echo "Complete! ${FILEOUT} was created."
