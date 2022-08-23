#include<bits/stdc++.h>
using namespace std;

#define NODE                2000
#define MIN_EDGE_WEIGHT     1
#define MAX_EDGE_WEIGHT     100
#define EDGE                NODE * min(200, max(1, NODE - 10))

bool mark[NODE + 1][NODE + 1];

struct edge
{
    int src, dest, w;
};

int main()
{
    memset(mark, 0, sizeof mark);
    default_random_engine generator;
    uniform_int_distribution<int> distribution(MIN_EDGE_WEIGHT, MAX_EDGE_WEIGHT);

    edge temp;
    vector<edge>graph;

    srand(time(NULL));
    for(int i = 0; i < EDGE; i++)
    {
        do {
            temp.src = (rand() % NODE) + 1;
            temp.dest = (rand() % NODE) + 1;
        } while(mark[temp.src][temp.dest] || temp.src == temp.dest);
        temp.w = distribution(generator);
        graph.push_back(temp);

        mark[temp.src][temp.dest] = 1;
        mark[temp.dest][temp.src] = 1;
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

    //freopen("graph_edge.txt", "w", stdout);
    freopen("input_set_4.txt", "w", stdout);
    for(int i = 0; i < graph.size(); i++)
    {
        printf("%d %d %d\n", graph[i].src, graph[i].dest, graph[i].w);
    }

    return 0;
}
