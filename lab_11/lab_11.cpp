#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

void fcfs(vector<int> req, int head) {
    int thm = 0;
    int current = head;
    for(int r : req) {
        thm += abs(r - current);
        current = r;
    }
    cout << "\nFCFS-total head movement: " << thm;
}

void sstf(vector<int> req, int head) {
    int thm = 0;
    int current = head;
    int n = req.size();
    vector<bool> visited(n, false);

    for(int i = 0; i < n; i++) {
        int min_dist = 1e9;
        int index = -1;
        for(int j = 0; j < n; j++) {
            if(!visited[j] && abs(req[j] - current) < min_dist) {
                min_dist = abs(req[j] - current);
                index = j;
            }
        }
        visited[index] = true;
        thm += min_dist;
        current = req[index];
    }
    cout << "\nSSTF-total head movement: " << thm;
}

void scan(vector<int> req, int head, int disk_size) {
    sort(req.begin(), req.end());
    int max_val = req.back();
    int thm = (head - 0) + (max_val - 0);
    cout << "\nSCAN-total head movement: " << thm;
}

void cscan(vector<int> req, int head, int disk_size) {
    sort(req.begin(), req.end());
    int max_disk = disk_size - 1;
    int last_small = -1;
    for(int r : req) {
        if(r < head) last_small = r;
    }

    int thm = (max_disk - head) + (last_small - 0);
    cout << "\nC-SCAN-total head movement: " << thm;
}

int main() {
    int n, head, disk_size;

    cout << "Enter total disk size: ";
    cin >> disk_size;

    cout << "Enter current head position: ";
    cin >> head;

    cout << "Enter number of requests: ";
    cin >> n;

    vector<int> requests(n);
    cout << "Enter the requests separated by space: ";
    for(int i = 0; i < n; i++) {
        cin >> requests[i];
    }

    cout << "\nresults: ";
    fcfs(requests, head);
    sstf(requests, head);
    scan(requests, head, disk_size);
    cscan(requests, head, disk_size);
    cout << endl;

    return 0;
}