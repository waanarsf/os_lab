#include <iostream>
#include <vector>

using namespace std;

void detectDeadlock() {
    int n, m;
    cout << "Enter number of processes: ";
    cin >> n;
    cout << "Enter number of resource types: ";
    cin >> m;
    vector<vector<int>> alloc(n, vector<int>(m));
    vector<vector<int>> request(n, vector<int>(m));
    vector<int> avail(m);
    vector<bool> finish(n, false);

    cout << "\nEnter Allocation Matrix:\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) cin >> alloc[i][j];

    cout << "\nEnter Request Matrix:\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) cin >> request[i][j];

    cout << "\nEnter Available Resources (A B C...): ";
    for (int i = 0; i < m; i++) cin >> avail[i];
    for (int i = 0; i < n; i++) {
        bool hasAllocation = false;
        for (int j = 0; j < m; j++) {
            if (alloc[i][j] > 0) {
                hasAllocation = true;
                break;
            }
        }
        if (!hasAllocation) finish[i] = true;
    }
    vector<int> work = avail;
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            if (!finish[i]) {
                bool canFinish = true;
                for (int j = 0; j < m; j++) {
                    if (request[i][j] > work[j]) {
                        canFinish = false;
                        break;
                    }
                }

                if (canFinish) {
                    for (int j = 0; j < m; j++) work[j] += alloc[i][j];
                    finish[i] = true;
                }
            }
        }
    }
    vector<int> deadlocked_procs;
    for (int i = 0; i < n; i++) {
        if (!finish[i]) deadlocked_procs.push_back(i);
    }

    cout << "\n--- Result ---\n";
    if (deadlocked_procs.empty()) {
        cout << "The system is in a SAFE state. No deadlock detected." << endl;
    } else {
        cout << "DEADLOCK DETECTED! The following processes are deadlocked: ";
        for (int p : deadlocked_procs) cout << "P" << p << " ";
        cout << endl;
    }
}

int main() {
    detectDeadlock();
    return 0;
}