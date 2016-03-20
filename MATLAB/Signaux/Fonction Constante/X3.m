function [] = X3(B)


xn = zeros(32768,1);
Xn = ones(32768,1);
Temps = ones(32768,1);
frequence = ones(32768,1);


for o = 1 : 32768
    
    tampon = -5 + (o-1) * 10/32768 ;
    Temps(o,1) = tampon;
    
end


for o = 1 : 32768
    if (Temps(o) >0 )
        
        xn(o) = exp(-B*Temps(o));
    end
end
for i = 1 : 32768
    
    tampon = -1638 + i *0.09998 ;
    frequence(i,1) = tampon;
    
end 

figure 
ax1 = subplot(2,2,1); 
ax2 = subplot(2,2,2);
ax3 = subplot(2,2,3);
ax4 = subplot(2,2,4);


plot(ax1,Temps,xn);

title(ax1,'Representation temporel')
ylabel(ax1,'f(t)')


Xn = tfour(xn');
plot(ax2,frequence, imag(Xn));
title(ax2,'Representation frequentiel imaginaire')
ylabel(ax2,'T(f(t))')

plot(ax3,frequence, Xn);
title(ax3,'Representation frequentiel r�el ')
ylabel(ax3,'T(f(t))')
 
xn=tfourinv(Xn);
plot(ax4,Temps, xn);
title(ax4,'Representation temporel de la transform� inverse ')
ylabel(ax4,'f(t)')
end