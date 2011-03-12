#!/usr/bin/perl
use strict;
my $copyright = <<COPYRIGHT;
/****************************************************************************
Copyright (C) 2010 Laszlo Simon <laszlo.simon\@gmail.com>

This file is part of the HidraVFX project.

HidraVFX is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

HidraVFX is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with HidraVFX. If not, see <http://www.gnu.org/licenses/>.
****************************************************************************/
COPYRIGHT

my %effects = do('../src/effects.pl');

my $funcdecl = <<CODE;
/** <DESC>
 *  \\return Error value */
int <NAME>(
  tLayerF srcimg /**< Source image */,
  tLayerF tarimg /**< Target image */,
  int fproc(int) /**< progress indicator function */<PARAMS>);  

CODE

my $funcdef = <<CODE;
/** <DESC> 
 *  \\return Error value */
int <NAME>(
  tLayerF srcimg /**< Source image */,
  tLayerF tarimg /**< Target image */,
  int fproc(int) /**< progress indicator function */<PARAMS>)  
{
  int err = 0;
  int ix, iy, ch;
  int w = srcimg.w;
  int h = srcimg.h;
  float src, tar;
  <INIT>
  for (iy = 0; iy < h; iy++)
  {
    if (fproc != NULL) { fproc(iy * 100 / h); }
    for (ix = 0; ix < w; ix++)
    {
      ch = 0;
      src = srcimg.ch[ch][iy][ix]; 
      <CALC>
      tarimg.ch[ch][iy][ix] = tar;
      ch = 1;
      src = srcimg.ch[ch][iy][ix];
      <CALC>
      tarimg.ch[ch][iy][ix] = tar;
      ch = 2;
      src = srcimg.ch[ch][iy][ix];
      <CALC>
      tarimg.ch[ch][iy][ix] = tar;
    }
  }
  return(err);
}

CODE

my $funccall = <<CODE;
  if (0 == strcmp(command, "<NAME>"))
  {
    err = <NAME>(image, result, print_process<PARAMCALLS>);
    print_process(100);
  }
CODE

my $funcdefs     = '';
my $funcdecls    = '';
my $funccalls    = '';
my $effectlist   = '';
my $effectdescs  = '';
my $paramindices = '';
my $paramnums    = '';
my $paramlist    = '';
my $paramdescs   = '';
my $effectcnt    = 0;
my $paramcnt     = 0;

for (sort(keys(%effects)))
{
  my $name = $_;
  my $desc = $effects{$_}->{desc};
  my $calc = $effects{$_}->{calc};
  my $init = $effects{$_}->{init};
  my $prms = $effects{$_}->{prms};
  my $paramdefs  = '';
  my $paramcalls = '';
  my $paramindex = $paramcnt;
  
  $paramindices .= "$paramindex, ";
  for (keys(%{$prms}))
  {
    $calc =~ s/$_/getpix($_,ch,ix,iy)/g;
    $paramdefs .= ",\n  tLayerF $_\t/* $prms->{$_}->{desc} */";
    $paramcalls.= ", getOpt(\"$_\")";
    $paramlist .= "\"$_\",\n";
    $paramdescs.= "\"$prms->{$_}->{desc}\",\n";
    $paramcnt++;
  } 
  $paramnums .= ($paramcnt-$paramindex).", ";
  
  $effectlist  .= "  \"$name\",\n";
  $effectdescs .= "  \"$desc\",\n";
    
  my $fdf = $funcdef;
  $fdf =~ s/<NAME>/$name/g;
  $fdf =~ s/<DESC>/$desc/g;
  $fdf =~ s/<CALC>/$calc/g;
  $fdf =~ s/<INIT>/$init/g;
  $fdf =~ s/<PARAMS>/$paramdefs/g;
  $funcdefs .= $fdf;

  my $fdc = $funcdecl;
  $fdc =~ s/<NAME>/$name/g;
  $fdc =~ s/<DESC>/$desc/g;
  $fdc =~ s/<PARAMS>/$paramdefs/g;
  $funcdecls .= $fdc; 

  my $fcl = $funccall;
  $fcl =~ s/<NAME>/$name/g;
  $fcl =~ s/<PARAMCALLS>/$paramcalls/g;
  $funccalls .= $fcl; 

  $effectcnt++;
}

open OUT, '>cmdproc.i';
print OUT <<CODE;
{ 
$funccalls
}
CODE
close OUT;

open OUT, '>effects.c';
print OUT <<CODE;
$copyright

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "mathplus.h"
#include "options.h"
#include "layer.h"
#include "effects.h"

int   effectnum = $effectcnt;

char *effectlist[] = {
$effectlist};

char *effectdescs[] = {
$effectdescs};

int   paramindices[] = {$paramindices};
int   paramnums[]    = {$paramnums};

char *paramlist[] = {
$paramlist};

char *paramdescs[] = {
$paramdescs};

$funcdefs

CODE
close OUT;

open OUT, '>effects.h';
print OUT <<CODE;
$copyright

#ifndef EFFECTS_H_
#define EFFECTS_H_

extern int   effectnum;
extern char *effectlist[];
extern char *effectdescs[];
extern int   paramindices[];
extern int   paramnums[];
extern char *paramlist[];
extern char *paramdescs[];

$funcdecls

#endif
CODE

print "codegen.pl: Code generation done.\n";