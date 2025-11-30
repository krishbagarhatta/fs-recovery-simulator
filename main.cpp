#include <bits/stdc++.h>
using namespace std;

struct File {
    string name;
    int size;
    vector<int> blocks;
};

class FileSystem {
    int totalBlocks;
    vector<int> disk;
    vector<bool> bad;

    map<string, File> dir;
    int nextId;
public:
    FileSystem(int blocks = 50) {
        totalBlocks = blocks;
        disk.assign(blocks, -1);
        bad.assign(blocks, false);
        nextId = 1;
    }
    void status() {
        int freeCount = 0;
        for (int b : disk) if (b == -1) freeCount++;
        cout << "Total Blocks: " << totalBlocks << "\n";
        cout << "Free Blocks: " << freeCount << "\n";
        cout << "Files: " << dir.size() << "\n";
    }

    void ls() {
        if (dir.empty()) {
            cout << "no files\n";
            return;
        }
        for (auto &p : dir) {
            cout << p.first << ": ";
            for (int b : p.second.blocks) cout << b << " ";
            cout << "\n";
        }
    }

    vector<int> allocate(int n) {
        vector<int> v;
        for (int i = 0; i < totalBlocks; i++) {
            if (disk[i] == -1) v.push_back(i);
            if (v.size() == n) return v;
        }
        return {};
    }

