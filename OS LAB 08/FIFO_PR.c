#include <stdio.h>

int main() {
    int frames[10], pages[30];
    int n, m, pageFaults = 0;
    int i, j, k, pos = 0, flag;

    printf("Enter number of frames: ");
    scanf("%d", &n);

    printf("Enter number of pages: ");
    scanf("%d", &m);

    printf("Enter the reference string:\n");
    for (i = 0; i < m; ++i)
        scanf("%d", &pages[i]);

    for (i = 0; i < n; ++i)
        frames[i] = -1;

    printf("\nPage Replacement Process (FIFO):\n");
    printf("--------------------------------\n");

    for (i = 0; i < m; ++i) {
        flag = 0;

        // Check if page is already in a frame (page hit)
        for (j = 0; j < n; ++j) {
            if (frames[j] == pages[i]) {
                flag = 1;
                break;
            }
        }

        // If page is not found (page fault)
        if (flag == 0) {
            frames[pos] = pages[i];
            pos = (pos + 1) % n;
            pageFaults++;

            printf("For page %2d: ", pages[i]);
            for (k = 0; k < n; ++k) {
                if (frames[k] == -1)
                    printf(" - ");
                else
                    printf("%2d ", frames[k]);
            }
            printf(" (Page Fault)\n");
        } else {
            printf("For page %2d: ", pages[i]);
            for (k = 0; k < n; ++k) {
                if (frames[k] == -1)
                    printf(" - ");
                else
                    printf("%2d ", frames[k]);
            }
            printf(" (Hit)\n");
        }
    }

    printf("\nTotal Page Faults = %d\n", pageFaults);
    printf("Total Page Hits = %d\n", m - pageFaults);

    return 0;
}
