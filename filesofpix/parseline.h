#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <atom.h>
#include <except.h>
#include <assert.h>


char *parseline(const char *line);

//same as parseline but uses length to iterate,
//rather than search until "\0"
char *parseline_ver2(const char *line, const size_t length);