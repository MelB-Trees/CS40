#include "readaline.h"
#include <stdlib.h>
#include <stdio.h>
#include <except.h>
#include <assert.h>
/*
 * readaline
 * parameters: a FILE pointer
 *             a double pointer to the char array representing
 * returns:    the bytes number of the line
 * usage:      process one single line from the FILE stream
 */
size_t readaline(FILE *inputfd, char **datapp)  
{
    assert(inputfd != NULL);

    int t; // buffer t. as fgetc will return an int. from 0 - 255
    t = fgetc(inputfd); // read the first byte
    if (t == EOF) { // when no more lines to be read, return
        *datapp = NULL;
        return 0;
    }


    assert((void*)&t != NULL); //assert that file can be read

    size_t size = 3, i = 0; // size is the current bytes assigned to line;
                            // i is the number of loops i.e. the current index
    char *line = (char*)malloc(3 * size); // at least two columns + infusion
    assert(line != NULL); //assert that memory allocation works

    while ((t != '\n') && (t != EOF)) { // when t did not reach the end
        if (i >= size - 1) { // examine if the line is full
            size = 2 * size + 1;
            //printf("Reallocing data to size %zu\n", size);
            line = realloc(line, size);
            assert(line != NULL); //assert that data rellocation works
        }

        line[i] = t; // put the newly read char into the end of line
        t = fgetc(inputfd); // get the next byte
        i++; // increment index
    }
    line[i] = '\0';

    *datapp = line;
    return i;
}

