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

    bool allocateFile(string name, int length) {
        int start = -1, count = 0;

        for(int i = 0; i < DISK_SIZE; ++i) {
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
            cout << "Not enough contiguous space to allocate file '" << name << "'." << endl;
            return false;
        }
    }

    void deallocateFile(string name) {
        for(int i = 0; i < files.size(); i++) {
            if(files[i].name == name) {
                for(int j = files[i].startBlock; j < files[i].startBlock + files[i].length; ++j) {
                    disk[j] = 0;
                }
                
                cout << "File '" << name << "' deallocated." << endl;
                files.erase(files.begin() + i);
                return;
            }
        }

        cout << "File '" << name << "' not found." << endl;
    }

    void showDiskStatus() {
        cout << "Disk blocks: \n";
        for(int i = 0; i < DISK_SIZE; i++) {
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
    FileSystem fs;
    int choice = 0, length = 0;
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
                cout << "Enter file name: ";
                cin >> name;
                cout << "Enter file size (in blocks): ";
                cin >> length;
                fs.allocateFile(name, length);
                break;
            case 2:
                cout << "Enter file name to deallocate: ";
                cin >> name;
                fs.deallocateFile(name);
                break;
            case 3:
                fs.showDiskStatus();
                break;
            case 4:
                fs.showFileTable();
                break;
            case 5:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice.\n";
        }
    } while (choice != 5);

    return 0;
}