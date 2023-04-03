#!/bin/bash

for s in *.svg; do
	convert -background none "$s" "${s//svg/png}"
done

cp pawn.png horse.png
cp pawn.png bishop.png
cp pawn.png king.png
cp pawn.png queen.png