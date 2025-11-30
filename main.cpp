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
    void crash(int n) {
    for (int i = 0; i < n; i++) {
        int x = rand() % totalBlocks;
        bad[x] = true;
        disk[x] = -2;
    }
    cout << "crashed\n";
}
void recover() {
    for (auto &p : dir) {
        vector<int> good;
        for (int x : p.second.blocks) {
            if (!bad[x] && disk[x] != -2) good.push_back(x);
        }
        p.second.blocks = good;
    }
    cout << "recovered\n";
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
int main() {
    FileSystem fs(50);

    cout << "Commands: status ls create delete read defrag map exit\n";

    string c;
    while (true) {
        cout << "> ";
        cin >> c;

        if (c == "exit") break;
        else if (c == "status") fs.status();
        else if (c == "ls") fs.ls();
        else if (c == "create") {
            string n; int s;
            cin >> n >> s;
            fs.createFile(n, s);
        }
        else if (c == "delete") {
            string n;
            cin >> n;
            fs.deleteFile(n);
        }
        else if (c == "read") {
            string n;
            cin >> n;
            fs.readFile(n);
        }
        else if (c == "crash") {
        int n;
        cin >> n;
        fs.crash(n);
    }
else if (c == "recover") fs.recover();

        else if (c == "defrag") fs.defrag();
        else if (c == "map") fs.mapBlocks();
        else cout << "wrong command\n";
    }

    return 0;
}




