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
    PEDESTRIAN
} TrafficPriority;

typedef enum {
    MAIN,
    DIVERSION
} TrafficLane;

typedef int Seconds;

typedef struct {
    TrafficPriority priority;
    TrafficLane lane;
    Seconds timeInSeconds; 
} Traffic;

typedef struct {
    Traffic traffic[MAX];
    int lastIndex;
} TrafficHeap;

#endif