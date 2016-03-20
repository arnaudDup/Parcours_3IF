#include <iostream>
using namespace std; 


void pgcd(int a, int b)
{
	if (b == 0)
	{
		cout << "PGCD : " << a << endl; 
		return;  
	}
	else 
	{
		cout << b << "  " << a%b << endl; 
		pgcd(b, a % b);
	}
}

int main ()
{	
	int entier1, entier2; 
	cin >> entier1 >> entier2;
	pgcd(entier1, entier2); 

	return 0; 
}

