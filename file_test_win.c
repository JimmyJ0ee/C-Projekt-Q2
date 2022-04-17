// To-Do
//      - pos_case datei muss 1x am Tag gecleared werden! oder einen neue Liste erstellt werden! -> done
//      - alle Dateien müssen durchiteriert werden (brauche: Verzeichnisinhalt + Dateinamen + Anzahl von Dateien in dem Verzeichnis)
//      - ctrl + c, um Datei zu beenden
#include <windows.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <assert.h>
#include <time.h>

// Liste mit den positiven Fällen wird erstellt -> Gesundheitsamt
void add_file_to_pos_case_list(char* dateiname){
    FILE* testdatei;
    FILE* pos_cases;
    char inhalt[80];
    testdatei = fopen(dateiname,"r");
    pos_cases = fopen("pos_case.txt","a"); 
    for(uint8_t i=0;i<3;i++){
        fscanf(testdatei, "%s",inhalt);
        fprintf(pos_cases,"%s\t", inhalt);
   }
   fprintf(pos_cases,"\n");
   fclose(testdatei);
   fclose(pos_cases);
}
void pos_case_reset(){
    fopen("pos_case.txt","w");
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
    //uint8_t a= rand()%2;
    int a=0;
    char* result;
    if (a==0){  //positiver Test
        result="positiv";
        write_result_in_file(result, dateiname);
        add_file_to_pos_case_list(dateiname);
    }
    else{       //negativer Test
        result="negativ";
        write_result_in_file(result, dateiname);
    }
}

int main() {
    char *path = "C:/Users/Z0127829/OneDrive - ZF Friedrichshafen AG/Desktop/DHBW/Programmieren/C und C++/Abgabe_2"; // Pfad zum ueberwachten Verzeichnis.
    pos_case_reset();
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
    printf("warten %s auf Änderungen...\n", path);

    while (true) {
        DWORD result = WaitForSingleObject(overlapped.hEvent, 0);
        char probe = getchar();             // stört Funktion des Programms
        if (result == WAIT_OBJECT_0) {
            DWORD bytes_transferred;
            GetOverlappedResult(file, &overlapped, &bytes_transferred, FALSE);
            FILE_NOTIFY_INFORMATION *event = (FILE_NOTIFY_INFORMATION*)change_buf;
            while(true) {
                DWORD name_len = event->FileNameLength / sizeof(wchar_t);

                switch (event->Action) {
                case FILE_ACTION_ADDED: {
                    wprintf(L"       Hinzugefügt: %.*s\n", name_len, event->FileName);
                }
                break;

                case FILE_ACTION_REMOVED: {
                    wprintf(L"     Gelöscht: %.*s\n", name_len, event->FileName);
                }
                break;

                case FILE_ACTION_MODIFIED: {
                    wprintf(L"    Verändert: %.*s\n", name_len, event->FileName);
                }
                break;

                case FILE_ACTION_RENAMED_OLD_NAME: {
                    wprintf(L"Name geändert von: %.*s\n", name_len, event->FileName);
                }
                break;

                case FILE_ACTION_RENAMED_NEW_NAME: {
                    wprintf(L"          zu: %.*s\n", name_len, event->FileName);
                }
                break;

                default: {
                    printf("Unerwartete Funktion\n");
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
        //ctrl + c workaround, um Programm zu beenden
        if(probe == 'r')
        {
            //printf("%s", DWORD);
            char* dateiname = "mus_test.txt";
            printf("\nklappt!");
            after_exit(dateiname);
            break;  
        }
        
        // Do other loop stuff here...
    }

}
