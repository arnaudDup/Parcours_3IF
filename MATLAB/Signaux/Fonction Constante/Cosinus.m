function [] = Cosinus(fo)


xn = ones(32768,1);
Xn = ones(32768,1);
Temps = ones(32768,1);
frequence = ones(32768,1);


for o = 1 : 32768
    
    tampon = -5 + (o-1) * 10/32768 ;
    Temps(o,1) = tampon;
    
end

for a = 1 : 32768
    xn(a,1) = cos(2*pi*fo*Temps(a));
end

xn = cos(2*pi*fo*Temps);

for i = 1 : 32768
    
    tampon = -1638 + i *0.09998 ;
    frequence(i,1) = tampon;
    
end 

figure 
ax1 = subplot(2,2,1); 
ax2 = subplot(2,2,2);
ax3 = subplot(2,2,3);


plot(ax1,Temps,xn);

title(ax1,'Representation temporel')
ylabel(ax1,'f(t)')

Xn = tfour(xn');
plot(ax2,frequence, Xn);
title(ax2,'Representation frequentiel')
ylabel(ax2,'T(f(t))')


xn = tfourinv(Xn);
plot(ax3,Temps, xn);
title(ax3,'Representation temps')
ylabel(ax3,'f(t)')

%Idée faire l'une moins l'autre dans la 4eme plac epour montreer = à zero
 
end