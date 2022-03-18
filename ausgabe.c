#include <stdio.h>
#include <stdint.h>
//Eingabe Gruppeneinteilung, E-Mailadressen, Anzahl an Gruppen -> beste Format wäre Liste mit Listennamen = Gruppennamen + Listeninhalt = E-Mailadressen
//Ausgabe Gruppenzuordnung formatiert in der Konsole 
//gruppeneinteilung[*(gr_ausg-1)]
int ausgabe(char **gruppeneinteilung, int anz_gr_1, int mitgl_1){
    int gr_ausg = anz_gr_1-(anz_gr_1-1);
    int mitgl_zaheler = mitgl_1-(mitgl_1-1);
    for (anz_gr_1;anz_gr_1!=0;anz_gr_1--){ 
        printf("\nGruppe %d:\t", gr_ausg);
        gr_ausg++;
    }
        for (mitgl_1;mitgl_1!=0;mitgl_1--){
            printf("%s ", gruppeneinteilung[gr_ausg][mitgl_zaheler]);
            mitgl_zaheler++;


    }
}

int main(){
    //char*[][]=gruppeneinteilung caro
    char *gruppe_1 [] = {"nico", "steven", "caro", "chris"};
    char *gruppe_2 [] = {"anna", "mogens", "hulia", "tom"};
    char *gruppe_3 [] = {"conni", "josi", "sandra", "eugen"};
    //char *gruppe_4 [] = {"gustav", "bernd"};
    int anz_gr_1=4;
    int mitgl_1=4;
    char *gruppeneinteilung [] ={gruppe_1, gruppe_2, gruppe_3}; 
   // char* gruppeneinteilung[14] = {"nico", "steven", "caro", "chris", "anna", "mogens", "hulia", "tom", "conni", "josi", "sandra", "eugen", "gustav", "bernd"};
    ausgabe(gruppeneinteilung, anz_gr_1, mitgl_1);

}