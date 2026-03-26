#include <iostream>
#include <vector>

using namespace std;
bool isSafe(int n, int m, vector<vector<int>>& alloc, vector<vector<int>>& need, vector<int> avail) {
    vector<int> work = avail;
    vector<bool> finish(n, false);
    vector<int> safeSeq;

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            if (!finish[i]) {
                bool canAllocate = true;
                for (int j = 0; j < m; j++) {
                    if (need[i][j] > work[j]) {
                        canAllocate = false;
                        break;
                    }
                }

                if (canAllocate) {
                    for (int j = 0; j < m; j++)
                        work[j] += alloc[i][j];
                    finish[i] = true;
                    safeSeq.push_back(i);
                }
            }
        }
    }

    if (safeSeq.size() == n) {
        cout << "System is in a SAFE state.\nSafe Sequence: ";
        for (int i = 0; i < n; i++) cout << "P" << safeSeq[i] << (i == n - 1 ? "" : " -> ");
        cout << endl;
        return true;
    } else {
        cout << "System is in Potential Deadlock!" << endl;
        return false;
    }
}

int main() {
    int n, m;
    cout << "Enter number of processes: "; cin >> n;
    cout << "Enter number of resource types: "; cin >> m;

    vector<vector<int>> alloc(n, vector<int>(m));
    vector<vector<int>> max_req(n, vector<int>(m));
    vector<vector<int>> need(n, vector<int>(m));
    vector<int> avail(m);

    cout << "Enter Allocation Matrix:\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) cin >> alloc[i][j];

    cout << "Enter Max Matrix:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> max_req[i][j];
            need[i][j] = max_req[i][j] - alloc[i][j];
        }
    }

    cout << "Enter Available resources: ";
    for (int i = 0; i < m; i++) cin >> avail[i];

    cout << "\n(a) Need Matrix:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) cout << need[i][j] << " ";
        cout << endl;
    }
    cout << "\n(b) Initial Safety Check:\n";
    isSafe(n, m, alloc, need, avail);
    int p_idx = 1;
    vector<int> request = {1, 0, 2};
    
    cout << "\n(c) Request for P" << p_idx << " of (1, 0, 2):\n";
        bool possible = true;
    for(int j=0; j<m; j++) {
        if(request[j] > need[p_idx][j] || request[j] > avail[j]) possible = false;
    }

    if(possible) {
        for(int j=0; j<m; j++) {
            avail[j] -= request[j];
            alloc[p_idx][j] += request[j];
            need[p_idx][j] -= request[j];
        }

        if(!isSafe(n, m, alloc, need, avail)) {
            for(int j=0; j<m; j++) {
                avail[j] += request[j];
                alloc[p_idx][j] -= request[j];
                need[p_idx][j] += request[j];
            }
        }
    } else {
        cout << "Request exceeds Need or Available resources." << endl;
    }

    return 0;
}