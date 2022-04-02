#include <stdio.h>
#include <stdint.h> //für bsp. int8_t
#include <stdlib.h> //malloc

int einlesen(){
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
    user_count--;
    return user_count;
}

uint8_t varianten (int8_t anz_user, int8_t gruppengroese, uint8_t *speicher){
    struct rueckgabe{
        uint8_t anz_gr_sinnvoll;
        uint8_t mitgl_gr_sinnvoll;
        uint8_t anz_gr_rest;
        uint8_t mitgl_gr_rest;
    };
    struct rueckgabe value;
    printf("\nFunktion fuer schwere Einteilung\n");
    //fall 1: teiler groeser als haelfte der user
    if (gruppengroese > (anz_user/2)){
        printf("\nDa die eingegebene Gruppengroesse ueber der Haelfte der Gesamtuser liegt,\nist eine Einteilung dieser Art nicht sinnvoll.\n");
        //fall gruppengroese = (anz_user/2): mod = 0 -> wird in gruppenvorschlag behandelt
    }else{
        //volle Gruppen ermitteln
        uint8_t probe = 0;
        uint8_t zaehler = 0;
        while (probe < anz_user){
            zaehler++;
            probe = gruppengroese*zaehler;
        }
        uint8_t anz_volle_gruppen=zaehler - 2; //grenze sinnvolle gruppenzahl
        uint8_t uebrige_user = anz_user - (gruppengroese*anz_volle_gruppen);
        printf("\nVerbleibende Anzahl User: %d\n", uebrige_user);
        uint8_t anz_gruppen_rest;
        uint8_t gruppengroese_rest;
        int wahl;
        if (uebrige_user % 2 == 0){
            gruppengroese_rest = 2;
            anz_gruppen_rest = uebrige_user/2;
            printf("\nEs gibt nun folgende sinnvolle Moglichkeiten:\n");
            printf("Ersterns: %d Gruppen mit %d Mitgliedern plus %d Gruppen zu je %d Mitgliedern\n", anz_volle_gruppen, gruppengroese, anz_gruppen_rest, gruppengroese_rest);
            printf("Zweitens: %d Gruppen mit %d Mitgliedern plus %d Gruppen zu je %d Mitgliedern\n", anz_volle_gruppen, gruppengroese, gruppengroese_rest, anz_gruppen_rest);
            printf("Drittens: %d Gruppen mit %d Mitgliedern plus eine Gruppe zu %d Mitgliedern\n", anz_volle_gruppen, gruppengroese, uebrige_user);
            printf("Welche Variante waehlen Sie? (Eingabe als 1, 2 oder 3)\n");
            scanf("%d", &wahl);
            if (wahl==1){
                value.anz_gr_sinnvoll = anz_volle_gruppen;
                value.mitgl_gr_sinnvoll = gruppengroese;
                value.anz_gr_rest = anz_gruppen_rest;
                value.mitgl_gr_rest = gruppengroese_rest;
            }
            if (wahl==2){
                value.anz_gr_sinnvoll = anz_volle_gruppen;
                value.mitgl_gr_sinnvoll = gruppengroese;
                value.anz_gr_rest = gruppengroese_rest;
                value.mitgl_gr_rest = anz_gruppen_rest;
            }
            if (wahl==3){
                value.anz_gr_sinnvoll = anz_volle_gruppen;
                value.mitgl_gr_sinnvoll = gruppengroese;
                value.anz_gr_rest = 1;
                value.mitgl_gr_rest = uebrige_user;
            }
            fflush(stdin); //löschen des Eingabepuffer
            //printf("\nIhre Wahl: %d Gruppen mit %d Mitgliedern plus %d Gruppen zu je %d Mitgliedern\n", value.anz_gr_sinnvoll, value.mitgl_gr_sinnvoll, value.anz_gr_rest, value.mitgl_gr_rest);
        }else if (uebrige_user % 3 == 0){
            gruppengroese_rest = 3;
            anz_gruppen_rest = uebrige_user/3;
            printf("\nEs gibt nun folgende sinnvolle Moglichkeiten:\n");
            printf("Erstens: %d Gruppen mit %d Mitgliedern plus %d Gruppen zu je %d Mitgliedern\n", anz_volle_gruppen, gruppengroese, anz_gruppen_rest, gruppengroese_rest);
            printf("Zweitens: %d Gruppen mit %d Mitgliedern plus %d Gruppen zu je %d Mitgliedern\n", anz_volle_gruppen, gruppengroese, gruppengroese_rest, anz_gruppen_rest);
            printf("Drittens: %d Gruppen mit %d Mitgliedern plus eine Gruppe zu %d Mitgliedern\n", anz_volle_gruppen, gruppengroese, uebrige_user);
            printf("Welche Variante waehlen Sie? (Eingabe als 1, 2 oder 3)\n");
            scanf("%d", &wahl);
            if (wahl==1){
                value.anz_gr_sinnvoll = anz_volle_gruppen;
                value.mitgl_gr_sinnvoll = gruppengroese;
                value.anz_gr_rest = anz_gruppen_rest;
                value.mitgl_gr_rest = gruppengroese_rest;
            }
            if (wahl==2){
                value.anz_gr_sinnvoll = anz_volle_gruppen;
                value.mitgl_gr_sinnvoll = gruppengroese;
                value.anz_gr_rest = gruppengroese_rest;
                value.mitgl_gr_rest = anz_gruppen_rest;
            }
            if (wahl==3){
                value.anz_gr_sinnvoll = anz_volle_gruppen;
                value.mitgl_gr_sinnvoll = gruppengroese;
                value.anz_gr_rest = 1;
                value.mitgl_gr_rest = uebrige_user;
            }
            fflush(stdin); //löschen des Eingabepuffer
            //printf("\nIhre Wahl: %d Gruppen mit %d Mitgliedern plus %d Gruppen zu je %d Mitgliedern\n", value.anz_gr_sinnvoll, value.mitgl_gr_sinnvoll, value.anz_gr_rest, value.mitgl_gr_rest);
        }else{
            printf("Die eingegebene Gruppengroese beschreibt keine sinnvolle Groese, das es hier sehr wenige Teiler gibt\n");
            value.anz_gr_sinnvoll = 0;
            value.mitgl_gr_sinnvoll = 0;
            value.anz_gr_rest = 0;
            value.mitgl_gr_rest = 0;
        }
    }
    *speicher = value.anz_gr_sinnvoll;
    *(speicher+1) = value.mitgl_gr_sinnvoll;
    *(speicher+2) = value.anz_gr_rest;
    *(speicher+3) = value.mitgl_gr_rest;
}

void gruppenvorschlag(int8_t anz_user, uint8_t *speicher){
    int8_t gruppengroese=0;
    printf("\nDie Anzahl der User betraegt: %d\nWie viele User sollen in eine Gruppe? (bitte ganze Zahl eingeben)\n", anz_user);
    scanf("%d", &gruppengroese);
    fflush(stdin); //löschen des Eingabepuffer
    //ganzzahliger Teiler
    if (anz_user % gruppengroese == 0){
        int8_t anz_gruppen;
        anz_gruppen = anz_user/gruppengroese;
        *speicher = anz_gruppen;
        *(speicher+1) = gruppengroese;
        *(speicher+2) = 0;
        *(speicher+3) = 0;
        printf("---------------------------------------------------------------------");
        printf("\n\nEs wird eine Einteilung in %d Gruppen zu je %d Mitglied(ern) empfohlen.\n", anz_gruppen, gruppengroese);
    }else{
        varianten(anz_user, gruppengroese, (uint8_t *)speicher);
    }
}

void ausgabe(){
    //char*[][]=gruppeneinteilung caro
    char gruppe_1 [4][8] = {"nico", "steven", "caro", "chris"};
    char gruppe_2 [4][8] = {"anna", "mogens", "hulia", "tom"};
    char gruppe_3 [4][8] = {"conni", "josi", "sandra", "eugen"};
    //char *gruppe_4 [] = {"gustav", "bernd"};
    int anz_gr_1=3;
    int mitgl_1=4;
    char groups[anz_gr_1][mitgl_1][8];
    memcpy(groups[0], gruppe_1, sizeof(groups[0]));
    memcpy(groups[1], gruppe_2, sizeof(groups[1]));
    memcpy(groups[2], gruppe_3, sizeof(groups[2])); 
    int gr_ausg = anz_gr_1-(anz_gr_1-1);
    int mitgl_zaheler = mitgl_1-(mitgl_1-1);
    for (int i = 0; i < anz_gr_1; ++i)
    { 
        printf("\nGruppe %d:\t", i);
    
        for (int m = 0; m < mitgl_1; ++m)
        {
            printf("%s\t", groups[i][m]);
        }
    }
}

int main(){
    //ab hier Steven
    uint8_t user_count = 0;
    user_count=einlesen();
    //ab hier christian
    uint8_t *speicher;
    speicher = malloc(sizeof(uint8_t)*4);   //reserviert speicher für 4 int auf heat
    if (speicher==NULL){
        printf("Es ist kein speicher verfügbar!");
        return 1;
    }
    gruppenvorschlag(user_count, (uint8_t *)speicher);
    printf("\n---------------------------------------------------------------------");
    printf("\nIhre Wahl: %d Gruppen mit %d Mitgliedern plus %d Gruppen zu je %d Mitgliedern\n", speicher[0], speicher[1], speicher[2], speicher[3]);
    //ab hier nico
    ausgabe();
    free (speicher);
}