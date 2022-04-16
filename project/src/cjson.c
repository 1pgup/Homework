#include <ctype.h>
#include <stdio.h>

#include "cjson.h"

int is_content_type_found(char* filename) {
    if (!filename) {
        return ERROR_NULL_PTR;
    }

    FILE* cur_ptr = fopen(filename, "r");
    if (!cur_ptr) {
        return ERROR_NULL_PTR;
    }

    char symbol = 0;

    while (fscanf(cur_ptr, "%c", &symbol) != -1) {
        if (symbol == '\n' || symbol == '\r') {
            fscanf(cur_ptr, "%c", &symbol);
            if (symbol == 'C') {
                fscanf(cur_ptr, "%c", &symbol);
                if (symbol == 'o') {
                    fscanf(cur_ptr, "%c", &symbol);
                    if (symbol == 'n') {
                        fscanf(cur_ptr, "%c", &symbol);
                        if (symbol == 't') {
                            fscanf(cur_ptr, "%c", &symbol);
                            if (symbol == 'e') {
                                fscanf(cur_ptr, "%c", &symbol);
                                if (symbol == 'n') {
                                    fscanf(cur_ptr, "%c", &symbol);
                                    if (symbol == 't') {
                                        fscanf(cur_ptr, "%c", &symbol);
                                        if (symbol == '-') {
                                            fscanf(cur_ptr, "%c", &symbol);
                                            if (symbol == 'T') {
                                                fscanf(cur_ptr, "%c", &symbol);
                                                if (symbol == 'y') {
                                                    fscanf(cur_ptr, "%c", &symbol);
                                                    if (symbol == 'p') {
                                                        fscanf(cur_ptr, "%c", &symbol);
                                                        if (symbol == 'e') {
                                                            fscanf(cur_ptr, "%c", &symbol);
                                                            if (symbol == ':') {
                                                                fclose(cur_ptr);
                                                                return 0;
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
                    }
                }
            }
        }
    }
    fclose(cur_ptr);
    return 1;
}

int is_multipart(char* filename, int content_type_is_found) {
    if (!filename) {
        return ERROR_NULL_PTR;
    }

    if (content_type_is_found) {
        return 1;
    }

    FILE* cur_ptr = fopen(filename, "r");
    if (!cur_ptr) {
        return ERROR_NULL_PTR;
    }

    char symbol = 0;

    while (fscanf(cur_ptr, "%c", &symbol) != -1) {
        if (isspace(symbol)) {
            fscanf(cur_ptr, "%c", &symbol);
            if (symbol == 'm') {
                fscanf(cur_ptr, "%c", &symbol);
                if (symbol == 'u') {
                    fscanf(cur_ptr, "%c", &symbol);
                    if (symbol == 'l') {
                        fscanf(cur_ptr, "%c", &symbol);
                        if (symbol == 't') {
                            fscanf(cur_ptr, "%c", &symbol);
                            if (symbol == 'i') {
                                fscanf(cur_ptr, "%c", &symbol);
                                if (symbol == 'p') {
                                    fscanf(cur_ptr, "%c", &symbol);
                                    if (symbol == 'a') {
                                        fscanf(cur_ptr, "%c", &symbol);
                                        if (symbol == 'r') {
                                            fscanf(cur_ptr, "%c", &symbol);
                                            if (symbol == 't') {
                                                fclose(cur_ptr);
                                                return 0;
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
    }
    fclose(cur_ptr);
    return 1;
}

int get_boundary(char* filename, char *boundary, int multipart_is_found) {
    if (!filename || !boundary) {
        return ERROR_NULL_PTR;
    }

    if (multipart_is_found) {
        return -1;
    }
    FILE* cur_ptr = fopen(filename, "r");
    if (!cur_ptr) {
        return ERROR_NULL_PTR;
    }

    int count_of_boundaries = 0;
    char symbol = 0;
    int i = 0;

    while (fscanf(cur_ptr, "%c", &symbol) != -1) {
            if (isspace(symbol)) {
                if (symbol == 'b') {
                    fscanf(cur_ptr, "%c", &symbol);
                    if (symbol == 'o') {
                        fscanf(cur_ptr, "%c", &symbol);
                        if (symbol == 'u') {
                            fscanf(cur_ptr, "%c", &symbol);
                            if (symbol == 'n') {
                                fscanf(cur_ptr, "%c", &symbol);
                                if (symbol == 'd') {
                                    fscanf(cur_ptr, "%c", &symbol);
                                    if (symbol == 'a') {
                                        fscanf(cur_ptr, "%c", &symbol);
                                        if (symbol == 'r') {
                                            fscanf(cur_ptr, "%c", &symbol);
                                            if (symbol == 'y') {
                                                fscanf(cur_ptr, "%c", &symbol);
                                                if (symbol == '=') {
                                                    while (true) {
                                                        fscanf(cur_ptr, "%c", &symbol);
                                                        if (symbol == '"') {
                                                            continue;
                                                        }
                                                        if (symbol == '\n' || symbol == '\r') {
                                                            break;
                                                        }
                                                        boundary[i] = symbol;
                                                        i+=1;
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
            }
        if (i > 0) {
            break;
        }
    }
    if (i != 0) {
        int j = 0;
        while (fscanf(cur_ptr, "%c", &symbol) != -1) {
            while (symbol == boundary[j]) {
                fscanf(cur_ptr, "%c", &symbol);
                j+=1;
                if (symbol != boundary[j]) {
                    j = 0;
                    break;
                }
                if (j == i-1) {
                    j = 0;
                    count_of_boundaries +=1;
                    break;
                }
            }
        }
    }
    fclose(cur_ptr);
    return count_of_boundaries;
}

int get_parts(int is_content_type, int is_multipart, int count_of_boundaries) {
    int parts = 0;
    if (!is_content_type || !is_multipart || (count_of_boundaries == 1)) {
        parts = 1;
    }
    if (count_of_boundaries > 1) {
        parts = count_of_boundaries - 1;
    }
    return parts;
}

int get_date(char* filename, char *date) {
    if (!filename || !date) {
        return ERROR_NULL_PTR;
    }

    FILE* cur_ptr = fopen(filename, "r");
    if (!cur_ptr) {
        return ERROR_NULL_PTR;
    }
    char symbol = 0;
    int i = 0;
    int counter_for_spaces_after_colon = 0;

    while (fscanf(cur_ptr, "%c", &symbol) != -1) {
        if (symbol == '\n' || symbol == '\r') {
            fscanf(cur_ptr, "%c", &symbol);
            if (symbol == 'D') {
                fscanf(cur_ptr, "%c", &symbol);
                if (symbol == 'a') {
                    fscanf(cur_ptr, "%c", &symbol);
                    if (symbol == 't') {
                        fscanf(cur_ptr, "%c", &symbol);
                        if (symbol == 'e') {
                            fscanf(cur_ptr, "%c", &symbol);
                            if (symbol == ':') {
                                while (true) {
                                    fscanf(cur_ptr, "%c", &symbol);
                                    if (symbol == ' ' && !counter_for_spaces_after_colon) {
                                        counter_for_spaces_after_colon = 1;
                                        continue;
                                    }
                                    if (symbol == '\n' || symbol == '\r') {
                                        fscanf(cur_ptr, "%c", &symbol);
                                        if (symbol != ' ') {
                                            break;
                                        }
                                    }
                                    date[i] = symbol;
                                    i+=1;
                                }
                            }
                        }
                    }
                }
            }
        }
        if (i > 0) {
            fclose(cur_ptr);
            return 0;
        }
    }
    fclose(cur_ptr);
    return 1;
}

int get_from(char* filename, char* from) {
    if (!filename || !from) {
        return ERROR_NULL_PTR;
    }

    FILE* cur_ptr = fopen(filename, "r");
    if (!cur_ptr) {
        return ERROR_NULL_PTR;
    }

    char symbol = 0;
    int i = 0;
    int counter_for_spaces_after_colon = 0;
    while (fscanf(cur_ptr, "%c", &symbol) != -1) {
        if (symbol == '\n' || symbol == '\r') {
            fscanf(cur_ptr, "%c", &symbol);
            if (symbol == 'F') {
            fscanf(cur_ptr, "%c", &symbol);
            if (symbol == 'r') {
                fscanf(cur_ptr, "%c", &symbol);
                if (symbol == 'o') {
                    fscanf(cur_ptr, "%c", &symbol);
                    if (symbol == 'm') {
                        fscanf(cur_ptr, "%c", &symbol);
                        if (symbol == ':') {
                            while (true) {
                                fscanf(cur_ptr, "%c", &symbol);
                                if (symbol == ' ' && !counter_for_spaces_after_colon) {
                                    counter_for_spaces_after_colon = 1;
                                    continue;
                                }
                                if (symbol == '\n' || symbol == '\r') {
                                    fscanf(cur_ptr, "%c", &symbol);
                                    if (isupper(symbol)) {
                                        fseek(cur_ptr, -1, SEEK_CUR);
                                        break;
                                    }
                                }
                                from[i] = symbol;
                                i+=1;
                            }
                        }
                    }
                }
            }
        }
        }
        if (i > 0) {
            fclose(cur_ptr);
            return 0;
        }
    }
    if (i == 0) {
        rewind(cur_ptr);
        while (fscanf(cur_ptr, "%c", &symbol) != -1) {
            if (symbol == 'F' && ftell(cur_ptr) == 1) {
                fscanf(cur_ptr, "%c", &symbol);
                if (symbol == 'r') {
                    fscanf(cur_ptr, "%c", &symbol);
                    if (symbol == 'o') {
                        fscanf(cur_ptr, "%c", &symbol);
                        if (symbol == 'm') {
                            fscanf(cur_ptr, "%c", &symbol);
                            if (symbol == ':') {
                                while (true) {
                                    fscanf(cur_ptr, "%c", &symbol);
                                    if (symbol == ' ' && !counter_for_spaces_after_colon) {
                                        counter_for_spaces_after_colon = 1;
                                        continue;
                                    }
                                    if (symbol == '\n' || symbol == '\r') {
                                        fscanf(cur_ptr, "%c", &symbol);
                                        if (isupper(symbol)) {
                                            break;
                                        }
                                    }
                                    from[i] = symbol;
                                    i+=1;
                                }
                            }
                        }
                    }
                }
            }
            if (i > 0) {
                fclose(cur_ptr);
                return 0;
            }
        }
    }
    fclose(cur_ptr);
    return 1;
}

int get_to(char* filename, char* to) {
    if (!filename || !to) {
        return ERROR_NULL_PTR;
    }

    FILE* cur_ptr = fopen(filename, "r");
    if (!cur_ptr) {
        return ERROR_NULL_PTR;
    }

    char symbol = 0;
    int i = 0;
    int counter_for_spaces_after_colon = 0;

    while (fscanf(cur_ptr, "%c", &symbol) != -1) {
        if (symbol == '\n' || symbol == '\r') {
            fscanf(cur_ptr, "%c", &symbol);
        if (symbol == 'T') {
            fscanf(cur_ptr, "%c", &symbol);
            if (symbol == 'o') {
                fscanf(cur_ptr, "%c", &symbol);
                    if (symbol == ':') {
                        while (true) {
                            fscanf(cur_ptr, "%c", &symbol);
                            if (symbol == ' ' && !counter_for_spaces_after_colon) {
                                counter_for_spaces_after_colon = 1;
                                continue;
                            }
                            if (symbol == '\n' || symbol == '\r') {
                                fscanf(cur_ptr, "%c", &symbol);
                                if (symbol != ' ') {
                                    break;
                                }
                            }
                            to[i] = symbol;
                            i+=1;
                        }
                    }
            }
        }
        }
        if (i > 0) {
            fclose(cur_ptr);
            return 0;
        }
    }
    fclose(cur_ptr);
    return 1;
}
