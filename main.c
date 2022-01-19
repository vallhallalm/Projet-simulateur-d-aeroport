/*!
*   \file main.c
*   \brief ce programme permet la gestion des passagers et des avions pour un aeroport.
*
*   \version 1.0
*   \date 20/12/2019
*   \author Magnier Louis Pellouard Mathieu
*/

/*!
*   \mainpage Gestion de passager dans un aeroport
*   Ce programme permet de gerer des passagers depuis leurs arrives dans l'aeroport jusqu'a leurs embarquement dans l'avion. Le programme gere egalement les differents vols.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

/*!
*   \struct billet
*   \brief cette structure correspond aux informations contenus sur un billet
*
*
*
*/
typedef struct billet
//Ici, on definit le premier type qui correspond aux informations necessaires pour generer un billet.
{
    char prenom[100];   ///cette variable sert à stocker le prenom du passager
    char nom[100];  ///cette variable sert à stocker le nom du passager
    int naissance[3];   ///cette variable sert à stocker le jour puis le mois et l'année de naissance d'un passager
    char passeport [10];    ///cete variable sert à stocker le numéro de passeport du passager
    char dest [100];    ///cette variable sert à stocker la destination du passager
    char nationalite[100];  ///cette variable sert à stocker la nationalité du passager
    char numbillet[11];     ///cette variable sert à stocker le numéro de billet du passager
}billet;

/*!
*   \struct boardpass
*   \brief cette structure correspond aux informations contenus dans un boarding pass
*/
typedef struct boardpass
//Ici, on definit le boarding pass (toutes les caracteristiques du passager)
{
    char prenom[100];   ///cette variable sert à stocker le prenom du passager
    char nom[100];  ///cette variable sert à stocker le nom du passager
    int naissance[3];   ///cette variable sert à stocker le jour puis le mois et l'année de naissance d'un passager
    char passeport[10];     ///cete variable sert à stocker le numéro de passeport du passager
    char dest [100];    ///cette variable sert à stocker la destination du passager
    char nationalite[100];  ///cette variable sert à stocker la nationalité du passager
    char numbillet[11];     ///cette variable sert à stocker le numéro de billet du passager
    int privilege;  ///cette variable sert à stocker le privilège du passager
    int nbbagage;   ///cette variable sert à stocker le nombre de bagage que le passager emporte
    int numplace;   ///cette variable sert à stocker le numéro de place du passager
}boardpass;

/*!
*   \struct bagage
*   \brief cette structure correspond aux informations necessaires pour stocker un bagage
*/
typedef struct bagage
//Ici, on définit le type qui permettra d'identifier chaque bagage
{
    char prenom[100];   ///cette variable sert à stocker le prenom du passager
    char nom [100];     ///cette variable sert à stocker le nom du passager
    char numbillet[11];     ///cette variable sert à stocker le numéro de billet du passager
    int numbagage;      ///cette variable sert à stocker le numéro du bagage du passager
    char passeport[10];     ///cette variable sert à stocker le numéro de passeport du passager
    int privilege;      ///cette variable sert à stocker le privilege du passager
}bagage;

/*!
*   \struct vol
*   \brief cette structure correspond aux informations necessaire pour creer un vol
*/
typedef struct vol
{
    char numerovol[6];      ///cette variable sert à stocker le numéro de vol
    int nbplace;        ///cette variable sert à stocker le nombre de place du vol
    char dest[50];      ///cette variable sert à stocker la destination du vol
}vol;

/*!
*   \fn void creer_vol()
*   \brief Cette fonction permet de créer un vol ainsi que tout ce qu'il implique au niveau de la gestion des données.
*
*/
void creer_vol() //cette fonction permet de créer un vol qui pourra être utilisé dans la suite du programme
{
    int i;
    boardpass vierge;
    FILE *ptr;
    FILE *ptr2;
    vol* ajout=(vol*)malloc(1*sizeof(vol));
    char nom2[20];
    //à partir d’ici, on s’occupe du fichier dans lequel sont stockés tout les vols
    char  nom[20]="vol.bin";
    system("CLS");
    ptr=fopen(nom ,"a+");
    //jusque la ligne 69 on remplit la structure vol qui sera entrée dans le fichier vol.bin et qui servira à créer le fichier du type «numerodevol ».bin
    printf("entrer la destination du vol cr%c%c (ecrire en majuscule et remplacer les espaces par des underscores)\n",130,130);
    scanf("%s",ajout->dest);
    printf("entrer le num%cro du vol cr%c%c (6 caract%cres)\n",130,130,130,138);
    scanf("%s",ajout->numerovol);
    printf("entrer le nombre de place dans l'avion cr%c%c\n",130,130);
    scanf("%d",&ajout->nbplace);
    strcpy(vierge.nom," ");//ici on remplit une structure qu’on rentrera dans le fichier « numerodevol ».bin pour faciliter la saisie des données des passagers plus tard
    fwrite(ajout, sizeof(vol), 1, ptr);// on ajoute simplement la structure au fichier vol.bin
    //sur les deux prochaines lignes on affecte le nom du fichier « numerodevol ».bin
    strcpy(nom2,ajout->numerovol);
    strcat(nom2,".bin");
    ptr2=fopen(nom2,"a+b");//on ouvre ce fichier
    // jusque la fin de la fonction,on rentre le nombre de place au debut puis les boardpass vierge (on en rentre autant qu’il y a de places)
    fwrite(&ajout->nbplace,sizeof(int),1,ptr2);
    for(i=0;i<ajout->nbplace;i++)
    {
        fwrite(&vierge,sizeof(boardpass),1,ptr2);
    }
    fclose(ptr);
    fclose(ptr2);
}


/*!
*   \fn bagage enregistrement_bagage(boardpass info,char nom[20],int i)
*   \brief Cette fonction permet de remplir la structure bagage et de stocker les données dans le fichier correspondant au vol qu'empreinte le passager.
*/
bagage enregistrement_bagage(boardpass info,char nom[20],int i)
{
    //le but de cette fonction est de remplir la structure bagage et de la saisir dans le fichier "numerodevol".bin correspondant au vol que prend le propriétaire du bagage
    bagage passage;
    FILE* volnom;
    //on commence par remplir la structure
    strcpy(info.nom,passage.nom);
    strcpy(info.prenom,passage.prenom);
    strcpy(passage.numbillet,info.numbillet);
    strcpy(passage.passeport,info.passeport);
    passage.privilege=info.privilege;
    passage.numbagage=i;
    //on saisie la structure à la fin du fichier "numerodevol".bin
    volnom=fopen(nom,"ab");
    fwrite(&passage,sizeof(bagage),1,volnom);
    fclose(volnom);
    printf("bagage enregistr%c\n",130);
    return passage;
}

/*!
*   \fn boardpass creation_boardpass (billet passager)
*   \brief Cette fonction permet de remplir la structure boardpass et de stocker les données dans le fichier correspondant au vol qu'empreinte le passager.
*/
boardpass creation_boardpass (billet passager)
{
    //le but ici va etre de créer le boardpass. Ici on rentrera toutes les informations.
    boardpass passage;
    int i, choix;
    int* retenu=(int*)malloc(sizeof(int));
    FILE* ptr;
    FILE* ptr2;
    FILE* ptr3;
    boardpass navig;
    char nom[20]="vol.bin";
    char nom2[20];
    vol transit;
    //on remplit la structure boardpass
    //les lignes 6 prochaines lignes sont des copies de la structure billet remplit dans la fonction du meme nom.
    printf ("boardpass en cr%cation\n",130);
    strcpy(passage.prenom,passager.prenom);
    strcpy(passage.nom,passager.nom);
    strcpy(passage.dest,passager.dest);
    strcpy(passage.nationalite,passager.nationalite);
    strcpy(passage.passeport,passager.passeport);
    strcpy(passage.numbillet,passager.numbillet);
    //on demande la date de naissance avec une simple boucle for
    for (i=0;i<3;i++)
    {
      passage.naissance[i]=passager.naissance[i];
    }
    // de la ligne 3 prichaines lignes on collecte encore des informations de l'utilisateur pour la structure et pour les bagages.
    printf("quel privil%cge souhaitez vous avoir : normal:0 ou priority:1\n",138);
    scanf("%d",&passage.privilege);
    printf("combien de bagage souhaitez vous emporter ?\n");
    scanf("%d",&passage.nbbagage);
    //à partir d'ici, on va rechercher dans le fichier "vol.bin" le numero de vol à partir de la destination saisie par l'utilisateur.
    ptr=fopen(nom,"rb");
    rewind(ptr);
    fread(&transit,sizeof(vol),1,ptr);
    while (strcmp(transit.dest,passage.dest)!=0)
    {
       fread(&transit,sizeof(vol),1,ptr);
    }
    fclose(ptr);
    //on va finir de preparer le nom du fichier "numerodevol".bin et on l'enverra dans la fonction enregistrement_bagage pour rentrer les bagages dans le fichier
    strcpy(nom2,transit.numerovol);
    strcat(nom2,".bin");
    for (i=0;i<passage.nbbagage;i++)
    {
        enregistrement_bagage(passage,nom2,i);
    }
    //à partir d'ici, on va donner le numéro de sa place à l'utilisateur. Il a deux choix devant lui: choisir sa place ou prendre la premiere place disponible.
    printf("d%csirez-vous choisir votre place : si oui tapez 1 si non tapez 0\n",130);
    choix=0;
    scanf("%d",&choix);
    ptr2=fopen(nom2,"r+b");
    if (choix == 1)
    {
        //premier choix : l'utilisateur choisit sa place.
        //Ici, on va d'abbord demander à l'utilisateur la place qu'il désire avoir.
        printf("vous pouvez choisir une place entre 0 et %d \n",transit.nbplace-1);
        scanf("%d",&passage.numplace);
        //ensuite, à l'aide du fichier "numerodevol".bin on va rechercher la place sélectionnée par l'utilisateur et vérifier qu'elle est libre. si ce n'est pas le cas l'utilisateur devra resaisir une place différente.
        fseek(ptr2,sizeof(int),SEEK_SET);
        fseek(ptr2,passage.numplace*sizeof(boardpass),SEEK_CUR);
        fread(&navig,sizeof(boardpass),1,ptr2);
        while(strcmp(navig.nom," ")!=0)
        {
            printf("cette place est d%cj%c prise, veuillez entrer un nouveau num%cro",130,133,130);
            scanf("%d",&passage.numplace);
            fseek(ptr2,sizeof(int),SEEK_SET);
            fseek(ptr2,passage.numplace*sizeof(boardpass),SEEK_CUR);
            fread(&navig,sizeof(boardpass),1,ptr2);
        }
        printf("Votre place sera donc %d\n",passage.numplace);
    }
    else
    {
        //deuxième choix, l'utilisateur ne desire pas choisir sa place
        //ici, on se sert du fichier "numerodevol".bin et on cherche la premiere place libre. Cette place sera affecté à l'utilisateur
        fseek(ptr2,sizeof(int),SEEK_SET);
        i=0;
        fread(&navig,sizeof(boardpass),1,ptr2);
        while((strcmp(navig.nom," ")!=0) || (feof(ptr2)!=0))
        {
            fread(&navig,sizeof(boardpass),1,ptr2);
            i++;
        }
        passage.numplace=i;
        printf("votre place sera donc la place num%cro %d\n",130,passage.numplace);
    }
    //grace au 6 prochaines lignes, on met à jour le nombre de place disponible dans l'avion(inscrit au début du fichier "numerodevol".bin)
    fseek(ptr2,0,SEEK_SET);
    fread(retenu,sizeof(int),1,ptr2);
    printf("%d",*retenu);
    (*retenu)--;
    rewind(ptr2);
    fwrite(retenu,sizeof(int),1,ptr2);
    //on entre ensuite le boardpass de l'utilisateur dans le fichier à la place qui a préalablement été définie
    fseek(ptr2,passage.numplace*sizeof(boardpass),SEEK_CUR);
    fwrite(&passage,sizeof(boardpass),1,ptr2);
    fclose(ptr2);
    //pour finir, on rentre le boardpas dans le fichier passager.bin où sont enregistré tout les passagers.
    ptr3=fopen("passager.bin", "a+b");
    fwrite(&passage, sizeof(boardpass), 1, ptr3);
    fclose(ptr3);
    return passage;
}

/*!
*   \fn boardpass achat_billet()
*   \brief cette fonction permet de remplir la structure billet qui servira plus tard à remplir la structure Boardpass
*/
boardpass achat_billet()
{
    billet passage;
    boardpass passager;
    //ici on va rentrer les infos d'un passager dans son billet.
    FILE* ptr;
    FILE* ptr2;
    vol tab[40];
    char nom[20];
    int controle,j,i=0;
    ptr=fopen("vol.bin","a+b");
    system("CLS");      // Clear Screen
    printf("Achat Billet\n\n");
    //à partir d'ici, on remplit la structure billet
    printf("entrer votre pr%cnom\n",130);
    scanf("%s",passage.prenom);
    printf("entrer votre nom\n");
    scanf("%s",passage.nom);
    printf("entrer votre date de naissance \n");
    printf("entrer le jour : ");
    scanf("%d",&passage.naissance[0]);
    //les 7 prochaines lignes sont un controle de cohérence pour le jour
    while ((passage.naissance[0]>31)||(passage.naissance[0]<0))
    {
        printf("jour non valide, veuillez entrer un nouveau chiffre");
        scanf("%d",&passage.naissance[0]);
    }
    printf("entrer le mois : ");
    scanf("%d",&passage.naissance[1]);
    //les lignes 241 à 245 sont un controle de cohérence pour le mois
    while ((passage.naissance[1]>12)||(passage.naissance[1]<1))
    {
        printf("mois non valide, veuillez entrer un nouveau chiffre");
        scanf("%d",&passage.naissance[1]);
    }
    printf("entrer l'ann%ce : ",130);
    scanf("%d",&passage.naissance[2]);
    printf("entrez votre num%cro de passeport(2 chiffres puis 2 lettres et 5 chiffres)\n",130);
    scanf("%s",passage.passeport);
    //à partir d'ici, on va afficher les vols disponibles afin que l'utilisateur puisse choisir sa destination
    printf("les destinations disponibles sont les suivantes :\n");
    fread(&tab[i],sizeof(vol),1,ptr);
    j=0;
    while (feof(ptr)==0)
    {
      strcpy(nom,tab[i].numerovol);
      strcat(nom,".bin");
      ptr2=fopen(nom,"r+b");
      fread(&controle,sizeof(int),1,ptr2);
      if(controle>0)
      {
          printf("\t%s\n",tab[i].dest);
          j++;
      }
      i++;
      fread(&tab[i],sizeof(vol),1,ptr);
    }
    if (j==0)
    {
        printf("aucun vol n'est disponible\n\n");
        return passager;
    }
    else
    {
        //le passager rentre sa destination
        printf("entrer votre destination :\n");
        scanf("%s",passage.dest);
        // les lignes 262 à 282 constituent un controle au cas où l'utilisateur rentre une destination pour laquelle aucun vol n'existe.
        controle=0;
        for (j=0;j<i;j++)
        {
            if(strcmp(passage.dest,tab[j].dest)==0)
            {
                controle=1;
            }
        }
        while (controle==0)
        {
            printf("destination invalide, veuillez r%cessayer",130);
            scanf("%s",passage.dest);
            for (j=0;j<i;j++)
            {
                if(strcmp(passage.dest,tab[j].dest)==0)
                {
                    controle=1;
                }
            }
        }
        //Ici, on crée le numero de billet de l'utilisateur et on l'affiche
        for(j=0;j<=i;j++)
        {
          if(strcmp(passage.dest,tab[j].dest)==0)
          {
            passage.numbillet[0]='N';
            passage.numbillet[1]=passage.nom[2];
            passage.numbillet[2]=tab[j].numerovol[0];
            passage.numbillet[3]=tab[j].numerovol[1];
            passage.numbillet[4]=tab[j].numerovol[2];
            passage.numbillet[5]=tab[j].numerovol[3];
            passage.numbillet[6]=tab[j].numerovol[4];
            passage.numbillet[7]=tab[j].numerovol[5];
            passage.numbillet[8]=passage.nom[0];
            passage.numbillet[9]=passage.prenom[0];
            passage.numbillet[10]='\0';
          }
        }
        printf(" votre num%cero de billet est le suivant : %s\n",130,passage.numbillet);
        // on finit de completer la structure
        printf("entrer votre nationalit%c au masculin, en majuscule et sans caract%cre sp%cciaux\n",130,138,130);
        scanf("%s",passage.nationalite);
        fclose(ptr);
        fclose(ptr2);
        //on apelle la fonction boarpass
        passager=creation_boardpass(passage);
        return passager;
    }
}

/*!
*   \fn void frontieres ()
*   \brief cette fonction imite le passage de frontières pour un passager et permet de conseiller le passager sur le besoin ou non d'un visa.
*/
void frontieres ()
//Ici on détermine si oui ou non le passager a besoin d'un visa selon sa nationalité et sa destination. On affichera sa destination, sa nationnalité et s'il a besoin d'un visa.
{
    FILE* fichier;
    boardpass passager;
    system("CLS");      // Clear Screen
    fichier=fopen("passager.bin","a+b");
    //je ne dois pas copier le paragraphe suivant, il me sert juste à remplir mon fichier  (normalemnt ce fichier sera remplit par le programme boardpass)

    fread(&passager,sizeof(boardpass),1,fichier);
    while (feof(fichier)==0)
    {
        printf("Le passager %s %s a pour nationalit%c : %s.\nSa destination est %s.\n", passager.prenom, passager.nom, 130, passager.nationalite, passager.dest);
        if (strcmp(passager.nationalite, "AMERICAIN")==0)
        {
            if(strcmp(passager.dest, "USA")==0 ||strcmp(passager.dest, "ETATS_UNIS")==0 || strcmp(passager.dest, "US")==0 || strcmp(passager.dest, "EU")==0) printf("Le passager n'a pas besoin de visa\n\n");
            else printf("Le passager a besoin d'un visa\n\n");
        }

        //Le cas où le passager est européen (francais, anglais, espagnol, allemand)
        if (strcmp(passager.nationalite, "FRANCAIS")==0 || strcmp(passager.nationalite, "ANGLAIS")==0 || strcmp(passager.nationalite, "ALLEMAND")==0 || strcmp(passager.nationalite, "ESPAGNOL")==0)
        {
            if(strcmp(passager.dest, "FRANCE")==0 || strcmp(passager.dest, "ANGLETERRE")==0 || strcmp(passager.dest, "ALLEMAGNE")==0 || strcmp(passager.dest, "ESPAGNE")==0) printf("Le passager n'a pas besoin de visa\n\n");
            else printf("Le passager a besoin d'un visa\n\n");
        }

        if (strcmp(passager.nationalite, "CHINOIS")==0)
        {
            if(strcmp(passager.dest, "CHINE")==0) printf("Le passager n'a pas besoin de visa\n\n");
            else printf("Le passager a besoin d'un visa\n\n");
        }
        fread(&passager, sizeof(boardpass),1,fichier);
    }
    fclose(fichier);
}

/*!
*   \fn void securite()
*   \brief cette fonction imite le passage de la sécurité pour un passager. Cela inclut le controle des affaires et notament le passage du sac au travers le scanner
*/
void securite()
{
    int nb_affaire,i;
    char affaire[100];
    system("CLS");
    printf("Les passagers doivent traverser la s%ccurit%c, leurs bagages %c main sont pass%cs au scanner.\nOn se propose ici de simuler ce passage...\nPour cela, vous jouerez le role du scanner. Autrement dit c'est vous qui indiquerez le contenu du bagage %c main.\nTout d'abord, saisir le nombre d'objets contenus dans le bagage %c main : ",130,130,133,130,133,133);
    scanf("%d", &nb_affaire);
    printf("\nVous allez saisir le nom des affaires contenues dans le bagage %c main.\n",133);
    printf("Voici quelques r%cgles a respecter...\nSi l'objet est compos%c de plusieurs mots, remplacer les espaces par des underscores et %ccrire en minuscule. Certains objets interdits en cabine ont %ct%c rassembl%cs en grande cat%cgorie. V%crifiez bien que le produit saisi n'en fait pas partie. Si c'est le cas respectez la d%cnomination donn%ce dans les informations.",138,130,130,130,130,130,130,130,130,130);
    for (i=0; i<nb_affaire ; i++){
    printf("\n\nPour information : \nSi le passager transporte une arme a feu saisir simplement : arme_a_feu\nSi le passager transporte une arme %clectrique saisir simplement : arme_electrique\nSi le passager transporte une arme tranchante saisir simplement : arme_tranchante\nSi le passager transporte un objet tranchant saisir simplement : objet_tranchant\nSi le passager transporte un instrument contondant saisir simplement :objet_contondant\nSi le passager transporte un article pyrotechnique saisir simplement : article_pyrotechnique\nSi le passager transporte un engin de deplacement avec batterie saisir simplement : engin_de_deplacement_avec_batterie\nSi le passager transporte une boisson alcoolis%ce saisir simplement : alcool\nSi le passager transporte un produit m%cnager saisir simplement : produit_menager\nSi le passager transporte un article de bricolage saisir simplement : produit_pour_bricolage\n\n",130,130,130);
    printf("\nQuel est le nom de l'objet %d ?  ", i+1);
    scanf("%s", affaire);
    if (strcmp(affaire, "aerosol")==0 || strcmp(affaire, "oxygene_liquide")==0 || strcmp(affaire, "thermometre_a_mercure")==0 || strcmp(affaire, "arme_a_feu")==0 || strcmp(affaire, "arme_electrique")==0 || strcmp(affaire, "arme_tranchante")==0 || strcmp(affaire, "objet_tranchant")==0 || strcmp(affaire, "objet_contondant")==0 || strcmp(affaire, "article_pyrotechnique")==0 || strcmp(affaire, "engin_de_deplacement_avec_batterie")==0 || strcmp(affaire, "alcool")==0 || strcmp(affaire, "produit_menager")==0 || strcmp(affaire, "produit_pour_bricolage")==0){
        printf("Il faudra retirer ce produit.\n");
    }
    else printf("Cet objet est autoris%c.\n",130);
    }
}

/*!
*   \fn void decollage(char* nom, boardpass *tabpass, bagage* tabbag, int nb_passager_emb,int choix )
*   \brief cette fonction permet de simuler le decollage d'un vol. Pour cela on verifie que l'embarquement s'est bien déroulé et que tout les passagers sont transférées, puis on supprime les fichiers inutiles.
*/

void decollage(char* nom, boardpass *tabpass, bagage* tabbag, int nb_passager_emb,int nb_bag_emb, int choix )
//ici on fait simplement quelques printf poyur indiquer si l'avion peut décoller.
{
  int nb_place,nb_avion_emb,nb_bag,pret,i;
  FILE *efichier;
  FILE *fichier;
  FILE *fnew;
  char nom_emb[20];
  char nom_file[20];
  char nomvol[20];
  vol navig;
  boardpass pass_emb;
  boardpass pass_navig;
  bagage b_circul;
  system("CLS");

  //Selon la décision de l'utilisateur dans la fonction embarquement, on distingue deux cas :
  //Soit l'utilisateur veut décoller l'avion tout de suite apres l'embarquement donc choix=1
  //Soit l'utilisateur ne veut pas décoller l'avion tout de suite apres l'embarquement. Quand il a change d'avis, il accede a la fonction decollage via le menu. Dans ce cas choix=0
  //Si l'utilisateur n'a pas fait d'embarquement préalablement, on entre dans le cas choix=0

  if (choix==0){
        //On affiche les vol qui ont été embarqués préalablement
    fichier=fopen("vol.bin", "rb");
    nb_avion_emb=0;
    printf("Voici les avions embarqu%cs : \n",130);
    fread(&navig,sizeof(vol),1,fichier);
    while (feof(fichier)==0)
    {
      strcpy(nom_emb,"E");
      strcpy(nom_file,navig.numerovol);
      strcat(nom_file,".bin");
      strcat(nom_emb, nom_file);
      efichier=fopen(nom_emb, "r+b");
      if (efichier!=NULL){
          printf("%s\n",nom_file);
          nb_avion_emb++;
      }
      fclose(efichier);
      fread(&navig,sizeof(vol),1,fichier);

    }
    //ici, aucun avion n a été embarqué, on indique à l'utilisateur quaucun vol ne peut décoller
    if (nb_avion_emb==0)
    {
            printf("Aucun avion n'est pret a d%ccoller. Embarquez pr%calablement un avion\n\n",130,130);
            pret=0;
    }

    //Dans ce cas, un ou plusieurs avions ont été embarqué, on doit donc déterminer quelle avion l'utilisateur veut il faire décoller
    else
    {     pret=1;
          printf("Quelle avion voulez-vous faire d%ccoller ?\n",130);
          scanf("%s",nom_file);
          strcpy(nomvol,nom_file);
          //Maintenant qu'on connait le numero de vol, on détermine le nombre de place total dans l'avion qui s'apprete a decoller
          rewind(fichier);
          fread(&navig,sizeof(vol),1,fichier);
          while (strcmp(navig.numerovol,nom_file)!=0)
          {
            fread(&navig,sizeof(vol),1,fichier);
          }
          nb_place=navig.nbplace;

        //Ici, on cherche a déterminer le nombre de personne qui ont embarqué
          strcat(nom_file,".bin");
          strcpy(nom_emb,"E");
          strcat(nom_emb, nom_file);
          efichier=fopen(nom_emb,"rb");
          fread(&pass_emb, sizeof(boardpass),1,efichier);

          while (feof(efichier)==0)
          {
            nb_passager_emb++;
            fread(&pass_emb, sizeof(boardpass),1,efichier);
          }
          if (nb_passager_emb==nb_place) printf("Tous les passagers ont embarqu%c.\n",130);
          fclose(efichier);

          //Maintenant, il vaut vérifier que tous les bagages des passagers sont stockés dans l'avion
          //Ici on détermine le nombre de bagage que doit contenir l'avion avant de décoller
          nb_bag=0;
          efichier=fopen(nom_file, "rb");
          fseek(efichier, sizeof(int), SEEK_SET);
          fseek(efichier, nb_place*sizeof(boardpass),SEEK_CUR);
          while (feof(efichier)==0)
          {
            fread(&b_circul,sizeof(bagage),1,efichier);
            nb_bag++;
          }
          fclose(efichier);

          //Ici on détermine le nombre de bagage embarque
          strcpy(nom_emb,"BE");
          strcat(nom_emb, nom_file);
          efichier=fopen(nom_emb,"rb");
          fread(&b_circul, sizeof(bagage),1,efichier);
          while (feof(efichier)==0)
          {
            nb_bag_emb++;
            fread(&b_circul,sizeof(bagage),1,efichier);
          }

          fclose(efichier);
          if (nb_bag==nb_bag_emb)printf("Tous les bagages ont %ct%c embarqu%c.\n",130,130,130);
          fclose(fichier);
        }
    }
    //Dans cette condition, l'utilisateur a choist de faire décoller son avion tout de suite après l'embarquement, nous récuppérons donc de la fonction embarquement un certain nombre d'information
    else
    {
        //Vérifions que tous les personnes qui ont achete un ticket ont embarqué
        pret=1;
        fichier=fopen("vol.bin", "rb");
        fread(&navig,sizeof(vol),1,fichier);
        while (strcmp(nom,navig.numerovol)!=0)fread(&navig,sizeof(vol),1,fichier);
        if (navig.nbplace==nb_passager_emb)printf("Tous les passagers ont embarqu%cs.\n",130);
        printf("%d",nb_passager_emb);
        fclose(fichier);

        //Maintenant, il vaut vérifier que tous les bagages des passagers sont stockés dans l'avion
        nb_bag=0;
        strcpy(nom_file,nom);
        strcat(nom_file,".bin");
        fichier=fopen(nom_file, "rb");
        fseek(fichier, sizeof(int), SEEK_SET);
        fseek(fichier, navig.nbplace*sizeof(boardpass),SEEK_CUR);
        while (feof(fichier)==0)
          {
            nb_bag++;
            fread(&b_circul,sizeof(bagage),1,fichier);
          }
          fclose(fichier);
          nb_bag--;
          if (nb_bag==nb_bag_emb)printf("Tous les bagages ont %ct%c embarqu%c.\n",130,130,130);
          strcpy(nomvol,nom);
    }

    //Toutes les conditions pour décoller sont respecter, on peut procéder a la simulation du décollage
    if (pret==1){
    printf("\n\nD%ccollage en cour...\n",130);

    //Nous devons supprimer des informations relatifs a l'avion qui est sur le point de decoller
    //La 1ere etape consiste a supprimer le vol du fichier vol.bin (qui rassemble toutes nos structure vol)
    fnew=fopen("newvol.bin","a+b");
    fichier=fopen("vol.bin","r+b");
    fread(&navig,sizeof(vol), 1, fichier);
    while (feof(fichier)==0)
    {
        if (strcmp(navig.numerovol,nomvol)!=0) fwrite(&navig, sizeof(vol),1,fnew);
        fread(&navig,sizeof(vol), 1, fichier);
    }
    fclose(fnew);
    fclose(fichier);
    remove("vol.bin");
    rename("newvol.bin","vol.bin");

    //La 2eme partie consiste a supprimer les passager du vol qui sont contenus daans le fichier passager.bin (qui rassemble toutes nos structures boardpass)

    if (choix==1)
    {
        for (i=0;i<nb_passager_emb;i++)
        {
            fnew=fopen("newpassager.bin","a+b");
            fichier=fopen("passager.bin","r+b");
            fread(&pass_navig,sizeof(boardpass),1,fichier);
            while (feof(fichier)==0)
            {
                if(strcmp(pass_navig.passeport,tabpass[i].passeport)!=0)fwrite(&pass_navig,sizeof(boardpass),1,fnew);
                fread(&pass_navig,sizeof(boardpass),1,fichier);
            }
            fclose(fnew);
            fclose(fichier);
            remove("passager.bin");
            rename("newpassager.bin","passager.bin");
        }
    }

    else
    {
        strcpy(nom_emb,"E");
        strcat(nom_emb, nom_file);
        efichier=fopen(nom_emb, "r+b");

        for (i=0;i<nb_passager_emb;i++)
        {
           fnew=fopen("newpassager.bin","a+b");
           fichier=fopen("passager.bin","r+b");
           fread(&pass_emb,sizeof(boardpass),1,efichier);
           fread(&pass_navig,sizeof(boardpass),1,fichier);
            while (feof(fichier)==0)
            {
                if(strcmp(pass_navig.passeport,pass_emb.passeport)!=0)fwrite(&pass_navig,sizeof(boardpass),1,fnew);
                fread(&pass_navig,sizeof(boardpass),1,fichier);
            }
            fclose(fnew);
            fclose(fichier);
            remove("passager.bin");
            rename("newpassager.bin","passager.bin");
        }
        fclose(efichier);
    }

     //Pour simuler le decollage nous allons supprimer tous les fichiers relatifs au vol en question

   remove(nom_file);
   if (choix==0)
   {
     remove(nom_emb);
     strcpy(nom_emb,"BE");
     strcat(nom_emb, nom_file);
     remove(nom_emb);
   }

    printf("L'avion vient de d%ccoller.\n\n",130);
    }
}

/*!
*   \fn boardpass* embarquement
*   \brief cette fonction permet de simuler l'embarquement. Pour cela on transfère les données stockées dans les fichiers dans des tableaux dynamiques.
*/
boardpass* embarquement()
{
    //ici on remet tout les passagers dans un meme tableau à partir du fichier "numerodevol".bin
    FILE* ptr;
    FILE* ptr2;
    FILE* ptremb;
    boardpass* passage, passager;
    bagage *tab;
    bagage transit;
    char nom [20];
    char nom2[20];
    char nomemb[20];
    int retenu,i,j,choix;
    vol navig;
    system("CLS");
    // en premier lieu on va afficher les vols qui ne possèdent plus de places à vendre et qui sont, de ce fait, pret pour l'embarquement
    ptr=fopen("vol.bin","r+b");
    fread(&navig,sizeof(vol),1,ptr);
    printf("Les vols disponibles pour l'embarquement sont : \n");
    i=0;
    while (feof(ptr)==0)
    {
        strcpy(nom,navig.numerovol);
        strcat(nom,".bin");
        ptr2=fopen(nom,"r+b");
        fread(&retenu,sizeof(int),1,ptr2);
        if (retenu==0)
        {
            printf("\n\t %s",nom);
            i++;
        }
        fclose(ptr2);
        fread(&navig,sizeof(vol),1,ptr);
    }
    //on demande à l'utilisateur le vol qu'il veut faire embarquer. Deux cas se présentent : soit il n'y a pas de vols à faire embarquer soit il y en a
    if (i==0)
    {
        //cas1 : il n'y a pas de vol à faire embarquer, on renvoie donc l'utilisateur au menu
        printf("Aucun vol ne peut embarquer car aucun vol n'est complet.\n");
        return 0;
    }
    else
    {
        //cas 2 : il y a des vols à faire embarquer
        printf("\nEntrer le numero du vol a faire embarquer (ne pas saisir l'extension .bin)\n");
        scanf("%s",nom);
        strcpy(nom2,nom);
        strcat(nom,".bin");
        ptr2=fopen(nom,"r+b");
        //Ici on recherche le nombre de place dans l'avion pour créer le tableau dynamique
        fseek(ptr2,sizeof(int),SEEK_SET);
        strcpy(navig.numerovol,"000000");
        while(strcmp(nom2,navig.numerovol)==0)
        {
            fread(&navig,sizeof(vol),1,ptr);
        }
        passage=(boardpass*)malloc(navig.nbplace*sizeof(boardpass));
        //à partir d'ici, on remplit le tableau avec d'abbord les passagers priority dans la première boucle for puis avec les passagers normaux dans la deuxieme boucle for
        j=0;
        fseek(ptr2,sizeof(int),SEEK_SET);
        for(i=0;i<navig.nbplace;i++)
        {
            fread(&passager,sizeof(boardpass),1,ptr2);
            if(passager.privilege==1)
            {
                passage[j]=passager;
                j++;
            }
        }
        fseek(ptr2,sizeof(int),SEEK_SET);
        for(i=0;i<navig.nbplace;i++)
        {
            fread(&passager,sizeof(boardpass),1,ptr2);
            if(passager.privilege==0)
            {
                passage[j]=passager;
                j++;
            }
        }
        printf("\nVoici la liste des passagers embarques : \n");
        for(i=0;i<navig.nbplace;i++)
        {
            printf("nom : %s\n",passage[i].nom);
            printf("prenom : %s\n\n",passage[i].prenom);
        }
        printf("Embarquement des bagages\n");
        fseek(ptr2,sizeof(int),SEEK_SET);
        fseek(ptr2,navig.nbplace*sizeof(boardpass),SEEK_CUR);
        i=0;
        while(feof(ptr2)==0)
        {
            fread(&transit,sizeof(bagage),1,ptr2);
            i++;
        }
        tab=(bagage*)malloc((i+1)*sizeof(bagage));
        fseek(ptr2,sizeof(int),SEEK_SET);
        fseek(ptr2,navig.nbplace*sizeof(boardpass),SEEK_CUR);
        for(j=0;j<i;j++)
        {
            fread(&tab[i],sizeof(bagage),1,ptr2);
        }
        j=i;
        fclose(ptr);
        fclose(ptr2);
        printf("L'embarquement de l'avion est termin%ce. Voulez-vous proc%cdez au d%ccolage ? entrez 1 si oui et 0 si non\n",130,130,130);
        scanf("%d",&choix);
        if (choix==1)
        {
            decollage(nom2, passage,tab,navig.nbplace,j-1, 1);
        }
        else
        {
            strcpy(nomemb,"E");
            strcat(nomemb,nom);
            ptremb=fopen(nomemb,"a+b");
            for(i=0;i<navig.nbplace;i++)
            {
                fwrite(&passage[i],sizeof(boardpass),1,ptremb);
            }
            fclose(ptremb);
            strcpy(nomemb,"BE");
            strcat(nomemb,nom);
            ptremb=fopen(nomemb,"a+b");
            for(i=0;i<j;i++)
            {
                fwrite(&tab[i],sizeof(bagage),1,ptremb);
            }
            fclose(ptremb);
        }
        return passage;
    }

}

/*!
*   \fn int main()
*   \brief fonction principale du programme qui servira de menu pour naviquer entre les différentes fonctions.
*/
int main()
{
    char choix;
    choix='0';
    while (choix!='Q')
    {
        printf("Gestion des Vols\n\n\tC: cr%cation de vol,\n\tA: achat billet / boardpass / enregistrement bagage, \n\tF: passage de fronti%cres, \n\tS: s%ccurit%c, \n\tE: embarquement, \n\tD: d%ccollage, \n\tQ: quitter\nQue souhaitez vous faire ?",138,130,130,130,130);
        scanf("%s",&choix);
        choix=toupper(choix);
        switch (choix)
        {
            case 'A' : achat_billet(); break;
            case 'F' : frontieres(); break;
            case 'S' : securite(); break;
            case 'D' : decollage(NULL, NULL, NULL,0,0,0); break;
            case 'E' : embarquement(); break;
            case 'C' : creer_vol(); break;
            case 'Q' : printf("%c bient%ct\n",133,147) ;break;
            default : printf(" commande inexistante\n");
        }
    }
    return 0;
}


