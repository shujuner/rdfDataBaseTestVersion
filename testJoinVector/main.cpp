#include <iostream>
#include <time.h>
#include <vector>
#include <set>
#include <map>
#include<Windows.h>
#define N 10000
using namespace std;
void complex_n2(vector<int> v1,vector<int> v2)
{
    cout<<"complex_n2中的数据为:"<<endl;
    for(int val1:v1)
    {
        cout<<val1<<" ";
    }
    cout<<endl;
    for(int val2:v2)
    {
        cout<<val2<<" ";
    }
    cout<<endl;
    DWORD start_time = GetTickCount();
    int size_v1=v1.size();
    int size_v2=v2.size();
    set<int> s;
    for(int i=0;i<size_v1;i++)
    {
        for(int j=0;j<size_v2;j++)
        {
            if(v1[i]==v2[j])
            {
               s.insert(v1[i]);
               break;
            }
        }
    }
    cout<<"sum="<<s.size()<<endl;
    DWORD end_time = GetTickCount();
    cout << "complex_n2 run time is:" << (end_time - start_time) << "ms" << endl;
}
void complex_initial_n(vector<int> v1,vector<int> v2)
{
//    cout<<"complex_initial_n中的数据为:"<<endl;
//    for(int val1:v1)
//    {
//        cout<<val1<<" ";
//    }
//    cout<<endl;
//    for(int val2:v2)
//    {
//        cout<<val2<<" ";
//    }
//    cout<<endl;
    DWORD start_time = GetTickCount();
    int size_v1=v1.size();
    int size_v2=v2.size();
    int sum=0;
    map<int,int> m;
    for(int i=0;i<size_v1;i++)
    {
        m[v1[i]]=1;
    }
   // DWORD end_time = GetTickCount();
  //  cout << "complex_initial_n initial time is:" << (end_time - start_time) << "ms" << endl;
    for(int i=0;i<size_v2;i++)
    {
        if(m[v2[i]]==1)
        {
            sum++;
        }
    }
    cout<<"sum="<<sum<<endl;
    DWORD end_time = GetTickCount();
    cout << "complex_initial_n run time is:" << (end_time - start_time) << "ms" << endl;
}
void complex_bitStore_n(vector<int> v1,vector<int> v2)
{
//    cout<<"complex_bitStore_n中的数据为:"<<endl;
//    for(int val1:v1)
//    {
//        cout<<val1<<" ";
//    }
//    cout<<endl;
//    for(int val2:v2)
//    {
//        cout<<val2<<" ";
//    }
//    cout<<endl;
    double run_time;
	_LARGE_INTEGER time_start;
	_LARGE_INTEGER time_over;
	double dqFreq;
	LARGE_INTEGER f;
    QueryPerformanceFrequency(&f);
    dqFreq=(double)f.QuadPart;
    QueryPerformanceCounter(&time_start);
    int size_v1=v1.size();
    int size_v2=v2.size();
    int sum=0;
    int *arr=new int[100000];
    for(int i=0;i<size_v1;i++)
    {
        int id1=v1[i];
        arr[(id1-1)>>5] |= (1<<(id1&31));
    }
    //DWORD end_time = GetTickCount();
    //cout << "complex_bitStore_n initial time is:" << (end_time - start_time) << "ms" << endl;
    for(int i=0;i<size_v2;i++)
    {
        int id2=v2[i];
        if(arr[(id2-1)>>5] & (1<<(id2&31)))
        {
            sum++;
        }
    }
    QueryPerformanceCounter(&time_over);
    run_time=1000000*(time_over.QuadPart-time_start.QuadPart)/dqFreq;
    printf("\nrun_time %fus\n",run_time);
    cout<<"sum="<<sum<<endl;
    delete []arr;
}

void multi_complex_bitStore_n(vector<vector<int>> allInterResult)
{
     double run_time;
	_LARGE_INTEGER time_start;
	_LARGE_INTEGER time_over;
	double dqFreq;
	LARGE_INTEGER f;
    QueryPerformanceFrequency(&f);
    dqFreq=(double)f.QuadPart;
    QueryPerformanceCounter(&time_start);//开始计时

    int sizeOfInter=allInterResult.size();
    int** arr = new int*[10];
    for(int i=0; i<10; ++i) {
        arr[i] = new int[1000000];
    }
    int sum=0;
    for(int i=0;i<sizeOfInter-1;i++)
    {
        int lengthInter=allInterResult[i].size();
        for(int j=0;j<lengthInter;j++)
        {
            int id1=allInterResult[i][j];
            arr[i][(id1-1)>>5] |= (1<<(id1&31));
        }
    }
    int lastInterIndex=sizeOfInter-1;
    int lastSize=allInterResult[lastInterIndex].size();
    for(int i=0;i<lastSize;i++)
    {
        int id2=allInterResult[lastInterIndex][i];
        int tempCount=0;
        for(int j=0;j<lastInterIndex;j++)
        {
            if(arr[j][(id2-1)>>5] & (1<<(id2&31)))
            {
                tempCount++;
            }
            else
            {
                break;
            }
        }
        if(tempCount==lastInterIndex)
        {
            sum++;
        }
    }

    QueryPerformanceCounter(&time_over);//结束计时
    run_time=1000000*(time_over.QuadPart-time_start.QuadPart)/dqFreq;
    printf("\n multi_complex_bitStore_n run_time %fus\n",run_time);
    cout<<"sum="<<sum<<endl;
    for(int i=0; i<10; i++)
    {
        delete[] arr[i];
    }
    delete[] arr;
}
int main()
{
    vector<int> v1,v2;
    srand((unsigned)time(NULL));
    for(int i = 0; i < N;i++ )
    {
        v1.push_back(rand()%N);
        v2.push_back(rand()%N);
    }
    //complex_n2(v1,v2);
    complex_initial_n(v1,v2);
    vector<vector<int>> v;
    v.push_back(v1);
    v.push_back(v2);
    complex_bitStore_n(v1,v2);
    multi_complex_bitStore_n(v);

    return 0;
}
