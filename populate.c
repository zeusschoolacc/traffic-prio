#include "./header/traffic.h"

#define FILE_NAME "./files/traffic.dat"

int main() {
    initFile(FILE_NAME);

    TrafficHeap tHeap = getTraffic(FILE_NAME);
    TrafficHeap nHeap = newHeap();

    Traffic temp;

    printf("%10s%10s%10s\n", "Type", "Lane", "Time");
    while(tHeap.lastIndex > -1) {
        temp = deleteMin(&tHeap);
        insert(&nHeap, temp);
        printf("%10d%10d%10d\n", temp.type, temp.lane, temp.timeInSeconds);
    }

    tHeap = nHeap;
    
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

    updateFile(FILE_NAME, tHeap);

    return 0;
}