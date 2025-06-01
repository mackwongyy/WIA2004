#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

struct Process {
    int pid, arrival, burst, completion, turnaround, waiting;
};

struct BurstCompare {
    bool operator()(const Process* a, const Process* b) const {
        if(a->burst != b->burst) {
            return a->burst > b->burst;
        }
        
        return a->arrival > b->arrival;
    }
};

void SJF(vector<Process>& processes) {
    sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
        if (a.arrival != b.arrival)
            return a.arrival < b.arrival;
        return a.pid < b.pid;
    });

    priority_queue<Process*, vector<Process*>, BurstCompare> priorityQueue;
    int processIndex = 0, completedProcesses = 0, time = 0;

    while(completedProcesses < processes.size()) {
        while(processIndex < processes.size() && processes[processIndex].arrival <= time) {
            priorityQueue.push(&processes[processIndex]);
            processIndex++;
        }

        if(priorityQueue.empty()) {
            time = processes[processIndex].arrival;
            continue;
        }

        Process* currentProcess = priorityQueue.top();
        priorityQueue.pop();
        time += currentProcess->burst;
        currentProcess->completion = time;
        currentProcess->turnaround = currentProcess->completion - currentProcess->arrival;
        currentProcess->waiting = currentProcess->turnaround - currentProcess->burst;
        completedProcesses++;
    }

    cout << "\n--- Optimised Non-Preemptive SJF Scheduling ---" << endl;
    cout << "PID\tArrival\tBurst\tTAT\tWaiting\n";
    sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
        return a.pid < b.pid;
    });

    for(const auto& process : processes) {
        cout << process.pid << "\t" << process.arrival << "\t" << process.burst << "\t" << process.turnaround << "\t" << process.waiting << "\n";
    }
}

int main() {
    unsigned long long n = 0;
    vector<Process> processes(n);
    cout << "Enter the number of processes: ";
    
    while(!(cin >> n) || n < 1) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Enter a positive whole number: ";
    }

    for(unsigned long long i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        cout << "Enter the arrival time for Process " << processes[i].pid << ": ";

        while(!(cin >> processes[i].arrival) || processes[i].arrival < 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Enter a non-negative whole number: ";
        }

        cout << "Enter the burst time for Process " << processes[i].pid << ": ";
        
        while(!(cin >> processes[i].burst) || processes[i].burst < 1) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Enter a positive whole number: ";
        }
    }

    SJF(processes);
    return 0;
}