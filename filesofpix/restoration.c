#include "restoration.h"

const int HINT = 1000; //expected max file length

void readfile(FILE *inputfd, Seq_T *file_data, Seq_T *infusion_data);
void print_data(Seq_T *original_data, size_t *length);
void free_data(Seq_T *file_data, Seq_T *file_length, 
                                Seq_T *infusion_data, Seq_T *original_data);

int main(int argc, char *argv[])
{
    //assert that multiple arguments aren't supplied before starting program
    assert(argc <= 2); 

    Seq_T file_data = Seq_new(HINT);
    Seq_T file_length = Seq_new(HINT);

    (void) file_length;

    FILE *t;
    if (argc == 1) {
        //reads in stdin as a file
        t = stdin;
    } else {
        t = fopen(argv[1], "r");   
    }

    //check that file exists
    assert(t != NULL);

    //construct sequence to hold the respective char infusions of each row
    Seq_T infusion_data = Seq_new(HINT);

    //read entire file into a sequence of char*
    readfile(t, &file_data, &infusion_data);
    //readfile2(t, &file_data, &file_length, &infusion_data);
    fclose(t);

    //representation of pgm file with the correct rows and no infusions
    Seq_T original_data = Seq_new(HINT);
    size_t length;

    //find and clean correct rows from file_data
    hash(&infusion_data, &file_data, &original_data, &length);

    //print out raw P5 file
    print_data(&original_data, &length);

    //deallocate memory
    free_data(&file_data, &file_length, &infusion_data, &original_data);

    //exit_success if program is run properly
    exit(EXIT_SUCCESS);
}

//deallocates data after finishing program
void free_data(Seq_T *file_data, Seq_T *file_length, 
                        Seq_T *infusion_data, Seq_T *original_data) {
    for(int i = 0; i < Seq_length(*file_data); i++) {
        free(Seq_get(*file_data, i));
    }
    for(int i = 0; i < Seq_length(*file_length); i++) {
        free(Seq_get(*file_length, i));
    }
    for(int i = 0; i < Seq_length(*infusion_data); i++) {
        free(Seq_get(*infusion_data, i));
    }
    for(int i = 0; i < Seq_length(*original_data); i++) {
        free(Seq_get(*original_data, i));
    }
    Seq_free(file_data);
    Seq_free(file_length);
    Seq_free(infusion_data);
    Seq_free(original_data);
}

/*
 * readfile
 * parameters: a FILE pointer
 *             a pointer to an empty Hanson sequence
 * returns:    n/a
 * usage:      processes a FILE and calls readaline on each line
 *             stores a *char representation of lines into sequence
 */
void readfile(FILE *inputfd, Seq_T *file_data,  Seq_T *infusion_data) {
    char *datapp; 
    size_t i = 0;
    size_t length = readaline(inputfd, &datapp);
    while(datapp != NULL) {
        Seq_addhi(*file_data, datapp);

        //process the line to extract chars
        //uses the returned length from readaline to iterate through 
        //the corrupted line in case of "/0" occurence
        Seq_addhi(*infusion_data, 
                    parseline_ver2(Seq_get(*file_data, i), length));

        //debug print statement
        //printf("%s\n", (char *)Seq_get(*file_data, i));

        i++;
        //printf("Reading row %zu\n", i);
        length = readaline(inputfd, &datapp);

        
    }
    return;
}

/*
 * print_data
 * parameter: a const Hansen Struct Seq stored lines from the corrupted file
 *            the length (width) of a single row from the original pgm
 * return:    void
 * purpose:   print out a raw pgm of the corrupted file with proper header
 */
void print_data(Seq_T *original_data, size_t *length) {
    int num = Seq_length(*original_data);
    //header
    printf("P5\n");
    printf("%d %d\n", (int)*length, num);
    printf("255\n");

    for(int i = 0; i < num; i++) {
        unsigned char *line = Seq_get(*original_data, i);
        for(int j = 0; j < (int)*length; j++) {
            printf("%c", line[j]);
        }
    }
}

