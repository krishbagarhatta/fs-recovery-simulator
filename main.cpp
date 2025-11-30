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
