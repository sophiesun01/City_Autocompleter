#include "autocomplete.h"
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    struct term **terms = (struct term**)malloc(sizeof(struct term*));
    int nterms;
    struct term **answer = (struct term **)malloc(sizeof(struct term*));
    int n_answer;
    //int num = line_counter("testing.txt");
    //printf("%d", num);
    read_in_terms(terms, &nterms, "testing.txt"); 
    int high = highest_match(*terms, nterms, "T");
    printf("%d\n", high);
    int low = lowest_match(*terms, nterms, "T");
    printf("%d\n", low);
    autocomplete(answer, &n_answer, *terms, nterms, "T");
    for(int a = 0; a< n_answer; a++){
        printf("%f\n", (*answer)[a].weight);
        printf("%s\n", (*answer)[a].term); 
    }
    free(terms);
    free(*terms);
    free(answer);
    free(*answer);

    return 0;

}
//gcc main.c autocomplete.c -o main