#include <stdio.h>
#include <stdint.h> //für bsp. int8_t
#include <stdlib.h> //atio
#include <string.h>

void main()
{
    //dateiname kommt von programm
    char dateiname [] = "max_0815.txt";
    //get dateiname ohne endung
    char* input = strtok(dateiname, ".");
    printf("Input: %s", input);
    //get name
    char* name = strtok(input, "_");
    //get time
    char* time = strtok(NULL, "_");
    printf("\nName: %s\nTime: %s", name, time);
    char *str = time;
    int len = strlen(str);
    int len1 = len/2;
    int len2 = len - len1; // Compensate for possible odd length
    char *s1 = malloc(len1+1); // one for the null terminator
    memcpy(s1, str, len1);
    s1[len1] = '\0';
    char *s2 = malloc(len2+1); // one for the null terminator
    memcpy(s2, str+len1, len2);
    s2[len2] = '\0';
    printf("S1: %s\n", s1);
    printf("S2: %s\n", s2);
    char colon[] = ":";
    char* hour = s1;
    char* minute = s2;
    printf("Hour: %s\tColon: %s\tMinute: %s\n", hour, colon, minute);
    strcat(hour, colon);
    strcat(hour, minute);
    printf("Fertige Time: %s", hour);
    //ab hier zeit in file löschen
    const char* name_datei_termine = "time.txt";
    //char* hour = "09:00";
    FILE* time_datei_einlesen = fopen(name_datei_termine, "r");
    char inhalt_time[40][6];
    int count_time = 0;
    while (!feof(time_datei_einlesen))
    {
        fscanf(time_datei_einlesen, "%s", inhalt_time[count_time]);
        count_time++;
    }
    fclose(time_datei_einlesen);
    int a=0;
    //prüfen, wo übereinstimmung der uhrzeit
    while (a<count_time)
    {
        const char* check= inhalt_time[a];
        int check_result = strcmp(check, hour);
        if (check_result==0)
        {
            break;
        }
        a++;
    }
    int size = sizeof(inhalt_time)/sizeof(inhalt_time[0]);
    //löscht element bzw überschreibt alle elemente eins nach vorne
    for (int h = a; h<count_time; h++)
    {
        for (int k = 0; k<=5; k++)
        {
            inhalt_time[h][k] = inhalt_time[h+1][k];
        }
    }
    int size_time = 0;
    int zaehler_schleife = 0;
    int loop_control=0;
    FILE* time_datei = fopen(name_datei_termine, "w");
    if (time_datei != NULL)
    {
        for (int l = 0; l<(count_time-2); l++)
        {
            fprintf(time_datei, "%s\n", inhalt_time[l]);
        }
    }
    else
    {
        printf("Datei leer oder nicht vorhanden!");
    }
    fclose(time_datei);
    free(s1);
    free(s2);
}