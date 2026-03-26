#include <iostream>
#include <cmath>

using namespace std;

int main() {
    int totalMemory, pageSize, logicalAddr;
    cout << "--- Flexible Memory Mapping Simulation ---" << endl;
    cout << "Enter Total Memory size (e.g., 256): ";
    cin >> totalMemory;
    cout << "Enter Page Size (e.g., 32): ";
    cin >> pageSize;
    int totalBits = log2(totalMemory); 
    cout << "\nSYSTEM INFO:" << endl;
    cout << "Total Address Bits: " << totalBits << endl;
    cout << "Number of Pages: " << (totalMemory / pageSize) << endl;
    while (true) {
        cout << "\nEnter a logical address (or -1 to quit): ";
        cin >> logicalAddr;
        if (logicalAddr == -1) break;
        if (logicalAddr < 0 || logicalAddr >= totalMemory) {
            cout << "Invalid! Address must be between 0 and " << totalMemory - 1 << endl;
            continue;
        }
        int pageNumber = logicalAddr / pageSize; 
        int offset = logicalAddr % pageSize;     
        cout << ">> Result for " << logicalAddr << " -> Page: " << pageNumber << ", Offset: " << offset << endl;
    }
    cout << "ended" << endl;
    return 0;
}