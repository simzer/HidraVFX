#!/usr/bin/perl

`mkdir -p report`;
`mkdir -p report/images`;
`convert test1.png -endian LSB report/test.pfm`;
`convert test2.png -endian LSB report/addimg.pfm`;

$time = 0;
$report .= <<REPORT;
<table>
REPORT
open TESTS, 'tests';
for (<TESTS>) 
{
  chomp;
  ($cmd, @params) = split /\s+/, $_;
  if ( -e "report/images/$cmd.jpg" ) {} else {
    $report .= "<tr><td><a href=\"images/$cmd.jpg\"><img src=\"images/$cmd.jpg\" width=\"240\" height=\"180\" /></a></td><td>\n<pre>";
    $report .=  `../bin/hidravfx help $cmd`;
    $report .=  "</pre></td></tr>\n";
    $res = `cd report; (time ../../bin/hidravfx $cmd --out=images/$cmd.pfm @params test.pfm >/dev/null) 2>&1`;
    $res =~ /real\s+(\d+)+m(\d+)\.(\d+)s/;
    $time += $1 * 60 + $2 + $3/1000;
    print "Testing $cmd command: \t";
    print "$1 min $2.$3 sec, done.\n";
    `cd report/images; convert $cmd.pfm $cmd.jpg`;
  }
}
$report .= <<REPORT;
</table>
REPORT
close TESTS;

open REPORT, '>report/index.html';
print REPORT $report;
close REPORT;

open INDEX, '../../HidraVFX-gh-pages/index.html';
$content = join('',<INDEX>);
close INDEX;
$content =~ s/<!--TABLE -->.*<!--TABLE -->/<!--TABLE -->$report---<!--TABLE -->/s;
open INDEX, '>../../HidraVFX-gh-pages/index.html';
print INDEX $content ;
close INDEX;

print ("Testing done. Processing time: $time sec\n\n");
`rm report/images/*.pfm`;
`cp -r report/images ../../HidraVFX-gh-pages`;