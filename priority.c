#include <stdio.h>
#include <string.h>

#define MAX 50

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
    int n = 0;

    char name[10];

    /* Read input (works with or without n) */
    while (scanf("%s %d %d %d", name, &p[n].at, &p[n].bt, &p[n].pr) == 4) {
        sscanf(name, "P%d", &p[n].pid);
        p[n].rt = p[n].bt;
        n++;
    }

    int completed = 0;
    int time = 0;

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

    for (int i = 0; i < n; i++) {
        printf("P%d %d %d %d\n",
               p[i].pid,
               p[i].ct,
               p[i].tat,
               p[i].wt);
    }

    return 0;
}
