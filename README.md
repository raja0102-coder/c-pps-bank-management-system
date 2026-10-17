# PPS Bank Account Management System (Real-Life C Project)

A complete Semester 1 Programming for Problem Solving (PPS) C application providing a menu-driven banking system with file persistence, balance inquiry, cash deposits, and withdrawals.

## PPS Concepts Integrated
* **Structures (`struct`)**: Grouping bank account attributes (Account Number, Holder Name, Balance).
* **File Stream Handling (`fopen`, `fprintf`, `fscanf`)**: Persistent storage of financial records on disk.
* **Record Updating**: Reading file streams, modifying specific account balances in memory, and safely rewriting records using temporary files.
* **Menu-Driven CLI Loops**: Infinite runtime loops controlled by `switch-case` dispatchers.

## How to Compile & Run
```bash
gcc main.c -o bank_system
./bank_system
