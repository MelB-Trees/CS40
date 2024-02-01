#include "getintegers.h"

/*
 * getintegers
 * parameters: a char pointer to a corrupted line
 *             a pointer to return the number of integers in the line
 * returns:    a pointer to the processed line containing only the original
 *                  integers, cast as unsigned chars
 * usage:      process one single line from the corrupted file data
 *                  to extract the original integers
 */
unsigned char *getintegers(const char* line, size_t *j) {
    int i;
    for (i = 0; line[i] != '\0'; i++); // i now is the length of line
    i--; // skip '\0', we are reading backwards

    *j = 0; // number of integers found, will be length of an original row

    size_t k = 2; // size of row, starts at 2
    int t = 0; // holds the computed value of each integer
    int p = 1; // power of current digit, used to compute int value

    unsigned char *row = (unsigned char*)malloc(k * sizeof(char));
    assert(row != NULL); //assert that memory allocation works

    while (i >= 0) {

        //end loop early if end of line is reached
        if (i < 0 || line[i] == '\0') break;

        //keep iterating backwards until next digit is found
        while(i >= 0 && !isdigit(line[i])) i--;

        while(i >= 0 && isdigit(line[i])) { // start to read in a number
            // first, type-cast line[i] into the int, minus 48 bc in ASCII table
            // 48 represents 0
            // when reading backwards, the fist char we encounters represent the
            // first digit
            t += ((int)(line[i]) - 48) * p;

             //debug statement
            // printf("The multiplier for digit %d is %d\n",
            //                            ((int)line[i] - 48), p);

            p = p * 10;
            i--; // continue to read backwards
        }

        // when the while loop finishes, we should computed value of t
        (*j)++;
        if (*j >= k) { // realloc row once it's too long
            k = 2 * k + 1;
            row = realloc(row, k);
            assert(row != NULL); 
        }
        row[*j - 1] = t; // store t as a char
        t = 0; // reset t, p;
        p = 1;

        while(i >= 0 && !isdigit(line[i])) i--; 
    }

    // reverse row so it is not stored backward
    char temp;
    for (int l = 0; l < (int)*j / 2; l++) {
       temp = row[l];
       row[l] = row[*j - l - 1];
       row[*j - l - 1] = temp;
    }
    row[*j] = '\0'; // add terminator
    return row;
}
