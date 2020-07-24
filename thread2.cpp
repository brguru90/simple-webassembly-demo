#include <iostream>
#include <string>
#include <unistd.h>

extern "C"
{
#include <cstdint>
#include <pthread.h>
}

using namespace std;

#define NUM_THREAD 10

extern "C" volatile void threadCompleteCallback(uint16_t sum);

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
    bool isActive = true;
};

typedef struct ThreadPropertyStruct ThreadProperties;

class myThreadClass
{
private:
    ThreadProperties threaddata[NUM_THREAD];

    static void *myThread(void *threadData)
    {
        ThreadProperties *localThreadData = (ThreadProperties *)threadData;
        // sleep(rand() % 5);
        int sum = 0;
        cout << "localThreadData->data.max" << localThreadData->data.max << endl;
        for (int i = 0; i < localThreadData->data.max; i++)
            localThreadData->data.sum += rand() % 100;
        cout << "Completed with message:" << localThreadData->data.message << endl;
        // pthread_exit(NULL);
        localThreadData->isActive = false;
        return NULL;
    }

    int start_thread()
    {
        pthread_t threads[NUM_THREAD];
        pthread_attr_t attr;
        void *status;
        time_t t;
        int rc, i = 0;
        cout << "startinng threads" << endl;

        srand((unsigned)time(&t));
        pthread_attr_init(&attr);
        pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

        for (i = 0; i < NUM_THREAD; i++)
        {
            threaddata[i].thread_id = i;
            threaddata[i].data.max = (rand() % 100) + 1;
            threaddata[i].data.message = "Thread id is " + to_string(i);
            // myThread(&threaddata[i]);
            cout << "startinng thread " << i << "max: " << threaddata[i].data.max << endl;
            // th[i] = std::thread(myThread, &threaddata[i]);
            rc = pthread_create(&threads[i], &attr, myThread, (void *)&threaddata[i]);
            if (rc)
            {
                // printf("----Error creating thread: %d----\n", rc);
                cout << "----Error creating thread:" << rc << " with id:" << i;
                exit(-1);
                // return 1;
            }
        }
        pthread_attr_destroy(&attr);
        // cout << "Joining threads" << endl;

        // for (i = 0; i < NUM_THREAD; i++)
        // {
        //     if (pthread_join(threads[i], &status))
        //     {
        //         cout << "Unable to join, id:" << i << endl;
        //         exit(-1);
        //         // return 2;
        //     }
        //     cout << "Completed thread with id:" << i << endl;
        // }

        // cout << "Totalling threads sums" << endl;
        // for (i = 0; i < NUM_THREAD; i++)
        // {
        //     // cout << threaddata[i].data.message << endl;
        //     // cout << threaddata[i].data.sum << endl;
        //     sum += threaddata[i].data.sum;
        // }
        // cout << "sum from class" << sum << endl;

        // pthread_exit(NULL);
        // monitor_threads();
        pthread_t monitoring_thread;
        if (pthread_create(&monitoring_thread, NULL, monitor_threads, (void *)&threaddata))
        {
            // printf("----Error creating thread: %d----\n", rc);
            cout << "----Error creating monitor thread:" << rc << endl;
            exit(-1);
            // return 1;
        }
    }

    static void *monitor_threads(void *th)
    {
        int sum = 0;
        ThreadProperties *threaddata = (ThreadProperties *)th;
        cout << "---Start monitoring background thread---" << endl;
        int i = 0, numOfThreadFinished = 0;
        while (numOfThreadFinished != NUM_THREAD)
        {
            numOfThreadFinished = 0;
            for (i = 0; i < NUM_THREAD; i++)
            {
                if (threaddata[i].isActive == false)
                {
                    numOfThreadFinished++;
                }
            }
            cout << ".";
            sleep(1);
        }
        cout << "\nAll threads finished execution" << endl;
        cout << "Totalling threads sums" << endl;
        for (i = 0; i < NUM_THREAD; i++)
        {
            // cout << threaddata[i].data.message << endl;
            // cout << threaddata[i].data.sum << endl;
            sum += threaddata[i].data.sum;
        }
        cout << "sum from monitor functionis " << sum << endl;
        threadCompleteCallback(sum);
    }

public:
    int sum = 0;
    myThreadClass()
    {
        start_thread();
    }
};

extern "C"
{
    int test()
    {
        myThreadClass *t = new myThreadClass();
        cout << "sum from text()" << t->sum << endl;
        // callback(t.sum);
        // pthread_exit(NULL);
        return t->sum;
    }
}

int main()
{
    cout << "Return to main" << test() << endl;
    return 0;
}
