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
    map<string, File> dir;
    int nextId;
public:
    FileSystem(int blocks = 50) {
        totalBlocks = blocks;
        disk.assign(blocks, -1);
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
    void createFile(string name, int size) {
        if (dir.count(name)) {
            cout << "exists\n";
            return;
        }
        auto b = allocate(size);
        if (b.size() < size) {
            cout << "no space\n";
            return;
        }
        File f;
        f.name = name;
        f.size = size;
        f.blocks = b;

        int id = nextId++;
        for (int x : b) disk[x] = id;

        dir[name] = f;
        cout << "created\n";
    }

    void deleteFile(string name) {
        if (!dir.count(name)) {
            cout << "no file\n";
            return;
        }
        for (int x : dir[name].blocks) disk[x] = -1;
        dir.erase(name);
        cout << "deleted\n";
    }

    void readFile(string name) {
        if (!dir.count(name)) {
            cout << "no file\n";
            return;
        }
        for (int x : dir[name].blocks) cout << x << " ";
        cout << "\n";
    }
    void defrag() {
        vector<int> newDisk(totalBlocks, -1);
        int k = 0;

        for (auto &p : dir) {
            File &f = p.second;
            vector<int> nb;
            for (int x : f.blocks) {
                newDisk[k] = disk[x];
                nb.push_back(k);
                k++;
            }
            f.blocks = nb;
        }

        disk = newDisk;
        cout << "done\n";
    }

    void mapBlocks() {
        for (int i = 0; i < totalBlocks; i++) {
            if (disk[i] == -1) cout << i << ":free  ";
            else cout << i << ":" << disk[i] << "  ";
            if ((i + 1) % 10 == 0) cout << "\n";
        }
        cout << "\n";
    }
};



