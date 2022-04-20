#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include "cjson.h"

#define ERROR_NULL_PTR     (-1)

static int delete_spaces_from_end(char* word) {
    if (!word) {
        return ERROR_NULL_PTR;
    }

    int length = strlen(word);

    while (isspace(word[length - 1])) {
        length -= 1;
    }

    char* changed_word = strndup(word, length);

    strcpy(word, changed_word);
    return 0;
}

int get_date(const char* path_to_eml, char* date) {
    if (!path_to_eml || !date) {
        return ERROR_NULL_PTR;
    }

    FILE *file_ptr = fopen(path_to_eml, "r");
    if (!file_ptr) {
        return ERROR_NULL_PTR;
    }

    int amount_of_assigned_values = fscanf(file_ptr, "%100s", date);

    while (amount_of_assigned_values != -1) {
        if (!strcmp(date, "Date") || !strcmp(date, "Date:")) {
            break;
        }
        amount_of_assigned_values = fscanf(file_ptr, "%100s", date);

        if (amount_of_assigned_values == -1) {
            strncpy(date, "", 1);
            fclose(file_ptr);
            return 0;
        }
    }

    if (!strcmp(date, "Date")) {
        fscanf(file_ptr, "%100s", date);
    }

    char potential_space[ ] = {0};

    fscanf(file_ptr, "%c", potential_space);

    while (!strcmp(potential_space, " ")) {
        fscanf(file_ptr, "%c", potential_space);
    }

    fgets(date, MAX_SIZE_OF_DATE, file_ptr);
    if (delete_spaces_from_end(date)) {
        return ERROR_NULL_PTR;
    }
    
    char secondary_word[MAX_SIZE_OF_SECONDARY_WORD] = {0};

    fgets(secondary_word, 100, file_ptr);
    if (delete_spaces_from_end(secondary_word)) {
        return ERROR_NULL_PTR;
    }

    while (secondary_word[0] == ' ' || secondary_word[0] == '\t') {
        strncat(date, secondary_word, MAX_SIZE_OF_SECONDARY_WORD);
        fgets(secondary_word, 100, file_ptr);
        if (delete_spaces_from_end(secondary_word)) {
            return ERROR_NULL_PTR;
        }
    }

    rewind(file_ptr);
    if (delete_spaces_from_end(date)) {
        return ERROR_NULL_PTR;
    }
    return 0;
}

int get_from(const char* path_to_eml, char* from) {
    if (!path_to_eml || !from) {
        return ERROR_NULL_PTR;
    }

    FILE *file_ptr = fopen(path_to_eml, "r");
    if (!file_ptr) {
        return ERROR_NULL_PTR;
    }

    int amount_of_assigned_values = fscanf(file_ptr, "%100s", from);

    while (amount_of_assigned_values != -1) {
        if (!strcmp(from, "From") || !strcmp(from, "From:")) {
            break; 
        }
        amount_of_assigned_values = fscanf(file_ptr, "%100s", from);

        if (amount_of_assigned_values == -1) {
            strncpy(from, "", 1);
            fclose(file_ptr);
            return 0;
        }
    }

    if (!strcmp(from, "From")) {
        fscanf(file_ptr, "%100s", from);
    }

    char potential_space[ ] = {0};

    fscanf(file_ptr, "%c", potential_space);

    while (!strcmp(potential_space, " ")) {
        fscanf(file_ptr, "%c", potential_space);
    }

    fgets(from, MAX_SIZE_OF_FROM, file_ptr);
    if (delete_spaces_from_end(from)) {
        return ERROR_NULL_PTR;
    }

    char secondary_word[MAX_SIZE_OF_SECONDARY_WORD] = {0};

    fgets(secondary_word, MAX_SIZE_OF_SECONDARY_WORD, file_ptr);
    if (delete_spaces_from_end(secondary_word)) {
        return ERROR_NULL_PTR;
    }

    while (secondary_word[0] == ' ' || secondary_word[0] == '\t') {
        strncat(from, secondary_word, MAX_SIZE_OF_SECONDARY_WORD);
        fgets(secondary_word, MAX_SIZE_OF_SECONDARY_WORD, file_ptr);
        if (delete_spaces_from_end(secondary_word)) {
            return ERROR_NULL_PTR;
        }
    }

    if (delete_spaces_from_end(from)) {
        return ERROR_NULL_PTR;
    }

    fclose(file_ptr);

    return 0;
}

int get_parts(const char* path_to_eml) {
    if (!path_to_eml) {
        return ERROR_NULL_PTR;
    }

    FILE *file_ptr = fopen(path_to_eml, "r");
    if (!file_ptr) {
        return ERROR_NULL_PTR;
    }

    int parts = 0;

    char test_word[MAX_SIZE_OF_SECONDARY_WORD] = {0};

    int amount_of_assigned_values = fscanf(file_ptr, "%99s", test_word);

    while (amount_of_assigned_values != -1) {
        if (!strcmp(test_word, "Content-Type") || !strcmp(test_word, "Content-Type:")) {
            break;
        }
        amount_of_assigned_values = fscanf(file_ptr, "%99s", test_word);

        if (amount_of_assigned_values == -1) {
            parts = 1;
            return parts;
        }
    }

    if (!strcmp(test_word, "Content-Type")) {
        fscanf(file_ptr, "%99s", test_word);
    }

    fscanf(file_ptr, "%99s", test_word);

    if (!strstr(test_word, "multipart")) {
        parts = 1;
        fclose(file_ptr);
        return parts;
    }

    char boundary[100] = {0};

    rewind(file_ptr);

    char symbol = 0;
    int i = 0;

    while (fscanf(file_ptr, "%c", &symbol) != -1) {
            if (symbol == 'b') {
                fseek(file_ptr, -2, SEEK_CUR);
                fscanf(file_ptr, "%c", &symbol);
                fseek(file_ptr, 1, SEEK_CUR);
                if (symbol != ' ') {
                    continue;
                }
                fscanf(file_ptr, "%c", &symbol);
                if (symbol == 'o') {
                    fscanf(file_ptr, "%c", &symbol);
                    if (symbol == 'u') {
                        fscanf(file_ptr, "%c", &symbol);
                        if (symbol == 'n') {
                            fscanf(file_ptr, "%c", &symbol);
                            if (symbol == 'd') {
                                fscanf(file_ptr, "%c", &symbol);
                                if (symbol == 'a') {
                                    fscanf(file_ptr, "%c", &symbol);
                                    if (symbol == 'r') {
                                        fscanf(file_ptr, "%c", &symbol);
                                        if (symbol == 'y') {
                                            fscanf(file_ptr, "%c", &symbol);
                                            if (symbol == '=') {
                                                while (1) {
                                                    fscanf(file_ptr, "%c", &symbol);
                                                    if (symbol == '"') {
                                                        continue;
                                                    }
                                                    if (isspace(symbol)) {
                                                        break;
                                                    }
                                                    boundary[i] = symbol;
                                                    i += 1;
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        if (i > 0) {
            break;
        }
    }
    if (i) {
        int count_of_boundaries = 0;
        int j = 0;
        while (fscanf(file_ptr, "%c", &symbol) != -1) {
            while (symbol == boundary[j]) {
                fscanf(file_ptr, "%c", &symbol);
                j += 1;
                if (symbol != boundary[j]) {
                    j = 0;
                    break;
                }
                if (j == i - 1) {
                    j = 0;
                    count_of_boundaries += 1;
                    break;
                }
            }
        }
        parts = count_of_boundaries - 1;
        fclose(file_ptr);
        return parts;
    }
    parts = 1;
    
    fclose(file_ptr);
    return parts;
}

int get_to(const char* path_to_eml, char* to) {
    if (!path_to_eml || !to) {
        return ERROR_NULL_PTR;
    }

    FILE *file_ptr = fopen(path_to_eml, "r");
    if (!file_ptr) {
        return ERROR_NULL_PTR;
    }

    char potential_space[ ] = {0};

    int amount_of_assigned_values = fscanf(file_ptr, "%99s", to);

    while (amount_of_assigned_values != -1) {
        if (!strcmp(to, "To") || !strcmp(to, "To:")) {
            break;
        }
        amount_of_assigned_values = fscanf(file_ptr, "%99s", to);

        if (amount_of_assigned_values == -1) {
            strncpy(to, "", 1);
            fclose(file_ptr);
            return 0;
        }
    }

    if (!strcmp(to, "To")) {
        fscanf(file_ptr, "%100s", to);
    }

    fscanf(file_ptr, "%c", potential_space);

    while (!strcmp(potential_space, " ")) {
        fscanf(file_ptr, "%c", potential_space);
    }

    fgets(to, MAX_SIZE_OF_TO, file_ptr);
    if (delete_spaces_from_end(to)) {
        return ERROR_NULL_PTR;
    }
    
    char secondary_word[MAX_SIZE_OF_SECONDARY_WORD] = {0};

    fgets(secondary_word, MAX_SIZE_OF_SECONDARY_WORD, file_ptr);
    if (delete_spaces_from_end(secondary_word)) {
        return ERROR_NULL_PTR;
    }

    while (secondary_word[0] == ' ' || secondary_word[0] == '\t') {
        strncat(to, secondary_word, MAX_SIZE_OF_SECONDARY_WORD);
        fgets(secondary_word, MAX_SIZE_OF_SECONDARY_WORD, file_ptr);
        if (delete_spaces_from_end(secondary_word)) {
            return ERROR_NULL_PTR;
        }
    }

    if (delete_spaces_from_end(to)) {
        return ERROR_NULL_PTR;
    }

    fclose(file_ptr);

    return 0;
}
