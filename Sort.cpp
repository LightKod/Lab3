#include "Utility.cpp"
#include <iostream>
#include <cstring>
#define INF 1000000007
typedef long long ll;


using namespace std;


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
void Merge(int* a, int l, int m, int r, ll& cc) {
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
		if (++cc && temp1[count1] > temp2[count2]) {
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
void MergeSort(int* a, int l, int r, ll& cc) {
	if (l < r) {
		int m = (l + r - 1) / 2;
		MergeSort(a, l, m, cc);
		MergeSort(a, m+1, r, cc);
		Merge(a, l, m, r,cc);
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
	if (largest != root){
		//Swap the largest child with its root
		int temp = a[largest];
		a[largest] = a[root];
		a[root] = temp;
		Heapify(a, n, largest, cc);
	} 
		
}
//https://www.geeksforgeeks.org/heap-sort/
void HeapSort(int *a, int n, ll& cc) {
	//Build max heap
	cc = 0;
	for (int i = 0; i < n/2-1; i++)
	{
		Heapify(a, n, i, cc);
	}

	//Swap and heapify
	for (int i = 0; i < n; i++)
	{
		int temp = a[0];
		a[0] = a[i];
		a[i] = temp;

		Heapify(a, i, 0,cc);
	}
}

//https://www.geeksforgeeks.org/selection-sort/
void SelectionSort(int *a, int n, ll& cc){
	int minIndex = 0;
	cc = 0;
	//Loop through the array
	for(int i = 0; i <  n; i ++){
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
	for(int i = 0; i <  n - 1; i++){
		for(int j = 0; j < n - i - 1; j++){
			if(++cc && a[j] > a[j+1]){
				int temp = a[i];
				a[i] = a[j];
				a[j] = temp;
			}
		}
	}
}

void shellSort(int arr[], int n, ll &cc)
{
    cc = 0;

    // Start with a big gap, then reduce the gap by half
    for (int gap = n / 2; gap > 0; gap /= 2)
    {
        // Do a gapped insertion sort for this gap size.
        // The first gap elements a[0..gap-1] are already in gapped order
        // keep adding one more element until the entire array is gap sorted
        for (int i = gap; i < n; i += 1)
        {
            // add a[i] to the elements that have been gap sorted
            // save a[i] in temp and make a hole at position i
            int temp = arr[i];

            // shift earlier gap-sorted elements up until the correct
            // location for a[i] is found
            int j;
            for (j = i; j >= gap && ++cc && arr[j - gap] > temp; j -= gap)
            {
                arr[j] = arr[j - gap];
            }

            //  put temp (the original a[i]) in its correct location
            arr[j] = temp;
        }
    }
}
/***** Ref:
 * https://www.codingeek.com/algorithms/counting-sort-explanation-pseudocode-and-implementation/
 * *****/
/*  Counting sort function  */
void countingSort(int A[], int k, int n, ll &cc)
{
    cc = 0;

    // B[] is output array
    // C[] is count array support sort procedure
    int *B = array1DInit(n);
    int *C = array1DInit(k + 1);
    int i, j;

    // Initializing counting array C[i] to 0
    memset(C, 0, (k + 1) * sizeof(int));

    // Store count of each element in array C
    for (j = 0; j < n; j++)
    {
        C[A[j]] = C[A[j]] + 1;
    }

    /* Change C[i] such that it contains actual
    position of these elements in output array*/
    for (i = 1; i < k + 1; i++)
    {
        C[i] = C[i] + C[i - 1];
    }

    // Creating Output array from C[i]
    // and decrementing value of C[i].
    for (j = n - 1; j >= 0; j--)
    {
        B[C[A[j]] - 1] = A[j];
        C[A[j]] = C[A[j]] - 1;
    }

    // copy value from B[] back to A[]
    memcpy(A, B, n * sizeof(n));

    freeArray1D(B, n);
    freeArray1D(C, k + 1);
}

/***** Ref:
 * https://github.com/HaiDuc0147/sortingAlgorithm/blob/main/reportSort/Sort.cpp
 * *****/
/*  Flash Fort function  */
// subroutine of flashSort
void insertionSortUtil(int a[], int n, ll &cc)
{
    for (int i = 1; i < n; i++)
    {
        int k = i - 1;
        int key = a[i];

        while (k >= 0 && ++cc && a[k] > key)
        {
            a[k + 1] = a[k];
            k--;
        }

        a[k + 1] = key;
    }
}
void flashSort(int a[], int n, ll &cc)
{
    cc = 0;

    int minVal = a[0];
    int max = 0;

    // calculate the number of buckets
    int m = int(0.45 * n);
    int *l = new int[m];

    // init l[] with value 0
    memset(l, 0, m * sizeof(int));

    // find min value of a[]
    // and idx of max elem
    for (int i = 1; i < n; i++)
    {
        if (++cc && a[i] < minVal)
        {
            minVal = a[i];
        }
        if (++cc && a[i] > a[max])
        {
            max = i;
        }
    }

    if (++cc && a[max] == minVal)
    {
        return;
    }

    double c1 = (double)(m - 1) / (a[max] - minVal);

    // count the number of elements in each bucket
    for (int i = 0; i < n; i++)
    {
        int k = int(c1 * (a[i] - minVal));
        ++l[k];
    }

    // calculate final index of each bucket
    for (int i = 1; i < m; i++)
    {
        l[i] += l[i - 1];
    }

    HoanVi(a[max], a[0]);
    int nmove = 0;
    int j = 0;
    int k = m - 1;
    int t = 0;
    int flash;
    while (nmove < n - 1)
    {
        // if elem in right bucket, do not swap
        // just find the next elem
        while (j > l[k] - 1)
        {
            j++;
            k = int(c1 * (a[j] - minVal));
        }

        flash = a[j];

        if (k < 0)
        {
            break;
        }

        while (j != l[k])
        {
            k = int(c1 * (flash - minVal));
            int hold = a[t = --l[k]];
            a[t] = flash;
            flash = hold;
            ++nmove;
        }
    }

    delete[] l;
    insertionSortUtil(a, n, cc);
}

int findMax(int a[], int n, ll &cc)
{
    int Max = -INF;
    for (int i = 0; ++cc && i < n; ++i)
    {
        if (++cc && a[i] > Max)
        {
            Max = a[i];
        }
    }
    return Max;
}

void shakerSort(int a[], int n, ll &cc)
{
    int l = 0, r = n - 1, k = 0;
    while (++cc && l < r)
    {
        for (int i = l; ++cc && i < r; ++i)
        {
            if (++cc && a[i] > a[i + 1])
            {
                HoanVi(a[i], a[i + 1]);
                k = i;
            }
        }
        r = k;
        for (int i = r; ++cc && i > l; --i)
        {
            if (++cc && a[i] < a[i - 1])
            {
                HoanVi(a[i], a[i - 1]);
            }
        }
        l = k;
    }
}
void quickSort(int a[], int l, int r, ll &cc)
{
    int pivot;
    if (++cc &&l < r)
    {
        pivot = (l + r) / 2;
        int i = l, j = r;
        while (++cc && i < j)
        {
            while (++cc && a[i] < a[pivot])
                i++;
            while (++cc && a[j] > a[pivot])
                j--;
            if (++c && i < j)
            {
                HoanVi(a[i], a[j]);
                i++;
                j--;
            }
        }
        quickSort(a, l, pivot - 1, cc);
        quickSort(a, pivot + 1, r, cc);
    }
}
/*
Ref: https://www.geeksforgeeks.org/radix-sort/
*/
void countSForRadix(int a[], int n, int exp, ll& cc)
{
    int* output = array1DInit(n);
    int i, count[10] = {0};

    // Store count of occurrences in count[]
    for (i = 0; ++cc && i < n; i++)
        count[(a[i] / exp) % 10]++;

    // Change count[i] so that count[i] now contains actual
    //  position of this digit in output[]
    for (i = 1; ++c && i < 10; i++)
        count[i] += count[i - 1];

    // Build the output array
    for (i = n - 1; ++cc && i >= 0; i--)
    {
        output[count[(a[i] / exp) % 10] - 1] = a[i];
        count[(a[i] / exp) % 10]--;
    }

    // Copy the output array to arr[], so that arr[] now
    // contains sorted numbers according to current digit
    for (i = 0; ++c && i < n; i++)
        a[i] = output[i];
    freeArray1D(output, n);
}

void radixSort(int a[], int n, ll &cc)
{
    int k = findMax(a, n, cc);
    for (int exp = 1; k / exp > 0; exp *= 10)
    {
        countSForRadix(a, n, exp, cc);
    }
}