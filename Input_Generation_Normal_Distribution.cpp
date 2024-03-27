#include<bits/stdc++.h>
using namespace std;

#define NODE                    25000
#define MIN_EDGE_WEIGHT         1.0
#define MAX_EDGE_WEIGHT         100000.0
#define EDGE_DENSE              5

#define INPUT_SET               43

default_random_engine zero_one_generator;
uniform_int_distribution<int> zero_one_distribution(0, 1);

default_random_engine edge_dense_generator;
uniform_int_distribution<int> edge_dense_distribution(0, EDGE_DENSE - 1);
int weight_cnt, min_weight, max_weight;

class Generator
{
    std::default_random_engine generator;
    std::normal_distribution<double> distribution;
    double min;
    double max;
public:
    Generator(double min, double max):
        distribution((min + max) / 2, (max - min) / 6), min(min), max(max)
    {}

    double operator ()()
    {
        while (true)
        {
            double number = this->distribution(generator);
            if (number >= this->min && number <= this->max)
                return number;
        }
    }
};

int get_zero_one()
{
    return zero_one_distribution(zero_one_generator);
}

int get_edge_dense()
{
    return edge_dense_distribution(edge_dense_generator);
}

Generator g(MIN_EDGE_WEIGHT, MAX_EDGE_WEIGHT);

int get_weight()
{
    return g();
//    if(weight_cnt < 2)
//    {
//        if(weight_cnt == 0)
//        {
//            weight_cnt++;
//            return MIN_EDGE_WEIGHT;
//        }
//        else
//        {
//            weight_cnt++;
//            return MAX_EDGE_WEIGHT;
//        }
//    }
//    return distribution(generator);
}

struct edge
{
    int src, dest, w;
};

void generate_node_left_randomly(vector<int>&vv)
{
    for(int i = 1; i <= NODE; i++)
    {
        vv.push_back(i);
    }
    random_shuffle(vv.begin(), vv.end());
}

void generate_edge(int node, vector<edge>& vv)
{
    if(node + 1 >= NODE)
    {
        return;
    }
    vector<int>v1;
    // Need to find out the density for all the nodes.
    // For write-up.
    for(int i = node + 1; i <= NODE; i++)
    {
        /*
            Always connect the current node with (node + 1),
            so that the full graph is connected.
        */
        if(i == node + 1)
        {
            v1.push_back(i);
        }
        /*
            It will connect all other nodes based on a probability
            Let's say we have 100 nodes in our graph,
            Our current node number is 5,
            then it will connect some of the nodes starting from 7 to 100
            for which get_edge_dense() will return 0.
            As, it is a uniform distribution, so it will maintain the graph's density.
        */
        else if(!get_edge_dense())
        {
            v1.push_back(i);
        }
    }
    if(v1.size() > 1)
    {
        random_shuffle(v1.begin(), v1.end());
    }

    for(int i = 0; i < v1.size(); i++)
    {
        edge temp;
        if(get_zero_one())
        {
            temp.src = node;
            temp.dest = v1[i];
        }
        else
        {
            temp.src = v1[i];
            temp.dest = node;
        }
        temp.w = get_weight();
        vv.push_back(temp);
    }
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

string get_data_file_path()
{
    string path = "data\\";
    path += "input_set_" + get_str(INPUT_SET);
    path += "\\";
    path += "input_set_" + get_str(INPUT_SET) + "_data.txt";
    return path;
}

string get_metadata_file_path()
{
    string path = "data\\";
    path += "input_set_" + get_str(INPUT_SET);
    path += "\\";
    path += "input_set_" + get_str(INPUT_SET) + "_metadata.txt";
    return path;
}

int main()
{
    weight_cnt = 0;
    min_weight = 1e9;
    max_weight = 0;

    ofstream file_for_data, file_for_metadata;

    file_for_data.open(get_data_file_path());
    file_for_metadata.open(get_metadata_file_path());

    srand(unsigned(time(NULL)));

    /*
        Generate all the left nodes randomly;
        Example: edge(1 <--> 2) means 1 is left node,
                                and 2 is right node.
    */
    vector<int>node_left;
    generate_node_left_randomly(node_left);
    int total_edge = 0;
    for(int i = 0; i < node_left.size(); i++)
    {
        vector<edge>vv;
        generate_edge(node_left[i], vv);
        total_edge += vv.size();
        for(int j = 0; j < vv.size(); j++)
        {
            file_for_data << vv[j].src << " " << vv[j].dest << " " << vv[j].w << endl;
            min_weight = min(min_weight, vv[j].w);
            max_weight = max(max_weight, vv[j].w);
        }
    }

    file_for_data.close();


    file_for_metadata << "Total Edge    : " << total_edge << endl;
    file_for_metadata << "Total Node    : " << NODE << endl;
    file_for_metadata << "Min Weight    : " << min_weight << endl;
    file_for_metadata << "Max Weight    : " << max_weight << endl << endl;

    double total_edge_for_dense = (NODE * (NODE - 1)) / 2;
    file_for_metadata << "For fully connected graph it should contain " << (long long int)total_edge_for_dense << " edges." << endl;
    file_for_metadata << "But it contains " << total_edge << " edges." << endl;
    file_for_metadata << "So Density is: " << (double)((total_edge / total_edge_for_dense) * 100.0) << "%" << endl;

    file_for_metadata.close();

    return 0;
}
