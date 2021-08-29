#!/usr/local/bin/fontforge
# Quick and dirty hack: converts a font to truetype (.ttf)
#fontforge -script otf2ttf.sh FONTNAME.otf
#for i in *.otf; do fontforge -script otf2ttf.sh $i; done

#!/bin/bash

for f in $(find . -type f -name "*.otf")
do
	echo "Processing $f ..."
	Print("Opening "+$f);
	Open($f);
	Print("Saving "+$f:r+".ttf");
	Generate($f:r+".ttf");
	Quit(0);
done

#find . -type f -name "*.png" -exec convert {} -strip {} \;
