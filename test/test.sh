#!/bin/bash

EFFECTS="none invert pitinvert"
          
for i in $EFFECTS; 
do
  if [ ! -e test-$i-after.png ]
  then
    cp temp.png test-$i-before.png
    convert test-$i-before.png -endian LSB test-$i-before.pfm
    ../bin/hidravfx --cmd=$i --in=test-$i-before.pfm --out=test-$i-after.pfm
    convert test-$i-after.pfm test-$i-after.png
  fi
done