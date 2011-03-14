#!/usr/bin/perl

`mkdir -p report`;
`convert test1.png -endian LSB report/test.pfm`;
`convert test2.png -endian LSB report/addimg.pfm`;

$time = 0;
open REPORT, '>report/index.html';
print REPORT <<REPORT;
<html><head>HIDRA VFX report</head><body>
<table>
REPORT
open TESTS, 'tests';
for (<TESTS>) 
{
  chomp;
  ($cmd, @params) = split /\s+/, $_;
  if ( -e "report/$cmd.png" ) {} else {
    print REPORT "<tr><td><a href=\"$cmd.jpg\"><img src=\"$cmd.jpg\" width=\"320\" height=\"240\" /></a></td><td>\n<pre>";
    print REPORT `../bin/hidravfx help $cmd`;
    print REPORT "</pre></td></tr>\n";
    $res = `cd report; (time ../../bin/hidravfx $cmd --out=$cmd.pfm @params test.pfm >/dev/null) 2>&1`;
    $res =~ /real\s+(\d+)+m(\d+)\.(\d+)s/;
    $time += $1 * 60 + $2 + $3/1000;
    print "Testing $cmd command: \t";
    print "$1 min $2.$3 sec, done.\n";
    `cd report; convert $cmd.pfm $cmd.jpg`;
  }
}
print REPORT <<REPORT;
</table></body></html>
REPORT
close TESTS;
close REPORT;

print ("Testing done. Processing time: $time sec\n\n");
`rm report/*.pfm`;
