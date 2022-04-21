#include <windows.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <assert.h>
#include <time.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

//klappt, wenn variable "dateiname" noch variabel gecodet: aufgabe fertig
//Prototypen
void after_exit(char* dateiname);

//ctrl+c abfangen Funktion + Dateien Einlesen & Auswerten
void sig_handler(int signo)
{
    if (signo == SIGINT){
        struct _finddata_t c_file;
        long hFile;
        // Find first file in current directory 
        if( (hFile = _findfirst( "*.*", &c_file )) == -1L ){
            printf("Keine Dateien im aktuellen Verzeichnis!\n");
        }
        // Find the rest of the .c files
        else{
            printf("Auswerten der Testanfragen folgt...\n");
            do{
            if(c_file.name[0]!='.' && c_file.name[0]!='a'){
                printf("Diese Datei wurde veraendert: %s\n", c_file.name);
                after_exit(c_file.name);
            }
            }while( _findnext( hFile, &c_file ) == 0 );
        _findclose( hFile );
        }        
    exit(0);
    printf("shouldn't be displayed!");
    }
}
// Liste mit den positiven Fällen wird erstellt -> Gesundheitsamt
void add_file_to_pos_case_list(char* dateiname){
    FILE* testdatei;
    FILE* pos_cases;
    char inhalt[80];
    testdatei = fopen(dateiname,"r");
    pos_cases = fopen(".pos_case.txt","a"); 
    for(uint8_t i=0;i<3;i++){
        fscanf(testdatei, "%s",inhalt);
        fprintf(pos_cases,"%s\t", inhalt);
   }
   fprintf(pos_cases,"\n");
   fclose(testdatei);
   fclose(pos_cases);
}
// Ergebnis des Tests wird in die Testanfrage geschrieben!
void write_result_in_file(char* result, char* dateiname){
    FILE* test_write_result;
    test_write_result = fopen(dateiname,"a");
    fprintf(test_write_result,"\n%s", result);
    fclose(test_write_result);
}
// Auswerten einer Datei nach Eingabe von "r"
void after_exit(char* dateiname){
    srand(time(NULL));
    uint8_t a = rand()%2;
    printf("\n%d\n",a);
    char* result;
    if (a==0){
        result="positiv";
        write_result_in_file(result, dateiname);
        add_file_to_pos_case_list(dateiname);
    }
    else{
        result="negativ";
        write_result_in_file(result, dateiname);
    }
}

int main() {
    char *path = "."; // Pfad zum ueberwachten Verzeichnis.
    fopen(".pos_case.txt","w");
    // Handle fuer das Verzeichnis
    HANDLE file = CreateFile(path,
                             FILE_LIST_DIRECTORY,
                             FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
                             NULL,
                             OPEN_EXISTING,
                             FILE_FLAG_BACKUP_SEMANTICS | FILE_FLAG_OVERLAPPED,
                             NULL);
    assert(file != INVALID_HANDLE_VALUE);

    // Event erstellen
    OVERLAPPED overlapped;
    overlapped.hEvent = CreateEvent(NULL, FALSE, 0, NULL);

    // Speicher holen, hier auf dem Stack
    uint8_t change_buf[1024];

    // den Buffer, die Notifications die abgeholt werden und das Event verknüpfen
    BOOL success = ReadDirectoryChangesW(
                       file, change_buf, 1024, TRUE,
                       FILE_NOTIFY_CHANGE_FILE_NAME  |
                       FILE_NOTIFY_CHANGE_DIR_NAME   |
                       FILE_NOTIFY_CHANGE_LAST_WRITE,
                       NULL, &overlapped, NULL);

    // es geht los
    printf("Verzeichnis %s wird auf Aendeurngen ueberprueft...\n", path);

    while (true) {
        DWORD result = WaitForSingleObject(overlapped.hEvent, 0);

        if (result == WAIT_OBJECT_0) {
            DWORD bytes_transferred;
            GetOverlappedResult(file, &overlapped, &bytes_transferred, FALSE);

            FILE_NOTIFY_INFORMATION *event = (FILE_NOTIFY_INFORMATION*)change_buf;
            while(true) {
                DWORD name_len = event->FileNameLength / sizeof(wchar_t);

                switch (event->Action) {
                case FILE_ACTION_ADDED: {
                    wprintf(L"      Datei hinzugefuegt: %.*s\n", name_len, event->FileName);
                    //dateiname kommt von programm
                    char* dateiname = (char*) malloc(50);
                    wcstombs(dateiname, event->FileName, 50);
                    printf("Dateiname: %s", dateiname);
                    const char* name_datei_termine = ".time.txt";
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
                    char* hour = strtok(inhalt[1], ":");
                    //gettet das erste element
                    char* minute = strtok(NULL, ":");
                    //gettet das zweite element
                    int hour_int = atoi(hour);
                    int minute_int = atoi(minute);
                    //const char* namedatei = "1345.txt";
                    char* namedatei = (char*) malloc(50);
                    wcstombs(namedatei, event->FileName, 50);
                    printf("Namedatei: %s", namedatei);
                    char meldung[11]="\nabgelehnt";
                    if((8<=hour_int) && (hour_int<=18) && (minute_int % 15 ==0))
                    {
                        //printf("\nDatei valide!\n");
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
                            rename(name, mark_invalid);
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
                        rename(dateiname, mark_invalid);
                    }
                    free(dateiname);
                    free(namedatei);
                }
                break;

                case FILE_ACTION_REMOVED: {
                    wprintf(L"      Datei geloescht: %.*s\n", name_len, event->FileName);
                    //dateiname kommt von programm
                    //char dateiname [] = "hallo_1115.txt";
                    char* dateiname = (char*) malloc(50);
                    wcstombs(dateiname, event->FileName, 50);
                    printf("Dateiname: %s", dateiname);
                    //get dateiname ohne endung
                    char* input = strtok(dateiname, ".");
                    //get name
                    char* name = strtok(input, "_");
                    //get time
                    char* time = strtok(NULL, "_");
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
                    char colon[] = ":";
                    char* hour = s1;
                    char* minute = s2;
                    strcat(hour, colon);
                    strcat(hour, minute);
                    //ab hier zeit in file löschen
                    const char* name_datei_termine = ".time.txt";
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
                    free(dateiname);
                }
                break;

                case FILE_ACTION_MODIFIED: {
                    wprintf(L"      Datei veraendert: %.*s\n", name_len, event->FileName);
                }
                break;

                case FILE_ACTION_RENAMED_OLD_NAME: {
                    wprintf(L"      Datei umbenannt von: %.*s\n", name_len, event->FileName);
                }
                break;

                case FILE_ACTION_RENAMED_NEW_NAME: {
                    wprintf(L"          zu: %.*s\n", name_len, event->FileName);
                }
                break;

                default: {
                    printf("Ungueltige Eingabe!\n");
                }
                break;
                }

                // Are there more events to handle?
                if (event->NextEntryOffset) {
                    *((uint8_t**)&event) += event->NextEntryOffset;
                } else {
                    break;
                }
            }

            // Queue the next event
            BOOL success = ReadDirectoryChangesW(
                               file, change_buf, 1024, TRUE,
                               FILE_NOTIFY_CHANGE_FILE_NAME  |
                               FILE_NOTIFY_CHANGE_DIR_NAME   |
                               FILE_NOTIFY_CHANGE_LAST_WRITE,
                               NULL, &overlapped, NULL);

        }

        //Abfangen von ctrl + c
        if (signal(SIGINT, sig_handler) == SIG_ERR)
        printf("\ncan't catch SIGINT\n"); 
    }
}
