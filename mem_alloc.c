#include <stdio.h>

void allocate(int block_orig[], int m, int proc[], int n, int mode) {
    int block[50], alloc[50];
    for (int i = 0; i < m; i++) block[i] = block_orig[i];
    for (int i = 0; i < n; i++) alloc[i] = -1;

    for (int i = 0; i < n; i++) {
        int idx = -1;
        for (int j = 0; j < m; j++) {
            if (block[j] >= proc[i]) {
                if (mode == 0) { idx = j; break; }
                else if (mode == 1 && (idx == -1 || block[j] < block[idx])) idx = j;
                else if (mode == 2 && (idx == -1 || block[j] > block[idx])) idx = j;
            }
        }
        if (idx != -1) {
            alloc[i] = idx;
            block[idx] -= proc[i];
        }
    }

    const char *names[] = {"First Fit", "Best Fit", "Worst Fit"};
    printf("\n--- %s ---\nProcess\tSize\tBlock\n", names[mode]);
    for (int i = 0; i < n; i++) {
        if (alloc[i] != -1) printf("P%d\t%d\tB%d\n", i + 1, proc[i], alloc[i] + 1);
        else printf("P%d\t%d\tNot Allocated\n", i + 1, proc[i]);
    }
}

int main() {
    int m, n, blocks[50], procs[50];
    printf("Enter number of blocks and processes: ");
    scanf("%d %d", &m, &n);
    printf("Enter block sizes: ");
    for (int i = 0; i < m; i++) scanf("%d", &blocks[i]);
    printf("Enter process sizes: ");
    for (int i = 0; i < n; i++) scanf("%d", &procs[i]);

    allocate(blocks, m, procs, n, 0);
    allocate(blocks, m, procs, n, 1);
    allocate(blocks, m, procs, n, 2);
    return 0;
}