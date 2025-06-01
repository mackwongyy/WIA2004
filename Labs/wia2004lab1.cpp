#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

int main() {
    unsigned long long n = 0, currentTime = 0, totalTurnaroundTime = 0, totalWaitingTime = 0;
    vector<unsigned long long> bursts(n), completions(n);
    cout << "Enter the number of processes: ";
    
    while(!(cin >> n) || n < 1) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Enter a positive integer: ";
    }

    for(unsigned long long i = 0; i < n; i++) {
        cout << "Enter the burst time for Process " << (i + 1) << ": ";
        
        while(!(cin >> bursts[i]) || bursts[i] < 1) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Enter a positive whole number for burst time: ";
        }
    }

    for(unsigned long long i = 0; i < n; i++) {
        currentTime += bursts[i];
        completions[i] = currentTime;
    }

    cout << "\nPID\tBurst\tCompletion\tTurnaround\tWaiting\n";
    for(unsigned long long i = 0; i < n; i++) {
        unsigned long long currentTurnaroundTime = completions[i];
        unsigned long long currentWaitingTime = currentTurnaroundTime - bursts[i];
        totalTurnaroundTime += currentTurnaroundTime;
        totalWaitingTime += currentWaitingTime;
        cout << setw(3) << (i + 1) << "\t" << setw(5) << bursts[i] << "\t" << setw(10) << completions[i] << "\t" << setw(11) << currentTurnaroundTime << "\t" << setw(7) << currentWaitingTime << endl;
    }

    double averageTurnaroundTime = static_cast<double>(totalTurnaroundTime) / n, averageWaitingTime = static_cast<double>(totalWaitingTime) / n;
    cout << fixed << setprecision(2) << endl;
    cout << "Average Turnaround Time: " << averageTurnaroundTime << "\nAverage Waiting Time: " << averageWaitingTime << endl;
    return 0;
}