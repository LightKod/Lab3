#include <iostream>
#include "DataGenerator.cpp"

using namespace std;

int* CreateArray(int n, int type) {
	int* a = new int[n];
	switch (type) {
	case 0:
		for (int i = 0; i < n; i++)
		{
			a[i] = rand();
		}
		break;
	case 1:
		//int* a = new int[n];
		for (int i = 0; i < n; i++)
		{
			a[i] = i;
		}
		break;
	case -1:
		//int* a = new int[n];
		for (int i = 0; i < n; i++)
		{
			a[i] = n - i;
		}
		break;
	}
	return a;
}
void PrintArray(int* a, int n) {
	for (int i = 0; i < n; i++)
	{
		cout << a[i] << " ";
		if ((i+1) % 10 == 0) cout << endl;
	}
}
void InsertionSort(int *a, int n) {
	int j, key;

	for (int i = 0; i < n; i++)
	{
		key = a[i];
		j = i - 1;

		while (j >= 0 && a[j] > key) {
			a[j + 1] = a[j];
			j--;
		}
		a[j + 1] = key;
	}
}
void Merge(int* a, int l, int m, int r) {
	int n1 = m - l + 1;
	int n2 = r - m;

	int* temp1 = new int[n1];
	int* temp2 = new int[n2];

	for (int i = 0; i < n1; i++)
	{
		temp1[i] = a[l + i];
	}
	for (int i = 0; i < n2; i++)
	{
		temp2[i] = a[m + i + 1];
	}

	int count1 = 0, count2 = 0;
	int k = l;
	while (count1 < n1 && count2 < n1) {
		if (temp1[count1] > temp2[count2]) {
			a[k++] = temp2[count2++];
		}
		else {
			a[k++] = temp1[count1++];
		}
	}

	while (count1 < n1) {
		a[k++] = temp1[count1++];
	}

	while (count2 < n2) {
		a[k++] = temp2[count2++];
	}
}
void MergeSort(int* a, int l, int r) {
	if (l < r) {
		int m = (l + r - 1) / 2;

		MergeSort(a, l, m);
		MergeSort(a, m+1, r);
		Merge(a, l, m, r);
	}
}
void Heapify(int* a, int n, int root) {
	int largest = root;

	int c1 = root * 2 + 1;
	int c2 = root * 2 + 2;

	if (c1 < n && a[c1] > a[largest]) {
		largest = c1;
	}

	if (c2 < n && a[c2] > a[largest]) {
		largest = c2;
	}

	if (largest != root) Heapify(a, n, largest);
}
void HeapSort(int *a, int n) {
	for (int i = 0; i < n/2-1; i++)
	{
		Heapify(a, n, i);
	}

	for (int i = 0; i < n; i++)
	{
		int temp = a[0];
		a[0] = a[i];
		a[i] = temp;

		Heapify(a, i, 0);
	}
}
void SelectionSort();
void BubbleSort();

int main()
{

    return 0;
}