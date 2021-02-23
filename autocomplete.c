#include "autocomplete.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


int comparterms(const void *pa, const void *pb){
    const struct term *p1 = pa;
    const struct term *p2 = pb; 
    return strcmp(p1->term, p2->term);
}

int line_counter(char *filename){
    FILE *fp = fopen(filename, "r");
    char line[200];
    int count = 0;
    while ( fgets(line, sizeof(line), fp) != NULL){
        count ++;
    }
    return count;
}

void read_in_terms(struct term **terms, int *pnterms, char *filename)
{
    FILE *fp = fopen(filename, "r");
    
    if(fp == NULL)
    {
        printf("Error opening file\n");
        exit(1);
    }
    //keeps count of how many lines there are

    fscanf(fp, "%d", pnterms);
    int count = *pnterms;
    printf("%d\n", *pnterms);
    //struct term arr_term[count];
    *terms = (struct term*)malloc(sizeof(struct term) * count);
    for(int i = 0; i < count; i++){
        fscanf(fp, "%lf", &((*terms)[i].weight));
        fgetc(fp);
        fscanf(fp, "%200[^\n]\n", (*terms)[i].term);
        //printf("%f\n", (*terms)[i].weight);
        //printf("%s\n", (*terms)[i].term); 
        }
    qsort(*terms, *pnterms, sizeof(struct term), comparterms);
    for(int a = 0; a<count; a++){
        printf("%f\n", (*terms)[a].weight);
        printf("%s\n", (*terms)[a].term); 
    }
    fclose(fp);
}

int highest_match(struct term *terms, int nterms, char *substr){
    int low = 0;
    int high = nterms-1;
    int sub_len = strlen(substr);
    while((high - low) >= 2){
        int mid = (low + high) /2;

        if(strncmp(substr, (terms)[mid].term, sub_len) == 0){
            if(strncmp(substr, (terms)[high].term, sub_len) == 0){
                return high;
            }
            else if(strncmp(substr, (terms)[mid+1].term, sub_len) ==0){
                low ++;
            }
            else{
                return mid;
            }
        }
        else if(strncmp(substr, (terms)[mid].term, sub_len) < 0){

            high = mid - 1;
        }
        else if(strncmp(substr, (terms)[mid].term, sub_len) > 0){
            low = mid + 1;
            //strncmp is positive when first str has a higher ASCII index then the second str
            //higher ASCII Index means it is lower alphabetically
            //therefore you should be searching in the upper half 
        }
    }

    if (strncmp(substr, (terms)[high].term, sub_len)==0){
        return high;
    }
    else if (strncmp(substr, (terms)[low].term, sub_len)==0){
        return low;
    }
    return -1;
}

int lowest_match(struct term *terms, int nterms, char *substr){
    int low = 0;
    int high = nterms-1;
    int sub_len = strlen(substr);
    while((high - low) >= 2){
        int mid = (low + high) /2;

        if(strncmp(substr, (terms)[mid].term, sub_len) == 0){
            if(strncmp(substr, (terms)[low].term, sub_len) == 0){
                return low;
            }
            else if(strncmp(substr, (terms)[mid-1].term, sub_len) ==0){
                high --;
            }
            else{
                return mid;
            }
        }
        else if(strncmp(substr, (terms)[mid].term, sub_len) < 0){
            high = mid - 1;
        }
        else if(strncmp(substr, (terms)[mid].term, sub_len) > 0){
            low = mid + 1;
        }
    }
    if (strncmp(substr, (terms)[low].term, sub_len)==0){
        return low;
    }
    else if (strncmp(substr, (terms)[high].term, sub_len)==0){
        return high;
    }
    
    return 0;
}

int comparweight(const void *pa, const void *pb){
    const struct term *p1 = pa;
    const struct term *p2 = pb; 
    return p2->weight - p1->weight;
}
void autocomplete(struct term **answer, int *n_answer, struct term *terms, int nterms, char *substr){
    int low = lowest_match(terms, nterms, substr);
    int high = highest_match(terms, nterms, substr);
    *n_answer = (high - low)+1;
    *answer = (struct term*)malloc(sizeof(struct term)*(*n_answer));
    int e = 0;
    memcpy((*answer), &((terms)[low]), sizeof(struct term)*(*n_answer));


    qsort(*answer, *n_answer, sizeof(struct term), comparweight);
}
//autocomplete 0 not 1
