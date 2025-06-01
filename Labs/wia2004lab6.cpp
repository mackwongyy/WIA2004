#include <iostream>
#include <vector>
using namespace std;

void calculateBalance(const vector <vector<unsigned long long> >& maxMatrix, const vector< vector<unsigned long long> > &allocationMatrix, vector< vector<unsigned long long> > &neededResources, unsigned long long numberOfProcesses, unsigned long long numberOfResources) {
    for(unsigned long long i = 0; i < numberOfProcesses; i++) {
        for(unsigned long long j = 0; j < numberOfResources; j++) {
            neededResources[i][j] = maxMatrix[i][j] - allocationMatrix[i][j];
        }
    }
}

bool isSafeAllocation(const vector < vector<unsigned long long> > &allocationMatrix, const vector< vector<unsigned long long> > &neededResources, const vector<unsigned long long> &availableResources, unsigned long long numberOfProcesses, unsigned long long numberOfResources, vector<unsigned long long> &safeSequence) {
    vector<unsigned long long> work = available;
    vector<bool> finishedProcesses(numberofProcesses, false);
    unsigned long long count = 0;

    while(count < numberOfProcesses) {
        bool progress = false;
        
        for(unsigned long long i = 0; i < numberOfProcesses; i++) {
            if(!finishedProcesses[i]) {
                bool canFinish = true;
                
                for(unsigned long long j = 0; j < numberOfProcesses; j++) {
                    if(neededResources[i][j] > work[j]) {
                        canFinish = false;
                        break;
                    }
                }
                
                if(canFinish) {
                    for(unsigned long long j = 0; j < numberOfResources; j++) {
                        work[j] += allocationMatrix[i][j];
                    }
                    
                    safeSequence[count++] = i;
                    finishedProcesses[i] = true;
                    progress = true;
                }
            }
        }

        if(!progress)
            return false;
    }

    return true;
}

int main() {
    unsigned long long numberOfProcesses = 0, numberOfResources = 0;
    cout << "Enter the number of processes: ";
    do {
        cin >> p;
    } while(numberOfProcesses < 1);
    cout << "Enter the number of resource types: ";
    do {
        cin >> r;
    } while(numberOfResources < 1);
    vector<vector <unsigned long long> > allocationMatrix(p, vector<unsigned long long>(r)), maxMatrix(p, vector<unsigned long long>(r));
    vector<unsigned long long> availableResources(r);

    cout << "Enter the Allocation Matrix, where the horizontal axis represents the processes, and the vertical axis represents the resources:-" << endl;
    for(unsigned long long i = 0; i < numberOfProcesses; i++) {
        for(unsigned long long j = 0; j < numberOfResources; j++) {
            do {
                cin >> allocationMatrix[i][j];
            } while(allocationMatrix[i][j] < 0);
        }
    }

    cout << "Enter the Max Matrix, where the horizontal axis represents the processes, and the vertical axis represents the resources:-" << endl;
    for(unsigned long long i = 0; i < numberOfProcesses; i++) {
        for(unsigned long long j = 0; j < numberOfResources; j++) {
            do {
                cin >> maxMatrix[i][j];
            } while(maxMatrix[i][j] < 0);
        }
    }

    cout << "Enter all the available resources (with a total of " << r << " values): ";
    for(unsigned long long j = 0; j < numberOfResources; j++) {
        do {
            cin >> availableResources[j];
        } while(availableResources[j] < 0);
    }

    vector< vector<unsigned long long> > neededResources(numberOfProcesses, vector<unsigned long long>(numberOfResources));
    calculateBalance(maxMatrix, allocationMatrix, neededResources, numberOfProcesses, numberofResources);
    vector<unsigned long long> safeSequence(numberOfProcesses);

    if(isSafeAllocation(allocationMatrix, neededResources, availableResources, numberOfProcesses, numberOfResources, safeSequence)) {
        cout << "The resource allocation is safe.\nThe safe sequence is: ";
        for(unsigned long long i = 0; i < numberofProcesses; i++) {
            cout << "Process " << safeSequence[i] + 1;
            
            if(i != p - 1) {
                cout << " ---> ";
            }
        }
        cout << endl;
    } else {
        cout << "The resource allocation is unsafe." << endl;
    }

    return 0;
}