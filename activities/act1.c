#include "../header/traffic.h"
#define FILE_NAME "./files/traffic.dat"

int getTimeForMainPedestrian(TrafficHeap tHeap);

int main() {
    initFile(FILE_NAME);
    TrafficHeap tHeap = getTraffic(FILE_NAME);
    
    int s = getTimeForMainPedestrian(tHeap);

    if(s != -1) {
        int seconds = s;

        int hours = seconds / 3600;
        seconds %= 3600;

        int minutes = seconds / 60;
        seconds %= 60;

        printf("The total time it takes until a main pedestrian can START crossing the road is %d seconds or %02d:%02d:%02d.\n", s, hours, minutes, seconds);
    }
    else {
        printf("There are no main pedestrians in the traffic queue.\n");
    }

    return 0;
}

int getTimeForMainPedestrian(TrafficHeap tHeap) {
    int seconds = 0;
    bool isMainPed = false;
    while(tHeap.lastIndex > -1 && isMainPed == false) {
        Traffic temp = deleteMin(&tHeap);
        
        if(temp.type == PEDESTRIAN && temp.lane == MAIN) {
            isMainPed = true;
        }
        else {
            seconds += temp.timeInSeconds;
        }
    }

    return (isMainPed) ? seconds : -1;
}