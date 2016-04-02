#include <iostream>
#include <string>
using namespace std;

// définition du ou bit ou bit.
int XOR (char a, char b)
{
	if (a == b)
		return 0;
	else
		return 1 ;
}


int main()
{
	// on récupére des string bien plus facile à traiter que les int.
	string a, b;
	cin >> a >> b;
	for (int i=0; i< a.size(); i++)
		cout << XOR(a[i], b[i]);
	
	cout << endl ;
	return 0;
}


