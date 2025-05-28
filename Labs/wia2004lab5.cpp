#include <iostream>
#include <vector>
using namespace std;

void firstFit(vector<int> blockSize, int m, vector<int> processSize, int n) {
    vector<int> allocation(n, -1), originalBlockSize = blockSize;

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(blockSize[j] >= processSize[i]) {
                allocation[i] = j;
                blockSize[j] -= processSize[i];
                break;
            }
        }
    }

    cout << "Process Number\tProcess Size\tBlock Number\n";
    
    for(int i = 0; i < n; i++) {
        cout << (i + 1) << "\t\t" << processSize[i] << "\t\t";
        
        if(allocation[i] != -1) {
            cout << (allocation[i] + 1) << endl;
        } else {
            cout << "Not Allocated" << endl;
        }
    }

    cout << "\nRemaining Memory in Each Block:\n" << "Block Number\tOriginal Size\tRemaining Size\n";
    for(int j = 0; j < m; j++) {
        cout << (j + 1) << "\t\t" << originalBlockSize[j] << "\t\t" << blockSize[j] << "\n";
    }
}

int main() {
    int numberOfElements = 0;
    do {
        cin >> numberOfElements;
    } while(numberOfElements < 1);
    vector<int> blockSizes = {}, processSizes = {};

    for(int i = 0; i < numberOfElements; i++) {
        int blockSize = 0, processSize = 0;
        cout << "Enter your block size: ";
        do {
            cin >> blockSize;
        } while(blockSize < 1);

        cout << "Enter your process size: ";
        do {
            cin >> processSize;
        } while(processSize < 1);
        cout << endl;

        blockSizes.push_back(blockSize);
        processSizes.push_back(processSize);
    }

    firstFit(blockSizes, blockSizes.size(), processSizes, processSizes.size());
    return 0;
}