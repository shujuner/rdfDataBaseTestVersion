#include <iostream>
#include <vector>
#include "vector.h"
#include<Windows.h>
#include <time.h>
#define N 10000000
using namespace std;
class predicate
{
private:
    int pVal;
    int * objExist;
    lni::vector<int> objVector;
public:
    predicate()
    {
        this->objExist=new int[10000];
    }
    bool judgeObjExist(int obj)
    {

    }
    void push_object(int obj)
    {
        this->objVector.push_back(obj);
    }
//    lni::vector selectObj(int obj)
//    {
//
//    }
};
int main()
{
    DWORD start_time,end_time;
    double run_time;
	_LARGE_INTEGER time_start;
	_LARGE_INTEGER time_over;
	double dqFreq;
	LARGE_INTEGER f;

    lni::vector<int> lv;
    vector<int> v;
    int *dArray=new int[N+1];
    srand((unsigned)time(NULL));
    QueryPerformanceFrequency(&f);
    dqFreq=(double)f.QuadPart;
    QueryPerformanceCounter(&time_start);
    for(int i=0;i<N;i++)
    {
        lv.push_back(rand()%N);
    }
    QueryPerformanceCounter(&time_over);
    run_time=1000000*(time_over.QuadPart-time_start.QuadPart)/dqFreq;
    printf("\n lni::vec run_time %fus\n",run_time);


    QueryPerformanceFrequency(&f);
    dqFreq=(double)f.QuadPart;
    QueryPerformanceCounter(&time_start);
    for(int i=0;i<N;i++)
    {
        v.push_back(rand()%N);
    }
    QueryPerformanceCounter(&time_over);
    run_time=1000000*(time_over.QuadPart-time_start.QuadPart)/dqFreq;
    printf("\n stl::vec run_time %fus\n",run_time);

    QueryPerformanceFrequency(&f);
    dqFreq=(double)f.QuadPart;
    QueryPerformanceCounter(&time_start);
    for(int i=0;i<N;i++)
    {
        dArray[i]=rand()%N;
    }
    QueryPerformanceCounter(&time_over);
    run_time=1000000*(time_over.QuadPart-time_start.QuadPart)/dqFreq;
    printf("\n dArray run_time %fus\n",run_time);

    return 0;
}
