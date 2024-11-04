#ifndef TRAFFIC_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TRAFFIC_HEADER

#define MAX 50

typedef enum {
    STRAIGHT,
    LEFT,
    RIGHT,
    PEDESTRIAN,
    TYPE_ERROR
} TrafficType;

typedef enum {
    MAIN,
    DIVERSION,
    LANE_ERROR
} TrafficLane;

typedef int Seconds;

typedef struct {
    TrafficType type;
    TrafficLane lane;
    Seconds timeInSeconds; 
} Traffic;

typedef struct {
    Traffic traffic[MAX];
    int lastIndex;
} TrafficHeap;

void initFile(char *fileName);
void updateFile(char *fileName, TrafficHeap tHeap);
TrafficHeap getTraffic(char *fileName);
int getPriority(Traffic traffic);
void insert(TrafficHeap *tHeap, Traffic temp);
Traffic deleteMin(TrafficHeap *tHeap);

#endif