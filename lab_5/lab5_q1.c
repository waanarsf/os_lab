#include <stdio.h>
#include <stdlib.h> // Necessary for exit()
#include <string.h>

struct Process {
    char id[10];
    int at, bt, priority, ct, tat, wt, remaining_bt;
};

// Function to reset process data so algorithms can be re-run in the menu
void reset(struct Process p[], int n) {
    for (int i = 0; i < n; i++) {
        p[i].remaining_bt = p[i].bt;
        p[i].ct = 0;
        p[i].tat = 0;
        p[i].wt = 0;
    }
}

void display(struct Process p[], int n) {
    float total_tat = 0, total_wt = 0;
    printf("\nID\tAT\tBT\tPrio\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%s\t%d\t%d\t%d\t%d\t%d\t%d\n", p[i].id, p[i].at, p[i].bt, p[i].priority, p[i].ct, p[i].tat, p[i].wt);
        total_tat += p[i].tat;
        total_wt += p[i].wt;
    }
    printf("\nAverage Turnaround Time: %.2f", total_tat / n);
    printf("\nAverage Waiting Time: %.2f\n\n", total_wt / n);
}

// 1. FCFS
void fcfs(struct Process p[], int n) {
    int current_time = 0;
    printf("\nGantt Chart (FCFS): ");
    for (int i = 0; i < n; i++) {
        if (current_time < p[i].at) current_time = p[i].at;
        printf("| %s ", p[i].id);
        current_time += p[i].bt;
        p[i].ct = current_time;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
    }
    printf("|\n");
    display(p, n);
}

// 2. SRTF
void srtf(struct Process p[], int n) {
    int completed = 0, t = 0, min_bt = 999, shortest = -1;
    printf("\nGantt Chart (SRTF): ");
    while (completed != n) {
        shortest = -1;
        min_bt = 999;
        for (int i = 0; i < n; i++) {
            if (p[i].at <= t && p[i].remaining_bt < min_bt && p[i].remaining_bt > 0) {
                min_bt = p[i].remaining_bt;
                shortest = i;
            }
        }
        if (shortest == -1) { t++; continue; }
        p[shortest].remaining_bt--;
        if (p[shortest].remaining_bt == 0) {
            completed++;
            p[shortest].ct = t + 1;
            p[shortest].tat = p[shortest].ct - p[shortest].at;
            p[shortest].wt = p[shortest].tat - p[shortest].bt;
            printf("| %s ", p[shortest].id);
        }
        t++;
    }
    printf("|\n");
    display(p, n);
}

// 3. Round Robin
void rr(struct Process p[], int n, int q) {
    int t = 0, completed = 0;
    printf("\nGantt Chart (RR): ");
    while (completed < n) {
        int active = 0;
        for (int i = 0; i < n; i++) {
            if (p[i].at <= t && p[i].remaining_bt > 0) {
                active = 1;
                printf("| %s ", p[i].id);
                if (p[i].remaining_bt > q) {
                    t += q;
                    p[i].remaining_bt -= q;
                } else {
                    t += p[i].remaining_bt;
                    p[i].remaining_bt = 0;
                    p[i].ct = t;
                    p[i].tat = p[i].ct - p[i].at;
                    p[i].wt = p[i].tat - p[i].bt;
                    completed++;
                }
            }
        }
        if (!active) t++;
    }
    printf("|\n");
    display(p, n);
}

// 4. Non-Preemptive Priority (Higher number = Higher Priority)
void priorityNP(struct Process p[], int n) {
    int completed = 0, t = 0;
    int done[10] = {0};
    printf("\nGantt Chart (Priority): ");
    while (completed < n) {
        int idx = -1, high_p = -1;
        for (int i = 0; i < n; i++) {
            if (p[i].at <= t && !done[i]) {
                if (p[i].priority > high_p) {
                    high_p = p[i].priority;
                    idx = i;
                }
            }
        }
        if (idx == -1) { t++; continue; }
        printf("| %s ", p[idx].id);
        t += p[idx].bt;
        p[idx].ct = t;
        p[idx].tat = p[idx].ct - p[idx].at;
        p[idx].wt = p[idx].tat - p[idx].bt;
        done[idx] = 1;
        completed++;
    }
    printf("|\n");
    display(p, n);
}

int main() {
    int choice;
    struct Process p[4] = {
        {"P1", 0, 60, 3, 0, 0, 0, 60},
        {"P2", 3, 30, 2, 0, 0, 0, 30},
        {"P3", 4, 40, 1, 0, 0, 0, 40},
        {"P4", 9, 10, 4, 0, 0, 0, 10}
    };

    while(1) {
        reset(p, 4); // Clear previous results before running a new algorithm
        printf("Menu:\n1. FCFS\n2. SRTF\n3. RR (q=10)\n4. Priority\n5. EXIT\nEnter choice: ");
        if (scanf("%d", &choice) != 1) break;

        if (choice == 5) exit(0);
        
        switch(choice) {
            case 1: fcfs(p, 4); break;
            case 2: srtf(p, 4); break;
            case 3: rr(p, 4, 10); break;
            case 4: priorityNP(p, 4); break;
            default: printf("Invalid choice\n");
        }
    }
    return 0;
}