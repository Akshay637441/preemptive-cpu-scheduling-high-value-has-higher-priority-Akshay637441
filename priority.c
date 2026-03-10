#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

struct process {
    char pid[10];
    int at, bt, pr;
    int rt;
    int ct, wt, tat;
};

int main() {
    struct process p[20];
    int n = 0;

    char first[10];
    scanf("%s", first);

    /* Check if first token is a number (n given) or a PID (no n) */
    int is_number = 1;
    for (int k = 0; first[k] != '\0'; k++) {
        if (!isdigit(first[k])) { is_number = 0; break; }
    }

    if (is_number) {
        /* Normal case: first token is process count */
        n = atoi(first);
        for (int i = 0; i < n; i++) {
            scanf("%s %d %d %d", p[i].pid, &p[i].at, &p[i].bt, &p[i].pr);
            p[i].rt = p[i].bt;
        }
    } else {
        /* No count given: first token is already a PID, read until EOF */
        strncpy(p[0].pid, first, 9);
        scanf("%d %d %d", &p[0].at, &p[0].bt, &p[0].pr);
        p[0].rt = p[0].bt;
        n = 1;
        while (scanf("%s %d %d %d", p[n].pid, &p[n].at, &p[n].bt, &p[n].pr) == 4) {
            p[n].rt = p[n].bt;
            n++;
        }
    }

    /* Preemptive Priority Scheduling */
    int completed = 0, time = 0;
    int idx, max_pr, i;

    while (completed < n) {
        idx    = -1;
        max_pr = -1;
        for (i = 0; i < n; i++) {
            if (p[i].at <= time && p[i].rt > 0 && p[i].pr > max_pr) {
                max_pr = p[i].pr;
                idx    = i;
            }
        }
        if (idx != -1) {
            p[idx].rt--;
            time++;
            if (p[idx].rt == 0) {
                p[idx].ct = time;
                completed++;
            }
        } else {
            time++;
        }
    }

    /* Compute WT and TAT */
    float avg_wt = 0, avg_tat = 0;
    for (i = 0; i < n; i++) {
        p[i].tat  = p[i].ct - p[i].at;
        p[i].wt   = p[i].tat - p[i].bt;
        avg_wt   += p[i].wt;
        avg_tat  += p[i].tat;
    }

    printf("Waiting Time:\n");
    for (i = 0; i < n; i++) printf("%s %d\n", p[i].pid, p[i].wt);

    printf("\nTurnaround Time:\n");
    for (i = 0; i < n; i++) printf("%s %d\n", p[i].pid, p[i].tat);

    printf("\nAverage Waiting Time: %.2f\n",    avg_wt  / n);
    printf("Average Turnaround Time: %.2f\n",   avg_tat / n);

    return 0;
}
