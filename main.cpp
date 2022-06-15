#include "DataGenerator.cpp"
#include "Sort.cpp"

#include <algorithm>
#include <chrono>
#include <thread>
#include <time.h>
#include <iomanip>
#define TIMING
/*
https://www.eriksmistad.no/measuring-runtime-in-milliseconds-using-the-c-11-chrono-library/
*/
#define TIMING

#ifdef TIMING
#define INIT_TIMER auto start = std::chrono::high_resolution_clock::now();
#define START_TIMER start = std::chrono::high_resolution_clock::now();
#define STOP_TIMER(info) std::cout << info << " " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start).count() << " ms ";
#else
#define INIT_TIMER
#define START_TIMER
#define STOP_TIMER(info)
#endif


/*FOR TERMINAL RUN
    g++ main.cpp
    .\a.exe -a heap-sort 70000 -comp
*/
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
		start = std::chrono::high_resolution_clock::now();
        SelectionSort(a, n, cc);
        dur = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start).count();
    }
    else if (algo_name == "insertion-sort")
    {
		start = std::chrono::high_resolution_clock::now();
        InsertionSort(a, n, cc);
        dur = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start).count();
    }
    else if (algo_name == "bubble-sort")
    {
		start = std::chrono::high_resolution_clock::now();
        BubbleSort(a, n, cc);
        dur = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start).count();
    }
    else if (algo_name == "shaker-sort")
    {
    }
    else if (algo_name == "shell-sort")
    {
        start = std::chrono::high_resolution_clock::now();
        shellSort(a, n, cc);
        dur = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start).count();
    }
    else if (algo_name == "heap-sort")
    {
		start = std::chrono::high_resolution_clock::now();
        HeapSort(a, n, cc);
        dur = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start).count();
    }
    else if (algo_name == "merge-sort")
    {
		start = std::chrono::high_resolution_clock::now();
        MergeSort(a, 0, n-1, cc);
        dur = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start).count();
    }
    else if (algo_name == "quick-sort")
    {
    }
    else if (algo_name == "counting-sort")
    {
        start = std::chrono::high_resolution_clock::now();
        countingSort(a, n, n, cc);
        dur = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start).count();
    }
    else if (algo_name == "radix-sort")
    {
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

int main(int argc, char *argv[])
{
    // cmd 3
    if (is_command_3(argc, argv))
    {
        command_3_main_function(argc, argv);
    }
    // cmd 4
    if (is_command_4(argc, argv))
    {
        command_4_main_function(argc, argv);
    }
}