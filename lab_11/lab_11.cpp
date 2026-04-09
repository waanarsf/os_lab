#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void moveHead(int from, int to, int &totalDist) {
    int dist = abs(to - from);
    cout << "  moving from " << from << " to " << to << " Distance: " << dist << "\n";
    totalDist += dist;
}

int main() {
    int n, head, diskSize;

    cout << "max disk cylinders: "; cin >> diskSize;
    cout << "starting position of head: "; cin >> head;
    cout << "How many requests: "; cin >> n;

    vector<int> req(n);
    cout << "Enter the requests: ";
    for(int i = 0; i < n; i++) cin >> req[i];

    cout << "\nFCFS:";
    int fcfsDist = 0, current = head;
    for(int r : req) {
        moveHead(current, r, fcfsDist);
        current = r;
    }
    cout << "Total FCFS Movement: " << fcfsDist << endl;
    cout << "\nSSTF:";
    int sstfDist = 0;
    current = head;
    vector<int> temp = req;
    while(!temp.empty()) {
        int closestIdx = 0;
        for(int i = 1; i < temp.size(); i++) {
            if(abs(temp[i] - current) < abs(temp[closestIdx] - current))
                closestIdx = i;
        }
        moveHead(current, temp[closestIdx], sstfDist);
        current = temp[closestIdx];
        temp.erase(temp.begin() + closestIdx);
    }
    cout << "Total SSTF Movement: " << sstfDist << endl;
    cout << "\nSCAN:";
    int scanDist = 0;
    current = head;
    sort(req.begin(), req.end());

    vector<int> left, right;
    for(int r : req) {
        if(r < head) left.push_back(r);
        else right.push_back(r);
    }
    reverse(left.begin(), left.end());

    for(int r : left) { moveHead(current, r, scanDist); current = r; }
    moveHead(current, 0, scanDist); current = 0; // Hit the boundary
    for(int r : right) { moveHead(current, r, scanDist); current = r; }
    cout << "Total SCAN Movement: " << scanDist << endl;
    cout << "\nC-SCAN:";
    int cscanDist = 0;
    current = head;

    for(int r : req) {
        if(r >= head) {
            moveHead(current, r, cscanDist);
            current = r;
        }
    }
    moveHead(current, diskSize - 1, cscanDist); 
    cout << "  [Jump] Resetting to 0...\n";
    current = 0;
    for(int r : req) {
        if(r < head) {
            moveHead(current, r, cscanDist);
            current = r;
        }
    }
    cout << "Total C-SCAN Movement: " << cscanDist << endl;

    return 0;
}