function[flouDuDirac] = h (x,y)

flouDuDirac = zeros(512,512);

for ix= 0 : x
    for iy =0 : y
        flouDuDirac(256-x/2+ix,256-y/2+iy)=1/35;
    end
end

flouDuDirac=fftshift(flouDuDirac)
end