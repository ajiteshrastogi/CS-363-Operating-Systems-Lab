#include <stdio.h>
#include <stdbool.h>

#define MAX_FRAMES 10
#define MAX_PAGES 30

// ---------- FIFO Page Replacement ----------
void fifo(int pages[], int n, int framesCount) {
    int frames[MAX_FRAMES], pageFaults = 0, pos = 0, i, j, flag;

    for (i = 0; i < framesCount; i++)
        frames[i] = -1;

    printf("\nPage Replacement Process (FIFO):\n");
    printf("--------------------------------\n");

    for (i = 0; i < n; i++) {
        flag = 0;

        // Check for hit
        for (j = 0; j < framesCount; j++) {
            if (frames[j] == pages[i]) {
                flag = 1;
                break;
            }
        }

        // Page fault if not found
        if (flag == 0) {
            frames[pos] = pages[i];
            pos = (pos + 1) % framesCount;
            pageFaults++;
        }

        printf("For page %2d: ", pages[i]);
        for (j = 0; j < framesCount; j++) {
            if (frames[j] == -1)
                printf(" - ");
            else
                printf("%2d ", frames[j]);
        }
        if (flag == 0)
            printf(" (Page Fault)\n");
        else
            printf(" (Hit)\n");
    }

    printf("\nTotal Page Faults = %d\n", pageFaults);
    printf("Total Page Hits = %d\n", n - pageFaults);
}

// ---------- Optimal Page Replacement ----------
void optimal(int pages[], int n, int framesCount) {
    int frames[MAX_FRAMES], future[MAX_FRAMES];
    int pageFaults = 0, i, j, k, pos, flag1, flag2, max;

    for (i = 0; i < framesCount; i++)
        frames[i] = -1;

    printf("\nPage Replacement Process (Optimal):\n");
    printf("-----------------------------------\n");

    for (i = 0; i < n; i++) {
        flag1 = flag2 = 0;

        // Check if page already exists
        for (j = 0; j < framesCount; j++) {
            if (frames[j] == pages[i]) {
                flag1 = flag2 = 1;
                break;
            }
        }

        // Empty frame available
        if (flag1 == 0) {
            for (j = 0; j < framesCount; j++) {
                if (frames[j] == -1) {
                    frames[j] = pages[i];
                    pageFaults++;
                    flag2 = 1;
                    break;
                }
            }
        }

        // No empty frame — find optimal page to replace
        if (flag2 == 0) {
            for (j = 0; j < framesCount; j++) {
                future[j] = -1;
                for (k = i + 1; k < n; k++) {
                    if (frames[j] == pages[k]) {
                        future[j] = k;
                        break;
                    }
                }
            }

            pos = -1;
            max = -1;
            for (j = 0; j < framesCount; j++) {
                if (future[j] == -1) {
                    pos = j;
                    break;
                } else if (future[j] > max) {
                    max = future[j];
                    pos = j;
                }
            }

            frames[pos] = pages[i];
            pageFaults++;
        }

        printf("For page %2d: ", pages[i]);
        for (j = 0; j < framesCount; j++) {
            if (frames[j] == -1)
                printf(" - ");
            else
                printf("%2d ", frames[j]);
        }

        if (flag1 == 0)
            printf(" (Page Fault)\n");
        else
            printf(" (Hit)\n");
    }

    printf("\nTotal Page Faults = %d\n", pageFaults);
    printf("Total Page Hits = %d\n", n - pageFaults);
}

// ---------- LRU (Counter Method) ----------
void lru_counter(int pages[], int n, int framesCount) {
    int frames[MAX_FRAMES], counter[MAX_FRAMES];
    int time = 0, pageFaults = 0, i, j, pos, flag1, flag2, min;

    for (i = 0; i < framesCount; i++) {
        frames[i] = -1;
        counter[i] = 0;
    }

    printf("\nPage Replacement Process (LRU - Counter Method):\n");
    printf("-------------------------------------------------\n");

    for (i = 0; i < n; i++) {
        flag1 = flag2 = 0;

        // Check if page already exists
        for (j = 0; j < framesCount; j++) {
            if (frames[j] == pages[i]) {
                time++;
                counter[j] = time;
                flag1 = flag2 = 1;
                break;
            }
        }

        // Empty frame available
        if (flag1 == 0) {
            for (j = 0; j < framesCount; j++) {
                if (frames[j] == -1) {
                    time++;
                    frames[j] = pages[i];
                    counter[j] = time;
                    pageFaults++;
                    flag2 = 1;
                    break;
                }
            }
        }

        // No empty frame — find least recently used
        if (flag2 == 0) {
            min = counter[0];
            pos = 0;
            for (j = 1; j < framesCount; j++) {
                if (counter[j] < min) {
                    min = counter[j];
                    pos = j;
                }
            }
            time++;
            frames[pos] = pages[i];
            counter[pos] = time;
            pageFaults++;
        }

        printf("For page %2d: ", pages[i]);
        for (j = 0; j < framesCount; j++) {
            if (frames[j] == -1)
                printf(" - ");
            else
                printf("%2d ", frames[j]);
        }
        if (flag1 == 1)
            printf(" (Hit)\n");
        else
            printf(" (Page Fault)\n");
    }

    printf("\nTotal Page Faults = %d\n", pageFaults);
    printf("Total Page Hits = %d\n", n - pageFaults);
}

// ---------- LRU (Stack Method) ----------
void lru_stack(int pages[], int n, int framesCount) {
    int stack[MAX_FRAMES], pageFaults = 0, i, j, k, top = -1, found;

    printf("\nPage Replacement Process (LRU - Stack Method):\n");
    printf("------------------------------------------------\n");

    for (i = 0; i < n; i++) {
        found = 0;

        // Check if page exists in stack
        for (j = 0; j <= top; j++) {
            if (stack[j] == pages[i]) {
                found = 1;
                int temp = stack[j];
                for (k = j; k < top; k++)
                    stack[k] = stack[k + 1];
                stack[top] = temp; // Move to top (most recently used)
                break;
            }
        }

        // If not found
        if (found == 0) {
            if (top < framesCount - 1) {
                stack[++top] = pages[i];
            } else {
                for (j = 0; j < top; j++)
                    stack[j] = stack[j + 1];
                stack[top] = pages[i];
            }
            pageFaults++;
        }

        printf("For page %2d: ", pages[i]);
        for (j = 0; j <= top; j++)
            printf("%2d ", stack[j]);
        for (; j < framesCount; j++)
            printf(" - ");
        if (found == 0)
            printf(" (Page Fault)\n");
        else
            printf(" (Hit)\n");
    }

    printf("\nTotal Page Faults = %d\n", pageFaults);
    printf("Total Page Hits = %d\n", n - pageFaults);
}

// ---------- Main Function ----------
int main() {
    int pages[MAX_PAGES], n, framesCount, choice, i;

    printf("Enter number of pages: ");
    scanf("%d", &n);

    printf("Enter the reference string:\n");
    for (i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    printf("Enter number of frames: ");
    scanf("%d", &framesCount);

    printf("\nSelect Page Replacement Algorithm:\n");
    printf("1. FIFO\n");
    printf("2. Optimal\n");
    printf("3. LRU (Counter Method)\n");
    printf("4. LRU (Stack Method)\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            fifo(pages, n, framesCount);
            break;
        case 2:
            optimal(pages, n, framesCount);
            break;
        case 3:
            lru_counter(pages, n, framesCount);
            break;
        case 4:
            lru_stack(pages, n, framesCount);
            break;
        default:
            printf("Invalid choice!\n");
    }

    return 0;
}
