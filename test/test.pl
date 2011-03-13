#!/usr/bin/perl

`convert temp-base.png -endian LSB test.pfm`;
`convert temp-add.png -endian LSB add.pfm`;

for (<DATA>) 
{
  chomp;
  ($cmd, @params) = split /\s+/, $_;
  if ( -e "$cmd.png" ) {} else {
    print "Testing $cmd command\n";
    `../bin/hidravfx $cmd --out=$cmd.pfm @params test.pfm`;
    `convert $cmd.pfm $cmd.png`;
  }
}

`rm *.pfm`;

__DATA__
none
invert 
geoinvert
pitinvert
upshift          --shift=0.2
bright           --bright=0.2
contrast         --gain=1.5
dark             --gain=0.5
light            --gain=0.5
bright2          --bright=0.2
stone            --power=2
cloud            --limit=0.4 --xmax=4
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
bolyaiSphere     --x0=0.5 --y0=0.5 --z0=0.3 --R=0.5
spherize         --x0=0.5 --y0=0.5 --radius=0.5 --angle=1.0
invbolyaiSphere  --x0=0.5 --y0=0.5 --z0=0.5 --R=0.6
shift            --x0=0.3 --y0=0.5 
polarToDescartes
descartesToPolar
rotate           --x0=0.4 --y0=0.5 --angle=1.0471 
swirl            --x0=0.4 --y0=0.5 --radial=15 --angle=0.5
pinch            --scale=2
sinusoidal       --scale=1
centermirror     --x0=0.4 --y0=0.5 
axismirror       --x0=0.4 --y0=0.5 --axisx=0.4 --axisy=0.5
misterx          --rad=1
tube             --x0=0.4 --y0=0.5 --rad=0.1 --numX=6 --numY=3 --dX=0 --dY=0 