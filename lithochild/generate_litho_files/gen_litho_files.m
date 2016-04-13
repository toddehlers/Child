%% simple spatially variable diffusion test
clear all
close all

xmax=100000
ymax=50000

x=linspace(0,xmax,1000);
y=linspace(0,ymax,500);

[xi, yi]=meshgrid(x,y);
bi=zeros(length(y),length(x));
bi(xi==0 | yi==0 | xi==xmax | yi==ymax)=2;


xi=xi+rand([length(y),length(x)]);
yi=yi+rand([length(y),length(x)]);




zi=zeros(length(y),length(x))+10+(5.*rand(length(y),length(x)));
zi(bi==2)=0;


kd=zeros(length(y),length(x));
kd2=zeros(length(y),length(x))+1;
kd3=kd2+1;


depths=kd-7000;
depths2=depths-1000;
depths3=depths2-30000;

% zi(xi>25000 & xi<75000 & yi>25000 & yi<75000)=10;
% zi(xi>125000 & xi<175000 & yi>25000 & yi<75000)=10;


% 
% kd(xi>=100000)=0;
% kd2(xi<100000)=1;

surf(xi,yi,zi,kd)%, 'edgecolor','none')
xx=xi(:);
yy=yi(:);
zz=zi(:);
bb=bi(:);
kdd=kd(:);
dpdd=depths(:);
kdd2=kd2(:);
dpdd2=depths2(:);
kdd3=kd3(:);
dpdd3=depths3(:);

m=[xx yy zz bb kdd dpdd kdd2 dpdd2 kdd3 dpdd3];
gg=sortrows(m,[4 1 2]);
x2=gg(:,1);
y2=gg(:,2);
z2=gg(:,3);
b2=gg(:,4);
kd2=gg(:,5);
dpdd_2=gg(:,6);
kd2_2=gg(:,7);
dpdd2_2=gg(:,8);

kd3_2=gg(:,9);
dpdd3_2=gg(:,10);


  fid=fopen('simplediff_test.pts', 'wt');
     fprintf(fid, '%i\n', size(x2,1));
  for i=1:size(x2)
     fprintf(fid,'%-f %f %f %i\n',x2(i),y2(i),z2(i),b2(i));
  end
  
  fclose(fid)  

  fid=fopen('kdunits', 'wt');
     
  for i=1:size(x2)
      kd2(i);
      kd(i);
     fprintf(fid,'%i %i %i\n',kd2(i), kd2_2(i), kd3_2(i));
  end
  
  fclose(fid)  
  
    fid=fopen('unitdepths', 'wt');
     
  for i=1:size(x2)
     fprintf(fid,'%f %f %f\n',dpdd_2(i), dpdd2_2(i), dpdd3_2(i));
  end
  
  fclose(fid)  
  
  
  units=[0 1 2];
  kdvals=[0.0001 0.00001 0.00001]; %hillslope diffusivity
  kbvals=[0.000005 0.00001 0.000005]; %fluvial erodibility
  sedrockflag=[1 1 1];
  Dgrade=[1 1 1];
    fid=fopen('kdtable', 'wt');
     
  for i=1:length(units)
     fprintf(fid,'%f %f %i %f\n',kdvals(i), kbvals(i), sedrockflag(i), Dgrade(i));
  end
  
  fclose(fid)  