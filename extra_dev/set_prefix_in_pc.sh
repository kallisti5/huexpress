#!/bin/sh

sed 's/^prefix.*/prefix=\/usr\/i586-mingw32msvc/' $1 > /tmp/$$.tmp && mv /tmp/$$.tmp  $1