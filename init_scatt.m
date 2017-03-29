   figure(1) ; clf();
   hp = plot3(0,0,0,'.');
   hold on
   hr = plot3(0,0,0,'r.');
   axis manual;
   axis([-160,160,-60,60, -5, 500]);
   view(180,-90);
   set(hp,'xdata',x,'ydata',y, 'zdata', z);
   set(hr,'xdata',x,'ydata',y, 'zdata', z);
   b = 0;
   %az = 0;
   %el = 90;
   
   %set(hp, 'axis',[0,78600,0,78600]);