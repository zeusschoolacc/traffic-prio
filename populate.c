#include "./header/traffic.h"

#define FILENAME "./files/traffic.dat"

int main() {
    initFile(FILENAME);

    TrafficHeap tHeap = getTraffic(FILENAME);

    

}