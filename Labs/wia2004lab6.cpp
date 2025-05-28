#include <iostream>
#include <vector>
using namespace std;

void calculateBalance(const vector <vector<int> >& target, const vector< vector<int> > &allocation, vector< vector<int> > &balance, int p, int r) {
    for(int i = 0; i < p; i++) {
        for(int j = 0; j < r; j++) {
            balance[i][j] = target[i][j] - allocation[i][j];
        }
    }
}

bool isSafeAllocation(const vector < vector<int> > &allocation, const vector< vector<int> > &balance, const vector<int> &available, int p, int r, vector<int> &safeSequence) {
    vector<int> work = available;
    vector<bool> finished(p, false);
    int count = 0;

    while(count < p) {
        bool progress = false;
        
        for(int i = 0; i < p; i++) {
            if(!finished[i]) {
                bool canFinish = true;
                
                for(int j = 0; j < r; j++) {
                    if(balance[i][j] > work[j]) {
                        canFinish = false;
                        break;
                    }
                }
                
                if(canFinish) {
                    for(int j = 0; j < r; j++) {
                        work[j] += allocation[i][j];
                    }
                    
                    safeSequence[count++] = i;
                    finished[i] = true;
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
    int p, r;
    cout << "Enter number of processes: ";
    cin >> p;
    cout << "Enter number of resource types: ";
    cin >> r;

    vector<vector <int> > allocation(p, vector<int>(r));
    vector<vector <int> > target(p, vector<int>(r));
    vector<int> available(r);

    cout << "Enter the Allocation Matrix, where the horizontal axis represents the processes, and the vertical axis represents the resources:-" << endl;
    for(int i = 0; i < p; i++) {
        for(int j = 0; j < r; j++) {
            cin >> allocation[i][j];
        }
    }

    cout << "Enter the Target Matrix, where the horizontal axis represents the processes, and the vertical axis represents the resources:-" << endl;
    for(int i = 0; i < p; i++) {
        for(int j = 0; j < r; j++) {
            cin >> target[i][j];
        }
    }

    cout << "Enter all the available resources (with a total of " << r << " values): ";
    for(int j = 0; j < r; j++) {
        cin >> available[j];
    }

    vector< vector<int> > balance(p, vector<int>(r));
    calculateBalance(target, allocation, balance, p, r);

    vector<int> safeSequence(p);

    if(isSafeAllocation(allocation, balance, available, p, r, safeSequence)) {
        cout << "The resource allocation is safe.\nThe safe sequence is: ";
        for(int i = 0; i < p; i++) {
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