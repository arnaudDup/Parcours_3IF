#include <iostream>
using namespace std; 

int exponentielle(int entier)
{
	int exponentielle = 1;
	if (entier <= 1)
	{
		return exponentielle;
	}

	for (int i = 1; i <= entier; i++)
	{
		exponentielle *= i;
	}
	return exponentielle;
}

int main ()
{
	int entier = 0; 
	cin >> entier; 
	cout << exponentielle(entier) << endl;
}