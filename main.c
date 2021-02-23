#include "autocomplete.h"
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    struct term **terms = (struct term**)malloc(sizeof(struct term*));
    int nterms;
    read_in_terms(terms, &nterms, "testing.txt"); 
    int low = highest_match(*terms, nterms, "Shang");
    printf("%d", low);
    free(terms);
    free(*terms);

    return 0;

}
//gcc main.c autocomplete.c -o main