#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void* foo() {
    pthread_t thisThread = pthread_self();
    while(1){
        printf("Created a new thread, ID: %lu\n", (unsigned long)thisThread);
        sleep(2);
    }
    return NULL;
}

void* foofoo() {
    pthread_t thisThread = pthread_self();
    while(1){
        printf("Created a second thread, ID: %lu\n", (unsigned long)thisThread);
        sleep(5);
    }
    return NULL;
}

int main() {
    pthread_t thread1;
    pthread_t thread2;
    pthread_create(&thread1, NULL, foo, NULL);
    pthread_create(&thread2, NULL, foofoo, NULL);
    sleep(10);
    pthread_cancel(thread1);
    pthread_cancel(thread2);
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    printf("Main thread finished.\n");
    return 0;
}