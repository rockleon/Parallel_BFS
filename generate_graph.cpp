#include <iostream>
#include <fstream>
#include <string>
#include <time.h>

using namespace std;

int main()
{
    int n, N = 10000, edges = 0;
    srand(time(0));

    cout << "Generating data...";

    ofstream file("dummy.txt");
    string st;

    for (int i = 0; i < N; i++)
    {
        st = "";
        for (int j = 0; j < N; j++)
        {
            if (i == j)
                n = 0;
            else
                n = rand() % 2;
            st = st + to_string(n) + ",";
            if (n == 1)
                edges++;
        }
        st.pop_back();
        file << st << endl;
    }

    file.close();
    cout << "\n\nFile Generated!" << endl;
    cout << "Number of edges: " << edges << endl
         << endl;
    return 0;
}