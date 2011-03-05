#!/bin/bash
for i in none invert ; do
  cp temp.png test-$i-before.png
  convert test-$i-before.png test-$i-before.pfm
  echo ../bin/hidravfx --cmd=$i --in=test-$i-before.pfm --out=test-$i-after.pfm
  ../bin/hidravfx --cmd=$i --in=test-$i-before.pfm --out=test-$i-after.pfm
  convert test-$i-after.pfm test-$i-after.png
done