#include<iostream>
#include<cstdio>
#include <map>

using namespace std;

int main() {
    
    // define variables
    int lon; cin >> lon;
    int cais [3];
    
    // initiate the array
    cais[0] = 0;
    cais[1] = 0;
    cais[2] = 0;
    
    
    // make the background work
    for(int i = 0; i < lon; i++){
        
        int a; cin >> a;
        
        switch (a) {
                
            case 25 :
                cais[0] ++;
                break;
                
            case 50:
                
                if(cais[0] <= 0){
                    cout << "NO";
                    return 0;
                }
                cais[0] --;
                cais[1] ++;
                break;
                
            case 100 :
                
                if (cais[1] >= 1 && cais[0] >= 1)
                {
                    cais[0] --;
                    cais[1] --;
                }
                
                else if (cais[0] >= 3)
                {
                    cais[0] -= 3 ;
                }
                
                else
                {
                    cout << "NO";
                    return 0;
                }
                
                cais[2] ++; 
                break;
        }        
    }
    cout << "YES";
    return 0; 
}
