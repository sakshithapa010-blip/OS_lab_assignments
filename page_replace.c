#include <stdio.h>

int contains(int frames[], int f, int page) {
    for (int i = 0; i < f; i++) if (frames[i] == page) return i;
    return -1;
}

void fifo(int pages[], int n, int f) {
    int frames[50], ptr = 0, faults = 0;
    for (int i = 0; i < f; i++) frames[i] = -1;
    for (int i = 0; i < n; i++) {
        if (contains(frames, f, pages[i]) == -1) {
            frames[ptr] = pages[i];
            ptr = (ptr + 1) % f;
            faults++;
        }
    }
    printf("FIFO Page Faults    = %d\n", faults);
}

void lru(int pages[], int n, int f) {
    int frames[50], last[50], faults = 0;
    for (int i = 0; i < f; i++) { frames[i] = -1; last[i] = -1; }
    for (int i = 0; i < n; i++) {
        int pos = contains(frames, f, pages[i]);
        if (pos != -1) last[pos] = i;
        else {
            int victim = 0;
            for (int j = 1; j < f; j++) if (last[j] < last[victim]) victim = j;
            frames[victim] = pages[i];
            last[victim] = i;
            faults++;
        }
    }
    printf("LRU Page Faults     = %d\n", faults);
}

void optimal(int pages[], int n, int f) {
    int frames[50], faults = 0;
    for (int i = 0; i < f; i++) frames[i] = -1;
    for (int i = 0; i < n; i++) {
        if (contains(frames, f, pages[i]) == -1) {
            int victim = -1, farthest = -1;
            for (int j = 0; j < f; j++) {
                if (frames[j] == -1) { victim = j; break; }
                int next = n + 1;
                for (int k = i + 1; k < n; k++)
                    if (pages[k] == frames[j]) { next = k; break; }
                if (next > farthest) { farthest = next; victim = j; }
            }
            frames[victim] = pages[i];
            faults++;
        }
    }
    printf("Optimal Page Faults = %d\n", faults);
}

int main() {
    int n, f, pages[100];
    printf("Enter number of pages and frames: ");
    scanf("%d %d", &n, &f);
    printf("Enter reference string: ");
    for (int i = 0; i < n; i++) scanf("%d", &pages[i]);

    fifo(pages, n, f);
    lru(pages, n, f);
    optimal(pages, n, f);
    return 0;
}