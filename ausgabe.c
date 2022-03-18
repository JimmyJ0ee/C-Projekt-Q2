#include <stdio.h>
#include <stdint.h>
#include <string.h>
//Eingabe Gruppeneinteilung, E-Mailadressen, Anzahl an Gruppen -> beste Format wäre Liste mit Listennamen = Gruppennamen + Listeninhalt = E-Mailadressen
//Ausgabe Gruppenzuordnung formatiert in der Konsole 
//gruppeneinteilung[*(gr_ausg-1)]

int main(){
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
    for (anz_gr_1;anz_gr_1!=0;anz_gr_1--){ 
        printf("\nGruppe %d:\t", gr_ausg);
        gr_ausg++;
    }
        for (mitgl_1;mitgl_1!=0;mitgl_1--){
            printf("%s ", groups[gr_ausg][mitgl_zaheler]);
            mitgl_zaheler++;


    }
   // char* gruppeneinteilung[14] = {"nico", "steven", "caro", "chris", "anna", "mogens", "hulia", "tom", "conni", "josi", "sandra", "eugen", "gustav", "bernd"};
   // ausgabe(groups, anz_gr_1, mitgl_1);

}