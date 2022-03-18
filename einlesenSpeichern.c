#include <stdio.h> //Standardbibliothek, die braucht man immer, sodass C läuft
#include <stdint.h> //das muss man importieren für uint und int

int main()
{   
    const uint8_t total_users = 100;
    const uint8_t name_len = 58; //29 Zeichen a 2 chars 

    const char* file_name = "anonym.txt"; //array von chars ist der Typ von file_name //die chars sind die Zeichen aus denen sich der string zusammensetzt
    char inhalt[total_users][name_len]; //zuerst Zeile dann Spalte, wegen Dimensionen (zweidimensionales Array)

    for(uint8_t x = 0; x < total_users; ++x) //x wird gleich 0 gesetzt und solange x kleiner als 100 ist, solange steigt der Wert von x
    {
        for(uint8_t y = 0; y < name_len; ++y) //y wird gleich 0 gesetzt und solange y kleiner als 100 ist, solange steigt der Wert von y
        {
            inhalt[x][y] = 0; //hier wird klargestellt, dass es sich bei x um die erste Dimension im zweidimensionalen array inhalt handelt und bei y um die zweite Dimension
        }
    }
    uint8_t user_count = 0; //hier wird user_count gleich 0 gesetzt und da ich nichts negatives möchte, als uint

    FILE* file = fopen(file_name, "r");
    if(file != NULL) //wenn der Pointer nicht leer ist
    {
        while (!feof(file)) //solange das Ende der Datei nicht erreicht ist
        {
            fgets(inhalt[user_count], name_len, file); //um das zu verstehen, die Funktion fgets googlen (zukünftig für alle Funktionen so machen)
            printf("%s", inhalt[user_count]); // %s sagt der Funktion printf, dass ein string geprinted werden soll MERKE: geht auch mit %c für char, etc.
            ++user_count;
        }
        fclose(file);
    }

    return 0;
}
