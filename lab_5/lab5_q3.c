#include <stdio.h>
struct Process {
    char id[10];
    int at;       
    int bt;       
    int deadline; 
    int remaining_bt;
    int ct;       
};

void edf_scheduling(struct Process p[], int n) {
    int time = 0, completed = 0;
    int prev_p = -1;

    printf("\nGantt Chart: ");

    while (completed < n) {
        int best_p = -1;
        int min_deadline = 9999;

        for (int i = 0; i < n; i++) {
            if (p[i].at <= time && p[i].remaining_bt > 0) {
                if (p[i].deadline < min_deadline) {
                    min_deadline = p[i].deadline;
                    best_p = i;
                }
            }
        }

        if (best_p != -1) {
            if (best_p != prev_p) {
                printf("| %s ", p[best_p].id);
                prev_p = best_p;
            }

            p[best_p].remaining_bt--;
            time++;

            if (p[best_p].remaining_bt == 0) {
                p[best_p].ct = time;
                completed++;
                if (p[best_p].ct > p[best_p].deadline) {
                    printf("(Missed!) ");
                }
            }
        } else {
            time++; 
        }
    }
    printf("|\n");
}

int main() {
    int n = 3;
    struct Process p[3] = {
        {"P1", 0, 10, 25, 10, 0},
        {"P2", 5, 5, 15, 5, 0},
        {"P3", 2, 8, 30, 8, 0}
    };

    printf("EDF Real-Time Scheduling Simulation\n");
    edf_scheduling(p, n);

    printf("\nID\tAT\tBT\tDeadline\tCT\tStatus\n");
    for (int i = 0; i < n; i++) {
        printf("%s\t%d\t%d\t%d\t\t%d\t%s\n", 
               p[i].id, p[i].at, p[i].bt, p[i].deadline, p[i].ct, 
               (p[i].ct <= p[i].deadline) ? "Success" : "Deadline Missed");
    }

    return 0;
}