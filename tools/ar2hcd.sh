#!/bin/bash

# Convert an PC Engine CDROM2 game archive into an hcd archive.
# Copyright 2012-2014, Alexander von Gluck IV for HuExpress
# Released under the terms of the MIT license

# DO NOT USE THIS TOOL FOR PIRACY!
# Archives are for personal use only unless you have
# written permission of the title publisher.


# This tool runs on a large number of compressed games
# and converts them into a HCD enabled zip archive.

# This tool makes a few assumptions:
#   Tracks are in order starting at 01, Track01, etc
#   No "extra mp3's or iso's are in the archive"
#   Tracks are already broken apart and audio compressed as mp3 or ogg
#   Game name is in the title of the archive.
#   Archive is a zip or a rar

# The output of this tool can be a little rough, it is
# made to assit converting a large number of games into
# a common HCD format that contain game metadata. YMMV

if [ $# -ne 2 ]; then
	echo "Usage: $0 <search path> <out path>"
	exit 1
fi

BASEPATH="$1"
OUTPATH="$2"
TMPPATH="/tmp/ar2hcd"

CSVDB="./pcecd.csv"
if [ -f /usr/share/huexpress/pcecd.csv ]; then
    CSVDB="/usr/share/huexpress/pcecd.csv";
fi

rm -rf $TMPPATH

find $BASEPATH -name "*.rar" -or -name "*.zip" | while read line
do
	mkdir -p "$TMPPATH/output"

	AREXT="${line##*.}"
	case $AREXT in
		rar*)
			unrar x "$line" "$TMPPATH/" &> /dev/null
			;;
		zip*)
			unzip "$line" -d "$TMPPATH/" &> /dev/null
			;;
		*)
			echo "Unknown extension: $AREXT"
			;;
	esac

	find "$TMPPATH/" -name "*.iso" -or -name "*.mp3" -or -name "*.ogg" -or -name "*.cue" -or -name "*.toc" | while read file
	do
		mv "$file" "$TMPPATH/output/"
	done

	TRACKS=$(find "$TMPPATH/" -name "*.iso" -or -name "*.mp3" -or -name "*.ogg" | wc -l)
	HCDPATH="${TMPPATH}/output/game.hcd"
	TITLE=$(echo ${line##*/} | cut -d'(' -f1 | cut -d'-' -f1 | sed 's/ *$//')

	gameID="unknown"
	gameName="unknown"
	gameDeveloper="unknown"
	gameRelease="unknown"
	gameCountry="unknown"
	gameMedia="CDROM2"
	if [ $(grep "${TITLE}" ${CSVDB} | wc -c) -le 2 ]; then
		echo "Warning: '${TITLE}' is not known to me. Metadata is unknown"
	else
		gameID=$(grep "${TITLE}" ${CSVDB} | head -1 | cut -d"," -f1)
		gameName=$(grep "${TITLE}" ${CSVDB} | head -1 | cut -d"," -f2)
		gameDeveloper=$(grep "${TITLE}" ${CSVDB} | head -1 | cut -d"," -f3)
		gameRelease=$(grep "${TITLE}" ${CSVDB} | head -1 | cut -d"," -f4)
		gameCountry=$(grep "${TITLE}" ${CSVDB} | head -1 | cut -d"," -f5)
		gameMedia=$(grep "${TITLE}" ${CSVDB} | head -1 | cut -d"," -f6)
		echo "Info:    '${TITLE}' (${gameCountry}) was found in local database."
	fi

	echo "[main]" >> "${HCDPATH}"
	echo "id=${gameID}" >> "${HCDPATH}"
	echo "media=${gameMedia}" >> "${HCDPATH}"
	echo "country=${gameCountry}" >> "${HCDPATH}"
	echo "title=${TITLE}" >> "${HCDPATH}"
	echo "developer=${gameDeveloper}" >> "${HCDPATH}"
	echo "release=${gameRelease}" >> "${HCDPATH}"
	echo "price=unknown" >> "${HCDPATH}"
	echo "first_track=1" >> "${HCDPATH}"
	echo "last_track=${TRACKS}" >> "${HCDPATH}"
	echo "minimum_bios=1" >> "${HCDPATH}"
	echo "" >> "${HCDPATH}"

	no=1
	find "$TMPPATH/output" -name "*.iso" -or -name "*.mp3" -or -name "*.ogg" | while read file
	do
		EXT="${file##*.}"
		echo "[track${no}]" >> "${HCDPATH}"
		case $EXT in
			iso*)
				echo "type=CODE" >> "${HCDPATH}"
				;;
			mp3*)
				echo "type=AUDIO" >> "${HCDPATH}"
				;;
			ogg*)
				echo "type=AUDIO" >> "${HCDPATH}"
				;;
		esac
		echo "filename=$(basename ${file})" >> "${HCDPATH}"
		echo "" >> "${HCDPATH}"
		no=$((no+1))
	done
	
	cd ${TMPPATH}/output/
	zip -9 -D "${OUTPATH}/${TITLE}.zip" * 1> /dev/null
	cd - &> /dev/null

	rm -rf "${TMPPATH}"
done
