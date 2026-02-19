#include <stdio.h>
struct process {
    char name;
    int at, bt, wt, tat, rt, ct, remaining_bt;
} p[10];

int main() {
    int n, i, j, time = 0, total_wt = 0, total_tat = 0;
    int q1_n = 0, q2_n = 0, q3_n = 0;
    int q1_quantum = 8, q2_quantum = 16;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        p[i].name = 'A' + i;
        printf("Enter Arrival Time and Burst Time for Process %c: ", p[i].name);
        scanf("%d %d", &p[i].at, &p[i].bt);
        p[i].remaining_bt = p[i].bt;
    }

    printf("\nGantt Chart: ");
    for (i = 0; i < n; i++) {
        if (time < p[i].at) time = p[i].at;
        
        if (p[i].remaining_bt <= q1_quantum) {
            printf("| %c ", p[i].name);
            time += p[i].remaining_bt;
            p[i].remaining_bt = 0;
            p[i].ct = time;
        } else {
            printf("| %c ", p[i].name);
            time += q1_quantum;
            p[i].remaining_bt -= q1_quantum;
            
        }
    }

    for (i = 0; i < n; i++) {
        if (p[i].remaining_bt > 0) {
            if (p[i].remaining_bt <= q2_quantum) {
                printf("| %c ", p[i].name);
                time += p[i].remaining_bt;
                p[i].remaining_bt = 0;
                p[i].ct = time;
            } else {
                printf("| %c ", p[i].name);
                time += q2_quantum;
                p[i].remaining_bt -= q2_quantum;
                
            }
        }
    }

    for (i = 0; i < n; i++) {
        if (p[i].remaining_bt > 0) {
            printf("| %c ", p[i].name);
            time += p[i].remaining_bt;
            p[i].remaining_bt = 0;
            p[i].ct = time;
        }
    }
    printf("|\n");

    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\n");
    for (i = 0; i < n; i++) {
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
        total_tat += p[i].tat;
        total_wt += p[i].wt;
        printf("%c\t%d\t%d\t%d\t%d\t%d\n", p[i].name, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    }

    printf("\nAverage Turnaround Time: %.2f", (float)total_tat / n);
    printf("\nAverage Waiting Time: %.2f\n", (float)total_wt / n);

    return 0;
}