#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "StrutturaAlberoUtente.h"
#include "StrutturaGrafi.h"

int main(int argc, char const *argv[])
{
    AlberoUtenti Clienti = NULL;
    AlberoUtenti ClienteCorrente = NULL;
    FILE *fpInClienti, *fpOutClienti;
    FILE *fpInAlberghi,*fpOutAlberghi;
    MappaCollegamenti CollegamentiTreno,CollegamentiAereo,CollegamentiAlberghi;
    FILE *fpInCollegamentiAereo, *fpOutCollegamentiAereo;
    FILE *fpInCollegamentiTreno, *fpOutCollegamentiTreno;
    FILE *fpInCollegamentiAlberghi, *fpOutCollegamentiAlberghi;
    char Scelta[MAX_STRINGHE],MailInput[MAX_STRINGHE],PasswordInput[MAX_STRINGHE];
    char FileAlberghi[MAX_STRINGHE];
    int i,selector;
    int repeat = 1;

    fpInClienti = fopen("ClientiRegistrati.txt","r");
    if(fpInClienti != NULL){
        Clienti = LetturaDaFileUtenti(fpInClienti, Clienti);
    }else{ 
        printf("\n<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< 0 >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");   
        Clienti = Ins_OrdUtenti("ADMIN","ADMIN",0,Clienti);
    }
    fclose(fpInClienti);

    
    printf("\n<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< || >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
    printf("Siete attualmente un cliente registrato? [Y/n]");
    scanf("%s", &Scelta);
    if (strcmp(Scelta,"y")==0 || strcmp(Scelta,"Y") == 0){
        printf("Login\n");
        printf("Inserisci Mail: ");
        scanf("%s", MailInput);
        printf("Inserisci Password: ");
        scanf("%s",PasswordInput);      
    }
    else{
        printf("Registrazione\n");
        printf("Inserisci Mail: ");
        scanf("%s", MailInput);
        printf("Inserisci Password: ");
        scanf("%s",PasswordInput);
        Clienti = Ins_OrdUtenti(MailInput,PasswordInput,0,Clienti);
    }
    printf("\n<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< || >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");

    ClienteCorrente = RicercaBinariaUtenti(MailInput,PasswordInput,Clienti);

    if (strcmp(ClienteCorrente->Mail,"ADMIN") == 0)
    {
        /* code */ //modalità admin
    }
    else
    {
        /* code */ //modalita utente

        /*
        sprintf(FileAlberghi, "%sAlberghi.txt", /*città corrente/);
        fpInAlberghi = fopen(FileAlberghi,"r");
        if(FileAlberghi!=NULL){
       // 	printf("SIGNAL FUORI DA funzione LETTURA FILE DESIDERI\n");
            CollegamentiAlberghi = LetturaDaFileAlberghi(fpInAlberghi,CollegamentiAlberghi);
        }
        fclose(fpInAlberghi); 
        */

    }
    

    fpOutClienti = fopen("ClientiRegistrati.txt","w+");
    if (fpOutClienti==NULL) exit(-1);
    CreazioneFILERisultatoUtenti(fpOutClienti,Clienti);
    fclose(fpOutClienti);

    //TODO funzione per deallocare tutti i grafi
    DeallocaAlberoUtenti(Clienti);
    return 0;
}
