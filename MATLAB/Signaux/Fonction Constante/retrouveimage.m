function [Pb,Pi,W]= retrouveimage()
% Lecture de l'image
[im, map]=imread('photoRef.png') ;
% Affichage de l'image sur la figure 1
Im = fftshift(fft2(im));
H = fftshift( fft2 (h(4,6)));
Matrice_avec_bruit = H.*Im;
Matrice_avec_bruit_Spatiale = ifft2(fftshift(Matrice_avec_bruit));
matrice_sans_bruit_spaciale = floor ( Matrice_avec_bruit_Spatiale);
bruit  = Matrice_avec_bruit_Spatiale - matrice_sans_bruit_spaciale;
Bruit = fftshift(fft2(bruit));
Pi = abs(Im).*abs(Im);
Pb = abs(Bruit).*abs(Bruit);

W=(1./H).*((abs(H).*abs(H))./(((abs(H).*abs(H))+(Pb./Pi))));

[im2, map2]=imread('photoTexte.png') ;
Im2 = fftshift(fft2(im2));
I = Im2 .* W;
affIM= ifft2(fftshift(I));

figure(2)
image(affIM)
colormap(map2)

end