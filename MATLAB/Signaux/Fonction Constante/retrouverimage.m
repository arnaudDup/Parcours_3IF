function []= retrouverimage()
% Lecture de l'image
[im, map]=imread('photoTexte.png') ;
% Affichage de l'image sur la figure 1
figure(1)
image(im)
colormap(map)
% Calcul de la FFT 2D
IM=fftshift(fft2(im));
% Recadrage du spectre d'amplitude
% pour affichage sous forme d'image niveaux de gris
affIM=abs(IM)+1;
maxi=max(max(affIM));
mini=min(min(affIM));
affIM=(log(affIM)-log(mini))/(log(maxi)-log(mini))*255;
figure(2)
image(affIM)
colormap(map)
end