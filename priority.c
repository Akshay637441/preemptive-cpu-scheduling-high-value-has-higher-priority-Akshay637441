#include <stdio.h>

#define MAX 20

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

int highest_priority(Process p[], int n, int time) {
    int index = -1;

    for (int i = 0; i < n; i++) {
        if (p[i].arrival <= time && p[i].remaining > 0) {
            if (index == -1 || p[i].priority > p[index].priority) {
                index = i;
            }
        }
    }

    return index;
}

int main() {
    int n;
    scanf("%d", &n);

    Process p[MAX];

    for (int i = 0; i < n; i++) {
        char name[5];
        scanf("%s %d %d %d", name, &p[i].arrival, &p[i].burst, &p[i].priority);

        p[i].pid = i + 1;
        p[i].remaining = p[i].burst;
    }

    int completed = 0;
    int time = 0;

    while (completed < n) {

        int idx = highest_priority(p, n, time);

        if (idx == -1) {
            time++;
            continue;
        }

        p[idx].remaining--;
        time++;

        if (p[idx].remaining == 0) {
            completed++;

            p[idx].completion = time;
            p[idx].turnaround = p[idx].completion - p[idx].arrival;
            p[idx].waiting = p[idx].turnaround - p[idx].burst;
        }
    }

    printf("PID AT BT PR CT TAT WT\n");

    float total_tat = 0;
    float total_wt = 0;

    for (int i = 0; i < n; i++) {

        printf("P%d %d %d %d %d %d %d\n",
               p[i].pid,
               p[i].arrival,
               p[i].burst,
               p[i].priority,
               p[i].completion,
               p[i].turnaround,
               p[i].waiting);

        total_tat += p[i].turnaround;
        total_wt += p[i].waiting;
    }

    printf("Average TAT: %.2f\n", total_tat / n);
    printf("Average WT: %.2f\n", total_wt / n);

    return 0;
}
