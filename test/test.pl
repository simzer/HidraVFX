#!/usr/bin/perl

`convert temp1.png -endian LSB test.pfm`;
`convert temp2.png -endian LSB add.pfm`;

for (<DATA>) 
{
  chomp;
  ($cmd, @params) = split /\s+/, $_;
  if ( -e "$cmd.png" ) {} else {
    print "Testing $cmd command\n";
    `../bin/hidravfx --cmd=$cmd --in=test.pfm --out=$cmd.pfm @params`;
    `convert $cmd.pfm $cmd.png`;
  }
}

`rm *.pfm`;

__DATA__
none
invert 
pitinvert
allanon          --add=add.pfm 
multiply         --add=add.pfm 
bleach           --add=add.pfm 
screen           --add=add.pfm 
divide           --add=add.pfm 
add              --add=add.pfm 
sub              --add=add.pfm 
diff             --add=add.pfm 
difference       --add=add.pfm 
paralel          --add=add.pfm 
darken           --add=add.pfm 
lighten          --add=add.pfm 
texture          --add=add.pfm 
light            --add=add.pfm 
dark             --add=add.pfm 
ekvivalence      --add=add.pfm 
addSub           --add=add.pfm 
pitagoras        --add=add.pfm 
arctan           --add=add.pfm 
exclusion        --add=add.pfm 
geomMean         --add=add.pfm 
gammaDark        --add=add.pfm 
gammaLight       --add=add.pfm 
burn             --add=add.pfm 
linearLight      --add=add.pfm 
colorDodge       --add=add.pfm 
colorBurn        --add=add.pfm 
pinLight         --add=add.pfm 
hardLight        --add=add.pfm 
softLight        --add=add.pfm 
vividLight       --add=add.pfm 
overlay          --add=add.pfm 
bolyaiSphere     --x0=600 --y0=300 --z0=150 --R=400
spherize         --x0=600 --y0=300 --rc=200 --factor=80
invbolyaiSphere  --x0=600 --y0=300 --z0=150 --R=400
shift            --x0=600 --y0=300 
polarToDescartes
descartesToPolar
rotate           --angle=1.0471 --x0=600 --y0=300
swirl            --angle=0.5235 --x0=600 --y0=300 --radial=50
pinch            --scale=2
sinusoidal       --scale=100
centermirror     --x0=600 --y0=300 
axismirror       --x0=600 --y0=300 --axisx=10 --axisy=100
misterx          --rad=400
tube             --x0=600 --y0=300 --rad=0.1 --numX=6 --numY=2 --dX=0 --dY=0 