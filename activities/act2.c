#include "../header/traffic.h"
#define FILE_NAME "./files/traffic.dat"

int main() {
    initFile(FILE_NAME);
    TrafficHeap tHeap = getTraffic(FILE_NAME);

    return 0;
}