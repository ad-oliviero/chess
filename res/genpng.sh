#!/bin/bash

for s in *.svg; do
	convert -background none "$s" "${s//svg/png}"
done