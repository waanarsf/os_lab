#include <iostream>
#include <vector>

using namespace std;

void simulate(string name, vector<int> blocks, vector<int> processes) {
    int n_b = blocks.size();
    int n_p = processes.size();
    vector<int> allocation(n_p, -1);

    for (int i = 0; i < n_p; i++) {
        int targetIdx = -1;
        for (int j = 0; j < n_b; j++) {
            if (blocks[j] >= processes[i]) {
                if (name == "First-fit") {
                    targetIdx = j;
                    break; 
                } else if (name == "Best-fit") {
                    if (targetIdx == -1 || blocks[j] < blocks[targetIdx])
                        targetIdx = j;
                } else if (name == "Worst-fit") {
                    if (targetIdx == -1 || blocks[j] > blocks[targetIdx])
                        targetIdx = j;
                }
            }
        }

        if (targetIdx != -1) {
            allocation[i] = targetIdx;
            blocks[targetIdx] -= processes[i]; 
        }
    }

    cout << "\n--- " << name << " Results ---" << endl;
    cout << "Process No.\tSize\tBlock No." << endl;
    for (int i = 0; i < n_p; i++) {
        cout << i + 1 << "\t\t" << processes[i] << "\t";
        if (allocation[i] != -1) cout << allocation[i] + 1 << endl;
        else cout << "Not Allocated" << endl;
    }
}

int main() {
    vector<int> blocks = {100, 500, 200, 300, 600};
    vector<int> processes = {212, 417, 112, 426};

    simulate("First-fit", blocks, processes);
    simulate("Best-fit", blocks, processes);
    simulate("Worst-fit", blocks, processes);

    return 0;
}