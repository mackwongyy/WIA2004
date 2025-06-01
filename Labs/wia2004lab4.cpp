#include <iostream>
#include <vector>
using namespace std;

void bestFit(vector<unsigned long long> blockSizes, unsigned long long m, vector<unsigned long long> processSizes, unsigned long long n) {
    vector<unsigned long long> allocations(n, -1), originalBlockSizes = blockSizes;

    for(unsigned long long i = 0; i < n; i++) {
        unsigned long long bestIndex = -1;

        for(unsigned long long j = 0; j < m; j++) {
            if(blockSizes[j] >= processSizes[i]) {
                if(bestIndex == -1 || blockSizes[j] < blockSizes[bestIndex]) {
                    bestIndex = j;
                }
            }
        }

        if(bestIndex != -1) {
            allocations[i] = bestIndex;
            blockSizes[bestIndex] -= processSizes[i];
        }
    }

    cout << "Process Number\tProcess Size\tBlock Number\n";
    
    for(unsigned long long i = 0; i < n; i++) {
        cout << (i + 1) << "\t\t" << processSizes[i] << "\t\t";
        
        if(allocations[i] != -1) {
            cout << (allocations[i] + 1) << endl;
        } else {
            cout << "Not Allocated" << endl;
        }
    }

    cout << "\nRemaining Memory in Each Block:\n" << "Block Number\tOriginal Size\tRemaining Size\n";
    
    for(unsigned long long j = 0; j < m; j++) {
        cout << (j + 1) << "\t\t" << originalBlockSizes[j] << "\t\t" << blockSizes[j] << "\n";
    }
}

int main() {
    unsigned long long numberOfElements = 0;
    cout << "Enter the number of elements: ";
    do {
        cin >> numberOfElements;
    } while(numberOfElements < 1);
    cout << endl;
    vector<unsigned long long> blockSizes, processSizes;

    for(unsigned long long i = 0; i < numberOfElements; i++) {
        unsigned long long blockSize = 0, processSize = 0;
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

    bestFit(blockSizes, blockSizes.size(), processSizes, processSizes.size());
    return 0;
}