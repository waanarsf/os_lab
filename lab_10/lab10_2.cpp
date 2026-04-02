#include <iostream>
#include <iomanip>

using namespace std;
int findLRU(int time[], int n) {
    int minimum = time[0], pos = 0;
    for (int i = 1; i < n; i++) {
        if (time[i] < minimum) {
            minimum = time[i];
            pos = i;
        }
    }
    return pos;
}

int main() {
    int n, capacity, pageFaults = 0, counter = 0;
    cout << "Enter number of pages: ";
    cin >> n;
    int* pages = new int[n];
    cout << "Enter reference string: ";
    for (int i = 0; i < n; i++) cin >> pages[i];

    cout << "Enter number of frames: ";
    cin >> capacity;
    int* frames = new int[capacity];
    int* time = new int[capacity];
    for (int i = 0; i < capacity; i++) frames[i] = -1;
    cout << "\nLRU Simulation " << endl;
    for (int i = 0; i < n; i++) {
        bool found = false;
        for (int j = 0; j < capacity; j++) {
            if (frames[j] == pages[i]) {
                counter++;
                time[j] = counter; 
                found = true;
                break;
            }
        }
        if (!found) {
            bool emptySlot = false;
            for (int j = 0; j < capacity; j++) {
                if (frames[j] == -1) {
                    counter++;
                    pageFaults++;
                    frames[j] = pages[i];
                    time[j] = counter;
                    emptySlot = true;
                    break;
                }
            }
            if (!emptySlot) {
                int pos = findLRU(time, capacity);
                counter++;
                pageFaults++;
                frames[pos] = pages[i];
                time[pos] = counter;
            }
        }
    }

    int hits = n - pageFaults;
    double hitRatio = (double)hits / n;
    cout << "Total Page Faults: " << pageFaults << endl;
    cout << "Total Hits: " << hits << endl;
    cout << fixed << setprecision(2);
    cout << "Hit Ratio: " << hitRatio << " (" << hitRatio * 100 << "%)" << endl;
    delete[] pages;
    delete[] frames;
    delete[] time;

    return 0;
}