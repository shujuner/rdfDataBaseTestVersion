#include <iostream>
#include <time.h>
#include <vector>
#include <map>
#include<Windows.h>
#define N 300000
using namespace std;
void complex_n2(vector<int> v1,vector<int> v2)
{
    DWORD start_time = GetTickCount();
    int size_v1=v1.size();
    int size_v2=v2.size();
    int sum=0;
    for(int i=0;i<size_v1;i++)
    {
        for(int j=0;j<size_v2;j++)
        {
            if(v1[i]==v2[j])
            {
               sum++;
            }
        }
    }
    DWORD end_time = GetTickCount();
    cout << "complex_n2 run time is:" << (end_time - start_time) << "ms" << endl;
}
void complex_initial_n(vector<int> v1,vector<int> v2)
{
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
    DWORD end_time = GetTickCount();
    cout << "complex_initial_n run time is:" << (end_time - start_time) << "ms" << endl;
}
void complex_bitStore_n(vector<int> v1,vector<int> v2)
{
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
    int arr[10000];
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
    complex_n2(v1,v2);
    complex_initial_n(v1,v2);
    complex_bitStore_n(v1,v2);

    return 0;
}
