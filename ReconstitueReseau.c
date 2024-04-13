#include "Reseau.h"
#include "Chaine.h"
#include "Hachage.h"
#include"ArbreQuat.h"
#include "SVGwriter.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

int main(int argc,char** argv){

    if (argc!=3)
    {
         printf("Mauvais nombre d'argument\n");
          exit(EXIT_FAILURE);
    }

    FILE* fLecture=fopen(argv[1],"r");
    check_pointer(fLecture);
    FILE* fEcriture=fopen("test2.res","w");
    check_pointer(fEcriture);

    int methode_choisie=atoi(argv[2]);

    Chaines* chaine=lectureChaines(fLecture);

    clock_t debut, fin; 

    if(methode_choisie==1)
    {
        debut = clock(); // début mesure du temps
        Reseau* reseau_listeCh=reconstitueReseauListe(chaine);
        fin = clock(); // fin mesure du temps
        double temps_execution = ((double) (fin - debut)) / CLOCKS_PER_SEC; // Calcul du temps écoulé
        fprintf(fEcriture, "Temps d'exécution pour la méthode Liste : %f secondes\n", temps_execution); // Enregistrement du temps dans le fichier de sortie
        
        afficheReseauSVG(reseau_listeCh,"testreseauLCH");
        ecrireReseau(reseau_listeCh,fEcriture);
        liberer_reseau(reseau_listeCh);
    }
    
    if(methode_choisie==2)
    {
        debut = clock();
        Reseau* reseau_tableH=reconstitueReseauHachage(chaine,50);
        fin = clock();
        double temps_execution = ((double) (fin - debut)) / CLOCKS_PER_SEC;
        fprintf(fEcriture, "Temps d'exécution pour la méthode Hachage : %f secondes\n", temps_execution);
        
        afficheReseauSVG(reseau_tableH,"testreseauH");
        ecrireReseau(reseau_tableH,fEcriture);
        liberer_reseau(reseau_tableH);
    }

    if(methode_choisie==3)
    {
        debut = clock();
        Reseau* reseau_arbreQ=reconstitueReseauArbre(chaine);
        fin = clock();
        double temps_execution = ((double) (fin - debut)) / CLOCKS_PER_SEC;
        fprintf(fEcriture, "Temps d'exécution pour la méthode ArbreQuat : %f secondes\n", temps_execution);
        
        afficheReseauSVG(reseau_arbreQ,"testreseauAQ");
        ecrireReseau(reseau_arbreQ,fEcriture);
        liberer_reseau(reseau_arbreQ);
    }

    if(methode_choisie > 3){
        printf("Méthode inexistante, veuillez choisir 1 2 ou 3\n");
    }

    liberer_chaine(chaine);
    fclose(fLecture);
    fclose(fEcriture);

    return 0;
}

