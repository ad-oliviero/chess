#!/bin/bash

res_fname="../src/headers/res_generated.hpp"
files=("pawn.svg" "tower.svg" "horse.svg" "bishop.svg" "king.svg" "queen.svg")
rm -f "$res_fname"

printf "#ifndef _RES_HPP_\n#define _RES_HPP_\n\n" >> "$res_fname"

for s in "${files[@]}"; do
	newf="${s//svg/png}"
	convert -background none "$s" "$newf"
	xxd -i "$newf" >> "$res_fname"
done

printf "\nunsigned char* images_data[] = {%s};\n" "$(grep 'unsigned char' $res_fname | sed 's/unsigned char //g;s/\[\] = {/,/g')" >> "$res_fname"
printf "\nunsigned int images_data_len[] = {%s};\n" "$(grep 'unsigned int' $res_fname | awk '{ print $5 }' | sed 's/;/,/g')" >> "$res_fname"

wget "https://github.com/IdreesInc/Monocraft/releases/download/v2.5/Monocraft.ttf" -O font.ttf
xxd -i font.ttf >> "$res_fname"
rm -f font.ttf

printf "\n#endif // _RES_HPP_" >> "$res_fname"
