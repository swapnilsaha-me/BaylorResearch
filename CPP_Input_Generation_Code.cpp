#include<bits/stdc++.h>
using namespace std;

#define NODE                15000
#define MIN_EDGE_WEIGHT     1
#define MAX_EDGE_WEIGHT     100
#define EDGE                NODE * min(15000, max(1, NODE - 10))

struct edge
{
    int src, dest, w;
};

//map<pair<int, int>, bool>mark;
bitset<NODE * NODE + 5>mark;
vector<edge>graph;
edge temp;

bool connected()
{
    vector<int>g[NODE + 1];
    bitset<NODE + 1>vis;
    int src, dest;
    queue<int>Q;

    for(int i = 0; i < graph.size(); i++)
    {
        g[graph[i].src].push_back(graph[i].dest);
        g[graph[i].dest].push_back(graph[i].src);
    }

    Q.push(1);
    vis[1] = 1;
    while(!Q.empty())
    {
        src = Q.front();
        Q.pop();
        for(int i = 0; i < g[src].size(); i++)
        {
            dest = g[src][i];
            if(!vis[dest])
            {
                vis[dest] = 1;
                Q.push(dest);
            }
        }
    }
    for(int i = 1; i <= NODE; i++)
    {
        if(!vis[i])
        {
            return false;
        }
    }
    return true;
}

int getHash(int a, int b)
{
    return (min(a, b) * NODE) + max(a, b);
}

int main()
{
    while(!connected())
    {
        mark.reset();
        graph.clear();
        default_random_engine generator;
        uniform_int_distribution<int> distribution(MIN_EDGE_WEIGHT, MAX_EDGE_WEIGHT);

        srand(time(NULL));
        for(int i = 0; i < EDGE; i++)
        {
            do
            {
                temp.src = (rand() % NODE) + 1;
                temp.dest = (rand() % NODE) + 1;
            }
            while(temp.src == temp.dest || mark[getHash(temp.src, temp.dest)]);
            temp.w = distribution(generator);
            graph.push_back(temp);

            mark[getHash(temp.src, temp.dest)] = 1;
        }

        /*
        int arr[105];
        int node[NODE + 1];
        memset(arr, 0, sizeof arr);
        memset(node, 0, sizeof node);

        cout << graph.size() << endl;
        for(int i = 0; i < graph.size(); i++)
        {
            arr[graph[i].w]++;
            node[graph[i].src]++;
            node[graph[i].dest]++;
        }

        for(int i = MIN_EDGE_WEIGHT; i <= MAX_EDGE_WEIGHT; i++)
        {
            cout << i << " : " << arr[i] << endl;
        }
        cout << endl;

        for(int i = 1; i <= NODE; i++)
        {
            cout << i << " : " << node[i] << endl;
        }
        */
    }

    //freopen("graph_edge.txt", "w", stdout);
    freopen("input_set_6.txt", "w", stdout);
    for(int i = 0; i < graph.size(); i++)
    {
        printf("%d %d %d\n", graph[i].src, graph[i].dest, graph[i].w);
    }

    return 0;
}
