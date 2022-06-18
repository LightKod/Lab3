#include "DataGenerator.cpp"
#include "Sort.cpp"

#include <algorithm>
#include <chrono>
#include <thread>
#include <time.h>
#include <iomanip>
#define TIMING
#define INF 1000000007
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
    //Command 1
    .\a.exe -a radix-sort input.txt -both
    //Command 2
    .\a.exe -a selection-sort 50 -rand -time
    //Command 3
    .\a.exe -a heap-sort 70000 -comp
    //Command 4
    .\a.exe -c heap-sort merge-sort input.txt
    //Command 5
    .\a.exe -c heap-sort merge-sort 100000 -nsorted
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
void print_para_output(string output_para, ll dur, ll cc)
{
    bool runtime = 0, cmp = 0;
    checkOutPutPara(output_para, runtime, cmp);
    if (runtime)
    {
        cout << "Running time:" << " " << dur << " ms\n";
    }
    if (cmp)
    {
        cout << "Comparisions:" << " " << cc << endl;
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

//Command 1
void handle_command_1(string algo_name, string input_file, string output_para)
{
    // create array
    int input_size = 0;
    int *a = loadFile(input_file, input_size);
    if (a == NULL)
    {
        cout << "Error: do not have enough memory !\n";
        return;
    }

    ll rtime = 0;
    ll cc = 0;

    cout << "\nInput:\n";
    cout << "-------------------------\n";
    writeFile("input.txt", a, input_size);
    process_sort(a, input_size, algo_name, rtime, cc);
    writeFile("output.txt", a, input_size);
    print_para_output(output_para, rtime, cc);
    // free memory
    freeArray1D(a, input_size);
}
void command_1_main_function(int argc, char *argv[])
{
    string algo_name = argv[2];
    string input_file = argv[3];
    string output_para = argv[4];

    cout << "Algorithm: " << GetAlgoType(algo_name) << endl;
    handle_command_1(algo_name, input_file, output_para);
}

//Command2
void handle_command_2(string algo_name, int input_size, string input_order, string output_para)
{
    int* a = array1DInit(input_size);
    if (a == NULL)
    {
        cout << "Error: do not have enough memory !\n";
        return;
    }

    ll rtime = 0;
    ll cc = 0;

    if (input_order == "-rand")
    {
        cout << "\nInput order: Randomize\n";
        cout << "-------------------------\n";
        GenerateData(a, input_size, 0);
    }

    else if (input_order == "-sorted")
    {
        cout << "\nInput order: Sorted\n";
        cout << "-------------------------\n";
        GenerateData(a, input_size, 1);
    }

    else if (input_order == "-rev")
    {
        cout << "\nInput order: Reverse sorted\n";
        cout << "-------------------------\n";
        GenerateData(a, input_size, 2);
    }

    else
    {
        cout << "\nInput order: Nearly sorted\n";
        cout << "-------------------------\n";
        GenerateData(a, input_size, 3);
    }

    writeFile("input.txt", a, input_size);
    process_sort(a, input_size, algo_name, rtime, cc);
    writeFile("output.txt", a, input_size);
    print_para_output(output_para, rtime, cc);
}
void command_2_main_function(int argc, char *argv[])
{
    string algo_name = argv[2];
    int input_size = stoi(argv[3]);
    string input_order = argv[4];
    string output_para = argv[4];

    cout << "Algorithm: " << GetAlgoType(algo_name) << endl;
    handle_command_2(algo_name, input_size, input_order, output_para);
}

//Command 3
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
void command_3_main_function(int argc, char *argv[])
{
    string mode = argv[1];
    string algo_name = argv[2];
    int input_size = stoi(argv[3]);
    string output_para = argv[4];

    getMode(mode);
    cout << "Algorithm: " << GetAlgoType(algo_name) << endl;
    cout << "Input size: " << input_size << "\n";
    handle_command_3(algo_name, input_size, output_para);
}

//Command 4
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
    cout << "Algorithm: " << GetAlgoType(algo_1_name) << " | " << GetAlgoType(algo_2_name) << endl;
    cout << "Input file: " << input_file << "\n";
    handle_command_4(input_file, algo_1_name, algo_2_name);
}

//Command 5
void handle_command_5(string input_order, int input_size,string algo_1, string algo_2){
    // create array
    int *a = array1DInit(input_size);
    if (a == NULL)
    {
        cout << "Error: do not have enough memory !\n";
        return;
    }

    if(input_order == "-rand"){
        GenerateRandomData(a, input_size);
    }else if(input_order == "-nsorted"){
        GenerateNearlySortedData(a, input_size);
    }
    else if(input_order == "-sorted"){
        GenerateSortedData(a, input_size);
    }else if(input_order == "-rev"){
        GenerateReverseData(a, input_size);
    }

    ll run_time[2] = {0, 0};
    ll count_cmp[2] = {0, 0};
    process_sort(a, input_size, algo_1, run_time[0], count_cmp[0]);
    process_sort(a, input_size, algo_2, run_time[1], count_cmp[1]);

    cout << "Running time: " << run_time[0] << " ms\t"
         << "| " << run_time[1] << " ms\n";
    cout << "Comparisions: " << count_cmp[0] << "\t| " << count_cmp[1] << "\n";
}
void command_5_main_function(int argc, char *argv[])
{
    string mode = argv[1];
    string algo_1_name = argv[2];
    string algo_2_name = argv[3];
    int input_size = stoi(argv[4]);
    string input_order = argv[5];

    getMode(mode);
    cout << "Algorithm: " << GetAlgoType(algo_1_name) << " | " << GetAlgoType(algo_2_name) << endl;
    cout << "Input size: " << input_size << "\n";
    cout << "Input order: " << GetInputOrder(input_order) << "\n";
    handle_command_5(input_order,input_size, algo_1_name, algo_2_name);
}

//Kiem tra dieu kiem command
void commandChecker(int argc, char *argv[]){
    if(argc > 2){
        string mode = argv[1];
        if(mode == "-c"){
            if(argc == 5){
                //Command 4
                command_4_main_function(argc, argv);
            }else if(argc == 6){
                //Command 5
                command_5_main_function(argc, argv);
            }
        }
        if(mode == "-a"){
            if(argc == 5){
                if(isVari(argv[3])){
                    //Command 3
                    command_3_main_function(argc, argv);
                }else{
                    //Command 1
                    command_1_main_function(argc, argv);
                }
            }else if(argc == 6){
                //Command 2
                command_2_main_function(argc, argv);
            }
        }
    }
}

int main(int argc, char *argv[])
{
    commandChecker(argc, argv);
}
