#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//Wichtig! time includen!
 

//Funktion tauscht Positionen durch   
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

//Funnktion mischt Zahlenarray-Positionen abhängig von Zufallsfaktor Zeit
void randomize(int arr[], int n) {
    srand(time(NULL));
    int i;
    for(i = n-1; i > 0; i--) {
        int j = rand() % (i+1);
        swap(&arr[i], &arr[j]);
    }
}


int main() {
    //Variablen übernehmen vom vorherigen Schritt/Christian:
    int group_even_number = 3;
    int group_even_members = 6;
    const int members_smart = group_even_members;
    int group_odd_number = 1;
    int group_odd_members = 2;
    const int group_number_total = group_even_number + group_odd_number;
    int group_members_total;
    //if Schleife

    //group übernehmen vom ersten Schritt/Steven:
    //arr / group_random: automatisch an Größe group anpassen!?
    int arr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19};
    int n = sizeof(arr)/ sizeof(arr[0]);
    char* group[] = {"anna", "bert", "celine", "dennis", "emil", "franz", "giselle", "helga", "ida", "jan", "hgu", "ngh", "njgu", "nfh", "nfihd", "nfuh", "ifh", "kfh", "ihfh", "lur"};
    char* group_random[20] = {};
    char* allocated_group[group_number_total][members_smart];
    
    char* group_1[6] = {};
    char* group_2[6] = {};
    char* group_3[6] = {};
    char* group_4[2] = {};

    int i;
    randomize (arr, n);
    for(i = 0; i < n; i++) {
        int index = arr[i];
    //    printf("%2d - %s\n", i+1, group[index]);
        group_random[i] = group[index];
    }    
    
    /*int x = 0;
    x = 0;
    printf("-------------------------\n");
    while(x <= 19) {
        printf("%s\n", group_random[x]);
        x++;
    }

    for(i = 0; i <=7; i++) {
        group_1[i] = group_random[i];
    }
    printf("-----Gruppe1-----\n");
    int y = 0;
    while(y <= 7) {
        printf("%s\n", group_1[y]);
        y++;
    }*/
    
    int e, f;
    for (f = 0; f <=(group_number_total-1); f++) {
        for (e = 0; e <= group_even_number; e++) {
            allocated_group[f][e] = group_random[e];
        }
    }

    return 0;
}
