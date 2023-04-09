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

curl "https://objects.githubusercontent.com/github-production-release-asset-2e65be/522358431/7a8f40f3-0d42-4441-8beb-01ff33c66df4?X-Amz-Algorithm=AWS4-HMAC-SHA256&X-Amz-Credential=AKIAIWNJYAX4CSVEH53A%2F20230409%2Fus-east-1%2Fs3%2Faws4_request&X-Amz-Date=20230409T185042Z&X-Amz-Expires=300&X-Amz-Signature=6b3ef4657f778d59fc5db8529e79bd2eb0bcdf9458fc82b2d56a0f72494f6096&X-Amz-SignedHeaders=host&actor_id=41623496&key_id=0&repo_id=522358431&response-content-disposition=attachment%3B%20filename%3DMonocraft.ttf&response-content-type=application%2Foctet-stream" -o font.ttf
xxd -i font.ttf >> "$res_fname"

printf "\n#endif // _RES_HPP_" >> "$res_fname"