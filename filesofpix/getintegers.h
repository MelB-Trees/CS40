#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <except.h>
#include <assert.h>


/*
 * getintegers
 * parameter: the char array of corrupted line (already made sure it is valid)
 * return:    a pointer to the char array, composed all the intgers (which we
 *            will easily type-cast into int when output) but in form of char,
 *            because, as int takes 8 bytes, char only takes 4.
 *            return NULL when there are invalid info (> Maxval 255)
 * purpose:   get all integers from the corrupted line
 */
unsigned char *getintegers(const char *line, size_t *j);