function [] = EchantillonnageEtAlising (f)


xn = zeros(32768,1);
Xn = ones(32768,1);
Temps = ones(32768,1);
frequence = ones(32768,1);


for o = 1 : 32768
    
    tampon = -5 + (o-1) * 10/(32768) ;
    Temps(o,1) = tampon;
    
end

xn=sin(2*pi*(f) *Temps)+ 2*sin (2*pi*(f +40) *Temps) + sin (2*pi*(f +80) *Temps) ;

for i = 1 : 32768
    
    tampon = -1638 + i *0.1;
    frequence(i,1) = tampon;
    
end 

figure 
ax1 = subplot(2,3,1); 
ax2 = subplot(2,3,2);
ax3 = subplot(2,3,3);
ax4 = subplot(2,3,6);
ax5 = subplot(2,3,4); 
ax6 = subplot(2,3,5);

plot(ax1,Temps,xn,'.r');

title(ax1,'Representation temporel')
ylabel(ax1,'real(f(t))')

plot(ax5,Temps,imag(xn));
title(ax5,'Representation temporel')
ylabel(ax5,'imag(f(t))')

Xn = tfour(xn');
plot(ax2,frequence, imag(Xn));
title(ax2,'Representation frequentiel imaginaire')
ylabel(ax2,'T(f(t))')

plot(ax3,frequence, Xn);
title(ax3,'Representation frequentiel r�el ')
ylabel(ax3,'T(f(t))')
 
xn=tfourinv(Xn);
plot(ax4,Temps, xn,'.r');
title(ax4,'Representation temporel de la transform� inverse ')
ylabel(ax4,'real(f(t)) reconst')

xn=tfourinv(Xn);
plot(ax6,Temps, imag(xn),'.r');
title(ax6,'partie imaginaire de la transform� inverse ')
ylabel(ax6,'imag(f(t)) rescont')
end