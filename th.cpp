#include<iostream>
#include<stdio.h>
#include <cstdlib>
#include<pthread.h>
#include<string>
#include<unistd.h>

using namespace std;

#define NUM_THREAD 5

struct  thread_data_struct{
    int thread_id;
    string message;
};


typedef struct thread_data_struct thread_data;
thread_data td[NUM_THREAD];

void *myThread(void *threaddata){
    sleep(rand() % 5);
    thread_data *data=(thread_data *)threaddata;
    printf("thread ID: %d\n",data->thread_id);
    // printf("thread message: %s\n",data->message.c_str());
    cout<<"thread message: "<<data->message<<endl;
    pthread_exit(NULL);
}


int main(){
    pthread_t threads[NUM_THREAD];
    pthread_attr_t attr;
    void *status;
    time_t t;
    int rc,i;

    srand((unsigned) time(&t));
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_JOINABLE);

    for(i=0;i<NUM_THREAD;i++){
        printf("creating thread with id:%d\n",i);

        td[i].thread_id=i;
        td[i].message="Thread with id: "+to_string(i);


        rc=pthread_create(&threads[i],&attr,myThread,(void *)&td[i]);

        if(rc){
            printf("----Error creating thread: %d----\n",rc);
            exit(-1);
        }
    }

    pthread_attr_destroy(&attr);
     for(i=0;i<NUM_THREAD;i++){
         if(pthread_join(threads[i],&status)){
             cout<<"Unable to join"<<endl;
             exit(-1);
         }
         cout<<"Completed thread with id:"<<i<<endl;
     }





    printf("Main thread exiting...\n");
    pthread_exit(NULL);
}