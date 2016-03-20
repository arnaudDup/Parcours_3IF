function [] = Sinus(fo)


xn = ones(32768,1);
Xn = ones(32768,1);
Temps = ones(32768,1);
frequence = ones(32768,1);


for o = 1 : 32768
    
    tampon = -5 + (o-1) * 10/32768 ;
    Temps(o,1) = tampon;
    
end

for a = 1 : 32768
    xn(a,1) = sin(2*pi*fo*Temps(a));
end

xn = sin(2*pi*fo*Temps);

for i = 1 : 32768
    
    tampon = -1638 + i *0.09998 ;
    frequence(i,1) = tampon;
    
end 

figure 
ax1 = subplot(2,1,1); 
ax2 = subplot(2,1,2);


plot(ax1,Temps,xn);

title(ax1,'Representation temporel')
ylabel(ax1,'f(t)')

x = linspace(-10,10);
Xn = tfour(xn');
plot(ax2,frequence, imag(Xn));
title(ax2,'Representation frequentiel')
ylabel(ax2,'T(f(t))')

 
end