#include "monster_utils.h"
#include "utils.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>


/*
 * Frees allocated memory of a monster.
 *
 */
void free_monster(void *monster) {
    // TODO: Cast the `void *monster` to the proper type and free
    //       all struct members that have allocated memory.

    monster_s *m = (monster_s *)monster;
    free(m->name);
    free(m->type);
    free(m);
}

/*
 * Prints the attributes of a single monster object.
 */
void print_monster(monster_s *monster) {
    // TODO: Cast the `void *monster` to the proper type and print
    //       the attributes.

    // Print as CSV
    printf("%s,%s,%d,%d,%d,%d,%d\n", monster->name, monster->type, monster->hp, monster->ac, monster->str, monster->dex, monster->con);
}

/*
 * Creates a monster based on user input.
 */
monster_s *create_monster() {
    char buffer[BUF_SIZE] = { 0 };

    monster_s *m = calloc(1, sizeof(monster_s));

    m->name = get_string("Enter a name: ");

    m->type = get_string("Enter a type: ");

    printf("Enter HP: ");
    scanf("%d", &m->hp);

    printf("Enter AC: ");
    scanf("%d", &m->ac);

    printf("Enter STR: ");
    scanf("%d", &m->str);

    printf("Enter DEX: ");
    scanf("%d", &m->dex);

    printf("Enter CON: ");
    scanf("%d", &m->con);

    return m;
}

/*
 * Parses a line of CSV containing monster stats.
 */
monster_s *parse_monster(char *csv_line) {
    char *token = strtok(csv_line, ",");
    int attr = 0;

    monster_s *monster = calloc(1, sizeof(monster_s));

    while (token) {
        switch(attr) {
            case 0:
                monster->name = strdup(token);
                break;
            case 1:
                monster->type = strdup(token);
                break;
            case 2:
                monster->hp = atoi(token);
                break;
            case 3:
                monster->ac = atoi(token);
                break;
            case 4:
                monster->str = atoi(token);
                break;
            case 5:
                monster->dex = atoi(token);
                break;
            case 6:
                monster->con = atoi(token);
                break;
        }

        attr++;
        token = strtok(NULL, ",");
    }

    return monster;
}

/*
 * Load monster data from a CSV file.
 *
 * Returns an `array_s` object containing the monsters loaded.
 */
array_s load_monsters_csv(char *filename) {

    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error opening file: %s\n", filename);
        return (array_s) { 0 };
    }

    array_s monsters = { 0 };

    // TODO: Complete this function.
    char buffer[BUF_SIZE] = { 0 };

    while (fgets(buffer, BUF_SIZE, fp)) {
        trim(buffer);
        if (strlen(buffer) == 0) {
            continue;
        }

        monster_s *monster = parse_monster(buffer);
        push(monster, &monsters);
    }

    return monsters;
}

/*
 * Generates a unique key for a monster based on its name.
 */
int get_key(monster_s *monster) 
{
    int key = 0;
    const char *name = monster->name;
    for (int i = 0; i < strlen(name); i++) 
    {
        key += name[i] * (i+1);
    }
    return key;
}
