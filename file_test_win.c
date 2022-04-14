#include <windows.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <assert.h>

int main() {
    char *path = "C:\\Users\\auchterc\\C\\abgabe_2"; // Pfad zum ueberwachten Verzeichnis.

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
                }
                break;

                case FILE_ACTION_REMOVED: {
                    wprintf(L"      Datei geloescht: %.*s\n", name_len, event->FileName);
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

        // Do other loop stuff here...
    }

    printf("Hier Ende?");
}
