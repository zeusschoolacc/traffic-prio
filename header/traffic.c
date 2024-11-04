#include "./traffic.h"

void initFile(char *fileName) {
    FILE* fptr;

    if(fptr = fopen(fileName, "rb") == NULL) {
        fclose(fptr);
        fptr = fopen(fileName, "wb");
    }

    fclose(fptr);
}

void updateFile(char *fileName, TrafficHeap tHeap) {
    FILE *fptr;

    if(fptr = fopen(fileName, "wb") == NULL) {
        printf("Error: Unable to open file");
    }
    else if(fwrite(tHeap.traffic, sizeof(Traffic), tHeap.lastIndex + 1, fptr) <= tHeap.lastIndex) {
        printf("Error: Unable to add all contents to file");
    }

    fclose(fptr);
}

TrafficHeap getTraffic(char *fileName) {
    FILE *fptr;
    TrafficHeap tHeap = {.lastIndex = -1};

    if(fptr = fopen(fileName, "rb") == NULL) {
        printf("Error: Unable to open file");
    }
    else {
        while(fread(tHeap.traffic + tHeap.lastIndex + 1, sizeof(Traffic), 1, fptr) != NULL) {
            tHeap.lastIndex++;
        }
    }

    return tHeap;
}