#include <stdio.h>

int main() {
    int n, m;
    printf("Enter number of processes and resources: ");
    scanf("%d %d", &n, &m);

    int alloc[20][20], max[20][20], need[20][20], avail[20];
    printf("Enter Allocation matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) scanf("%d", &alloc[i][j]);

    printf("Enter Max matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            scanf("%d", &max[i][j]);
            need[i][j] = max[i][j] - alloc[i][j];
        }

    printf("Enter Available resources: ");
    for (int j = 0; j < m; j++) scanf("%d", &avail[j]);

    int finish[20] = {0}, safe_seq[20], count = 0;
    while (count < n) {
        int found = 0;
        for (int i = 0; i < n; i++) {
            if (!finish[i]) {
                int ok = 1;
                for (int j = 0; j < m; j++)
                    if (need[i][j] > avail[j]) { ok = 0; break; }
                if (ok) {
                    for (int j = 0; j < m; j++) avail[j] += alloc[i][j];
                    safe_seq[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }
        if (!found) {
            printf("System is in an UNSAFE state (Deadlock possible).\n");
            return 0;
        }
    }

    printf("System is in a SAFE state.\nSafe Sequence: ");
    for (int i = 0; i < n; i++)
        printf("P%d%s", safe_seq[i], i == n - 1 ? "\n" : " -> ");
    return 0;
}