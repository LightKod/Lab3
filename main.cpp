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
void InsertionSort(int *a, int n, ll& cc) {
	int j, key;
	cc = 0;
	for (int i = 0; i < n; i++)
	{
		key = a[i];
		j = i - 1;

		while (++cc && j >= 0 && a[j] > key) {
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
void Heapify(int* a, int n, int root, ll& cc) {
	int largest = root;

	//Get the children nodes
	int c1 = root * 2 + 1;
	int c2 = root * 2 + 2;


	//Find largest children
	if (++cc && c1 < n && a[c1] > a[largest]) {
		largest = c1;
	}

	if (++cc && c2 < n && a[c2] > a[largest]) {
		largest = c2;
	}

	//If there is a child that is larger than the root
	if (++cc && largest != root){
		//Swap the largest child with its root
		int temp = a[largest];
		a[largest] = a[root];
		a[root] = temp;
		Heapify(a, n, largest);
	} 
		
}
//https://www.geeksforgeeks.org/heap-sort/
void HeapSort(int *a, int n, ll& cc) {
	//Build max heap
	cc = 0;
	for (int i = 0; i < n/2-1; i++)
	{
		Heapify(a, n, i);
	}

	//Swap and heapify
	for (int i = 0; i < n; i++)
	{
		int temp = a[0];
		a[0] = a[i];
		a[i] = temp;

		Heapify(a, i, 0,ll);
	}
}

//https://www.geeksforgeeks.org/selection-sort/
void SelectionSort(int *a, int n, ll& cc){
	int minIndex = 0;
	cc = 0;
	//Loop through the array
	for(int i = 0, i <  n; i ++){
		int minIndex = i;	
		//Find the min value of the array
		for(int j =i+1; j < n; j++){
			if(++cc && a[j] < a[minIndex]){
				minIndex = j;
			}
		}
	//Swap current index with min min value
	int temp = a[i];
	a[i] = a[minIndex];
	a[minIndex] = temp;
	}
}

//https://www.geeksforgeeks.org/bubble-sort/
void BubbleSort(int *a, int n, ll& cc){
	cc = 0;
	//Loop through the array twice and then swap any element that has the wrong order
	for(int i = 0, i <  n - 1; i++){
		for(int j = 0; j < n - i - 1; j++){
			if(++cc && a[j] > a[j+1]){
				int temp = a[i];
				a[i] = a[j];
				a[j] = temp;
			}
		}
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