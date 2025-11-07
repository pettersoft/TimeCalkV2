#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "string-functions.h"
#include "timecalk.h"

void printStatus(
const WORK_GRP *groups,
const size_t groups_added
);

int main(void) {

    char str[16];
    const size_t len = sizeof(str);
    printf("Klistra in eller ange manuellt\n");

    WORK_GRP grp;
    init_grp(&grp);
    str_alloc_copy(&grp.group_name, "Temp");

    WORK_GRP *groups = malloc(sizeof(WORK_GRP));

    int laps = 0;
    size_t groups_added = 0;
    size_t groups_cap = 1;
    while (fgets(str, len, stdin) != NULL) {
        if (str[0] == '\n') {
            printf("Avslutar loop\n");
            break;
        }

        size_t position_newline = strcspn(str, "\n");
        // Convert to EOL instead of newline
        if (str[position_newline] == '\n') {
            str[position_newline] = '\0';
        } else {
            int ch;
            printf("Overflow, rensar strömmen...");
            while ((ch = getchar()) != '\n' && ch != EOF) {
                printf("%d", (char)ch);
            }

            printf("\nStarta om varv\n");
            continue;
        }

        clear_whitespace(str);

        if (laps == 0 && str[0] != '#') {
            // LÄgg till grupp 1 på en gång
            groups[groups_added] = grp;
            groups_added++;
        }

        // Här kör vi logiken
        // Om en grupp inte är initierat så vill vi starta en grupp nu
        if (str[0] == '#') {
            // Första varvet behöver vi inte stänga föregående grupp
            if (laps == 0) {
                // Kopiera värdet till gruppens namn
                str_alloc_copy(&grp.group_name, str);
                printf("Grupp 1, med namn %s, har initierats\n", grp.group_name);

                // LÄgg till grupp 1 på en gång
                groups[groups_added] = grp;
                groups_added++;
            } else {
                if (groups_added == groups_cap) {
                    const size_t new_cap = groups_cap * 2;

                    WORK_GRP *tmp = realloc(groups, new_cap * sizeof(*groups));
                    if (!tmp) {
                        for (size_t i = 0; i < groups_added; ++i) free_grp(&groups[i]);
                        free(groups);
                        exit(EXIT_FAILURE);
                    }

                    groups = tmp;
                    groups_cap = new_cap;
                }

                printf("Den förra gruppen skall nu stängas\n");
                printf("Initierar ny grupp...\n");
                init_grp(&grp);
                // Sätt det nya namnet på gruppen
                str_alloc_copy(&grp.group_name, str);

                groups[groups_added++] = grp;
            }
        } else {
            // Om det inte börjar med # så försöker vi parsa
            // vi förväntar is 08:00->12:00
            int tmpMinutesWorked;
            if (parse_str_to_minutes_worked(str, &tmpMinutesWorked)) {
                groups[groups_added - 1].workedMinutes += tmpMinutesWorked;
            }
        }

        laps++;

        printStatus(groups, groups_added);
    }

    free(groups);
    return 0;
}

void printStatus(
const WORK_GRP *groups,
const size_t groups_added
) {
    printf("#############~Status~################\n");
    int total_worked = 0;
    int total_absence = 0;
    for (size_t i = 0; i < groups_added; i++) {
        const WORK_GRP *group = &groups[i];

        char *pretty = parse_minutes_to_pretty_str(group->workedMinutes);
        printf("För grupp %s, har du arbetat: %s\n", group->group_name, pretty);

        free(pretty);

        total_worked += groups[i].workedMinutes;
    }

    total_absence = 480 - total_worked;

    char *totStr = parse_minutes_to_pretty_str(total_worked);
    char *totAbsence = parse_minutes_to_pretty_str(total_absence);
    printf("Totalt har du arbetat %s, frånvaro: %s\n", totStr, totAbsence);

    free(totStr);
    free(totAbsence);

    printf("###############################\n");
}
