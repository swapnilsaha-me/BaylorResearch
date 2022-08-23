#include<bits/stdc++.h>
using namespace std;

struct edge
{
    int src, dest, w;
};

struct comp
{
    bool operator() (edge &a, edge &b)
    {
        return a.w > b.w;
    }
};

unordered_map<int, int>par;

int find_par(int r)
{
    stack<int>S;
    while(par[r] != r)
    {
        S.push(par[r]);
        r = par[r];
    }
    while(!S.empty())
    {
        par[S.top()] = r;
        S.pop();
    }
    return r;
}

bool edge_sort_comp(edge a, edge b)
{
    return a.w < b.w;
}

int main()
{
    //freopen("graph_edge.txt", "r", stdin);
    freopen("input_set_2.txt", "r", stdin);

    priority_queue<edge, vector<edge>, comp>Q;
    edge temp;
    while(scanf("%d %d %d", &temp.src, &temp.dest, &temp.w) == 3)
    {
        par[temp.src] = temp.src;
        par[temp.dest] = temp.dest;
        Q.push(temp);
    }

    int cost = 0;
    vector<edge>vv;
    while(!Q.empty())
    {
        temp = Q.top();
        Q.pop();
        int a = find_par(temp.src);
        int b = find_par(temp.dest);
        if(a != b)
        {
            par[a] = b;
            cost += temp.w;
            vv.push_back(temp);
        }
    }

    cout << endl << endl << endl;
    cout << "Cost is = " << cost << endl;
    cout << "Total Edges = " << vv.size() << endl;
    cout << "Edges are: " << endl;

    /*
    sort(vv.begin(), vv.end(), edge_sort_comp);
    for(int i = 0; i < vv.size(); i++)
    {
        cout << vv[i].src << " " << vv[i].dest << " " << vv[i].w << endl;
    }
    */
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
