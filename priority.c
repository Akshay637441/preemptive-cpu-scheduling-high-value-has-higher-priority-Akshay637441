#include <stdio.h>
#include <string.h>

#define MAX 10

typedef struct {
    int pid;
    int arrival;
    int burst;
    int priority;
    int remaining;
    int completion;
    int waiting;
    int turnaround;
} Process;

int get_highest(Process p[], int n, int t) {
    int best = -1;
    for (int i = 0; i < n; i++) {
        if (p[i].arrival <= t && p[i].remaining > 0) {
            if (best == -1 || p[i].priority > p[best].priority)
                best = i;
        }
    }
    return best;
}

int main(void) {
    int n;
    scanf("%d", &n);

    Process p[MAX];
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        scanf("%d %d %d", &p[i].arrival, &p[i].burst, &p[i].priority);
        p[i].remaining = p[i].burst;
        p[i].completion = p[i].waiting = p[i].turnaround = 0;
    }

    int done = 0, t = 0;
    while (done < n) {
        int idx = get_highest(p, n, t);
        if (idx == -1) {
            /* find next arrival */
            int next = -1;
            for (int i = 0; i < n; i++)
                if (p[i].remaining > 0 && (next == -1 || p[i].arrival < next))
                    next = p[i].arrival;
            t = next;
            continue;
        }
        p[idx].remaining--;
        t++;
        if (p[idx].remaining == 0) {
            done++;
            p[idx].completion = t;
            p[idx].turnaround = t - p[idx].arrival;
            p[idx].waiting    = p[idx].turnaround - p[idx].burst;
        }
    }

    printf("PID\tAT\tBT\tPR\tCT\tTAT\tWT\n");
    double tot_tat = 0, tot_wt = 0;
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].arrival, p[i].burst, p[i].priority,
               p[i].completion, p[i].turnaround, p[i].waiting);
        tot_tat += p[i].turnaround;
        tot_wt  += p[i].waiting;
    }
    printf("Average TAT: %.2f\n", tot_tat / n);
    printf("Average WT: %.2f\n",  tot_wt  / n);

    return 0;
}
