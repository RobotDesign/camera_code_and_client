set(hp,'xdata',x,'ydata',y, 'zdata', z);


rindex1 = z < 300;  %less than 60 cms in front
        
        rindex2 = y >30;   %greater than 15 cms tall
        rindex3 = y < 50;
        rindex4 = rindex2 & rindex3; 
        rindex = rindex1 & rindex4;  %some bitwise shit
        xx = x(rindex);       %xxr, yyr and zzr are the vectors of points which will plotted in red
        yy = y(rindex);      
        zz = z(rindex);
        
        data.x(frames) = xx;
        data.y(frames) = yy;
        data.z(frames) = zz;
        
        if fz(1) == 300
            save('C:\Users\Jack\Documents\MATLAB\data.mat', 'data');
        end
        
 s= sprintf(frames(1));
 set(hr,'string',s);
 set(hr,'xdata',xx,'ydata',yy, 'zdata', zz);