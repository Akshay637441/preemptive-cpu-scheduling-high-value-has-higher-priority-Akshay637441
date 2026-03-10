#include <stdio.h>

#define MAX 50

typedef struct {
    int pid;
    int arrival;
    int burst;
    int priority;
    int remaining;
    int completion;
    int turnaround;
    int waiting;
} Process;

int highest(Process p[], int n, int time) {
    int idx = -1;

    for (int i = 0; i < n; i++) {
        if (p[i].arrival <= time && p[i].remaining > 0) {
            if (idx == -1 || p[i].priority > p[idx].priority)
                idx = i;
        }
    }

    return idx;
}

int main() {

    Process p[MAX];
    int n = 0;

    /* Read until EOF */
    while (scanf("P%d %d %d %d",
                 &p[n].pid,
                 &p[n].arrival,
                 &p[n].burst,
                 &p[n].priority) == 4) {

        p[n].remaining = p[n].burst;
        n++;
    }

    int completed = 0;
    int time = 0;

    while (completed < n) {

        int idx = highest(p, n, time);

        if (idx == -1) {
            time++;
            continue;
        }

        p[idx].remaining--;
        time++;

        if (p[idx].remaining == 0) {
            completed++;
            p[idx].completion = time;
            p[idx].turnaround = time - p[idx].arrival;
            p[idx].waiting = p[idx].turnaround - p[idx].burst;
        }
    }

    for (int i = 0; i < n; i++) {
        printf("P%d %d %d %d %d %d %d\n",
               p[i].pid,
               p[i].arrival,
               p[i].burst,
               p[i].priority,
               p[i].completion,
               p[i].turnaround,
               p[i].waiting);
    }

    return 0;
}
