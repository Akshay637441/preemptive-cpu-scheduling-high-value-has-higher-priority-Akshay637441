#include <stdio.h>

#define MAX 10

typedef struct {
    int pid;
    int at;
    int bt;
    int pr;
    int rt;
    int ct;
    int tat;
    int wt;
} Process;

int select_process(Process p[], int n, int time) {
    int idx = -1;

    for (int i = 0; i < n; i++) {
        if (p[i].at <= time && p[i].rt > 0) {
            if (idx == -1 || p[i].pr > p[idx].pr)
                idx = i;
        }
    }

    return idx;
}

int main() {

    Process p[MAX];
    int n;

    if (scanf("%d", &n) != 1) return 0;

    for (int i = 0; i < n; i++) {
        char name[10];
        scanf("%s %d %d %d", name, &p[i].at, &p[i].bt, &p[i].pr);
        sscanf(name, "P%d", &p[i].pid);
        p[i].rt = p[i].bt;
    }

    int time = 0, completed = 0;

    while (completed < n) {

        int idx = select_process(p, n, time);

        if (idx == -1) {
            time++;
            continue;
        }

        p[idx].rt--;
        time++;

        if (p[idx].rt == 0) {
            completed++;
            p[idx].ct = time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
        }
    }

    double avg_wt = 0, avg_tat = 0;

    printf("Waiting Time:\n");
    for (int i = 0; i < n; i++) {
        printf("P%d %d\n", p[i].pid, p[i].wt);
        avg_wt += p[i].wt;
    }

    printf("Turnaround Time:\n");
    for (int i = 0; i < n; i++) {
        printf("P%d %d\n", p[i].pid, p[i].tat);
        avg_tat += p[i].tat;
    }

    printf("Average Waiting Time: %.2f\n", avg_wt / n);
    printf("Average Turnaround Time: %.2f\n", avg_tat / n);

    return 0;
}
