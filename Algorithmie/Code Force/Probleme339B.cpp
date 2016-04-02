#include <iostream>
#include <string>
using namespace std;


int main()
{
	// on récupére des string bien plus facile à traiter que les int.
	int a, b;
	cin >> a >> b;
    
	for (int i = 0 ; i < b; i++)
		cout << XOR(a[i], b[i]);
	
	cout << endl ;
	return 0;
}


