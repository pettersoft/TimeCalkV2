//
// Created by pettersoft on 10/30/25.
//

#include "timecalk.h"

#include <stdio.h>
#include <stdlib.h>

const int minutes_in_work_day = 480;

void init_grp(WORK_GRP *grp) {
    if (!grp) return;

    grp->group_name=NULL;
    grp->workedMinutes=0;
}
void free_grp(WORK_GRP *grp) {
    free(grp->group_name);

    init_grp((grp));
}

int parse_str_to_minutes_worked(const char *str, int *minutesWorked) {
    int startHour, startMinutes, endHour, endMinutes;

    if (sscanf(
        str,
        "%d:%d->%d:%d",
        &startHour,
        &startMinutes,
        &endHour,
        &endMinutes
        )
        ) {
        startMinutes += startHour * 60;
        endMinutes += endHour * 60;

        *minutesWorked = endMinutes - startMinutes;

        return 1;
    }
    return 0;
}

// Must free
char* parse_minutes_to_pretty_str(int minutesWorked) {
    int hours = minutesWorked / 60;
    int minutes = minutesWorked % 60;

    if (hours < 0) hours = 0;
    if (minutes < 0) minutes = 0;

    size_t size = 64;
    char *buffer = malloc(size);
    snprintf(buffer, size, "%d timmar och %d minuter", hours, minutes);

    return buffer;
}
