#include <stdio.h>

int main() {
    int total, disk[100] = {0};
    printf("Enter total disk blocks: ");
    scanf("%d", &total);

    // 1. Contiguous Allocation
    int start, len;
    printf("\n[Contiguous] Enter start block and length: ");
    scanf("%d %d", &start, &len);
    int ok = (start >= 0 && start + len <= total);
    for (int i = start; ok && i < start + len; i++) if (disk[i]) ok = 0;
    if (ok) {
        for (int i = start; i < start + len; i++) disk[i] = 1;
        printf("Allocated blocks: ");
        for (int i = start; i < start + len; i++) printf("%d ", i);
        printf("\n");
    } else printf("Contiguous allocation failed.\n");

    // 2. Linked Allocation
    int n, b;
    printf("\n[Linked] Enter number of blocks: ");
    scanf("%d", &n);
    printf("Enter block numbers: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &b);
        if (b >= 0 && b < total && !disk[b]) {
            disk[b] = 1;
            printf("%d%s", b, i == n - 1 ? "\n" : " -> ");
        } else printf("[busy %d]%s", b, i == n - 1 ? "\n" : " -> ");
    }

    // 3. Indexed Allocation
    int idx_blk, count, blocks[50];
    printf("\n[Indexed] Enter index block and number of data blocks: ");
    scanf("%d %d", &idx_blk, &count);
    printf("Enter data blocks: ");
    for (int i = 0; i < count; i++) scanf("%d", &blocks[i]);
    if (idx_blk >= 0 && idx_blk < total && !disk[idx_blk]) {
        disk[idx_blk] = 1;
        printf("Index Block %d -> ", idx_blk);
        for (int i = 0; i < count; i++) {
            if (blocks[i] >= 0 && blocks[i] < total && !disk[blocks[i]]) {
                disk[blocks[i]] = 1;
                printf("%d ", blocks[i]);
            }
        }
        printf("\n");
    } else printf("Index block unavailable.\n");

    return 0;
}