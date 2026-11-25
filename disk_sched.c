#include <stdio.h>
#include <stdlib.h>

int cmp(const void *a, const void *b) { return (*(int*)a - *(int*)b); }

void fcfs(int req[], int n, int head) {
    int seek = 0, cur = head;
    for (int i = 0; i < n; i++) { seek += abs(req[i] - cur); cur = req[i]; }
    printf("FCFS Total Head Movement   = %d\n", seek);
}

void sstf(int req[], int n, int head) {
    int vis[100] = {0}, seek = 0, cur = head;
    for (int step = 0; step < n; step++) {
        int idx = -1, min_d = 1e9;
        for (int i = 0; i < n; i++)
            if (!vis[i] && abs(req[i] - cur) < min_d) { min_d = abs(req[i] - cur); idx = i; }
        vis[idx] = 1; seek += min_d; cur = req[idx];
    }
    printf("SSTF Total Head Movement   = %d\n", seek);
}

void scan(int req[], int n, int head, int size, int dir) {
    int arr[105], k = 0;
    for (int i = 0; i < n; i++) arr[k++] = req[i];
    arr[k++] = head;
    arr[k++] = dir ? size - 1 : 0;
    qsort(arr, k, sizeof(int), cmp);

    int pos = 0;
    while (arr[pos] != head) pos++;
    int seek = 0, cur = head;
    if (dir) {
        for (int i = pos + 1; i < k; i++) { seek += abs(arr[i] - cur); cur = arr[i]; }
        for (int i = pos - 1; i >= 0; i--) { seek += abs(arr[i] - cur); cur = arr[i]; }
    } else {
        for (int i = pos - 1; i >= 0; i--) { seek += abs(arr[i] - cur); cur = arr[i]; }
        for (int i = pos + 1; i < k; i++) { seek += abs(arr[i] - cur); cur = arr[i]; }
    }
    printf("SCAN Total Head Movement   = %d\n", seek);
}

void cscan(int req[], int n, int head, int size) {
    int arr[105], k = 0;
    for (int i = 0; i < n; i++) arr[k++] = req[i];
    arr[k++] = head; arr[k++] = size - 1; arr[k++] = 0;
    qsort(arr, k, sizeof(int), cmp);

    int pos = 0;
    while (arr[pos] != head) pos++;
    int seek = 0, cur = head;
    for (int i = pos + 1; i < k; i++) { seek += abs(arr[i] - cur); cur = arr[i]; }
    for (int i = 0; i < pos; i++) { seek += abs(arr[i] - cur); cur = arr[i]; }
    printf("C-SCAN Total Head Movement = %d\n", seek);
}

int main() {
    int n, head, size, dir, req[100];
    printf("Enter requests count, head, disk size, direction (1=right, 0=left): ");
    scanf("%d %d %d %d", &n, &head, &size, &dir);
    printf("Enter request queue: ");
    for (int i = 0; i < n; i++) scanf("%d", &req[i]);

    fcfs(req, n, head);
    sstf(req, n, head);
    scan(req, n, head, size, dir);
    cscan(req, n, head, size);
    return 0;
}