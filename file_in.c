#include <stdio.h>
#include <stdint.h> //für bsp. int8_t
#include <stdlib.h> //atio
#include <string.h>

//noch zu tun: dateinamen getten

void main()
{
    //dateiname kommt von programm
    const char* dateiname = "1345.txt";
    const char* name_datei_termine = "time.txt";
    char inhalt[2][50];
    int count=0;
    FILE* datei = fopen(dateiname, "r");
    if (datei != NULL)
    {
        while (!feof(datei))
        {
            fscanf(datei, "%s", inhalt[count]);
            count++;
        }
    }
    else
    {
        printf("datei war leer");
    }
    fclose(datei);
    /*int a=0;
    while (a<count)
    {
        printf("%s\t", inhalt[a]);
        a++;
    }*/
    char* hour = strtok(inhalt[1], ":");
    //gettet das erste element
    char* minute = strtok(NULL, ":");
    //gettet das zweite element
    int hour_int = atoi(hour);
    int minute_int = atoi(minute);
    const char* namedatei = "1345.txt";
    char meldung[11]="\nabgelehnt";
    if((8<=hour_int) && (hour_int<=18) && (0<=minute_int) && (minute_int<=45) && (minute_int % 15 ==0))
    {
        printf("\nDatei valide!\n");
        char* name = inhalt[0];
        char zero [] = "0";
        char underscore [] = "_";
        char colon [] = ":";
        char filename_ending [] = ".txt";
        int len_hour = strlen(hour);
        if (len_hour == 1)  //wenn stunde einstellig -> zweistellig machen
        {
            strcat(zero,hour);
            strcat(name,underscore);
            strcat(name,zero);
            strcat(name,minute);
        }
        else
        {
            strcat(name,underscore);
            strcat(name,hour);
            strcat(name,minute);
        }
        strcat(name,filename_ending);
        rename(dateiname, name);
        //liest time.txt aus und prüft, ob neuer termin schon eingetragen wurde
        FILE* time_datei_einlesen = fopen(name_datei_termine, "r");
        char inhalt_time[40][6];
        int count_time = 0;
        while (!feof(time_datei_einlesen))
        {
            fscanf(time_datei_einlesen, "%s", inhalt_time[count_time]);
            count_time++;
        }
        int a=0;
        strcat(colon,minute);
        strcat(hour,colon);
        int time_already_used = 0;
        while (a<count_time)
        {
            char* check= inhalt_time[a];
            int check_result = strcmp(check, hour);
            if (check_result==0)
            {
                printf("Uebereinstimmung Uhrzeit!");
                time_already_used=1;
                break;
            }
            printf("%s\t", inhalt_time[a]);
            a++;
        }
        fclose(time_datei_einlesen);
        //wenn zeit noch nicht vorhanden
        if (time_already_used==0)
        {
            FILE* time_datei = fopen(name_datei_termine, "a");
            if (time_datei != NULL)
            {
                fprintf(time_datei, "%s\n", hour);
            }
            else
            {
                printf("Datei leer oder nicht vorhanden!");
            }
            fclose(time_datei);
        }
        else
        {
            printf("\nUhrzeit nicht valide!");
            FILE* datei_neu = fopen(name, "a");
            if (datei_neu != NULL)
            {
                fprintf(datei_neu, "%s", meldung);
            }
            else
            {
                printf("datei war leer");
            }
            fclose(datei_neu);
            char mark_invalid [] = "a_";
            strcat(mark_invalid,name);
            printf("\n%s",mark_invalid);
            rename(name, mark_invalid);
            printf("\nName: %s", name);
            //rename(name, name_cancled);    //2 dateien werden erstellt, nicht sinnvolle hier wieder gelöscht
        }
    }
    else
    {
        printf("\nDatei nicht valide!");
        FILE* datei_neu = fopen(namedatei, "a");
        if (datei_neu != NULL)
        {
            fprintf(datei_neu, "%s", meldung);
        }
        else
        {
            printf("datei war leer");
        }
        fclose(datei_neu);
        char mark_invalid [] = "a_";
        strcat(mark_invalid,dateiname);
        printf("\n%s",mark_invalid);
        rename(dateiname, mark_invalid);
    }
}