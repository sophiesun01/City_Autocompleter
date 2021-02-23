#include "autocomplete.h"
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    struct term **terms = (struct term**)malloc(sizeof(struct term*));
    int nterms;
    //int num = line_counter("testing.txt");
    //printf("%d", num);
    read_in_terms(terms, &nterms, "testing.txt"); 
    int high = highest_match(*terms, nterms, "T");
    printf("%d\n", high);
    int low = lowest_match(*terms, nterms, "T");
    printf("%d\n", low);
    free(terms);
    free(*terms);

    return 0;

}
//gcc main.c autocomplete.c -o main