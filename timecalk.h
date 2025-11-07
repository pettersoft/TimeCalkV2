//
// Created by pettersoft on 10/30/25.
//

#ifndef STRINGPARSER_TIMECALK_H
#define STRINGPARSER_TIMECALK_H
#include <stddef.h>

#endif //STRINGPARSER_TIMECALK_H

typedef struct {
    int hours;
    int minutes;
} TIME_CALK;

typedef struct  {
    char* group_name;
    int workedMinutes;
} WORK_GRP;

void init_grp(WORK_GRP *grp);
void free_grp(WORK_GRP *grp);

int parse_str_to_minutes_worked(const char *str, int *minutesWorked);
char* parse_minutes_to_pretty_str(int minutesWorked);