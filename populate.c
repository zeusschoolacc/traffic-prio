#include "./header/traffic.h"

#define FILENAME "./files/traffic.dat"

int main() {
    initFile(FILENAME);

    TrafficHeap tHeap = getTraffic(FILENAME);
    TrafficHeap newHeap = {.lastIndex = -1};

    Traffic temp;

    printf("%10s%10s%10s\n", "Type", "Lane", "Time");
    while(tHeap.lastIndex > -1) {
        temp = deleteMin(&tHeap);
        insert(&newHeap, temp);
        printf("%10d%10d%10d\n", temp.type, temp.lane, temp.timeInSeconds);
    }

    tHeap = newHeap;
    
    int t;

    printf("\nEnter type of intersection:\n");
    printf("[0] Straight\n");
    printf("[1] Left\n");
    printf("[2] Right\n");
    printf("[3] Pedestrian\n");
    printf("Choice: ");
    scanf("%d", &t);
    temp.type = t;

    printf("Enter type of lane:\n");
    printf("[0] Main\n");
    printf("[1] Diversion\n");
    printf("Choice: ");
    scanf("%d", &t);
    temp.lane = t;

    printf("Enter time to complete action (in seconds): ");
    scanf("%d", &temp.timeInSeconds);

    insert(&tHeap, temp);

    updateFile(FILENAME, tHeap);

    return 0;
}