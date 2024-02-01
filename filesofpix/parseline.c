#include "parseline.h"

/*
 * parseline
 * parameter: line is the char array containing the corrupted informations
 *            get_digit is a boolean value. If it's true, this function
 *            retrieves all the digit chars; otherwise, it retrieves all the
 *            non-digit chars (the infusions).
 * return:    a pointer to the char array the malloc'ed in the function
 * purpose:   parse the line into digit ones or non-digits as intended
 */
// reads one processed line from the seq version of the file
// if the current char is a nondigit, adds to the string infusion
char *parseline(const char *line) {
    int i = 0; // current index in the line;
    int j = 0; // how many infusions detected, will be length of infusion
    int k = 1; // size of memory allocation for infusion line

    char *inf = (char*)malloc(sizeof(char)); // start with 1 size of char

    assert(inf != NULL); //assert that memory allocation works

    while (line[i] != '\0') {
        if (!isdigit(line[i])) {
            if ((j + 1) >= k) { // need to realloc
                k = 2 * k + 1;
                inf = realloc(inf, k);
                assert(inf != NULL); //assert that memory allocation works
            }
            inf[j] = line[i]; // put the infusion char into infusion line
            j++;
        }
        i++;
    }
    inf[j] = '\0'; // add terminator
    return inf;
}

/*
 * parseline version 2
 * parameter: line is the char array containing the corrupted informations
 *            get_digit is a boolean value. If it's true, this function
 *            retrieves all the digit chars; otherwise, it retrieves all the
 *            non-digit chars (the infusions).
 *            The length of the given char array, provided it's already known
 *            beforehand
 * return:    a pointer to the char array the malloc'ed in the function
 * purpose:   parse the line into digit ones or non-digits as intended
 */
char *parseline_ver2(const char *line, const size_t length) {
    size_t i = 0; // current index in the line;
    int j = 0; // how many infusions detected, will be length of infusion
    int k = 1; // size of memory allocation for infusion line

    char *inf = (char*)malloc(sizeof(char)); // start with 1 size of char

    assert(inf != NULL); //assert that memory allocation works

    while (i < length) {
        if (!isdigit(line[i])) {
            if ((j + 1) >= k) { // need to realloc
                k = 2 * k + 1;
                inf = realloc(inf, k);
                assert(inf != NULL); //assert that memory allocation works
            }
            inf[j] = line[i]; // put the infusion char into infusion line
            j++;
        }
        i++;
    }
    inf[j] = '\0'; // add terminator
    return inf;
}