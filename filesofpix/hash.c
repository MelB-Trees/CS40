#include "hash.h" 

const int SIZE = 1000;

/*
 * hash
 * parameter: a const Hansen Sequence struct containing all the char array of 
 *            infusions;
 * return:    the value (the index of char array) that first repetition occurs
 * purpose:   find the same pattern of infusion.
 *            in a larger seense, find the original rows in the image.
 */
void hash(const Seq_T *infusion_data, Seq_T *file_data, Seq_T *original_data, size_t *length) {
    Table_T map = Table_new(SIZE, NULL, NULL);
    int found = 0;
    size_t curr_length;

    for (int i = 0; i < Seq_length(*infusion_data); i++) {
        const char *key = Atom_string(Seq_get(*infusion_data, i));
        
        if(Table_get(map, key) != NULL) {

            if(found == 0) {
                char *line = Table_get(map, key);
                //process first row, extract integers in char form
                Seq_addhi(*original_data, getintegers(line, length));
                found = 1;
            } 

            //printf("The index = %d and the val = %d\n", i, *first);
            //printf("The current row is %d and the infusion is: %s\n", *val, (unsigned char *)Seq_get(*infusion_data, *val));
            //printf("The current row is %d and the infusion is: %s\n", i, (unsigned char *)Seq_get(*infusion_data, i));

            //process current row if it's an original
            Seq_addhi(*original_data, getintegers(Seq_get(*file_data, i), &curr_length));

            //because a specific aspect of this program isn't implemented correctly
            //this assert is included to abort when the rows of cleaned data aren't matching lengths
            assert(curr_length == *length); 
            

        } else {
            if(found == 0) {
                //keep adding pointers to rows until first original line is found
                Table_put(map, key, Seq_get(*file_data, i));
            }
        }                    
    }
    //deallocate table
    Table_free(&map);
    return;
}