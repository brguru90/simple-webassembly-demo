#include <iostream>
#include <thread>
#include <string>
#include <unistd.h>
#include <vector>

using namespace std;

#define NUM_THREAD 5

typedef struct ThreadDataStruct
{
    string message;
    int max;
    int sum = 0;
} ThreadData;

struct ThreadPropertyStruct
{
    int thread_id;
    ThreadData data;
};

typedef struct ThreadPropertyStruct ThreadProperties;

class myThreadClass
{
private:
    ThreadProperties threaddata[NUM_THREAD];

    static void myThread(ThreadProperties *threadData)
    {
        sleep(rand() % 5);
        // int sum = 0;
        for (int i = 0; i < threadData->data.max; i++)
        {
            threadData->data.sum += rand() % 100;
        }
    }

public:
    int sum = 0;
    myThreadClass()
    {
        time_t t;
        thread th[NUM_THREAD];
        // vector<thread> th(NUM_THREAD);
        cout << "startinng threads" << endl;

        srand((unsigned)time(&t));
        int i = 0;
        for (i = 0; i < NUM_THREAD; i++)
        {
            threaddata[i].thread_id = i;
            threaddata[i].data.max = rand() % 100;
            threaddata[i].data.message = "Thread id is " + to_string(i);
            // myThread(&threaddata[i]);
            cout << "startinng thread "<<i << endl;
            th[i] = std::thread(myThread, &threaddata[i]);
        }
        // cout << "Joining threads" << endl;
        // for (i = 0; i < NUM_THREAD; i++)
        // {
        //     th[i].join();
        // }
        // cout << "Totalling threads sums" << endl;
        // for (i = 0; i < NUM_THREAD; i++)
        // {
        //     // cout << threaddata[i].data.message << endl;
        //     // cout << threaddata[i].data.sum << endl;
        //     sum += threaddata[i].data.sum;
        // }
    }
};

extern "C"
{
    int test()
    {
        myThreadClass t;
        // myThreadClass t();
        return t.sum;
    }
}
// int main(){
//     cout<<test()<<endl;
//     return 0;
// }
