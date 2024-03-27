#include <iostream>
#include <chrono>
#include <time.h>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;
typedef unsigned long long ull;

#define NODE                20000
#define INPUT_SET           43

string get_str(int num)
{
    string str;
    while(num)
    {
        str += ((num % 10) + '0');
        num /= 10;
    }
    reverse(str.begin(), str.end());
    return str;
}

string get_data_file_path()
{
    string path = "data\\";
    path += "input_set_" + get_str(INPUT_SET);
    path += "\\";
    path += "input_set_" + get_str(INPUT_SET) + "_data.txt";
    return path;
}

struct edge
{
    int src, dest, w;
};

bool comp(edge &a, edge &b)
{
    return a.w < b.w;
}

int par[NODE + 1];

int find_par(int r)
{
    return (par[r] == r) ? r : par[r] = find_par(par[r]);
}

vector<edge>vec;

void read_input()
{
    string str = get_data_file_path();
    char fileName[100];
    for(int i = 0; i < str.size(); i++)
    {
        fileName[i] = str[i];
    }
    fileName[str.size()] = '\0';

    FILE * fp;
    fp = fopen(fileName, "r");
    edge temp;
    while(fscanf(fp, "%d %d %d", &temp.src, &temp.dest, &temp.w) == 3)
    {
        vec.push_back(temp);
    }
    fclose(fp);
}

bool is_full_connected(vector<edge>&vect)
{
    for(int i = 1; i <= NODE; i++)
    {
        par[i] = i;
    }
    for(int j = 0; j < 2; j++)
    {
        for(int i = 0; i < vect.size(); i++)
        {
            int u = find_par(vect[i].src);
            int v = find_par(vect[i].dest);
            if(u != v)
            {
                par[u] = v;
            }
        }
    }
    for(int i = 2; i <= NODE; i++)
    {
        int u = find_par(vect[i].src);
        int v = find_par(vect[i].dest);
        if(u != v)
        {
            return false;
        }
    }
    return true;
}

int main()
{
    auto startTime = std::chrono::high_resolution_clock::now();

    read_input();
    sort(vec.begin(), vec.end(), comp);
    for(int i = 1; i <= NODE; i++)
    {
        par[i] = i;
    }
    int cost = 0;
    vector<edge>res;
    edge temp;
    for(int i = 0; i < vec.size(); i++)
    {
        temp = vec[i];
        int a = find_par(temp.src);
        int b = find_par(temp.dest);
        if(a != b)
        {
            par[a] = b;
            cost += temp.w;
            res.push_back(temp);
        }
    }

    auto stopTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stopTime - startTime);
    double elapsedTime = duration.count() / 1000000.0;

    cout << "Total edges in the graph   = " << vec.size() << endl;
    cout << "Cost of this graph is      = " << cost << endl;
    cout << "Total required edges       = " << res.size() << endl;
    cout << "Required seconds           = " << (double)elapsedTime << endl;
    cout << "Full graph connected?      = " << is_full_connected(res) << endl;

    return 0;
}

/*

9
1 2 28
1 6 10
2 3 16
2 7 14
3 4 12
4 7 18
4 5 22
5 6 25
5 7 24

https://www.gatevidyalay.com/kruskals-algorithm-kruskals-algorithm-example/

*/
