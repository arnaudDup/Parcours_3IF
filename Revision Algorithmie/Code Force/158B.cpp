#include <iostream>
 using namespace std;
 int tab [51];
 int main ()
 {
     int nombre;
     int NbSup;
     int decompte = 0 ;
 
 
     cin >> nombre >> NbSup;
     for (int i = 0; i < nombre ; i++)
     {
         int entre;
         cin >> entre;
         tab[i] = entre;
 
     }
 
 

 
 
 decompte = NbSup;
 while ( tab[decompte-1] == tab[decompte])
 {
 if( tab[0] == 0  )
 {
 decompte = 0;
 break;
 }
 else if (tab[decompte-1] == 0)
 decompte  = decompte - 2;
 
 decompte ++;
 }
 cout << decompte;
 return 0;
 }