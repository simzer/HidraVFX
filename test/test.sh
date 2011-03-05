#!/bin/bash

EFFECTS="none invert pitinvert"
          
cp temp.png test.png
convert test.png -endian LSB test.pfm
for i in $EFFECTS; 
do
  if [ ! -e test-$i-after.png ]
  then
    echo Testing $i command
    ../bin/hidravfx --cmd=$i --in=test.pfm --out=test-$i-after.pfm
    convert test-$i-after.pfm test-$i-after.png
  fi
done

BLENDINGS="allanon multiply bleach screen divide add sub diff "
BLENDINGS+="difference paralel darken lighten texture light "
BLENDINGS+="dark ekvivalence addSub pitagoras arctan exclusion "
BLENDINGS+="geomMean gammaDark gammaLight burn linearLight "
BLENDINGS+="colorDodge colorBurn pinLight hardLight softLight "
BLENDINGS+="vividLight overlay"

cp temp1.png blend-base.png
cp temp2.png blend-add.png
convert blend-base.png -endian LSB blend-base.pfm
convert blend-add.png -endian LSB blend-add.pfm
for i in $BLENDINGS ; 
do
  if [ ! -e blend-$i-after.png ]
  then
    echo Testing $i command
    ../bin/hidravfx --cmd=$i --in=blend-base.pfm --add=blend-add.pfm --out=blend-$i-after.pfm
    convert blend-$i-after.pfm blend-$i-after.png
  fi
done

rm *.pfm