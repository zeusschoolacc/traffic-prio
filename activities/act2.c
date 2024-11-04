#include "../header/traffic.h"
#define FILE_NAME "./files/traffic.dat"
#define SCENARIO_FILE_NAME "./files/traffic_result.dat"

void insertScenario(Scenarios *s, char *scenario);
void trafficToScenario(TrafficHeap tHeap, Scenarios *s);
void addScenarioToFile(Scenarios s);

int main() {
    initFile(FILE_NAME);
    TrafficHeap tHeap = getTraffic(FILE_NAME);

    char choice;
    printf("Save current scenario in traffic.dat into traffic_result.dat? [y/n]: ");
    scanf(" %c", &choice);

    if(tolower(choice) == 'y') {
        Scenarios s = newScenario();
        trafficToScenario(tHeap, &s);
        addScenarioToFile(s);
    }

    printf("Clear traffic.dat? [y/n]: ");
    scanf(" %c", &choice);

    if(tolower(choice) == 'y') {
        remove(FILE_NAME);
    }

    return 0;
}

void insertScenario(Scenarios *s, char *scenario) {
    if(s->count < MAX) {
        strcpy(s->scenario[s->count++], scenario);
    }
}

void trafficToScenario(TrafficHeap tHeap, Scenarios *s) {
    int queueNum = 1;
    while(tHeap.lastIndex > -1) {
        Traffic temp = deleteMin(&tHeap);
        char tString[SCENARIOLENGTH];
        sprintf(tString, "%-10d%-15s%-15s%8d\n", queueNum++, translateLane(temp.lane), translateType(temp.type), temp.timeInSeconds);
        insertScenario(s, tString);
        printf("%s", tString);
    }
}

void addScenarioToFile(Scenarios s) {
    FILE *fptr;

    if((fptr = fopen(SCENARIO_FILE_NAME, "r")) == NULL) {
        fptr = fopen(SCENARIO_FILE_NAME, "w");
    }
    else {
        fclose(fptr);
        fptr = fopen(SCENARIO_FILE_NAME, "a");

        fputs(",\n", fptr);
    }

    for(int i = 0; i < s.count; i++) {
        fputs(s.scenario[i], fptr);
    }

    fclose(fptr);
}