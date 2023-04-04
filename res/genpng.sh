#!/bin/bash

images_data_fname="../src/headers/images.hpp"
files=("pawn.svg" "tower.svg" "horse.svg" "bishop.svg" "king.svg" "queen.svg")
rm "$images_data_fname"

for s in "${files[@]}"; do
	newf="${s//svg/png}"
	convert -background none "$s" "$newf"
	xxd -i "$newf" >> "$images_data_fname"
done

printf "\nunsigned char* images_data[] = {%s};\n" "$(grep 'unsigned char' $images_data_fname | sed 's/unsigned char //g;s/\[\] = {/,/g')" >> $images_data_fname
printf "\nunsigned int images_data_len[] = {%s};\n" "$(grep 'unsigned int' $images_data_fname | awk '{ print $5 }' | sed 's/;/,/g')" >> $images_data_fname