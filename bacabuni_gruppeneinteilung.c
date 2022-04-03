#include <stdio.h>
#include <stdint.h> //für bsp. int8_t
#include <stdlib.h> //malloc
#include <time.h>   //srand

uint8_t varianten (int8_t anz_user, int8_t gruppengroese, uint8_t *speicher)
{
    struct rueckgabe
    {
        uint8_t anz_gr_sinnvoll;
        uint8_t mitgl_gr_sinnvoll;
        uint8_t anz_gr_rest;
        uint8_t mitgl_gr_rest;
    };
    struct rueckgabe value;
    //fall 1: teiler groeser als haelfte der user
    if (gruppengroese > (anz_user/2))
    {
        printf("\nDa die eingegebene Gruppengroesse ueber der Haelfte der Gesamtuser liegt,\nist eine Einteilung dieser Art nicht sinnvoll.\n");
        //fall gruppengroese = (anz_user/2): mod = 0 -> wird in gruppenvorschlag behandelt
    }
    else
    {
        //volle Gruppen ermitteln
        uint8_t probe = 0;
        uint8_t zaehler = 0;
        while (probe < anz_user)
        {
            zaehler++;
            probe = gruppengroese*zaehler;
        }
        uint8_t anz_volle_gruppen=zaehler - 2; //grenze sinnvolle gruppenzahl
        uint8_t uebrige_user = anz_user - (gruppengroese*anz_volle_gruppen);
        uint8_t anz_gruppen_rest;
        uint8_t gruppengroese_rest;
        int wahl;
        if (uebrige_user % 2 == 0)
        {
            gruppengroese_rest = 2;
            anz_gruppen_rest = uebrige_user/2;
            printf("\nEs gibt nun folgende sinnvolle Moglichkeiten:\n");
            printf("Ersterns: %d Gruppen mit %d Mitgliedern plus %d Gruppen zu je %d Mitgliedern\n", anz_volle_gruppen, gruppengroese, anz_gruppen_rest, gruppengroese_rest);
            printf("Zweitens: %d Gruppen mit %d Mitgliedern plus %d Gruppen zu je %d Mitgliedern\n", anz_volle_gruppen, gruppengroese, gruppengroese_rest, anz_gruppen_rest);
            printf("Drittens: %d Gruppen mit %d Mitgliedern plus eine Gruppe zu %d Mitgliedern\n", anz_volle_gruppen, gruppengroese, uebrige_user);
            printf("Welche Variante waehlen Sie? (Eingabe als 1, 2 oder 3)\n");
            scanf("%d", &wahl);
            if (wahl==1)
            {
                value.anz_gr_sinnvoll = anz_volle_gruppen;
                value.mitgl_gr_sinnvoll = gruppengroese;
                value.anz_gr_rest = anz_gruppen_rest;
                value.mitgl_gr_rest = gruppengroese_rest;
            }
            if (wahl==2)
            {
                value.anz_gr_sinnvoll = anz_volle_gruppen;
                value.mitgl_gr_sinnvoll = gruppengroese;
                value.anz_gr_rest = gruppengroese_rest;
                value.mitgl_gr_rest = anz_gruppen_rest;
            }
            if (wahl==3)
            {
                value.anz_gr_sinnvoll = anz_volle_gruppen;
                value.mitgl_gr_sinnvoll = gruppengroese;
                value.anz_gr_rest = 1;
                value.mitgl_gr_rest = uebrige_user;
            }
            fflush(stdin); //löschen des Eingabepuffer
        }
        else if (uebrige_user % 3 == 0)
        {
            gruppengroese_rest = 3;
            anz_gruppen_rest = uebrige_user/3;
            printf("\nEs gibt nun folgende sinnvolle Moglichkeiten:\n");
            printf("Erstens: %d Gruppen mit %d Mitgliedern plus %d Gruppen zu je %d Mitgliedern\n", anz_volle_gruppen, gruppengroese, anz_gruppen_rest, gruppengroese_rest);
            printf("Zweitens: %d Gruppen mit %d Mitgliedern plus %d Gruppen zu je %d Mitgliedern\n", anz_volle_gruppen, gruppengroese, gruppengroese_rest, anz_gruppen_rest);
            printf("Drittens: %d Gruppen mit %d Mitgliedern plus eine Gruppe zu %d Mitgliedern\n", anz_volle_gruppen, gruppengroese, uebrige_user);
            printf("Welche Variante waehlen Sie? (Eingabe als 1, 2 oder 3)\n");
            scanf("%d", &wahl);
            if (wahl==1)
            {
                value.anz_gr_sinnvoll = anz_volle_gruppen;
                value.mitgl_gr_sinnvoll = gruppengroese;
                value.anz_gr_rest = anz_gruppen_rest;
                value.mitgl_gr_rest = gruppengroese_rest;
            }
            if (wahl==2)
            {
                value.anz_gr_sinnvoll = anz_volle_gruppen;
                value.mitgl_gr_sinnvoll = gruppengroese;
                value.anz_gr_rest = gruppengroese_rest;
                value.mitgl_gr_rest = anz_gruppen_rest;
            }
            if (wahl==3)
            {
                value.anz_gr_sinnvoll = anz_volle_gruppen;
                value.mitgl_gr_sinnvoll = gruppengroese;
                value.anz_gr_rest = 1;
                value.mitgl_gr_rest = uebrige_user;
            }
            fflush(stdin); //löschen des Eingabepuffer
        }
        else
        {
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

void gruppenvorschlag(int8_t anz_user, uint8_t *speicher)
{
    int8_t gruppengroese=0;
    printf("\nDie Anzahl der User betraegt: %d\nWie viele User sollen in eine Gruppe? (bitte ganze Zahl eingeben)\n", anz_user);
    scanf("%d", &gruppengroese);
    fflush(stdin); //löschen des Eingabepuffer
    //ganzzahliger Teiler
    if (anz_user % gruppengroese == 0)
    {
        int8_t anz_gruppen;
        anz_gruppen = anz_user/gruppengroese;
        *speicher = anz_gruppen;
        *(speicher+1) = gruppengroese;
        *(speicher+2) = 0;
        *(speicher+3) = 0;
        printf("---------------------------------------------------------------------");
        printf("\n\nEs wird eine Einteilung in %d Gruppen zu je %d Mitglied(ern) empfohlen.\n", anz_gruppen, gruppengroese);
    }
    else
    {
        varianten(anz_user, gruppengroese, (uint8_t *)speicher);
    }
}

//Funktion tauscht Positionen durch   
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

//Funnktion mischt Zahlenarray-Positionen abhängig von Zufallsfaktor Zeit
void randomize(int arr[], int n)
{
    srand(time(NULL));
    int i;
    for(i = n-1; i > 0; i--)
    {
        int j = rand() % (i+1);
        swap(&arr[i], &arr[j]);
    }
}

int main()
{
    //ab hier steven
    const uint8_t total_users = 100;
    const uint8_t name_len = 58; //29 Zeichen a 2 chars 

    const char* file_name = "anonym.txt"; //array von chars ist der Typ von file_name //die chars sind die Zeichen aus denen sich der string zusammensetzt
    char inhalt[total_users][name_len]; //zuerst Zeile dann Spalte, wegen Dimensionen (zweidimensionales Array)

    for (uint8_t x = 0; x < total_users; ++x) //x wird gleich 0 gesetzt und solange x kleiner als 100 ist, solange steigt der Wert von x
    {
        for (uint8_t y = 0; y < name_len; ++y) //y wird gleich 0 gesetzt und solange y kleiner als 100 ist, solange steigt der Wert von y
        {
            inhalt[x][y] = 0; //hier wird klargestellt, dass es sich bei x um die erste Dimension im zweidimensionalen array inhalt handelt und bei y um die zweite Dimension
        }
    }
    uint8_t user_count = 0; //hier wird user_count gleich 0 gesetzt und da ich nichts negatives möchte, als uint

    FILE* file = fopen(file_name, "r");
    if (file != NULL) //wenn der Pointer nicht leer ist
    {
        while (!feof(file)) //solange das Ende der Datei nicht erreicht ist
        {
            fgets(inhalt[user_count], name_len, file); //um das zu verstehen, die Funktion fgets googlen (zukünftig für alle Funktionen so machen)
            ++user_count;
        }
        fclose(file);
    }
    user_count--;


    //ab hier christian
    uint8_t *speicher;
    speicher = malloc(sizeof(uint8_t)*4);   //reserviert speicher für 4 int auf heat
    if (speicher==NULL)
    {
        printf("Es ist kein speicher verfügbar!");
        return 1;
    }
    gruppenvorschlag(user_count, (uint8_t *)speicher);
    printf("\n---------------------------------------------------------------------");
    printf("\nIhre Wahl: %d Gruppen mit %d Mitgliedern plus %d Gruppen zu je %d Mitgliedern\n", speicher[0], speicher[1], speicher[2], speicher[3]);
    
    
    //ab hier caro
    //Variablen übernehmen vom vorherigen Schritt/Christian:
    int group_even_number = speicher[0];
    int group_even_members = speicher[1];
    const int members_smart = group_even_members;
    int group_odd_number = speicher[2];
    int group_odd_members = speicher[3];
    const int group_number_total = group_even_number + group_odd_number;
    int group_members_total;

    //group übernehmen vom ersten Schritt/Steven:
    int arr[user_count];
    int count;
    for (count=0; count <= (user_count-1); count++)
    {
        arr[count] = count;
    }

    int n = sizeof(arr)/ sizeof(arr[0]);
    char* group_random[user_count];
    char* allocated_group[group_number_total][members_smart];
    
    int i;
    randomize (arr, n);
    for(i = 0; i < n; i++)
    {
        int index = arr[i];
        group_random[i] = inhalt[index];
    }

    int e, f, g, h;
    int group_random_count=0;
    for (e=0; e <= (group_even_number-1); e++)
    {
        for (f = 0; f <= (group_even_members-1); f++)
        {
            allocated_group[e][f] = group_random[group_random_count];
            group_random_count++;
        }
    }
    group_odd_number=group_odd_number+e;
    for (g=e; g <= group_odd_number; g++)
    {
        for (h=0; h <= (group_odd_members-1); h++)
        {
            allocated_group[g][h] = group_random[group_random_count];
            group_random_count++;
        }
    }


    //ab hier nico
    int anz_gr_1=speicher[0];
    int mitgl_1=speicher[1];
    int anz_gr_2=speicher[2];
    int mitgl_2=speicher[3];
    int a;
    for (a = 0; a < anz_gr_1; ++a)
    { 
        printf("\nGruppe %d:\n", a+1);
    
        for (int m = 0; m < mitgl_1; ++m)
        {
            printf("\t%s", allocated_group[a][m]);
        }
    }
    for (int j = 0; j < anz_gr_2; ++j)
    {
        printf("\nGruppe %d:\n", j+a+1);
    
        for (int n = 0; n < mitgl_2; ++n)
        {
            printf("\t%s", allocated_group[j][n]);
        }
    }
    free (speicher);
}