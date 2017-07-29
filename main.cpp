#include <iostream>
#include <pthread.h>
#include <sys/epoll.h>
#include <sys/eventfd.h>
#include <zconf.h>
// By George
int THREAD_COUNT=1;
int EPOLL_SIZE=5;
pthread_mutex_t mutex;

using namespace std;


int tempFd;

void* childThread(void* ptr){
    char array[]={'1'};
    write(tempFd,array,8);

}



void* mainThread(void* ptr){
    //创建epoll获取epoll的Fd句柄
    int epollFd = epoll_create(EPOLL_SIZE);


    epoll_event *event = new epoll_event;

    event->data.fd=tempFd;
    event->events=EPOLLIN;
    epoll_ctl(epollFd, EPOLL_CTL_ADD, tempFd, event);
    
    while(true){
        epoll_event *events = event;

        int epollDataSize = epoll_wait(epollFd, events,5,2000);

        cout<<"loopering...data:"<<endl;

        for (int i = 0; i < epollDataSize; ++i) {
            int fd = events[i].data.fd;
            char dataArray[8];
            read(fd,dataArray,8);
            cout<<dataArray<<endl;
        }


    }
}

int main() {


    tempFd = eventfd(0,EFD_CLOEXEC | EFD_NONBLOCK);
    pthread_t threadArray[THREAD_COUNT];

    for (int i = 0; i < THREAD_COUNT; i++) {
        pthread_create(&threadArray[i],NULL,childThread,NULL);
    }

    pthread_t mainThreadArray[1];
    for (int i = 0; i < 1; i++) {
        pthread_create(&mainThreadArray[i],NULL,mainThread,NULL);
    }

    pthread_exit(NULL);
}
