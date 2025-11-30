# fs-recovery-simulator
Simple File System Recovery &amp; Optimization Simulator
File System Recovery and Optimization Simulator

This project is a simple file system simulator made in C++.  
The aim of the project is to understand how basic file systems work and to simulate some features like:

- creating files
- deleting files
- reading files
- managing free space
- defragmentation
- crash simulation
- recovery after crash
- showing the block map

The project does not use any external libraries.  
Data is stored in vectors and maps to represent a small in-memory file system

🔧 Features Implemented

### 1. Create File
Allocates the required number of blocks from the free space and stores the block numbers.

### 2. Delete File
Frees the blocks used by the file.

### 3. Read File
Shows which blocks belong to the file.

### 4. Defragmentation
Moves allocated blocks to the left side to reduce fragmentation.

### 5. Crash Simulation
Random blocks are marked as corrupted and unusable.

### 6. Recovery
Scans all files and removes corrupted blocks from their block lists.

### 7. Status Command
Shows total blocks, free blocks, and number of files.

### 8. Block Map
Shows every block and whether it is free or used.


## 🏗 How the Project Works Internally

- The "disk" is just a vector of integers.
- `-1` means the block is free.
- A positive number means the block contains file data.
- A `bad` vector marks corrupted blocks.
- A map stores the file name and its block list.
- Simple functions simulate file system behavior.

This setup gives an idea of how an operating system allocates space and recovers from damage.

---

## ▶️ How to Run the Program

1. Compile using g++:
