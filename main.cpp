#include <iostream>
#include "DataGenerator.cpp"

using namespace std;

void PrintArray(int* a, int n) {
	for (int i = 0; i < n; i++)
	{
		cout << a[i] << " ";
		if ((i+1) % 10 == 0) cout << endl;
	}
}

int main()
{
	int a[1000];
	int n = 1000;
	GenerateRandomData(a, n);
	PrintArray(a,1000);
    return 0;
}