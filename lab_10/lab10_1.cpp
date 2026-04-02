#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool isPageInFrames(int page, int* frames, int capacity) {
    for (int i = 0; i < capacity; i++) {
        if (frames[i] == page) return true;
    }
    return false;
}

void simulateFIFO(int* pages, int n, int capacity) {
    int* frames = new int[capacity];
    for (int i = 0; i < capacity; i++) frames[i] = -1;
    int pageFaults = 0;
    int index = 0; 
    cout << "\nFIFO Simulation" << endl;
    for (int i = 0; i < n; i++) {
        if (!isPageInFrames(pages[i], frames, capacity)) {
            frames[index] = pages[i];
            index = (index + 1) % capacity;
            pageFaults++;
        }
    }
    cout << "Total Page Faults: " << pageFaults << endl;
    delete[] frames;
}

void simulateOptimal(int* pages, int n, int capacity) {
    int* frames = new int[capacity];
    for (int i = 0; i < capacity; i++) frames[i] = -1;
    int pageFaults = 0;
    cout << "\nOptimal Simulation" << endl;
    for (int i = 0; i < n; i++) {
        if (!isPageInFrames(pages[i], frames, capacity)) {
            bool emptySlotFound = false;
            for (int j = 0; j < capacity; j++) {
                if (frames[j] == -1) {
                    frames[j] = pages[i];
                    emptySlotFound = true;
                    break;
                }
            }

            if (!emptySlotFound) {
                int farthest = i, replaceIndex = -1;
                for (int j = 0; j < capacity; j++) {
                    int k;
                    for (k = i + 1; k < n; k++) {
                        if (frames[j] == pages[k]) break;
                    }
                    if (k == n) { 
                        replaceIndex = j;
                        break;
                    }
                    if (k > farthest) {
                        farthest = k;
                        replaceIndex = j;
                    }
                }
                frames[replaceIndex] = pages[i];
            }
            pageFaults++;
        }
    }
    cout << "Total Page Faults: " << pageFaults << endl;
    delete[] frames;
}

int main() {
    int n, capacity;
    cout << "Enter number of pages in reference string: ";
    cin >> n;
    int* pages = new int[n];
    cout << "Enter the reference string (space separated): ";
    for (int i = 0; i < n; i++) cin >> pages[i];
    cout << "Enter number of frames: ";
    cin >> capacity;
    simulateFIFO(pages, n, capacity);
    simulateOptimal(pages, n, capacity);
    delete[] pages;

    return 0;
}