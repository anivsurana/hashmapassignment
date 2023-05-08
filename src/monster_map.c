#include "monster_utils.h"
#include "hash_map_utils.h"
#include "utils.h"

#include <stdlib.h>
#include <stdio.h>


/*
 * Returns the hash value of a given key.
 */
int hash_function(void *key) {
    // TODO: Implement the hash function.
}

/*
 * Returns the index of a given key.
 */
int compute_index(void *key, int map_size) {
    // TODO: Implement the hash function.
}

/*
 * Returns 1 if the keys are equal, 0 otherwise.
 */
int key_equals(void *key1, void *key2) {
    // TODO: Implement the key comparison function.
}

/*
 * Returns the next index based on a probing function.
 */
int probe_fn(int index, int i, int map_size) {
    // TODO: Implement the probing function.
}

/*
 * Inserts a new element into the map.
 */
void insert_fn(void *elem, void *new_elem) {
    // TODO: Implement the insertion function.
}

void add_monster(hash_map_t *map) {
    monster_s *monster = create_monster();
    hash_element_t *elem = calloc(1, sizeof(hash_element_t));
    elem->key = monster->name;
    elem->value = monster;

    // TODO: Check if the monster already exists. If it does, free the monster and return.

    insert(map, elem);
}

void search_monsters(hash_map_t *map) {
    char *name = get_string("Enter monster name: ");
    hash_element_t *elem = search(map, name);
    if (elem != NULL) {
        print_monster(elem->value);
    } else {
        printf("No monster found with name %s\n", name);
    }
    free(name);
}

void print_map(hash_map_t *map) {
    printf("Primary Map:\n");
    for (int i = 0; i < map->map_size; i++) {
        if (map->primary[i] != NULL) {
            print_monster(map->primary[i]->value);
        }
    }
    if (map->temp != NULL) {
        printf("Temp Map:\n");
        for (int i = 0; i < map->temp_size; i++) {
            if (map->temp[i] != NULL) {
                print_monster(map->temp[i]->value);
            }
        }
    }
}

void print_menu() {
    printf("1. Add Monster\n");
    printf("2. Import CSV File\n");
    printf("3. Search\n");
    printf("4. Print Map\n");
    printf("5. Exit\n");
}

// TODO: Create function to create an array of hash_element_t based on unique entries in array.
void add_monsters(hash_map_t *map) {
    // Loop through `monsters` and check which of them are unique using `search`
    // For each unique monster, place it in a `hash_element_t` object using the monster's name as its key.
    // Add the array of `hash_element_t` objects to the hash map.
    char *filename = get_string("Enter filename: ");
    array_s monsters = load_monsters_csv(filename);

    if (monsters.numel == 0) {
        printf("No monsters found in file %s\n", filename);
        return;
    }

    array_s unique_monsters = { 0 };
    for (int i = 0; i < monsters.numel; i++) {
        monster_s *monster = monsters.data[i];
        if (search(map, monster->name) != NULL) {
            continue;
        }
        hash_element_t *elem = calloc(1, sizeof(hash_element_t));
        elem->key = monster->name;
        elem->value = monster;

        push(elem, &unique_monsters);
    }

    bulk_insert(map, &unique_monsters);
}

int main() {
    hash_map_t *map = calloc(1, sizeof(hash_map_t));
    char selection = 0;

    init_map(map, 4, hash_function, compute_index, key_equals, probe_fn, insert_fn);

    while (selection != '5') {
        print_menu();
        printf("> ");
        scanf("%c", &selection);

        // Clear buffer if newline stuck.
        if (selection != '\n') while (getchar() != '\n');

        switch (selection) {
            case '1':
                // Create a monster via `create_monster` and add it to the map.
                add_monster(map);
                break;
            case '2':
                // Load a monsters via CSV.
                add_monsters(map);
                break;
            case '3':
                // Prompt the user for a search key and then call `search`
                search_monsters(map);
                break;
            case '4':
                print_map(map);
                break;
            case '5':
                printf("Good bye!\n");
                // TODO: Free all memory currently allocated.
                break;
            default:
                printf("Invalid selection.\n");
        }
    }

    return 0;
}
