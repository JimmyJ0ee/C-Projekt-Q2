#include <windows.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <assert.h>
#include <time.h>
#include <signal.h>
#include <unistd.h>

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
    printf("warten im akutellen Verzeichnis auf Aenderungen...\n");
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
                    wprintf(L"       Hinzugefuegt: %.*s\n", name_len, event->FileName);
                }
                break;

                case FILE_ACTION_REMOVED: {
                    wprintf(L"     Geloescht: %.*s\n", name_len, event->FileName);
                }
                break;

                case FILE_ACTION_MODIFIED: {
                    wprintf(L"    Veraendert: %.*s\n", name_len, event->FileName);
                }
                break;

                case FILE_ACTION_RENAMED_OLD_NAME: {
                    wprintf(L"Name geaendert von: %.*s\n", name_len, event->FileName);
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
        //Abfangen von ctrl + c
        if (signal(SIGINT, sig_handler) == SIG_ERR)
        printf("\ncan't catch SIGINT\n"); 
    }

}