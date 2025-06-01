#include <iostream>
#include <vector>
#include <string>
using namespace std;

const int DISK_SIZE = 100;

struct File {
    string name;
    int startBlock, length;
};

class FileSystem {
private:
    vector<int> disk;
    vector<File> files;

public:
    FileSystem() {
        disk.resize(DISK_SIZE, 0);
    }

    bool allocateFile(string name, unsigned long long length) {
        unsigned long long start = -1, count = 0;

        for(unsigned long long i = 0; i < DISK_SIZE; ++i) {
            if(disk[i] == 0) {
                if(count == 0) {
                    start = i;
                }

                count++;
                
                if(count == length) {
                    break;
                }
            } else {
                count = 0;
            }
        }

        if(count == length) {
            for(int i = start; i < start + length; ++i) {
                disk[i] = 1;
            }
            
            files.push_back({name, start, length});
            cout << "File '" << name << "' allocated from block " << start << " to " << start + length - 1 << "." << endl;
            return true;
        } else {
            cout << "Not enough contiguous space to allocate File '" << name << "'." << endl;
            return false;
        }
    }

    void deallocateFile(string name) {
        for(unsigned long long i = 0; i < files.size(); i++) {
            if(files[i].name == name) {
                for(unsigned long long j = files[i].startBlock; j < files[i].startBlock + files[i].length; ++j) {
                    disk[j] = 0;
                }
                
                cout << "File '" << name << "' has been deallocated." << endl;
                files.erase(files.begin() + i);
                return;
            }
        }

        cout << "File '" << name << "' was not found." << endl;
    }

    void showDiskStatus() {
        cout << "Disk blocks: \n";
        for(unsigned long long i = 0; i < DISK_SIZE; i++) {
            cout << disk[i] << " ";
        }
        cout << endl;
    }

    void showFileTable() {
        cout << "--- File Table ---" << endl;
        for(const auto& file : files) {
            cout << "File: " << file.name << ", Start Block: " << file.startBlock << ", Length: " << file.length << "\n";
        }
        cout << endl;
    }
};

int main() {
    FileSystem fileSystem;
    int choice = 0;
    unsigned long long length = 0;
    string name = "";

    do {
        cout << "\n--- Sequential File Allocation Menu ---\n";
        cout << "1. Allocate File\n";
        cout << "2. Deallocate File\n";
        cout << "3. Show Disk Status\n";
        cout << "4. Show File Table\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch(choice) {
            case 1:
                cout << "Enter the file name: ";
                cin >> name;
                cout << "Enter the file size (in blocks): ";
                do {
                    cin >> length;
                } while(length < 1);
                fileSystem.allocateFile(name, length);
                break;
            case 2:
                cout << "Enter the file name to deallocate: ";
                cin >> name;
                fileSystem.deallocateFile(name);
                break;
            case 3:
                fileSystem.showDiskStatus();
                break;
            case 4:
                fileSystem.showFileTable();
                break;
            case 5:
                cout << "Exiting the system..." << endl;
                break;
            default:
                cout << "Invalid choice." << endl;
        }
    } while(choice != 5);

    return 0;
}