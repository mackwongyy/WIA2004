#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <sstream>
#include <iomanip>
using namespace std;

int main() {
    unsigned long long numberOfFrames = 0, numberOfPages = 0;
    cout << "Enter the number of frames: ";
    while(!(cin >> numberOfFrames) || numberOfFrames < 1) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Enter a positive whole number for the number of frames: ";
    }

    cout << "Enter the number of page references: ";
    while(!(cin >> numberOfPages) || numberOfPages < 1) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Enter a positive whole number for the number of references: ";
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Enter all page references in one line, separated by spaces:";
    string line;
    getline(cin, line);
    istringstream iss(line);
    vector<unsigned long long> pages;
    unsigned long long x;
    
    while(iss >> x) {
        pages.push_back(x);
    }

    while(pages.size() != numberOfPages) {
        cout << "Expected " << numberOfPages << " numbers, but got " << pages.size() << ". Re-enter all page references in one line:";
        pages.clear();
        getline(cin, line);
        iss.clear();
        iss.str(line);
        
        while(iss >> x) {
            pages.push_back(x);
        }
    }

    vector<long long> frames(numberOfFrames, -1LL);
    queue<unsigned long long> fifoQueue;
    unordered_set<unsigned long long> loadedPages;
    unordered_map<unsigned long long, unsigned long long> pageToIndex;
    unsigned long long nextFreeFrame = 0, hits = 0, faults = 0;

    cout << setw(10) << "Reference";
    for(unsigned long long i = 0; i < numberOfFrames; i++) {
        cout << setw(10) << ("Frame " + to_string(i + 1));
    }
    cout << setw(10) << "  Hit/Fault" << endl;

    unsigned long long totalColumns = 1 + static_cast<int>(numberOfFrames) + 1;
    unsigned long long totalWidth = totalColumns * 10;
    for(unsigned long long i = 0; i < totalWidth + 1; i++) {
        cout << "-";
    }
    cout << endl;

    for(unsigned long long reference : pages) {
        bool isHit = (loadedPages.count(reference) > 0);
        
        if(isHit) {
            hits++;
        } else {
            faults++;
            
            if(nextFreeFrame < numberOfFrames) {
                frames[nextFreeFrame] = reference;
                fifoQueue.push(reference);
                loadedPages.insert(reference);
                pageToIndex[reference] = nextFreeFrame;
                nextFreeFrame++;
            } else {
                unsigned long long victim = fifoQueue.front();
                fifoQueue.pop();
                unsigned long long index = pageToIndex[victim];

                loadedPages.erase(victim);
                pageToIndex.erase(victim);

                frames[index] = reference;
                fifoQueue.push(reference);
                loadedPages.insert(reference);
                pageToIndex[reference] = index;
            }
        }

        cout << setw(10) << reference;
        for(unsigned long long i = 0; i < numberOfFrames; i++) {
            if(frames[i] == -1) {
                cout << setw(10) << "-";
            } else {
                cout << setw(10) << frames[i];
            }
        }
        cout << setw(10) << (isHit ? "   Hit" : "   Fault") << endl;
    }

    cout << "\nTotal References: " << numberOfPages << "\nHits             :" << hits << "\nFaults            :" << faults << endl;
    double hitRatio = (100.0 * static_cast<double>(hits)) / static_cast<double>(numberOfPages);
    cout << fixed << setprecision(2) << "Hit Ratio (%)    :" << hitRatio << endl;
    return 0;
}
