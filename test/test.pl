#!/usr/bin/perl

`convert temp-base.png -endian LSB test.pfm`;
`convert temp-add.png -endian LSB add.pfm`;

open TESTS, 'tests';
for (<TESTS>) 
{
  chomp;
  ($cmd, @params) = split /\s+/, $_;
  if ( -e "$cmd.png" ) {} else {
    print "Testing $cmd command\n";
    `../bin/hidravfx $cmd --out=$cmd.pfm @params test.pfm`;
    `convert $cmd.pfm $cmd.png`;
  }
}
close TESTS;

`rm *.pfm`;