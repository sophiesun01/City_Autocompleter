#include "autocomplete.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    struct term *terms;
    int nterms;
    struct term *answer;
    int n_answer;
    //int num = line_counter("testing.txt");
    //printf("%d", num);
    read_in_terms(&terms, &nterms, "cities.txt"); 
    // for(int b = 0; b< nterms; b++){
    //     printf("%f\n", (terms)[b].weight);
    //     printf("%s\n", (terms)[b].term); 
    // }
    // int high = highest_match(terms, nterms, "Kaifeng, C");
    // printf("%d\n", high);
    // int low = lowest_match(terms, nterms, "Kaifeng, C");
    // printf("%d\n", low);
    autocomplete(&answer, &n_answer, terms, nterms, "Toro");
    for(int a = 0; a< n_answer; a++){
        printf("%f\n", (answer)[a].weight);
        printf("%s\n", (answer)[a].term); 
    }
    free(terms);
    free(answer);

    return 0;

}
//gcc main.c autocomplete.c -o main
