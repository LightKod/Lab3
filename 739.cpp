#include "DataGenerator.cpp"
typedef long long ll;
#include <fstream>
#include <cstring>
#include <algorithm>
#include <chrono>
#include <thread>
#include <time.h>
#include <sstream>
#include <iomanip>
#define TIMING
/*
https://www.eriksmistad.no/measuring-runtime-in-milliseconds-using-the-c-11-chrono-library/
*/
#define TIMING

#ifdef TIMING
#define INIT_TIMER auto start = std::chrono::high_resolution_clock::now();
#define START_TIMER start = std::chrono::high_resolution_clock::now();
#define INF 1000000007
#define STOP_TIMER(info) std::cout << info << " " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start).count() << " ms ";
#else
#define INIT_TIMER
#define START_TIMER
#define STOP_TIMER(info)
#endif

// dynamic allocate
int *array1DInit(int n)
{
    int *a = new int[n];
    return a;
}
// free memory
void freeArray1D(int *&a, int n)
{
    if (a != NULL)
    {
        memset(a, 0, n * sizeof(n));
        delete[] a;
        a = NULL;
    }
}
/***** Ref: https://www.geeksforgeeks.org/shellsort/ *****/
/* function to sort arr using shellSort */
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
// k is the largest element in array A[]
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
    if (l < r)
    {
        pivot = (l + r) / 2;
        int i = l, j = r;
        while (i < j)
        {
            while (++cc && a[i] < a[pivot])
                i++;
            while (++cc && a[j] > a[pivot])
                j--;
            if (i < j)
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
void countSForRadix(int a[], int n, int exp)
{
    int* output = array1DInit(n);
    int i, count[10] = {0};

    // Store count of occurrences in count[]
    for (i = 0; i < n; i++)
        count[(a[i] / exp) % 10]++;

    // Change count[i] so that count[i] now contains actual
    //  position of this digit in output[]
    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];

    // Build the output array
    for (i = n - 1; i >= 0; i--)
    {
        output[count[(a[i] / exp) % 10] - 1] = a[i];
        count[(a[i] / exp) % 10]--;
    }

    // Copy the output array to arr[], so that arr[] now
    // contains sorted numbers according to current digit
    for (i = 0; i < n; i++)
        a[i] = output[i];
    delete[] output;
}

void radixSort(int a[], int n, ll &cc)
{
    int k = findMax(a, n, cc);
    for (int exp = 1; k / exp > 0; exp *= 10)
    {
        countSForRadix(a, n, exp);
    }
}


// Kiểm tra chuỗi hiện tại có phải là số nguyên hay không
bool isVari(string s)
{
    try
    {
        stoi(s);
        return true;
    }
    catch (std::invalid_argument)
    {
        return false;
    }
    return false;
}

void printArray(int *a, int n, ostream &os)
{
    os << n;
    if (n > 0)
    {
        os << '\n';
        os << a[0];
        for (int i = 1; i < n; i++)
        {
            os << " " << a[i];
        }
    }
}
void getMode(string mode)
{
    if (mode == "-a")
    {
        cout << "ALGORITHM MODE" << endl;
    }
    else if (mode == "-c")
    {
        cout << "COMPARE MODE" << endl;
    }
    else
    {
        cout << "INVALID MODE" << endl;
    }
}
void writeFile(string path, int *a, int n)
{
    ofstream ofs(path);
    if (ofs.is_open())
    {
        printArray(a, n, ofs);
        ofs.close();
    }
}
int *loadFile(string path, int &n)
{
    ifstream ifs(path);
    if (ifs.is_open())
    {
        ifs >> n;
        int *a = array1DInit(n);
        for (int i = 0; i < n; i++)
        {
            ifs >> a[i];
        }
        ifs.close();
        return a;
    }
    return NULL;
}
// kiểm tra cần xuất thông tin gì ra console
void checkOutPutPara(string output_para, bool &runtime, bool &cmp)
{
    runtime = cmp = 0;
    if (output_para == "-time")
    {
        runtime = 1;
    }
    else if (output_para == "-comp")
    {
        cmp = 1;
    }
    else if (output_para == "-both")
    {
        runtime = cmp = 1;
    }
}
void compare_info(ll cc, string line_info)
{
    cout << line_info << " " << cc << endl;
}
void runtime_info(ll dur, string line_info)
{
    cout << line_info << " " << dur << " ms\n";
}
void print_para_output(string output_para, ll dur, ll cc, string rt_info = "Running time:", string cmp_info = "Comparisions:")
{
    bool runtime = 0, cmp = 0;
    checkOutPutPara(output_para, runtime, cmp);
    if (runtime)
    {
        runtime_info(dur, rt_info);
    }
    if (cmp)
    {
        compare_info(cc, cmp_info);
    }
}
void process_sort(int *a, int n, string algo_name, ll &ret_dur, ll &ret_count_cmp)
{
    auto start = std::chrono::high_resolution_clock::now();

    ret_count_cmp = 0;

    ll dur = 0;
    ll cc = 0;

    if (algo_name == "selection-sort")
    {
    }
    else if (algo_name == "insertion-sort")
    {
    }
    else if (algo_name == "bubble-sort")
    {
    }
    else if (algo_name == "shaker-sort")
    {
        start = std::chrono::high_resolution_clock::now();
        shakerSort(a, n, cc);
        dur = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start).count();
    }
    else if (algo_name == "shell-sort")
    {
        start = std::chrono::high_resolution_clock::now();
        shellSort(a, n, cc);
        dur = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start).count();
    }
    else if (algo_name == "heap-sort")
    {
    }
    else if (algo_name == "merge-sort")
    {
    }
    else if (algo_name == "quick-sort")
    {
        start = std::chrono::high_resolution_clock::now();
        quickSort(a, 0, n-1, cc);
        dur = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start).count();
    }
    else if (algo_name == "counting-sort")
    {
        start = std::chrono::high_resolution_clock::now();
        countingSort(a, n, n, cc);
        dur = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start).count();
    }
    else if (algo_name == "radix-sort")
    {
        start = std::chrono::high_resolution_clock::now();
        radixSort(a, n, cc);
        dur = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start).count();
    }
    else if (algo_name == "flash-sort")
    {
        start = std::chrono::high_resolution_clock::now();
        flashSort(a, n, cc);
        dur = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start).count();
    }

    ret_dur = dur;
    ret_count_cmp = cc;
}
void handle_command_3(string algo_name, int input_size, string output_para)
{
    // create array
    int *a = array1DInit(input_size);
    if (a == NULL)
    {
        cout << "Error: do not have enough memory !\n";
        return;
    }

    ll rtime = 0;
    ll cc = 0;

    // random data
    cout << "\nInput order: Randomize\n";
    cout << "-------------------------\n";
    GenerateRandomData(a, input_size);
    writeFile("input_1.txt", a, input_size);
    process_sort(a, input_size, algo_name, rtime, cc);
    print_para_output(output_para, rtime, cc);

    // nearly sorted data
    cout << "\nInput order: Nearly Sorted\n";
    cout << "-------------------------\n";
    GenerateNearlySortedData(a, input_size);
    writeFile("input_2.txt", a, input_size);
    process_sort(a, input_size, algo_name, rtime, cc);
    print_para_output(output_para, rtime, cc);

    // sorted data
    cout << "\nInput order: Sorted\n";
    cout << "-------------------------\n";
    GenerateSortedData(a, input_size);
    writeFile("input_3.txt", a, input_size);
    process_sort(a, input_size, algo_name, rtime, cc);
    print_para_output(output_para, rtime, cc);

    // revsorted data
    cout << "\nInput order: Reversed\n";
    cout << "-------------------------\n";
    GenerateReverseData(a, input_size);
    writeFile("input_4.txt", a, input_size);
    process_sort(a, input_size, algo_name, rtime, cc);
    print_para_output(output_para, rtime, cc);

    // free memory
    freeArray1D(a, input_size);
}
// kiem tra co phai command_3 hay khong
bool is_command_3(int argc, char *argv[])
{
    if (argc > 4)
    {
        string mode = argv[1];
        if (mode == "-a")
        {
            string line_3 = argv[3];
            if (isVari(line_3))
            {
                return 1;
            }
        }
    }
    return 0;
}
void command_3_main_function(int argc, char *argv[])
{
    string mode = argv[1];
    string algo_name = argv[2];
    int input_size = stoi(argv[3]);
    string output_para = argv[4];

    getMode(mode);
    cout << "Algorithm: " << algo_name << endl;
    cout << "Input size: " << input_size << "\n";
    handle_command_3(algo_name, input_size, output_para);
}

// kiem tra co phai command_4 hay khong
bool is_command_4(int argc, char *argv[])
{
    if (argc > 2)
    {
        string mode = argv[1];
        if (mode == "-c")
        {
            if (argc == 5)
            {
                return 1;
            }
        }
    }
    return 0;
}
void handle_command_4(string input_file, string algo_1, string algo_2)
{
    int n = 0;
    int *a = loadFile(input_file, n);
    cout << "Input size: " << n << endl;
    cout << "-------------------------\n";

    if (a == NULL)
    {
        cout << "Error: do not have enough memory !\n";
        return;
    }

    ll run_time[2] = {0, 0};
    ll count_cmp[2] = {0, 0};
    process_sort(a, n, algo_1, run_time[0], count_cmp[0]);
    process_sort(a, n, algo_2, run_time[1], count_cmp[1]);

    cout << "Running time: " << run_time[0] << " ms\t"
         << "| " << run_time[1] << " ms\n";
    cout << "Comparisions: " << count_cmp[0] << "\t| " << count_cmp[1] << "\n";
}
void command_4_main_function(int argc, char *argv[])
{
    string mode = argv[1];
    string algo_1_name = argv[2];
    string algo_2_name = argv[3];
    string input_file = argv[4];

    getMode(mode);
    cout << "Algorithm: " << algo_1_name << " | " << algo_2_name << endl;
    cout << "Input file: " << input_file << "\n";
    handle_command_4(input_file, algo_1_name, algo_2_name);
}
