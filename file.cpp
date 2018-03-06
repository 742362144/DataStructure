//
// Created by Coder on 2018/3/6.
//

#include<iostream>
#include <vector>
#include<fstream>

using namespace std;


void Order(vector<int>& data) //bubble sort
{
    int count = data.size() ;
    int tag = false ; // 设置是否需要继续冒泡的标志位
    for ( int i = 0 ; i < count ; i++)
    {
        for ( int j = 0 ; j < count - i - 1 ; j++)
        {
            if ( data[j] > data[j+1])
            {
                tag = true ;
                int temp = data[j] ;
                data[j] = data[j+1] ;
                data[j+1] = temp ;
            }
        }
        if ( !tag )
            break ;
    }
}


int main()
{
    vector<int> data;
    ifstream in("d:/data.txt");
    if ( !in)
    {
        cout << "data file error!";
        exit(1);
    }
    int temp;
    while (!in.eof())
    {
        in >> temp;
        data.push_back(temp);
    }
    in.close(); // 关闭输入文件流
    Order(data);
    ofstream out("d:/result.txt");
    if (!out)
    {
        cout<<"result file error!";
        exit(1);
    }
    for (int i = 0 ; i < data.size() ; i++)
        out << data[i] << " ";
    out.close(); // 关闭输出文件流
    return 0;
}