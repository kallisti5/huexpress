#!/bin/bash
# Convert an PC Engine CDROM2 game into an hcd archive.
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

ISO="${1}"
CUE="${2}"
TEMP="/tmp/iso2hcd"
CSVDB="./pcecd.csv"

if [ $# -ne 2 ]; then
	echo "Usage: $0 <iso> <cue>"
	echo
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

# Check for required tools...
checkTools bchunk oggenc grep wc

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
# Find last track of iso
lastTrack=$(egrep -Ri "TRACK \d*" ${CUE} | tail -1 | awk '{ print $2 }')
echo "Tracks: ${lastTrack}"
# Break out tracks
echo "Breaking apart disc tracks..."
bchunk -w -s ${ISO} ${CUE} Track &> /dev/null

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
