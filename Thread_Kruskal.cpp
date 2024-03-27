#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <string>
#include <ppl.h>
#include <concurrent_vector.h>

using namespace concurrency;
using namespace std;

#define     MAX_COST        100000
#define     NODE            15000
#define     INPUT_SET       43
#define     PROCESSOR       16

string get_num(int num)
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

string get_multiple_data_file_path(int proc, int ser)
{
    string path = "data\\";
    path += "input_set_" + get_str(INPUT_SET);
    path += "\\";
    path += "input_set_" + get_str(INPUT_SET) + "_replicate__" + get_str(proc) + "__" + get_str(ser) + ".txt";
    return path;
}


struct edge
{
    int src, dest, w;
};

concurrent_vector<edge>vec[PROCESSOR * 2 + 1]; // For map reduce steps
int parent_dict[PROCESSOR * 2 + 1][NODE + 1];

const int COST_DIV = (MAX_COST / PROCESSOR) + 1;

void inline insert_vec(edge& temp)
{
    int div = (int)(temp.w / COST_DIV);
    vec[div].push_back(temp);
}

void inline read_file(char file_name[])
{
    FILE* fp;
    if(fopen_s(&fp, file_name, "r") == 0)
    {
        edge temp;
        while (fscanf_s(fp, "%d %d %d", &temp.src, &temp.dest, &temp.w) == 3)
        {
            insert_vec(temp);
        }
        fclose(fp);
    }
}

inline bool comp(edge& a, edge& b)
{
    return a.w < b.w;
}

void read_input()
{
    // Create a parallel task for each file
    concurrency::parallel_for(0, PROCESSOR, [&](int i)
    {
        string str = get_multiple_data_file_path(PROCESSOR, i + 1);
        char file_name[100];
        for(int j = 0; j < str.size(); j++)
        {
            file_name[j] = str[j];
        }
        file_name[str.size()] = '\0';
        read_file(file_name);
    });
}

void sort_input()
{
    concurrency::parallel_for(0, PROCESSOR, [&](int i)
    {
        sort(vec[i].begin(), vec[i].end(), comp);
    });
}

void map_reduce(int nodeIdx, int idx1, int idx2)
{
    for (int i = 0; i <= NODE; i++)
    {
        parent_dict[nodeIdx][i] = i;
    }
    for (int i = 0; i < vec[idx1].size(); i++)
    {
        stack<int>s;
        edge temp = vec[idx1][i];
        int a = temp.src;
        int b = temp.dest;
        while (parent_dict[nodeIdx][a] != a)
        {
            s.push(parent_dict[nodeIdx][a]);
            a = parent_dict[nodeIdx][a];
        }
        while (!s.empty())
        {
            parent_dict[nodeIdx][s.top()] = a;
            s.pop();
        }

        while (parent_dict[nodeIdx][b] != b)
        {
            s.push(parent_dict[nodeIdx][b]);
            b = parent_dict[nodeIdx][b];
        }
        while (!s.empty())
        {
            parent_dict[nodeIdx][s.top()] = b;
            s.pop();
        }

        if (a != b)
        {
            parent_dict[nodeIdx][a] = b;
            vec[nodeIdx].push_back(temp);
        }
    }
    for (int i = 0; i < vec[idx2].size(); i++)
    {
        stack<int>s;
        edge temp = vec[idx2][i];
        int a = temp.src;
        int b = temp.dest;
        while (parent_dict[nodeIdx][a] != a)
        {
            s.push(parent_dict[nodeIdx][a]);
            a = parent_dict[nodeIdx][a];
        }
        while (!s.empty())
        {
            parent_dict[nodeIdx][s.top()] = a;
            s.pop();
        }

        while (parent_dict[nodeIdx][b] != b)
        {
            s.push(parent_dict[nodeIdx][b]);
            b = parent_dict[nodeIdx][b];
        }
        while (!s.empty())
        {
            parent_dict[nodeIdx][s.top()] = b;
            s.pop();
        }

        if (a != b)
        {
            parent_dict[nodeIdx][a] = b;
            vec[nodeIdx].push_back(temp);
        }
    }
}

void map_reduce()
{
    int nodeAdd = 0, mergeNodeAdd = 0, mul = 1;

    while (mul <= PROCESSOR)
    {
        mergeNodeAdd = nodeAdd;
        nodeAdd += (PROCESSOR / mul);
        mul *= 2;
        concurrency::parallel_for(0, PROCESSOR / mul, [&](int i)
        {
//            cout << nodeAdd + i << " " << mergeNodeAdd + (i * 2) << " " << mergeNodeAdd + (i * 2) + 1 << ", " << endl;
            map_reduce(nodeAdd + i, mergeNodeAdd + (i * 2), mergeNodeAdd + (i * 2) + 1);
        });
    }
}

int par[NODE + 1];

int find_par(int r)
{
    return (par[r] == r) ? r : par[r] = find_par(par[r]);
}

bool is_full_connected(concurrent_vector<edge>&vect)
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
    sort_input();
    map_reduce();

    auto stopTime = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stopTime - startTime);
    double elapsedTime = duration.count() / 1000000.0;

    for (int i = 0; i < PROCESSOR; i++)
    {
        for (int j = 1; j < vec[i].size(); j++)
        {
            if (vec[i][j - 1].w > vec[i][j].w)
            {
                cout << "Not Sorted : " << i << " - " << j << endl;
                break;
            }
        }
    }

    // Display the content of each file

    int total_cost = 0;
    for (int i = 0; i < vec[PROCESSOR * 2 - 2].size(); i++)
    {
        total_cost += vec[PROCESSOR * 2 - 2][i].w;
    }

    int sum = 0;
    for (int i = 0; i < PROCESSOR; i++)
    {
        cout << "Vec " << i << " : " << vec[i].size() << endl;
        sum += vec[i].size();
    }

    cout << "\n\n";
    cout << "Total edges in the graph   = " << sum << endl;
    cout << "Cost of this graph is      = " << total_cost << endl;
    cout << "Total required edges       = " << vec[PROCESSOR * 2 - 2].size() << endl;
    cout << "Required seconds           = " << (double)elapsedTime << endl;
    cout << "Full graph connected?      = " << is_full_connected(vec[PROCESSOR * 2 - 2]) << endl;

    return 0;
}

