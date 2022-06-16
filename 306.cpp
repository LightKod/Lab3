#include "739.cpp"
#include <vector>
#define MEASURE std::chrono::high_resolution_clock::now()
#define DURATION(start, end) std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

bool is_command_1(int argc, char* argv[])
{
    if (argc == 5)
    {
        string mode = argv[1];
        if (mode == "-a")
        {
            string line_3 = argv[3];
            if (!isVari(line_3))
            {
                return 1;
            }
        }
    }
    return 0;
}

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

bool is_command_2(int argc, char *argv[])
{
    if (argc == 6)
    {
        string mode = argv[1];
        if (mode == "-a")
        {
            return true;
        }
    }
    return false;
}

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

int main(int argc, char *argv[])
{
    if (is_command_1(argc, argv))
    {
        string algo_name = argv[2];
        string input_file = argv[3];
        string output_para = argv[4];
        handle_command_1(algo_name, input_file, output_para);
    }
    else if (is_command_2(argc, argv))
    {
        string algo_name = argv[2];
        int input_size = stoi(argv[3]);
        string input_order = argv[4];
        string output_para = argv[5];
        handle_command_2(algo_name, input_size, input_order, output_para);
    }
    else
        cout << "wrong";
    return 0;
}
/*
a.exe -a radix-sort 50 -rand -time
*/