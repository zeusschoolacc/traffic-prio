#include "./traffic.h"

void initFile(char *fileName) {
    FILE* fptr;

    if((fptr = fopen(fileName, "rb")) == NULL) {
        printf("Warning: File '%s' not found. Creating file...\n", fileName);
        // fclose(fptr); // NO FCLOSE BECAUSE IT IS NULL
        fptr = fopen(fileName, "wb");
    }

    fclose(fptr);
}

void updateFile(char *fileName, TrafficHeap tHeap) {
    FILE *fptr;

    if((fptr = fopen(fileName, "wb")) == NULL) {
        printf("Error: Unable to open file\n");
    }
    else if(fwrite(tHeap.traffic, sizeof(Traffic), tHeap.lastIndex + 1, fptr) <= tHeap.lastIndex) {
        printf("Error: Unable to add all contents to file\n");
    }

    fclose(fptr);
}

TrafficHeap getTraffic(char *fileName) {
    FILE *fptr;
    TrafficHeap tHeap = {.lastIndex = -1};

    if((fptr = fopen(fileName, "rb")) == NULL) {
        printf("Error: Unable to open file\n");
    }
    else {
        while( 
            tHeap.lastIndex + 1 < MAX
            && fread(tHeap.traffic + tHeap.lastIndex + 1, sizeof(Traffic), 1, fptr) > 0
        ) {
            tHeap.lastIndex++;
        }
    }

    return tHeap;
}

int getPriority(Traffic traffic) {
    return traffic.type * 2 + traffic.lane;
}

TrafficHeap newHeap() {
    TrafficHeap temp = {.lastIndex = -1};

    return temp;
}

Scenarios newScenario() {
    Scenarios temp = {.count = 0};

    return temp;
}

void insert(TrafficHeap *tHeap, Traffic temp) {
    if(tHeap->lastIndex + 1 < MAX && temp.lane != LANE_ERROR) {
        int child = ++tHeap->lastIndex;
        int parent = (child - 1) / 2;

        for(
            ; 
            child > 0 && getPriority(tHeap->traffic[parent]) > getPriority(temp);
            child = parent, parent = (parent - 1) / 2
        ) {
            tHeap->traffic[child] = tHeap->traffic[parent];
        }

        tHeap->traffic[child] = temp;
    }
}

Traffic deleteMin(TrafficHeap *tHeap) {
    Traffic temp = {TYPE_ERROR, LANE_ERROR, -1}; // default value

    if (tHeap->lastIndex > -1) {
        temp = tHeap->traffic[0];

        int parent = 0;
        int lChild = parent * 2 + 1;
        int rChild = parent * 2 + 2;
        int child = (rChild > tHeap->lastIndex || getPriority(tHeap->traffic[lChild])) < getPriority(tHeap->traffic[rChild]) ? lChild : rChild;

        for(
            ;
            child <= tHeap->lastIndex && getPriority(tHeap->traffic[child]) >= getPriority(temp);
            parent = child, lChild = parent * 2 + 1, rChild = parent * 2 + 2, child = (rChild > tHeap->lastIndex || getPriority(tHeap->traffic[lChild])) ? lChild : rChild
        ) {
            // printf("PARENT: %d, LCHILD: %d, RCHILD: %d\n", getPriority(tHeap->traffic[parent]), getPriority(tHeap->traffic[lChild]), getPriority(tHeap->traffic[rChild]));
            tHeap->traffic[parent] = tHeap->traffic[child];
        }

        tHeap->traffic[parent] = tHeap->traffic[tHeap->lastIndex--];
    }

    return temp;
}

char *translateType(TrafficType type) {
    char ret[15] = "";

    switch(type) {
        case STRAIGHT:
            strcpy(ret, "Straight"); break;
        case LEFT:
            strcpy(ret, "Left"); break;
        case RIGHT:
            strcpy(ret, "Right"); break;
        case PEDESTRIAN:
            strcpy(ret, "Pedestrian");
    }

    char *temp = (char *)malloc(sizeof(char) * (strlen(ret) + 1));
    strcpy(temp, ret);

    return temp;
}

char *translateLane(TrafficLane lane) {
    char ret[10] = "";

    switch(lane) {
        case MAIN:
            strcpy(ret, "Main"); break;
        case DIVERSION:
            strcpy(ret, "Diversion"); break;
    }

    char *temp = (char *)malloc(sizeof(char) * (strlen(ret) + 1));
    strcpy(temp, ret);

    return temp;
}