#!/usr/bin/perl
# Copyright (C) 2010 Laszlo Simon <laszlo.simon@gmail.com>
# This file is part of the HidraVFX project.
(
none => {      desc => 'Do nothing (for debug purpose)',
               calc => 'tar = src;'},

invert => {    desc => 'Invert.',
               calc => 'tar = 1.0 - src;'},

geoinvert => { desc => 'Multiplicative invert.',
               calc => 'tar = 0.001/sqrt(src);'},

pitinvert => { desc => 'Invert with Pythagorean theorem.',
               calc => 'tar = sqrt(1.0 - src*src);'},

upshift => {   desc => 'Increase with <shift>.', 
               calc => 'tar = src + shift; tar = tar - (int)tar;',
               prms => {'shift' => {}}}, 

bright => {    desc => 'Additional bright with <bright>.', 
               calc => 'tar = src + bright;',
               prms => {'bright' => {}}},

contrast => {  desc => 'Multiplicative contrast.', 
               calc => 'tar = (src - 0.5) * gain + 0.5;',
               prms => {'gain' => {}}},

bright2 => {   desc => 'Multiplicative bright', 
               calc => 'tar = (bright < 0) ? src*(1.0+bright) : src+(1.0-src)*bright;',
               prms => {'bright' => {}}},

stone => {     desc => '', 
               calc => 'tar = 1.0 - pow(1.0-src, power);',
               prms => {'power' => {}}},

cloud => {     desc => '', 
               calc => 'tar = src<=limit ? 0 : log(xmax*(src-limit)/(1.0-limit)+1)/log(xmax+1);',
               prms => {'limit' => {}, 
                        'xmax'  => {}}},
);
# BLENDINGS
allanon => {   desc => '', 
               calc => 'tar = (src+add)/2;',
               prms => {'add' => { desc => "Blend image."}}},
multiply => {  desc => '', 
               calc => 'tar = src*add;',
               prms => {'add' => { desc => "Blend image."}}},
bleach => {    desc => '', 
               calc => 'tar = (1-src)*(1-add);',
               prms => {'add' => { desc => "Blend image."}}},
screen => {    desc => '', 
               calc => 'tar = 1-(1-src)*(1-add);',
               prms => {'add' => { desc => "Blend image."}}},
divide => {    desc => '', 
               calc => 'tar = src / add;',
               prms => {'add' => { desc => "Blend image."}}},
add => {       desc => '', 
               calc => 'tar = src + add;',
               prms => {'add' => { desc => "Blend image."}}},
'sub' => {     desc => '', 
               calc => 'tar = src - add;',
               prms => {'add' => { desc => "Blend image."}}},
diff => {      desc => '', 
               calc => 'tar = fabs(src-add);',
               prms => {'add' => { desc => "Blend image."}}},
difference => {desc => '', 
               calc => 'tar = src - add + 1;',
               prms => {'add' => { desc => "Blend image."}}},
paralel => {   desc => '', 
               calc => 'tar = 2/(1/src+1/add);',
               prms => {'add' => { desc => "Blend image."}}},
darken => {    desc => '', 
               calc => 'tar = add < src ? add : src;',
               prms => {'add' => { desc => "Blend image."}}},
lighten => {   desc => '', 
               calc => 'tar = add > src ? add : src;',
               prms => {'add' => { desc => "Blend image."}}},
texture => {   desc => '', 
               calc => 'tar = src + add - 0.5;',
               prms => {'add' => { desc => "Blend image."}}},
light => {     desc => '', 
               calc => 'tar = src*(1-add)+add*add;',
               prms => {'add' => { desc => "Blend image."}}},
dark => {      desc => '', 
               calc => 'tar = (src+1-add)*add;',
               prms => {'add' => { desc => "Blend image."}}},
ekvivalence => {desc => '', 
               calc => 'tar = 1 - fabs(src-add);',
               prms => {'add' => { desc => "Blend image."}}},
addSub => {    desc => '', 
               calc => 'tar = fabs(src*src-add*add);',
               prms => {'add' => { desc => "Blend image."}}},
pitagoras => { desc => '', 
               calc => 'tar = sqrt(src*src+add*add)/sqrt(2);',
               prms => {'add' => { desc => "Blend image."}}},
arctan => {    desc => '', 
               calc => 'tar = atan(2*atan2(add,1-src)/PI);',
               prms => {'add' => { desc => "Blend image."}}},
exclusion => { desc => '', 
               calc => 'tar = src + add - 2 * src * add;',
               prms => {'add' => { desc => "Blend image."}}},
geomMean => {  desc => '', 
               calc => 'tar = sqrt(src * add);',
               prms => {'add' => { desc => "Blend image."}}},
gammaDark => { desc => '', 
               calc => 'tar = pow(src,add);',
               prms => {'add' => { desc => "Blend image."}}},
gammaLight => {desc => '', 
               calc => 'tar = pow(src,1/add);',
               prms => {'add' => { desc => "Blend image."}}},
burn => {      desc => '', 
               calc => 'tar = src + add - 1;',
               prms => {'add' => { desc => "Blend image."}}},
linearLight => {desc => '', 
               calc => 'tar = src + 2 * add - 1;',
               prms => {'add' => { desc => "Blend image."}}},
colorDodge => {desc => '', 
               calc => 'tar = src / (1-add);',
               prms => {'add' => { desc => "Blend image."}}},
colorBurn => { desc => '', 
               calc => 'tar = 1-(1-src)/add;',
               prms => {'add' => { desc => "Blend image."}}},
pinLight => {  desc => '', 
               calc => 'tar = max(2*add-1,min(src,2*add));',
               prms => {'add' => { desc => "Blend image."}}},
hardLight => { desc => '', 
               calc => 'tar = add < 0.5 ? 2*src*add : 1-2*(1-src)*(1-add);',
               prms => {'add' => { desc => "Blend image."}}},
softLight => { desc => '', 
               calc => 'tar = pow(src,pow(2,(2*(0.5-add))));',
               prms => {'add' => { desc => "Blend image."}}},
vividLight => {desc => '', 
               calc => 'tar = add < 0.5 ? 1-(1-src)/(2*add) : src/(2*(1-add));',
               prms => {'add' => { desc => "Blend image."}}},
overlay => {   desc => '', 
               calc => 'tar = add > 0.5 ? 2*src*add : 1-2*(1-src)*(1-add);',
               prms => {'add' => { desc => "Blend image."}}},
__DATA__                        
# CONFORM DISTORSIONS
bolyaiSphere => { desc => ''.
               crds => '
  double d, fi, d0;                    
  d = sqrt(sqr(x - x0) + sqr(y - y0)); 
  fi = atan2(y - y0, x - x0);          
  d0 = d * R / sqrt(sqr(d) + sqr(z0)); 
  x1 = x0 + d0 * cos(fi);              
  y1 = y0 + d0 * sin(fi);              
               ',
               prms => {x0 => {}, y0 => {}, z0  => {}, R => {} }},
spherize => {  desc => '',
               crds => '
  double alp0 = (PI/2)*factor/100;
  double d = sqrt(sqr(x-x0)+sqr(y-y0));
  if (d>rc) {
    x1 = x;
    y1 = y;
  } else {
    double fi, R, z0, tmp, z, d0;
    fi = atan2(y-y0,x-x0);
    R = rc/sin(alp0);
    z0 = R*cos(alp0);
    tmp = sqr(R)-sqr(x-x0)-sqr(y-y0);
    z = sqrt(tmp)+z0;
    d0 = (alp0 > 0) ? z0*d/(z-z0) : z0*d/(z+z0);
    x1 = x0+d0*cos(fi);
    y1 = y0+d0*sin(fi);
  }
               ',
               prms => {x0 => {}, y0 => {}, rc => {}, factor => {} }},
invbolyaiSphere => {  desc => '',
               crds => '
  double d, fi, tmp, z, d0; 
  d = sqrt(sqr(x-x0)+sqr(y-y0)); 
  fi = atan2(y-y0,x-x0); 
  tmp = sqr(R)-sqr(x-x0)-sqr(y-y0); 
     z = sqrt(tmp)+z0; 
     d0 = (z0 < 0)  ? -z0 * d / (z - z0) : 
                       z0 * d / (z + z0); 
  x1 = x0 + d0 * cos(fi); 
  y1 = y0 + d0 * sin(fi); 
               ',
               prms => {x0 => {}, y0 => {}, z0 => {}, R => {} }},
polarToDescartes => { desc => '',
               crds => '
  double zx, zy, ux, uy, r, fi, rCons, fiCons;
  rCons  = (h-1)/(sqrt(w*w+h*h)/2.0);
  fiCons = (w-1)/(2*PI);
  ux = (w/2.0)-1;
  uy = (h/2.0)-1;
  zx = x-ux;
  zy = y-uy;
  r = sqrt(sqr(zx)+sqr(zy));
  fi = atan2(zy,zx);
  x1 = fi * fiCons;
  y1 = h - r*rCons - 1;
               ' },
descartesToPolar => { desc => '',
               crds => '
  double rCons, fiCons, ux, uy;
  rCons  = (sqrt(w*w+h*h)/2.0)/(h-1);
  fiCons = (2*PI)/(w-1);
  ux = (w/2.0)-1;
  uy = (h/2.0)-1;
  x1 = y*rCons*cos(x*fiCons)+ux;
  y1 = y*rCons*sin(x*fiCons)+uy;
               ' },
rotate => {    desc => '',
               crds => '
  double o, ux, uy, rx, ry, zx, zy;
  rx = cos(angle);
  ry = sin(angle);
  zx = x-x0;
  zy = y-y0;
  if (ry == 0) {
     ux =zx/rx;
     uy =zy/rx;
  } else {
     o  =rx*rx+ry*ry;
     ux =(zx*rx+zy*ry)/o;
     uy =(zy*rx-zx*ry)/o;
  }
  x1 = ux+x0;
  y1 = uy+y0;
               ',               
               prms => {angle => {}, x0 => {}, y0 => {} }},
swirl => {     desc => '',
               crds => '
  double r,fi,zx,zy,ux,uy,tx,ty,z2x,z2y;
  tx = cos(angle);
  ty = sin(angle);
  zx  = x-x0;
  zy  = y-y0;
  r   = sqrt(sqr(zx)+sqr(zy))/radial;
  fi  = r * angle;
  ux  = cos(fi);
  uy  = sin(fi);
  z2x = zx * ux - zy * uy;
  z2y = zx * uy + zy * ux;
  x1  = (z2x*tx+z2y*ty)+x0;
  y1  = (z2y*tx-z2x*ty)+y0;
                       ',
               prms => {angle => {}, radial => {}, x0 => {}, y0 => {} }},
pinch => {     desc => '',
               crds => '
  double zx, zy, ux, uy, z2, r;
  ux = (2.0 * x / w) - 1;
  uy = (2.0 * y / h) - 1;
  r  = sqrt(sqr(ux) + sqr(uy));
  z2 = pow(r, scale);
  zx = z2 * ux / r;
  zy = z2 * uy / r;
  x1 = (zx+1)*(w/2.0);
  y1 = (zy+1)*(h/2.0);
               ',
               prms => {scale => {}  }},
sinusoidal => {desc => '',
               crds => '
  double ux,uy,zx,zy,arcsin;
  arcsin = 1.0/asin(scale/100.0);
  ux   = (x-(w/2.0))/(w/2.0);
  uy   = (y-(h/2.0))/(h/2.0);
  ux   = ux*scale/100.0;
  uy   = uy*scale/100.0;
  zx   = asin(ux)*arcsin;
  zy   = asin(uy)*arcsin;
  x1   = zx*(w/2.0)+(w/2.0);
  y1   = zy*(h/2.0)+(h/2.0);
               ',
               prms => {scale => {} }},
centermirror => { desc => '',
               crds => '
  x1 = x0 - (x - x0);
  y1 = y0 - (y - y0);
               ',
               prms => {x0 => {}, y0 => {} }},
axismirror => {desc => '',
               crds => '
  double tx, ty, d;
  d = sqrt(sqr(axisx)+sqr(axisy));
  axisx /= d;
  axisy /= d;
  tx = (x*axisx + y*axisy) / (d*d);
  ty = (x*axisy - y*axisx) / (d*d);
  x1 = (tx*axisx - ty*axisy) + x0;
  y1 = (tx*axisy + ty*axisx) + y0;
               ',
               prms => {x0 => {}, y0 => {}, axisx => {}, axisy => {} }},
misterx => {   desc => '',
               crds => '
  double zx,zy,o;
  zx = (x - (w / 2.0)) / rad;
  zy = (y - (h / 2.0)) / rad;
  o  = zx * zx + zy * zy;
  zx = zx / o;
  zy = -zy / o;
  x1  = zx*rad + (w / 2.0);
  y1  = zy*rad + (h / 2.0);
  if (x1 <  0)   x1 = -x1-1;
  if (x1 >= w*2) x1 = (2.0*w)*(x1/(2.0*w)-(int)(x1/(2.0*w)));
  if (x1 >= w)   x1 = w-1-(x1-w);
  if (y1 <  0)   y1 = -y1-1;
  if (y1 >= h*2) y1 = (2*h)*(y1/(2.0*h)-(int)(y1/(2.0*h)));
  if (y1 >= h)   y1 = h-1-(y1-h);
                       ',
               prms => {rad => {} }},
tube => {      desc => '',
               crds => '
  double d, fi, d0, dmax, fio, rmin, rmax;
  fio  = atan2(h/2.0-x0,w/2.0-y0);
  rmin = sqrt(sqr(w/2.0)+sqr(h/2.0))-sqrt(sqr(x0-w/2.0)+sqr(y0-h/2.0));
  rmax = sqrt(sqr(w/2.0)+sqr(h/2.0))+sqrt(sqr(x0-w/2.0)+sqr(y0-h/2.0));
  fi   =  atan2(y-y0,x-x0);
  dmax =  rmin+(rmax-rmin)*(1-cos(fi-fio))/2.0;
  d    =  sqrt(sqr(x-x0) + sqr(y-y0)) / dmax;
  d0   =  (d == 0) ? 0 : rad / d;
  x1   = x0 + numX * d0 * dmax + w*dX/100.0;
  y1   = y0 + numY * (fi/PI)*h + h*dY/100.0;
  if (x1 <  0)   x1 = -x1 - 1;
  if (x1 >= w*2) x1 = (2.0*w)*(x1/(2.0*w)-(int)(x1/(2.0*w)));
  if (x1 >= w)   x1 = w-1-(x1-w);
  if (y1 <  0)   y1 = -y1-1;
  if (y1 >= h*2) y1 = (2*h)*(y1/(2.0*h)-(int)(y1/(2.0*h)));
  if (y1 >= h)   y1 = h-1-(y1-h);
                       ',
               prms => {x0 => {}, y0 => {}, numX => {}, numY => {},
                        rad => {}, dX => {}, dY => {} }},
'shift' => {   desc => '',
               crds => '
  x1 = x + ((x < x0) ? w-x0 : -x0);
  y1 = y + ((y < y0) ? h-y0 : -y0);
               ',
               prms => {x0 => {}, y0 => {} }},
