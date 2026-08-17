#include <stdio.h>
#include <stdbool.h>

void simulate_lru(int page_requests[], int num_requests, int num_frames);
void print_frames(int frames[], int num_frames);

void simulate_lru(int page_requests[], int num_requests, int num_frames) {
    int frames[num_frames];
    int last_used[num_frames]; // Timestamp array
    int page_faults = 0;

    // initialize empty slots
    for (int i = 0; i < num_frames; i++) {
        frames[i] = -1;
        last_used[i] = -1;
    }

    for (int time = 0; time < num_requests; time++) {
        int page = page_requests[time];
        bool hit = false;

        // Check if 'page' is already in 'frames' (HIT)
        // loop through frames, if page found => hit, update its timestamp
        int hit_index = -1;
        for (int i = 0; i < num_frames; i++) {
            if (frames[i] == page) {
                hit = true;
                hit_index = i;
                last_used[i] = time;  // refresh timestamp since it was just used
                break;
            }
        }

        // Handle PAGE FAULT if not found
        if (!hit) {
            page_faults++;

            // first check for an empty slot
            int target = -1;
            for (int i = 0; i < num_frames; i++) {
                if (frames[i] == -1) {
                    target = i;
                    break;
                }
            }

            // if no empty slot, find LRU => smallest timestamp in last_used[]
            if (target == -1) {
                int min_time = last_used[0];
                target = 0;
                for (int i = 1; i < num_frames; i++) {
                    if (last_used[i] < min_time) {
                        min_time = last_used[i];
                        target = i;
                    }
                }
            }

            // replace that frame with the new page, stamp it with current time
            frames[target] = page;
            last_used[target] = time;
        }

        // print this request's status + current RAM state
        printf("%d\t%s\t", page, hit ? "HIT" : "FAULT");
        print_frames(frames, num_frames);
    }

    printf("Total Page Faults: %d\n", page_faults);
}

// helper to print frames like [1, -, -]
void print_frames(int frames[], int num_frames) {
    printf("[");
    for (int i = 0; i < num_frames; i++) {
        if (frames[i] == -1)
            printf("-");
        else
            printf("%d", frames[i]);

        if (i != num_frames - 1)
            printf(", ");
    }
    printf("]\n");
}

int main() {
    int requests[] = {1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 5};
    int num_requests = sizeof(requests) / sizeof(requests[0]);

    simulate_lru(requests, num_requests, 3);
    return 0;
}