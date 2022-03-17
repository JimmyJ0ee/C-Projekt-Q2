#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//Wichtig! time includen!
 
   
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void randomize(int arr[], int n) {
    srand(time(NULL));
    int i;
    for(i = n-1; i > 0; i--) {
        int j = rand() % (i+1);
        swap(&arr[i], &arr[j]);
    }
}

int main() {
    int arr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    //Anpassen je nach Gruppengröße
    int n = sizeof(arr)/ sizeof(arr[0]);
    char group[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j'};
    //Anpassen mit Original-Gruppe

    printf("before shuffle\n");
    int i;
    for(i = 0; i < n; i++) {
        int index = arr[i];
        printf("%2d - %c\n", i+1, group[index]);
    //Muss noch raus, nur zu Testzwecken drin
    }

    printf("after shuffle\n");
    randomize (arr, n);
    for(i = 0; i < n; i++) {
        int index = arr[i];
        printf("%2d - %c\n", i+1, group[index]);
    }

    return 0;
}