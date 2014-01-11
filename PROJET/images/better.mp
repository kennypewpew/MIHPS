u=1cm; % grid spacing
v=10; % grid size
d=3pt; % dot size

ox=4*u;
oy=1*u;

nz:=1;
nd:=1;

pair vz[];
pair vd[];

vz[nz]:=(4u,1u);
nz:=nz+1;

vd[nd]:=(3u,1u);
nd:=nd+1;
vd[nd]:=(5u,1u);
nd:=nd+1;
vd[nd]:=(4u,0u);
nd:=nd+1;
vd[nd]:=(4u,2u);
nd:=nd+1;


path obstacle;
obstacle = (3.5u,4.5u)--(3.5u,5.5u)--(6.5u,5.5u)--(6.5u,4.5u)--cycle;

path diamond;

i:=1.4;
diamond := (4u-(i-1)*u, 0)--(4u-i*u, 1u)--(4u,1u+i*u)--(4u+i*u, 1u)--(4u+(i-1)*u, 0)--cycle;

% number 1
fignum:=1;
beginfig(fignum);
  fill obstacle withcolor 0.7white;
  for i=0 upto v:
    for j=0 upto v:
      draw(i*u, j*u-d)..(i*u+d, j*u)..(i*u, j*u+d)..(i*u-d, j*u)..(i*u, j*u-d);
    endfor
  endfor

  pickup pencircle scaled 1.3pt;
  draw(ox,oy)--(ox+u,oy) withcolor (1,0,0);
  draw(ox,oy)--(ox-u,oy) withcolor (1,0,0);
  draw(ox,oy)--(ox,oy+u) withcolor (0,1,0);
  draw(ox,oy)--(ox,oy-u) withcolor (1,0,0);

  pickup pencircle scaled 2d;
  drawdot(4*u, 9*u) withcolor (0,0,1); % endpoint
  drawdot(4u, 1u) withcolor (1,0,0); % starting point

  % valid(open) points
  for i=1 upto nd-1:
    %drawdot(vd[i]) withcolor (0,1,0);
  endfor

  % visited(closed) points
  for i=1 upto nz-1:
    %drawdot(vz[i]) withcolor (1,0,0);
  endfor

endfig;

% number 2
fignum:=fignum+1;
ox:=ox;
oy:=oy+u;
beginfig(fignum);
  fill obstacle withcolor 0.7white;

  for i=0 upto v:
    for j=0 upto v:
      draw(i*u, j*u-d)..(i*u+d, j*u)..(i*u, j*u+d)..(i*u-d, j*u)..(i*u, j*u-d);
    endfor
  endfor

  pickup pencircle scaled 1.3pt;
  draw(ox,oy)--(ox+u,oy) withcolor (1,0,0);
  draw(ox,oy)--(ox-u,oy) withcolor (1,0,0);
  draw(ox,oy)--(ox,oy+u) withcolor (0,1,0);

  pickup pencircle scaled 2d;
  drawdot(4*u, 9*u) withcolor (0,0,1); % endpoint
  drawdot(3*u, 1*u) withcolor (0,1,0); % valid nodes

  % valid(open) points
  for i=1 upto nd-1:
    drawdot(vd[i]) withcolor (0,1,0);
  endfor

  % visited(closed) points
  for i=1 upto nz-1:
    drawdot(vz[i]) withcolor (1,0,0);
  endfor

endfig;

% number 3
fignum:=fignum+1;
ox:=ox;
oy:=oy+u;

vd[nd]:=(3u, 2u);
nd:=nd+1;
vd[nd]:=(5u, 2u);
nd:=nd+1;
vd[nd]:=(4u, 3u);
nd:=nd+1;

vz[nz]:=(4u,2u);
nz:=nz+1;

beginfig(fignum);
  fill obstacle withcolor 0.7white;

  for i=0 upto v:
    for j=0 upto v:
      draw(i*u, j*u-d)..(i*u+d, j*u)..(i*u, j*u+d)..(i*u-d, j*u)..(i*u, j*u-d);
    endfor
  endfor

  pickup pencircle scaled 1.3pt;
  draw(ox,oy)--(ox+u,oy) withcolor (1,0,0);
  draw(ox,oy)--(ox-u,oy) withcolor (1,0,0);
  draw(ox,oy)--(ox,oy+u) withcolor (0,1,0);

  pickup pencircle scaled 2d;
  drawdot(4*u, 9*u) withcolor (0,0,1); % endpoint
  drawdot(3*u, 1*u) withcolor (0,1,0); % valid nodes

  % valid(open) points
  for i=1 upto nd-1:
    drawdot(vd[i]) withcolor (0,1,0);
  endfor

  % visited(closed) points
  for i=1 upto nz-1:
    drawdot(vz[i]) withcolor (1,0,0);
  endfor

endfig;

% number 4
vd[nd]:=(3u,3u);
nd:=nd+1;
vd[nd]:=(5u,3u);
nd:=nd+1;
vd[nd]:=(4u,4u);
nd:=nd+1;

vz[nz]:=(4u,3u);
nz:=nz+1;

fignum:=fignum+1;
ox:=ox;
oy:=oy+u;
beginfig(fignum);
  fill obstacle withcolor 0.7white;

  for i=0 upto v:
    for j=0 upto v:
      draw(i*u, j*u-d)..(i*u+d, j*u)..(i*u, j*u+d)..(i*u-d, j*u)..(i*u, j*u-d);
    endfor
  endfor

  pickup pencircle scaled 1.3pt;
  draw(ox,oy)--(ox+u,oy) withcolor (1,0,0);
  draw(ox,oy)--(ox-u,oy) withcolor (1,0,0);
  %draw(ox,oy)--(ox,oy+u) withcolor (0,1,0);

  pickup pencircle scaled 2d;
  drawdot(4*u, 9*u) withcolor (0,0,1); % endpoint
  drawdot(3*u, 1*u) withcolor (0,1,0); % valid nodes

  % valid(open) points
  for i=1 upto nd-1:
    drawdot(vd[i]) withcolor (0,1,0);
  endfor

  % visited(closed) points
  for i=1 upto nz-1:
    drawdot(vz[i]) withcolor (1,0,0);
  endfor

endfig;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Restart from near origin  %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%ox:=ox;
%oy:=oy+u;
fignum:=fignum+1;

vz[nz]:=(4u,4u);
nz:=nz+1;

vd[nd]:=(5u,4u);
nd:=nd+1;
vd[nd]:=(3u,4u);
nd:=nd+1;

beginfig(fignum);
  fill obstacle withcolor 0.7white;
  fill diamond withcolor 0.8white;

  i:=1;
  %draw(4u, 1u+i*u)--(4u+i*u, 1u)--(4u,1u-i*u)--(4u-i*u, 1u)--(4u, 1u+i*u);
  %for i=2 upto 3:
    %draw(4u-(i-1)*u, 0)--(4u-i*u, 1u)--(4u,1u+i*u)--(4u+i*u, 1u)--(4u+(i-1)*u, 0);
  %endfor

  for i=0 upto v:
    for j=0 upto v:
      draw(i*u, j*u-d)..(i*u+d, j*u)..(i*u, j*u+d)..(i*u-d, j*u)..(i*u, j*u-d);
    endfor
  endfor

  i:=3;
  j:=1;
  d:=7pt;
  draw(i*u, j*u-d)..(i*u+d, j*u)..(i*u, j*u+d)..(i*u-d, j*u)..(i*u, j*u-d) withcolor (0,0,1);
  i:=5;
  draw(i*u, j*u-d)..(i*u+d, j*u)..(i*u, j*u+d)..(i*u-d, j*u)..(i*u, j*u-d) withcolor (0,0,1);

  d:=3pt;

  %pickup pencircle scaled 1.3pt;
  %draw(ox,oy)--(ox+u,oy) withcolor (1,0,0);
  %draw(ox,oy)--(ox-u,oy) withcolor (1,0,0);
  %draw(ox,oy)--(ox,oy+u) withcolor (0,1,0);

  pickup pencircle scaled 2d;
  drawdot(4*u, 9*u) withcolor (0,0,1); % endpoint

  % valid(open) points
  for i=1 upto nd-1:
    drawdot(vd[i]) withcolor (0,1,0);
  endfor

  % visited(closed) points
  for i=1 upto nz-1:
    drawdot(vz[i]) withcolor (1,0,0);
  endfor
endfig;


% number 6
%vd[nd]:=(3u,3u);
%nd:=nd+1;
%vd[nd]:=(5u,3u);
%nd:=nd+1;
%vd[nd]:=(4u,4u);
%nd:=nd+1;

%vz[nz]:=(4u,3u);
%nz:=nz+1;

fignum:=fignum+1;
ox1:=3u;
oy1:=1u;
ox2:=5u;
oy2:=1u;
beginfig(fignum);
  fill obstacle withcolor 0.7white;

  for i=0 upto v:
    for j=0 upto v:
      draw(i*u, j*u-d)..(i*u+d, j*u)..(i*u, j*u+d)..(i*u-d, j*u)..(i*u, j*u-d);
    endfor
  endfor

  pickup pencircle scaled 1.3pt;
  ox:=ox1;
  oy:=oy1;
  %draw(ox,oy)--(ox+u,oy) withcolor (1,0,0);
  draw(ox,oy)--(ox-u,oy) withcolor (1,0,0);
  draw(ox,oy)--(ox,oy+u) withcolor (0,1,0);
  draw(ox,oy)--(ox,oy-u) withcolor (1,0,0);

  pickup pencircle scaled 2d;
  drawdot(4*u, 9*u) withcolor (0,0,1); % endpoint
  drawdot(3*u, 1*u) withcolor (0,1,0); % valid nodes

  % valid(open) points
  for i=1 upto nd-1:
    drawdot(vd[i]) withcolor (0,1,0);
  endfor

  % visited(closed) points
  for i=1 upto nz-1:
    drawdot(vz[i]) withcolor (1,0,0);
  endfor
endfig;

% number 7
vd[nd]:=(3u,0u);
nd:=nd+1;
%vd[nd]:=(3u,2u);
%nd:=nd+1;
vd[nd]:=(2u,1u);
nd:=nd+1;

vz[nz]:=(3u,1u);
nz:=nz+1;

fignum:=fignum+1;
%ox1:=3u;
%oy1:=1u;
%ox2:=5u;
%oy2:=1u;
beginfig(fignum);
  fill obstacle withcolor 0.7white;

  for i=0 upto v:
    for j=0 upto v:
      draw(i*u, j*u-d)..(i*u+d, j*u)..(i*u, j*u+d)..(i*u-d, j*u)..(i*u, j*u-d);
    endfor
  endfor

  pickup pencircle scaled 1.3pt;
  %ox:=ox1;
  %oy:=oy1;
  ox:=ox2;
  oy:=oy2;
  draw(ox,oy)--(ox+u,oy) withcolor (1,0,0);
  %draw(ox,oy)--(ox-u,oy) withcolor (1,0,0);
  draw(ox,oy)--(ox,oy+u) withcolor (0,1,0);
  draw(ox,oy)--(ox,oy-u) withcolor (1,0,0);

  pickup pencircle scaled 2d;
  drawdot(4*u, 9*u) withcolor (0,0,1); % endpoint
  drawdot(3*u, 1*u) withcolor (0,1,0); % valid nodes

  % valid(open) points
  for i=1 upto nd-1:
    drawdot(vd[i]) withcolor (0,1,0);
  endfor

  % visited(closed) points
  for i=1 upto nz-1:
    drawdot(vz[i]) withcolor (1,0,0);
  endfor
endfig;

% number 8
vd[nd]:=(5u,0u);
nd:=nd+1;
%vd[nd]:=(3u,2u);
%nd:=nd+1;
vd[nd]:=(6u,1u);
nd:=nd+1;

vz[nz]:=(5u,1u);
nz:=nz+1;

fignum:=fignum+1;
%ox1:=ox1+u;
oy1:=oy1+u;
%ox2:=ox2+u;
%oy2:=oy2+u;
beginfig(fignum);
  fill obstacle withcolor 0.7white;

  for i=0 upto v:
    for j=0 upto v:
      draw(i*u, j*u-d)..(i*u+d, j*u)..(i*u, j*u+d)..(i*u-d, j*u)..(i*u, j*u-d);
    endfor
  endfor

  pickup pencircle scaled 1.3pt;
  ox:=ox1;
  oy:=oy1;
  %ox:=ox2;
  %oy:=oy2;
  %draw(ox,oy)--(ox+u,oy) withcolor (1,0,0);
  draw(ox,oy)--(ox-u,oy) withcolor (1,0,0);
  draw(ox,oy)--(ox,oy+u) withcolor (0,1,0);
  %draw(ox,oy)--(ox,oy-u) withcolor (1,0,0);

  pickup pencircle scaled 2d;
  drawdot(4*u, 9*u) withcolor (0,0,1); % endpoint
  drawdot(3*u, 1*u) withcolor (0,1,0); % valid nodes

  % valid(open) points
  for i=1 upto nd-1:
    drawdot(vd[i]) withcolor (0,1,0);
  endfor

  % visited(closed) points
  for i=1 upto nz-1:
    drawdot(vz[i]) withcolor (1,0,0);
  endfor
endfig;

% number 9
vd[nd]:=(2u,2u);
nd:=nd+1;
%vd[nd]:=(3u,2u);
%nd:=nd+1;
%vd[nd]:=(6u,1u);
%nd:=nd+1;

vz[nz]:=(3u,2u);
nz:=nz+1;

fignum:=fignum+1;
%ox1:=ox1+u;
%oy1:=oy1+u;
%ox2:=ox2+u;
oy2:=oy2+u;
beginfig(fignum);
  fill obstacle withcolor 0.7white;

  for i=0 upto v:
    for j=0 upto v:
      draw(i*u, j*u-d)..(i*u+d, j*u)..(i*u, j*u+d)..(i*u-d, j*u)..(i*u, j*u-d);
    endfor
  endfor

  pickup pencircle scaled 1.3pt;
  %ox:=ox1;
  %oy:=oy1;
  ox:=ox2;
  oy:=oy2;
  draw(ox,oy)--(ox+u,oy) withcolor (1,0,0);
  %draw(ox,oy)--(ox-u,oy) withcolor (1,0,0);
  draw(ox,oy)--(ox,oy+u) withcolor (0,1,0);
  %draw(ox,oy)--(ox,oy-u) withcolor (1,0,0);

  pickup pencircle scaled 2d;
  drawdot(4*u, 9*u) withcolor (0,0,1); % endpoint
  drawdot(3*u, 1*u) withcolor (0,1,0); % valid nodes

  % valid(open) points
  for i=1 upto nd-1:
    drawdot(vd[i]) withcolor (0,1,0);
  endfor

  % visited(closed) points
  for i=1 upto nz-1:
    drawdot(vz[i]) withcolor (1,0,0);
  endfor
endfig;

% number 10
vd[nd]:=(6u,2u);
nd:=nd+1;
%vd[nd]:=(3u,2u);
%nd:=nd+1;
%vd[nd]:=(6u,1u);
%nd:=nd+1;

vz[nz]:=(5u,2u);
nz:=nz+1;

fignum:=fignum+1;
%ox1:=ox1+u;
oy1:=oy1+u;
%ox2:=ox2+u;
%oy2:=oy2+u;
beginfig(fignum);
  fill obstacle withcolor 0.7white;

  for i=0 upto v:
    for j=0 upto v:
      draw(i*u, j*u-d)..(i*u+d, j*u)..(i*u, j*u+d)..(i*u-d, j*u)..(i*u, j*u-d);
    endfor
  endfor

  pickup pencircle scaled 1.3pt;
  ox:=ox1;
  oy:=oy1;
  %ox:=ox2;
  %oy:=oy2;
  %draw(ox,oy)--(ox+u,oy) withcolor (1,0,0);
  draw(ox,oy)--(ox-u,oy) withcolor (1,0,0);
  draw(ox,oy)--(ox,oy+u) withcolor (0,1,0);
  %draw(ox,oy)--(ox,oy-u) withcolor (1,0,0);

  pickup pencircle scaled 2d;
  drawdot(4*u, 9*u) withcolor (0,0,1); % endpoint
  drawdot(3*u, 1*u) withcolor (0,1,0); % valid nodes

  % valid(open) points
  for i=1 upto nd-1:
    drawdot(vd[i]) withcolor (0,1,0);
  endfor

  % visited(closed) points
  for i=1 upto nz-1:
    drawdot(vz[i]) withcolor (1,0,0);
  endfor
endfig;

% number 11
vd[nd]:=(2u,3u);
nd:=nd+1;
%vd[nd]:=(3u,2u);
%nd:=nd+1;
%vd[nd]:=(6u,1u);
%nd:=nd+1;

vz[nz]:=(3u,3u);
nz:=nz+1;

fignum:=fignum+1;
%ox1:=ox1+u;
%oy1:=oy1+u;
%ox2:=ox2+u;
oy2:=oy2+u;
beginfig(fignum);
  fill obstacle withcolor 0.7white;

  for i=0 upto v:
    for j=0 upto v:
      draw(i*u, j*u-d)..(i*u+d, j*u)..(i*u, j*u+d)..(i*u-d, j*u)..(i*u, j*u-d);
    endfor
  endfor

  pickup pencircle scaled 1.3pt;
  %ox:=ox1;
  %oy:=oy1;
  ox:=ox2;
  oy:=oy2;
  draw(ox,oy)--(ox+u,oy) withcolor (1,0,0);
  %draw(ox,oy)--(ox-u,oy) withcolor (1,0,0);
  draw(ox,oy)--(ox,oy+u) withcolor (0,1,0);
  %draw(ox,oy)--(ox,oy-u) withcolor (1,0,0);

  pickup pencircle scaled 2d;
  drawdot(4*u, 9*u) withcolor (0,0,1); % endpoint
  drawdot(3*u, 1*u) withcolor (0,1,0); % valid nodes

  % valid(open) points
  for i=1 upto nd-1:
    drawdot(vd[i]) withcolor (0,1,0);
  endfor

  % visited(closed) points
  for i=1 upto nz-1:
    drawdot(vz[i]) withcolor (1,0,0);
  endfor
endfig;

% number 12
vd[nd]:=(6u,3u);
nd:=nd+1;
%vd[nd]:=(3u,2u);
%nd:=nd+1;
%vd[nd]:=(6u,1u);
%nd:=nd+1;

vz[nz]:=(5u,3u);
nz:=nz+1;

fignum:=fignum+1;
%ox1:=ox1+u;
oy1:=oy1+u;
%ox2:=ox2+u;
%oy2:=oy2+u;
beginfig(fignum);
  fill obstacle withcolor 0.7white;

  for i=0 upto v:
    for j=0 upto v:
      draw(i*u, j*u-d)..(i*u+d, j*u)..(i*u, j*u+d)..(i*u-d, j*u)..(i*u, j*u-d);
    endfor
  endfor

  pickup pencircle scaled 1.3pt;
  ox:=ox1;
  oy:=oy1;
  %ox:=ox2;
  %oy:=oy2;
  %draw(ox,oy)--(ox+u,oy) withcolor (1,0,0);
  draw(ox,oy)--(ox-u,oy) withcolor (1,0,0);
  draw(ox,oy)--(ox,oy+u) withcolor (0,1,0);
  %draw(ox,oy)--(ox,oy-u) withcolor (1,0,0);

  pickup pencircle scaled 2d;
  drawdot(4*u, 9*u) withcolor (0,0,1); % endpoint
  drawdot(3*u, 1*u) withcolor (0,1,0); % valid nodes

  % valid(open) points
  for i=1 upto nd-1:
    drawdot(vd[i]) withcolor (0,1,0);
  endfor

  % visited(closed) points
  for i=1 upto nz-1:
    drawdot(vz[i]) withcolor (1,0,0);
  endfor
endfig;

% number 13
vd[nd]:=(2u,4u);
nd:=nd+1;
vd[nd]:=(3u,5u);
nd:=nd+1;
%vd[nd]:=(6u,1u);
%nd:=nd+1;

vz[nz]:=(3u,4u);
nz:=nz+1;

fignum:=fignum+1;
%ox1:=ox1+u;
%oy1:=oy1+u;
%ox2:=ox2+u;
oy2:=oy2+u;
beginfig(fignum);
  fill obstacle withcolor 0.7white;

  for i=0 upto v:
    for j=0 upto v:
      draw(i*u, j*u-d)..(i*u+d, j*u)..(i*u, j*u+d)..(i*u-d, j*u)..(i*u, j*u-d);
    endfor
  endfor

  pickup pencircle scaled 1.3pt;
  ox:=ox1;
  oy:=oy1;
  ox:=ox2;
  oy:=oy2;
  draw(ox,oy)--(ox+u,oy) withcolor (1,0,0);
  %draw(ox,oy)--(ox-u,oy) withcolor (1,0,0);
  %draw(ox,oy)--(ox,oy+u) withcolor (0,1,0);
  %draw(ox,oy)--(ox,oy-u) withcolor (1,0,0);

  pickup pencircle scaled 2d;
  drawdot(4*u, 9*u) withcolor (0,0,1); % endpoint
  drawdot(3*u, 1*u) withcolor (0,1,0); % valid nodes

  % valid(open) points
  for i=1 upto nd-1:
    drawdot(vd[i]) withcolor (0,1,0);
  endfor

  % visited(closed) points
  for i=1 upto nz-1:
    drawdot(vz[i]) withcolor (1,0,0);
  endfor
endfig;

% number 14
vd[nd]:=(6u,4u);
nd:=nd+1;
%vd[nd]:=(3u,5u);
%nd:=nd+1;
%vd[nd]:=(6u,1u);
%nd:=nd+1;

vz[nz]:=(5u,4u);
nz:=nz+1;

fignum:=fignum+1;
%ox1:=ox1+u;
oy1:=oy1+u;
%ox2:=ox2+u;
%oy2:=oy2+u;
beginfig(fignum);
  fill obstacle withcolor 0.7white;

  for i=0 upto v:
    for j=0 upto v:
      draw(i*u, j*u-d)..(i*u+d, j*u)..(i*u, j*u+d)..(i*u-d, j*u)..(i*u, j*u-d);
    endfor
  endfor

  pickup pencircle scaled 1.3pt;
  ox:=ox1;
  oy:=oy1;
  %ox:=ox2;
  %oy:=oy2;
  %draw(ox,oy)--(ox+u,oy) withcolor (1,0,0);
  draw(ox,oy)--(ox-u,oy) withcolor (1,0,0);
  draw(ox,oy)--(ox,oy+u) withcolor (0,1,0);
  %draw(ox,oy)--(ox,oy-u) withcolor (1,0,0);

  pickup pencircle scaled 2d;
  drawdot(4*u, 9*u) withcolor (0,0,1); % endpoint
  drawdot(3*u, 1*u) withcolor (0,1,0); % valid nodes

  % valid(open) points
  for i=1 upto nd-1:
    drawdot(vd[i]) withcolor (0,1,0);
  endfor

  % visited(closed) points
  for i=1 upto nz-1:
    drawdot(vz[i]) withcolor (1,0,0);
  endfor
endfig;


i:=2.4;
diamond := (4u-(i-1)*u, 0)--(4u-i*u, 1u)--(4u,1u+i*u)--(4u+i*u, 1u)--(4u+(i-1)*u, 0)--cycle;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Restart from near origin  %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% number 15

%ox:=ox;
%oy:=oy+u;
fignum:=fignum+1;

vz[nz]:=(3u,5u);
nz:=nz+1;

vd[nd]:=(2u,5u);
nd:=nd+1;
vd[nd]:=(3u,6u);
nd:=nd+1;

beginfig(fignum);
  fill obstacle withcolor 0.7white;
  fill diamond withcolor 0.8white;

  i:=1;
  %draw(4u, 1u+i*u)--(4u+i*u, 1u)--(4u,1u-i*u)--(4u-i*u, 1u)--(4u, 1u+i*u);
  %for i=2 upto 3:
    %draw(4u-(i-1)*u, 0)--(4u-i*u, 1u)--(4u,1u+i*u)--(4u+i*u, 1u)--(4u+(i-1)*u, 0);
  %endfor

  for i=0 upto v:
    for j=0 upto v:
      draw(i*u, j*u-d)..(i*u+d, j*u)..(i*u, j*u+d)..(i*u-d, j*u)..(i*u, j*u-d);
    endfor
  endfor

  i:=2;
  j:=1;
  d:=7pt;
  draw(i*u, j*u-d)..(i*u+d, j*u)..(i*u, j*u+d)..(i*u-d, j*u)..(i*u, j*u-d) withcolor (0,0,1);
  i:=6;
  draw(i*u, j*u-d)..(i*u+d, j*u)..(i*u, j*u+d)..(i*u-d, j*u)..(i*u, j*u-d) withcolor (0,0,1);

  d:=3pt;

  %pickup pencircle scaled 1.3pt;
  %draw(ox,oy)--(ox+u,oy) withcolor (1,0,0);
  %draw(ox,oy)--(ox-u,oy) withcolor (1,0,0);
  %draw(ox,oy)--(ox,oy+u) withcolor (0,1,0);

  pickup pencircle scaled 2d;
  drawdot(4*u, 9*u) withcolor (0,0,1); % endpoint

  % valid(open) points
  for i=1 upto nd-1:
    drawdot(vd[i]) withcolor (0,1,0);
  endfor

  % visited(closed) points
  for i=1 upto nz-1:
    drawdot(vz[i]) withcolor (1,0,0);
  endfor
endfig;


%%%%%%%%%%%%%%%%%%%%%%%%%%%
% number 16
%vd[nd]:=(2u,4u);
%nd:=nd+1;
%vd[nd]:=(3u,5u);
%nd:=nd+1;
%vd[nd]:=(6u,1u);
%nd:=nd+1;

%vz[nz]:=(3u,4u);
%nz:=nz+1;

fignum:=fignum+1;
%ox1:=ox1+u;
oy1:=oy1+u;
%ox2:=ox2+u;
%oy2:=oy2+u;
beginfig(fignum);
  fill obstacle withcolor 0.7white;

  for i=0 upto v:
    for j=0 upto v:
      draw(i*u, j*u-d)..(i*u+d, j*u)..(i*u, j*u+d)..(i*u-d, j*u)..(i*u, j*u-d);
    endfor
  endfor

  pickup pencircle scaled 1.3pt;
  ox:=ox1;
  oy:=oy1;
  %ox:=ox2;
  %oy:=oy2;
  draw(ox,oy)--(ox+u,oy) withcolor (0,1,0);
  draw(ox,oy)--(ox-u,oy) withcolor (1,0,0);
  draw(ox,oy)--(ox,oy+u) withcolor (0,1,0);
  %draw(ox,oy)--(ox,oy-u) withcolor (1,0,0);

  pickup pencircle scaled 2d;
  drawdot(4*u, 9*u) withcolor (0,0,1); % endpoint
  drawdot(3*u, 1*u) withcolor (0,1,0); % valid nodes

  % valid(open) points
  for i=1 upto nd-1:
    drawdot(vd[i]) withcolor (0,1,0);
  endfor

  % visited(closed) points
  for i=1 upto nz-1:
    drawdot(vz[i]) withcolor (1,0,0);
  endfor
endfig;

% number 17
vd[nd]:=(3u,7u);
nd:=nd+1;
vd[nd]:=(2u,6u);
nd:=nd+1;
vd[nd]:=(4u,6u);
nd:=nd+1;
vd[nd]:=(7u,1u);
nd:=nd+1;
vd[nd]:=(1u,1u);
nd:=nd+1;

vz[nz]:=(2u,1u);
nz:=nz+1;
vz[nz]:=(6u,1u);
nz:=nz+1;
vz[nz]:=(3u,6u);
nz:=nz+1;

fignum:=fignum+1;
%ox1:=ox1+u;
%oy1:=oy1+u;
%ox2:=ox2+u;
%oy2:=oy2+u;
beginfig(fignum);
  fill obstacle withcolor 0.7white;

  for i=0 upto v:
    for j=0 upto v:
      draw(i*u, j*u-d)..(i*u+d, j*u)..(i*u, j*u+d)..(i*u-d, j*u)..(i*u, j*u-d);
    endfor
  endfor

  pickup pencircle scaled 1.3pt;
  ox:=ox1;
  oy:=oy1;
  %ox:=ox2;
  %oy:=oy2;
  %draw(ox,oy)--(ox+u,oy) withcolor (0,1,0);
  %draw(ox,oy)--(ox-u,oy) withcolor (1,0,0);
  %draw(ox,oy)--(ox,oy+u) withcolor (0,1,0);
  %draw(ox,oy)--(ox,oy-u) withcolor (1,0,0);

  pickup pencircle scaled 2d;
  drawdot(4*u, 9*u) withcolor (0,0,1); % endpoint
  drawdot(3*u, 1*u) withcolor (0,1,0); % valid nodes

  % valid(open) points
  for i=1 upto nd-1:
    drawdot(vd[i]) withcolor (0,1,0);
  endfor

  % visited(closed) points
  for i=1 upto nz-1:
    drawdot(vz[i]) withcolor (1,0,0);
  endfor
endfig;

% number 18
vd[nd]:=(3u,8u);
nd:=nd+1;
vd[nd]:=(2u,7u);
nd:=nd+1;
vd[nd]:=(4u,7u);
nd:=nd+1;
vd[nd]:=(5u,6u);
nd:=nd+1;
vd[nd]:=(7u,2u);
nd:=nd+1;
vd[nd]:=(1u,2u);
nd:=nd+1;

vz[nz]:=(2u,2u);
nz:=nz+1;
vz[nz]:=(6u,2u);
nz:=nz+1;
vz[nz]:=(3u,7u);
nz:=nz+1;
vz[nz]:=(4u,6u);
nz:=nz+1;

fignum:=fignum+1;
ox1:=3u;
oy1:=7u;
ox2:=4u;
oy2:=6u;
beginfig(fignum);
  fill obstacle withcolor 0.7white;

  for i=0 upto v:
    for j=0 upto v:
      draw(i*u, j*u-d)..(i*u+d, j*u)..(i*u, j*u+d)..(i*u-d, j*u)..(i*u, j*u-d);
    endfor
  endfor

  pickup pencircle scaled 1.3pt;
  draw(ox1,oy1)--(ox1+u,oy1) withcolor (0,1,0);
  draw(ox2,oy2)--(ox2,oy2+u) withcolor (0,1,0);

  draw(3.7u,6.3u)--(4.3u,6.7u);
  draw(4.3u,6.3u)--(3.7u,6.7u);

  pickup pencircle scaled 2d;
  drawdot(4*u, 9*u) withcolor (0,0,1); % endpoint
  drawdot(3*u, 1*u) withcolor (0,1,0); % valid nodes

  % valid(open) points
  for i=1 upto nd-1:
    drawdot(vd[i]) withcolor (0,1,0);
  endfor

  % visited(closed) points
  for i=1 upto nz-1:
    drawdot(vz[i]) withcolor (1,0,0);
  endfor
endfig;

% number 19
vd[nd]:=(3u,9u);
nd:=nd+1;
vd[nd]:=(2u,8u);
nd:=nd+1;
vd[nd]:=(4u,8u);
nd:=nd+1;
vd[nd]:=(5u,7u);
nd:=nd+1;
vd[nd]:=(7u,3u);
nd:=nd+1;
vd[nd]:=(1u,3u);
nd:=nd+1;

vz[nz]:=(2u,3u);
nz:=nz+1;
vz[nz]:=(6u,3u);
nz:=nz+1;
vz[nz]:=(3u,8u);
nz:=nz+1;
vz[nz]:=(4u,7u);
nz:=nz+1;

fignum:=fignum+1;
%ox1:=ox1+u;
%oy1:=oy1+u;
%ox2:=ox2+u;
%oy2:=oy2+u;
beginfig(fignum);
  fill obstacle withcolor 0.7white;

  for i=0 upto v:
    for j=0 upto v:
      draw(i*u, j*u-d)..(i*u+d, j*u)..(i*u, j*u+d)..(i*u-d, j*u)..(i*u, j*u-d);
    endfor
  endfor

  pickup pencircle scaled 1.3pt;
  %ox:=ox1;
  %oy:=oy1;
  %ox:=ox2;
  %oy:=oy2;
  %draw(ox,oy)--(ox+u,oy) withcolor (0,1,0);
  %draw(ox,oy)--(ox-u,oy) withcolor (1,0,0);
  %draw(ox,oy)--(ox,oy+u) withcolor (0,1,0);
  %draw(ox,oy)--(ox,oy-u) withcolor (1,0,0);

  pickup pencircle scaled 2d;
  drawdot(4*u, 9*u) withcolor (0,0,1); % endpoint
  drawdot(3*u, 1*u) withcolor (0,1,0); % valid nodes

  % valid(open) points
  for i=1 upto nd-1:
    drawdot(vd[i]) withcolor (0,1,0);
  endfor

  % visited(closed) points
  for i=1 upto nz-1:
    drawdot(vz[i]) withcolor (1,0,0);
  endfor
endfig;

% number 20
vd[nd]:=(3u,10u);
nd:=nd+1;
vd[nd]:=(2u,9u);
nd:=nd+1;
vd[nd]:=(5u,8u);
nd:=nd+1;
vd[nd]:=(7u,4u);
nd:=nd+1;
vd[nd]:=(1u,4u);
nd:=nd+1;

vz[nz]:=(2u,4u);
nz:=nz+1;
vz[nz]:=(6u,4u);
nz:=nz+1;
vz[nz]:=(3u,9u);
nz:=nz+1;
vz[nz]:=(4u,8u);
nz:=nz+1;

fignum:=fignum+1;
%ox1:=ox1+u;
%oy1:=oy1+u;
%ox2:=ox2+u;
%oy2:=oy2+u;
beginfig(fignum);
  fill obstacle withcolor 0.7white;

  for i=0 upto v:
    for j=0 upto v:
      draw(i*u, j*u-d)..(i*u+d, j*u)..(i*u, j*u+d)..(i*u-d, j*u)..(i*u, j*u-d);
    endfor
  endfor

  pickup pencircle scaled 1.3pt;
  %ox:=ox1;
  %oy:=oy1;
  %ox:=ox2;
  %oy:=oy2;
  %draw(ox,oy)--(ox+u,oy) withcolor (0,1,0);
  %draw(ox,oy)--(ox-u,oy) withcolor (1,0,0);
  %draw(ox,oy)--(ox,oy+u) withcolor (0,1,0);
  %draw(ox,oy)--(ox,oy-u) withcolor (1,0,0);

  pickup pencircle scaled 2d;
  drawdot(4*u, 9*u) withcolor (0,1,1); % endpoint
  drawdot(3*u, 1*u) withcolor (0,1,0); % valid nodes

  % valid(open) points
  for i=1 upto nd-1:
    drawdot(vd[i]) withcolor (0,1,0);
  endfor

  % visited(closed) points
  for i=1 upto nz-1:
    drawdot(vz[i]) withcolor (1,0,0);
  endfor
endfig;

end
