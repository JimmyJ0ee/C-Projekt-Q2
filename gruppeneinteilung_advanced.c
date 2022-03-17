#include <stdio.h>
#include <stdint.h>

//geht bis Gruppengröße 15 Leute
//Input: Anz_user
//Output:
    //einfache Zuordnung: anz_gr, mitgl
    //individuelle Zuordnung: anz_gr_1, mitgl_1, anz_gr_2, mitgl_2

uint8_t varianten (int8_t anz_user, int8_t gruppengroese){
    uint8_t anz_gr_1, mitgl_1, anz_gr_2, mitgl_2;
    printf("\nSie sind in der Funktion fuer schwere Einteilung gelandet.\n");
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
        printf("\nVerbleibende Anzahl User: %d", uebrige_user);
        uint8_t anz_gruppen_rest;
        uint8_t gruppengroese_rest;
        uint8_t wahl;
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
                anz_gr_1 = anz_volle_gruppen;
                mitgl_1 = gruppengroese;
                anz_gr_2 = anz_gruppen_rest;
                mitgl_2 = gruppengroese_rest;
            }
            if (wahl==2){
                anz_gr_1 = anz_volle_gruppen;
                mitgl_1 = gruppengroese;
                anz_gr_2 = gruppengroese_rest;
                mitgl_2 = anz_gruppen_rest;
            }
            if (wahl==3){
                anz_gr_1 = anz_volle_gruppen;
                mitgl_1 = gruppengroese;
                anz_gr_2 = 1;
                mitgl_2 = uebrige_user;
            }
            fflush(stdin); //löschen des Eingabepuffer
            printf("Probe:\n%d\n%d\n%d\n%d\n", anz_gr_1, mitgl_1, anz_gr_2, mitgl_2);
            printf("\nIhre Wahl: %d Gruppen mit %d Mitgliedern plus %d Gruppen zu je %d Mitgliedern\n", anz_gr_1, mitgl_1, anz_gr_2, mitgl_2);
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
                anz_gr_1 = anz_volle_gruppen;
                mitgl_1 = gruppengroese;
                anz_gr_2 = anz_gruppen_rest;
                mitgl_2 = gruppengroese_rest;
            }
            if (wahl==2){
                anz_gr_1 = anz_volle_gruppen;
                mitgl_1 = gruppengroese;
                anz_gr_2 = gruppengroese_rest;
                mitgl_2 = anz_gruppen_rest;
            }
            if (wahl==3){
                anz_gr_1 = anz_volle_gruppen;
                mitgl_1 = gruppengroese;
                anz_gr_2 = 1;
                mitgl_2 = uebrige_user;
            }
            fflush(stdin); //löschen des Eingabepuffer
            printf("Probe:\n%d\n%d\n%d\n%d\n", anz_gr_1, mitgl_1, anz_gr_2, mitgl_2);
            printf("\nIhre Wahl: %d Gruppen mit %d Mitgliedern plus %d Gruppen zu je %d Mitgliedern\n", anz_gr_1, mitgl_1, anz_gr_2, mitgl_2);
        }else{
            printf("Die eingegebene Gruppengröße beschreibt keine sinnvolle Größe\n");
        }
    }
    //return  anz_gr_1, mitgl_1, anz_gr_2, mitgl_2;
}

void gruppenvorschlag(int8_t anz_user){
    int8_t gruppengroese=0;
    printf("Die Anzahl der User betraegt: %d\nWie viele User sollen in eine Gruppe? (bitte ganze Zahl eingeben)\n", anz_user);
    scanf("%d", &gruppengroese);
    fflush(stdin); //löschen des Eingabepuffer
    printf("\nDie Gruppengroese wurde von Ihnen auf %d Mitglieder bestimmt.\n", gruppengroese);
    //ganzzahliger Teiler
    if (anz_user % gruppengroese == 0){
        int8_t anz_gruppen;
        anz_gruppen = anz_user/gruppengroese;
        printf("---------------------------------------------------------------------");
        printf("\n\nEs wird eine Einteilung in %d Gruppen zu je %d Mitglied(ern) empfohlen.\n", anz_gruppen, gruppengroese);
    }else{
        printf("\nDie User koennen nicht in gleich grosse Gruppen aufgeteilt werden.\n");
        varianten(anz_user, gruppengroese);
    }
}

void main (void){
    int8_t anz_user=100;
    gruppenvorschlag(anz_user);
}