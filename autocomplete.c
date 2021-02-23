#include "autocomplete.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
/*
char *find_term(char *str){
    int ind = 0;
    int count = 0;
    char no_new[200];
    char *new_line = (char *)malloc(200*sizeof(char*));
    //leading spaces
    while (str[count] <= strlen(str)){
        if (str[count] == '\n'){
            str[count] = '\0';
            break;
        }
        count ++;
    }
    strncpy(no_new, str, strlen(str));
    while (isalpha(no_new[ind]) == 0){ 
        ind ++;
    }
    strcpy(new_line, &no_new[ind]);
    return new_line;   
}

int comparterms(const void *pa, const void *pb){
    const struct term *p1 = pa;
    const struct term *p2 = pb; 
    return strcmp(p1->term, p2->term);
}

void read_in_terms(struct term **terms, int *pnterms, char *filename)
{
    char line[200];
    FILE *fp = fopen(filename, "r");
    
    if(fp == NULL)
    {
        printf("Error opening file\n");
        exit(1);
    }
    //keeps count of how many lines there are
    fgets(line, sizeof(line), fp);
    printf("%s", line);
    sscanf(line, "%d", pnterms);
    int count = *pnterms;
    //struct term arr_term[count];
    *terms = (struct term*)malloc(sizeof(struct term) * count);
    for(int i = 0; i < count; i++){
        fgets(line, sizeof(line), fp); //read in at most sizeof(line) characters
        char newline[200];
        sscanf(line, "%lf", &((*terms)[i].weight));
        strcpy((*terms)[i].term, find_term(line));
        strcpy(newline, find_term(line));
        //(*terms)[i].weight = (double)my_weight;
        printf("%f\n", (*terms)[i].weight);
        printf("%s", (*terms)[i].term);
        }
    qsort(*terms, *pnterms, sizeof(struct term), comparterms);
    for(int a = 0; a<*pnterms; a++){
        //printf("%f\n", (*terms)[a].weight);
        //printf("%s\n", (*terms)[a].term); 
    }
    fclose(fp);
}
*/

/*
int lowest_match(struct term *terms, int nterms, char *substr){
    int low = 0;
    int high = nterms-1;
    while((high - low) >= 2){
        int mid = (low + high) /2;
        strncpy()
        strnchar* mid_str = terms[mid].term
        if(strcmp(substr, ((terms)[mid].term)) < 0){// substr is in the first half of the alphabet
            high = mid - 1;
        }
        else if(strcmp(substr, ((terms)[mid].term)) > 0){// substr is in the second half of the alphabet
            low = mid + 1;
        }
        else{
            if(strcmp(substr, ((terms)[low].term)) == 0){
                return low;
            }
            else if(strcmp(substr, (terms)[high-1].term)==0){
                high = high - 1;
            }
            else{
                return mid;
            }
        }
    }
    if (strcmp(substr, (terms)[high].term)==0){
        return high;
    }
    return -1;
}
*/


int comparterms(const void *pa, const void *pb){
    const struct term *p1 = pa;
    const struct term *p2 = pb; 
    return strcmp(p1->term, p2->term);
}
/*int lowest_match(struct term *terms, int nterms, char *substr){
    int i= 0;
    int ind = 0;
    while(i < nterms){
       if(strstr(terms[i].term, substr) != NULL){ 
           return i;
       }
       i++;
    }
    return -1;
}

int highest_match(struct term *terms, int nterms, char *substr){
    int i= nterms;
    int ind = 0;
    while(i >= 0){
       if(strstr(terms[i].term, substr) != NULL){ 
           return i+1;
       }
       i--;
    }
    return -1;
}*/
//blah
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
            else if(strncmp(substr, (terms)[high].term, sub_len) ==0){
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
        }
    }
    if (strncmp(substr, (terms)[low].term, sub_len)==0){
        return low;
    }
    return 0;
}
//autocomplete 0 not 1
