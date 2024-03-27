#include<bits/stdc++.h>
using namespace std;

#define INPUT_SET       43

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

string get_data_file_path()
{
    string path = "data\\";
    path += "input_set_" + get_str(INPUT_SET);
    path += "\\";
    path += "input_set_" + get_str(INPUT_SET) + "_data.txt";
    return path;
}

string get_output_file_path(int proc, int ser)
{
    string path = "data\\";
    path += "input_set_" + get_str(INPUT_SET);
    path += "\\";
    path += "input_set_" + get_str(INPUT_SET) + "_replicate__" + get_str(proc) + "__" + get_str(ser) + ".txt";
    return path;
}

int main()
{
    for(int proc = 8; proc <= 32; proc *= 2)
    {
        ifstream read_file(get_data_file_path());
        ofstream f[proc];
        for(int i = 0; i < proc; i++)
        {
            string str = get_output_file_path(proc, i + 1);
            f[i].open(str);
        }
        int a, b, c, cnt = 0;
        while(read_file >> a >> b >> c)
        {
            f[cnt % proc] << a << " " << b << " " << c << "\n";
            cnt++;
        }
        for(int i = 0; i < proc; i++)
        {
            f[i].close();
        }
    }

    return 0;
}
