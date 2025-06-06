#include <iostream>
#include <vector>
#include <pthread.h>
#include <unistd.h>
#include <cstdlib>
#include <ctime>
#include <semaphore.h>
using namespace std;

void sleep_random(unsigned long long minimumTime_ms, unsigned long long maximumTime_ms) {
    int range = maximumTime_ms - minimumTime_ms + 1;
    int ms = minimumTime_ms + (rand() % range);
    usleep(ms * 1000);
}

struct PhilosopherArguments {
    unsigned long long index, numberOfRounds, numberOfPhilosophers;
    pthread_mutex_t *forks;
};

sem_t waiter;

void* philosopherFunction(void *v_arg) {
    PhilosopherArguments* arguments = static_cast<PhilosopherArguments*>(v_arg);
    unsigned long long index = arguments->index;
    unsigned long long numberOfRounds = arguments->numberOfRounds;
    unsigned long long numberOfPhilosophers = arguments->numberOfPhilosophers;
    pthread_mutex_t *forks = arguments->forks;
    unsigned long long leftIndex  = index;
    unsigned long long rightIndex = (index + 1ULL) % numberOfPhilosophers;

    for(unsigned long long i = 0; i < numberOfRounds; i++) {
        cout << "[Philosopher " << index << "] is thinking (round " << (i + 1) << ")" << endl;
        sleep_random(200, 600);
        sem_wait(&waiter);

        unsigned long long firstFork = min(leftIndex, rightIndex), secondFork = max(leftIndex, rightIndex);

        pthread_mutex_lock(&forks[firstFork]);
        pthread_mutex_lock(&forks[secondFork]);

        cout << "[Philosopher " << index << "] has picked up forks (" << leftIndex << ", " << rightIndex << "), eating..." << endl;
        sleep_random(200, 600);

        pthread_mutex_unlock(&forks[firstFork]);
        pthread_mutex_unlock(&forks[secondFork]);

        cout << "[Philosopher " << index << "] has put down forks (" << leftIndex << ", " << rightIndex << "), thus round " << (i + 1) << " is done." << endl;
        sem_post(&waiter);
    }

    cout << "[Philosopher " << index << "] Finished all " << numberOfRounds << " rounds." << endl;
    return nullptr;
}

int main() {
    srand(static_cast<unsigned>(time(nullptr)));
    unsigned long long numberOfPhilosophers = 0, numberOfRounds = 0;

    cout << "Enter the number of philosophers: ";
    while(!(cin >> numberOfPhilosophers) || numberOfPhilosophers < 2ULL) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Enter a whole number greater than 1: ";
    }

    cout << "Enter the number of think/eat rounds per philosopher: ";
    while(!(cin >> numberOfRounds) || numberOfRounds < 1ULL) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Enter a positive whole number: ";
    }

    sem_init(&waiter, 0, numberOfPhilosophers - 1);

    pthread_mutex_t *forks = new pthread_mutex_t[numberOfPhilosophers];
    for(unsigned long long i = 0; i < numberOfPhilosophers; i++) {
        pthread_mutex_init(&forks[i], nullptr);
    }

    pthread_t *threads = new pthread_t[numberOfPhilosophers];
    PhilosopherArguments *arguments = new PhilosopherArguments[numberOfPhilosophers];

    for(unsigned long long i = 0; i < numberOfPhilosophers; i++) {
        arguments[i].index = i;
        arguments[i].numberOfRounds = numberOfRounds;
        arguments[i].numberOfPhilosophers = numberOfPhilosophers;
        arguments[i].forks = forks;
        pthread_create(&threads[i], nullptr, philosopherFunction, &arguments[i]);
    }

    for(unsigned long long i = 0; i < numberOfPhilosophers; i++) {
        pthread_join(threads[i], nullptr);
    }

    cout << "All philosophers have finished dining." << endl;

    for(unsigned long long i = 0; i < numberOfPhilosophers; i++) {
        pthread_mutex_destroy(&forks[i]);
    }
    delete[] forks;
    delete[] threads;
    delete[] arguments;

    sem_destroy(&waiter);

    return 0;
}
