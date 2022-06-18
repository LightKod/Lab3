//void writeFile(string path, int *a, int n)
// {
//     ofstream ofs(path);
//     if (ofs.is_open())
//     {
//         printArray(a, n, ofs);
//         ofs.close();
//     }
// }
// int *loadFile(string path, int &n)
// {
//     ifstream ifs(path);
//     if (ifs.is_open())
//     {
//         ifs >> n;
//         int *a = array1DInit(n);
//         for (int i = 0; i < n; i++)
//         {
//             ifs >> a[i];
//         }
//         ifs.close();
//         return a;
//     }
//     return NULL;
// }