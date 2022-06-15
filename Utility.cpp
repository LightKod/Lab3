#include <fstream>
#include <sstream>
#include <cstring>
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

void PrintArray(int* a, int n) {
	for (int i = 0; i < n; i++)
	{
		cout << a[i] << " ";
		if ((i+1) % 10 == 0) cout << endl;
	}
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
