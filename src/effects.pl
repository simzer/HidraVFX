#!/usr/bin/perl
# Copyright (C) 2010 Laszlo Simon <laszlo.simon@gmail.com>
# This file is part of the HidraVFX project.
(
basic => {
 mapeffects => {
  'none' => {        desc => 'Do nothing (for debug purpose)',
                     calc => 'tar = src;'},
  
  'invert' => {      desc => 'Invert.',
                     calc => 'tar = 1.0 - src;'},
  
  'geoinvert' => {   desc => 'Multiplicative invert.',
                     calc => 'tar = 0.001/sqrt(src);'},
  
  'pitinvert' => {    desc => 'Invert with Pythagorean theorem.',
                     calc => 'tar = sqrt(1.0 - src*src);'},
  
  'upshift' => {     desc => 'Increase with <shift>.', 
                     calc => 'tar = src + shift; tar = tar - (int)tar;',
                     prms => {'shift'  => { def => 0.25 }}}, 
  
  'bright' => {      desc => 'Additional bright with <bright>.', 
                     calc => 'tar = src + bright;',
                     prms => {'bright' => { def => 0.25 }}},
  
  'contrast' => {    desc => 'Multiplicative contrast.', 
                     calc => 'tar = (src - 0.5) * gain + 0.5;',
                     prms => {'gain'   => { def => 0.25 }}},
  
  'bright2' => {     desc => 'Multiplicative bright', 
                     calc => 'tar = (bright < 0) ? src*(1.0+bright) : src+(1.0-src)*bright;',
                     prms => {'bright' => { def => 0.25 }}},
  
  'stone' => {       desc => 'Special map for stone texture', 
                     calc => 'tar = 1.0 - pow(1.0-src, power);',
                     prms => {'power'  => { def => 2 }}},

  'cloud' => {       desc => 'Special map for cloud texture', 
                     calc => 'tar = src<=limit ? 0 : log(xmax*(src-limit)/(1.0-limit)+1)/log(xmax+1);',
                     prms => {'limit'  => { def => 0.25 }, 
                              'xmax'   => { def => 2 }}},
 },
 blendings => {
  'allanon' => {     desc => 'Mean of pixel pair.', 
                     calc => 'tar = (src+add)/2;',
                     prms => {'add' => { desc => "Blend image.",  
                                         test => "add.pfm" }}},
  'multiply' => {    desc => 'Pixel pair multiplied', 
                     calc => 'tar = src*add;',
                     prms => {'add' => { desc => "Blend image.",  
                                         test => "add.pfm"}}},
  'bleach' => {      desc => 'Inverted pixel pair multiplied', 
                     calc => 'tar = (1-src)*(1-add);',
                     prms => {'add' => { desc => "Blend image.",  
                                         test => "add.pfm"}}},
  'screen' => {      desc => 'Invert of multiplied inverted pixels', 
                     calc => 'tar = 1-(1-src)*(1-add);',
                     prms => {'add' => { desc => "Blend image.",  
                                         test => "add.pfm"}}},
  'divide' => {      desc => 'Pixels divided', 
                     calc => 'tar = src / add;',
                     prms => {'add' => { desc => "Blend image.",  
                                         test => "add.pfm"}}},
  'add' => {         desc => 'Sum of pixel pair', 
                     calc => 'tar = src + add;',
                     prms => {'add' => { desc => "Blend image.",  
                                         test => "add.pfm"}}},
  'sub' => {         desc => 'Pixels substracted', 
                     calc => 'tar = src - add;',
                     prms => {'add' => { desc => "Blend image.",  
                                         test => "add.pfm"}}},
  'diff' => {        desc => 'Absolute difference of pixels', 
                     calc => 'tar = fabs(src-add);',
                     prms => {'add' => { desc => "Blend image.",  
                                         test => "add.pfm"}}},
  'difference' => {  desc => 'Signed difference of pixels', 
                     calc => 'tar = src - add + 1;',
                     prms => {'add' => { desc => "Blend image.",  
                                         test => "add.pfm"}}},
  'paralel' => {     desc => 'Calculated as parallel connected resistances', 
                     calc => 'tar = 2/(1/src+1/add);',
                     prms => {'add' => { desc => "Blend image.",  
                                         test => "add.pfm"}}},
  'darken' => {      desc => 'Darker pixel selected', 
                     calc => 'tar = add < src ? add : src;',
                     prms => {'add' => { desc => "Blend image.",  
                                         test => "add.pfm"}}},
  'lighten' => {     desc => 'Lighter pixel selected', 
                     calc => 'tar = add > src ? add : src;',
                     prms => {'add' => { desc => "Blend image.",  
                                         test => "add.pfm"}}},
  'texture' => {     desc => 'Symmetric addition', 
                     calc => 'tar = src + add - 0.5;',
                     prms => {'add' => { desc => "Blend image.",  
                                         test => "add.pfm"}}},
  'light' => {       desc => 'Multiplicative lightening', 
                     calc => 'tar = src*(1-add)+add*add;',
                     prms => {'add' => { desc => "Blend image.",  
                                         test => "add.pfm"}}},
  'dark' => {        desc => 'Multiplicative darkening', 
                     calc => 'tar = src*add+(1-add)*add;',
                     prms => {'add' => { desc => "Blend image.",  
                                         test => "add.pfm"}}},
  'ekvivalence' => { desc => 'Inverted absolute difference', 
                     calc => 'tar = 1 - fabs(src-add);',
                     prms => {'add' => { desc => "Blend image.",  
                                         test => "add.pfm"}}},
  'addSub' => {      desc => 'Absolute square difference', 
                     calc => 'tar = fabs(src*src-add*add);',
                     prms => {'add' => { desc => "Blend image.",  
                                         test => "add.pfm"}}},
  'pitagoras' => {   desc => 'Squared geometric mean', 
                     calc => 'tar = sqrt(src*src+add*add)/sqrt(2);',
                     prms => {'add' => { desc => "Blend image.",  
                                         test => "add.pfm"}}},
  'arctan' => {      desc => 'Modified arcus tangent of pixels', 
                     calc => 'tar = atan(2*atan2(add,1-src)/PI);',
                     prms => {'add' => { desc => "Blend image.",  
                                         test => "add.pfm"}}},
  'exclusion' => {   desc => '', 
                     calc => 'tar = src + add - 2 * src * add;',
                     prms => {'add' => { desc => "Blend image.",  
                                         test => "add.pfm"}}},
  'geomMean' => {    desc => 'geometric mean', 
                     calc => 'tar = sqrt(src * add);',
                     prms => {'add' => { desc => "Blend image.",  
                                         test => "add.pfm"}}},
  'gammaDark' => {   desc => 'gamma correction', 
                     calc => 'tar = pow(src,add);',
                     prms => {'add' => { desc => "Blend image.",  
                                         test => "add.pfm"}}},
  'gammaLight' => {  desc => 'invert gamma correction', 
                     calc => 'tar = pow(src,1/add);',
                     prms => {'add' => { desc => "Blend image.",  
                                         test => "add.pfm"}}},
  'burn' => {        desc => 'substract inverse', 
                     calc => 'tar = src + add - 1;',
                     prms => {'add' => { desc => "Blend image.",  
                                         test => "add.pfm"}}},
  'linearLight' => { desc => 'symmetric addition', 
                     calc => 'tar = src + 2 * add - 1;',
                     prms => {'add' => { desc => "Blend image.", 
                     	                 test => "add.pfm"}}},
  'colorDodge' => {  desc => 'Divide by invert', 
                     calc => 'tar = src / (1-add);',
                     prms => {'add' => { desc => "Blend image.", 
                                         test => "add.pfm"}}},
  'colorBurn' => {   desc => 'Divide invert', 
                     calc => 'tar = 1-(1-src)/add;',
                     prms => {'add' => { desc => "Blend image.", 
                                         test => "add.pfm"}}},
  'pinLight' => {    desc => '', 
                     calc => 'tar = max(2*add-1,min(src,2*add));',
                     prms => {'add' => { desc => "Blend image.", 
                                         test => "add.pfm"}}},
  'hardLight' => {   desc => 'Multiplication/inverse multiplication', 
                     calc => 'tar = add < 0.5 ? 2*src*add : 1-2*(1-src)*(1-add);',
                     prms => {'add' => { desc => "Blend image.", 
                                         test => "add.pfm"}}},
  'softLight' => {   desc => 'Lighten by power', 
                     calc => 'tar = pow(src,pow(2,(2*(0.5-add))));',
                     prms => {'add' => { desc => "Blend image.", 
                                         test => "add.pfm"}}},
  'vividLight' => {  desc => '', 
                     calc => 'tar = add < 0.5 ? 1-(1-src)/(2*add) : src/(2*(1-add));',
                     prms => {'add' => { desc => "Blend image.", 
                                         test => "add.pfm"}}},
  'overlay' => {     desc => 'Multiplication/inverse multiplication', 
                     calc => 'tar = add > 0.5 ? 2*src*add : 1-2*(1-src)*(1-add);',
                     prms => {'add' => { desc => "Blend image.", 
                                         test => "add.pfm"}}},
 }
},
distortions => {
 conform => {
  # CONFORM DISTORSIONS
  'bolyaiSphere' => {desc => 'Bolyai hyperbolic geometry conversion',
                     calc => '
          double d, fi, d0;                    
          d = sqrt(sqr(x/w - x0) + sqr(y/h - y0)); 
          fi = atan2(y/h - y0, x/w - x0);          
          d0 = d * R / sqrt(sqr(d) + sqr(z0)); 
          x1 = w * (x0 + d0 * cos(fi));              
          y1 = h * (y0 + d0 * sin(fi));',
                     prms => {'x0' => { def => 0.5 },
                              'y0' => { def => 0.5 }, 
                              'z0' => { def => 0.2  }, 
                              'R'  => { def => 0.3 } }},
  'invbolyaiSphere' => {desc => 'Bolyai hyperbolic geometry inverse conversion',
                     calc => '
          double d, fi, z, d0, dx, dy;
          dx = x/w-x0;
          dy = y/h-y0;
          d = sqrt(sqr(dx)+sqr(dy)); 
          fi = atan2(dy,dx); 
          z = sqrt(sqr(R)-sqr(dx)-sqr(dy))+z0; 
          d0 = (z0 < 0)  ? -z0 * d / (z - z0) : 
                           z0 * d / (z + z0); 
          x1 = w * (x0 + d0 * cos(fi)); 
          y1 = h * (y0 + d0 * sin(fi));',
                     prms => {'x0' => { def => 0.5 }, 
                              'y0' => { def => 0.5 }, 
                              'z0' => { def => 0.2 }, 
                              'R'  => { def => 0.3 } }},
  'spherize' => {    desc => 'Transformation to  sphere surface',
                     calc => '
          double dx, dy, d;
          dx = x/w - x0;
          dy = y/h - y0;
          d = sqrt(sqr(dx)+sqr(dy));
          if (d>radius) {
            x1  = x;
            y1  = y;
          } else {
            double fi, R, z0, tmp, z, d0;
            fi  = atan2(dy,dx);
            R   = radius/sin(angle);
            z0  = R*cos(angle);
            tmp = sqr(R)-sqr(dx)-sqr(dy);
            z   = sqrt(tmp)+z0;
            d0  = (angle > 0) ? z0*d/(z-z0) : z0*d/(z+z0);
            x1  = w * (x0+d0*cos(fi));
            y1  = h * (y0+d0*sin(fi));
          }',
                     prms => {'x0'     => { def => 0.5 },
                              'y0'     => { def => 0.5 },
                              'radius' => { def => 0.5 }, 
                              'angle'  => { def => 1.0 } }},
  'polarToDescartes' => {desc => 'Convert from polar to descartes coordinate system',
                     calc => '
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
          y1 = h - r*rCons - 1;' },
  'descartesToPolar' => {desc => 'Convert from descartes to polar coordinate system',
                     calc => '
          double rCons, fiCons, ux, uy;
          rCons  = (sqrt(w*w+h*h)/2.0)/(h-1);
          fiCons = (2*PI)/(w-1);
          ux = (w/2.0)-1;
          uy = (h/2.0)-1;
          x1 = y*rCons*cos(x*fiCons)+ux;
          y1 = y*rCons*sin(x*fiCons)+uy;' },
  'rotate' => {      desc => 'Rotate with the given angle around the specified point',
                     calc => '
          double o, ux, uy, rx, ry, zx, zy;
          rx = cos(angle);
          ry = sin(angle);
          zx = x-w*x0;
          zy = y-h*y0;
          if (ry == 0) {
             ux =zx/rx;
             uy =zy/rx;
          } else {
             o  =rx*rx+ry*ry;
             ux =(zx*rx+zy*ry)/o;
             uy =(zy*rx-zx*ry)/o;
          }
          x1 = ux+w*x0;
          y1 = uy+h*y0;',
                     prms => {'angle' => { def => 1.0 }, 
                              'x0'    => { def => 0.5 }, 
                              'y0'    => { def => 0.5 } }},
  'swirl' => {       desc => 'Swirl distorsion',
                     calc => '
          double r,fi,zx,zy,ux,uy,tx,ty,z2x,z2y;
          tx = cos(angle);
          ty = sin(angle);
          zx  = x-x0*w;
          zy  = y-y0*h;
          r   = sqrt(sqr(zx)+sqr(zy))/radial;
          fi  = r * angle;
          ux  = cos(fi);
          uy  = sin(fi);
          z2x = zx * ux - zy * uy;
          z2y = zx * uy + zy * ux;
          x1  = (z2x*tx+z2y*ty)+x0*w;
          y1  = (z2y*tx-z2x*ty)+y0*h;',
                     prms => {'angle'  => { def => 0.5 }, 
                              'radial' => { def => 10 }, 
                              'x0'     => { def => 0.5  }, 
                              'y0'     => { def => 0.5 } }},
  'pinch' => {       desc => 'Pinch distorsion',
                     calc => '
          double zx, zy, ux, uy, z2, r;
          ux = (2.0 * x / w) - 1;
          uy = (2.0 * y / h) - 1;
          r  = sqrt(sqr(ux) + sqr(uy));
          z2 = pow(r, scale);
          zx = z2 * ux / r;
          zy = z2 * uy / r;
          x1 = (zx+1)*(w/2.0);
          y1 = (zy+1)*(h/2.0);',
                     prms => {'scale' => { def => 2 }  }},
  'sinusoidal' => {  desc => 'Distort distance from center with sine',
                     calc => '
          double ux,uy,zx,zy,arcsin;
          arcsin = 1.0/asin(scale);
          ux   = (x-(w/2.0))/(w/2.0);
          uy   = (y-(h/2.0))/(h/2.0);
          ux   = ux*scale;
          uy   = uy*scale;
          zx   = asin(ux)*arcsin;
          zy   = asin(uy)*arcsin;
          x1   = zx*(w/2.0)+(w/2.0);
          y1   = zy*(h/2.0)+(h/2.0);',
                     prms => {'scale' => { def => 1 } }},
  'centermirror' => {desc => 'Mirroring across specified center point',
                     calc => '
          x1 = w * (x0 - (x/w - x0));
          y1 = h * (y0 - (y/h - y0));',
                     prms => {'x0' => { def => 0.5 }, 
                              'y0' => { def => 0.5 } }},
  'axismirror' => {  desc => 'Mirroring across specified line',
                     calc => '
          double tx, ty, naxisx, naxisy, d;
          d = sqrt(sqr(axisx)+sqr(axisy));
          naxisx = axisx / d;
          naxisy = axisy / d;
          tx = (x*naxisx + y*naxisy);
          ty = (x*naxisy - y*naxisx);
          x1 = (tx*naxisx - ty*naxisy) + w*x0;
          y1 = (tx*naxisy + ty*naxisx) + h*y0;',
                     prms => {'x0'    => { def => 0.5 }, 
                              'y0'    => { def => 0.5 }, 
                              'axisx' => { def => 0.4 }, 
                              'axisy' => { def => 0.5 } }},
  'misterx' => {     desc => 'Position inversion to the center',
                     calc => '
          double zx,zy,o;
          zx = (x/w - (1.0 / 2.0)) / rad;
          zy = (y/h - (1.0 / 2.0)) / rad;
          o  = zx * zx + zy * zy;
          zx = zx / o;
          zy = -zy / o;
          x1  = w * (zx*rad + (1.0 / 2.0));
          y1  = h * (zy*rad + (1.0 / 2.0));
          if (x1 <  0)   x1 = -x1-1;
          if (x1 >= w*2) x1 = (2.0*w)*(x1/(2.0*w)-(int)(x1/(2.0*w)));
          if (x1 >= w)   x1 = w-1-(x1-w);
          if (y1 <  0)   y1 = -y1-1;
          if (y1 >= h*2) y1 = (2*h)*(y1/(2.0*h)-(int)(y1/(2.0*h)));
          if (y1 >= h)   y1 = h-1-(y1-h);',
                     prms => {'rad' => { def => 1} }},
  'tube' => {        desc => 'Transform to the surface of a tube',
                     calc => '
          double d, fi, d0, dmax, fio, rmin, rmax, xc, yc;
          xc   = x0 * w; yc = y0 * h;
          fio  = atan2(h/2.0-xc,w/2.0-yc);
          rmin = sqrt(sqr(w/2.0)+sqr(h/2.0))-sqrt(sqr(xc-w/2.0)+sqr(yc-h/2.0));
          rmax = sqrt(sqr(w/2.0)+sqr(h/2.0))+sqrt(sqr(xc-w/2.0)+sqr(yc-h/2.0));
          fi   =  atan2(y-yc,x-xc);
          dmax =  rmin+(rmax-rmin)*(1-cos(fi-fio))/2.0;
          d    =  sqrt(sqr(x-xc) + sqr(y-yc)) / dmax;
          d0   =  (d == 0) ? 0 : rad / d;
          x1   = xc + numX * d0 * dmax + w*dX/100.0;
          y1   = yc + numY * (fi/PI)*h + h*dY/100.0;
          if (x1 <  0)   x1 = -x1 - 1;
          if (x1 >= w*2) x1 = (2.0*w)*(x1/(2.0*w)-(int)(x1/(2.0*w)));
          if (x1 >= w)   x1 = w-1-(x1-w);
          if (y1 <  0)   y1 = -y1-1;
          if (y1 >= h*2) y1 = (2*h)*(y1/(2.0*h)-(int)(y1/(2.0*h)));
          if (y1 >= h)   y1 = h-1-(y1-h);',
                     prms => {'x0'   => { def => 0.4 }, 
                              'y0'   => { def => 0.5 }, 
                              'numX' => { def => 6   },
                              'numY' => { def => 2   },
                              'rad'  => { def => 0.1 }, 
                              'dX'   => { def => 0.3 }, 
                              'dY'   => { def => 0.2 } }},
  'shift' => {       desc => 'Shift with the specified relative vector.',
                     calc => '
          x1 = x + w * ((1 < x0) ? 1-x0 : -x0);
          y1 = y + h * ((1 < y0) ? 1-y0 : -y0);
                     ',
                     prms => {'x0' => { def => 0.25 }, 
                              'y0' => { def => 0.25 } }},
 }
}
); 