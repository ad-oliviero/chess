#!/bin/bash

for s in "$(find . -name '*.svg')";
do
	convert -background none "$s" "${s//svg/png}"
done
