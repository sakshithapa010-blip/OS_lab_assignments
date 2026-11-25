#include <stdio.h>

typedef struct {
    int id, at, bt, pr, rt, ct, tat, wt;
} Proc;

void print_stats(Proc p[], int n) {
    float avg_tat = 0, avg_wt = 0;
    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
        avg_tat += p[i].tat;
        avg_wt += p[i].wt;
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", p[i].id, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    }
    printf("Avg TAT = %.2f, Avg WT = %.2f\n\n", avg_tat / n, avg_wt / n);
}

void fcfs(Proc p[], int n) {
    int time = 0;
    for (int i = 0; i < n; i++) {
        if (time < p[i].at) time = p[i].at;
        time += p[i].bt;
        p[i].ct = time;
    }
    printf("--- FCFS ---\n");
    print_stats(p, n);
}

void sjf(Proc p[], int n) {
    int done = 0, time = 0, vis[50] = {0};
    while (done < n) {
        int idx = -1, min_bt = 1e9;
        for (int i = 0; i < n; i++) {
            if (!vis[i] && p[i].at <= time && p[i].bt < min_bt) {
                min_bt = p[i].bt;
                idx = i;
            }
        }
        if (idx == -1) time++;
        else {
            time += p[idx].bt;
            p[idx].ct = time;
            vis[idx] = 1;
            done++;
        }
    }
    printf("--- SJF (Non-Preemptive) ---\n");
    print_stats(p, n);
}

void priority_sched(Proc p[], int n) {
    int done = 0, time = 0, vis[50] = {0};
    while (done < n) {
        int idx = -1, best_pr = 1e9;
        for (int i = 0; i < n; i++) {
            if (!vis[i] && p[i].at <= time && p[i].pr < best_pr) {
                best_pr = p[i].pr;
                idx = i;
            }
        }
        if (idx == -1) time++;
        else {
            time += p[idx].bt;
            p[idx].ct = time;
            vis[idx] = 1;
            done++;
        }
    }
    printf("--- Priority (Non-Preemptive) ---\n");
    print_stats(p, n);
}

void round_robin(Proc p[], int n, int tq) {
    int time = 0, remain = n;
    for (int i = 0; i < n; i++) p[i].rt = p[i].bt;
    while (remain > 0) {
        int idle = 1;
        for (int i = 0; i < n; i++) {
            if (p[i].at <= time && p[i].rt > 0) {
                idle = 0;
                int run = (p[i].rt > tq) ? tq : p[i].rt;
                p[i].rt -= run;
                time += run;
                if (p[i].rt == 0) {
                    p[i].ct = time;
                    remain--;
                }
            }
        }
        if (idle) time++;
    }
    printf("--- Round Robin (TQ = %d) ---\n", tq);
    print_stats(p, n);
}

int main() {
    int n, tq;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    Proc base[50], tmp[50];
    for (int i = 0; i < n; i++) {
        base[i].id = i + 1;
        printf("P%d (AT BT Priority): ", i + 1);
        scanf("%d %d %d", &base[i].at, &base[i].bt, &base[i].pr);
    }
    printf("Enter Time Quantum: ");
    scanf("%d", &tq);

    for (int i = 0; i < n; i++) tmp[i] = base[i]; fcfs(tmp, n);
    for (int i = 0; i < n; i++) tmp[i] = base[i]; sjf(tmp, n);
    for (int i = 0; i < n; i++) tmp[i] = base[i]; priority_sched(tmp, n);
    for (int i = 0; i < n; i++) tmp[i] = base[i]; round_robin(tmp, n, tq);
    return 0;
}