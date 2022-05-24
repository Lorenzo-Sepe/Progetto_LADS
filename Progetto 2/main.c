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
    MappaCollegamenti CollegamentiTreno, CollegamentiAereo, CollegamentiAlberghi;
    FILE *fpInClienti, *fpOutClienti;
    FILE *fpInAlberghi,*fpOutAlberghi;
    FILE *fpInCollegamentiAereo, *fpOutCollegamentiAereo;
    FILE *fpInCollegamentiTreno, *fpOutCollegamentiTreno;
    FILE *fpInCollegamentiAlberghi, *fpOutCollegamentiAlberghi;
    char Scelta[MAX_STRINGHE],MailInput[MAX_STRINGHE],PasswordInput[MAX_STRINGHE];
    char FileAlberghi[MAX_STRINGHE];
    int i,selector=0;
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
        printf("Benvenuto nella sezione amministrativa del applicazione.\nPremere il corrispettivo tasto per eseguire una delle azioni qui riportate:\n");
        printf("0 - Aggiungi una Tappa ai viaggi in Aereo. \n");
        printf("1 - Rimuovi una Tappa ai viaggi in Aereo. \n");
        printf("2 - Aggiungi un collegamento tra gli Aereoporti. \n");
        printf("3 - Rimuovi un collegamento tra gli Aereoporti. \n");
        printf("4 - Aggiungi una Tappa ai viaggi in Treno. \n");
        printf("5 - Rimuovi una Tappa ai viaggi in Treno. \n");
        printf("6 - Aggiungi un collegamento tra le Stazioni Ferroviarie. \n");
        printf("7 - Rimuovi un collegamento tra gli le Stazioni Ferroviarie. \n");
        printf("8 - Aggiungi un Hotel dalla lista associata ad una tappa. \n");
        printf("9 - Rimuovi un Hotel dalla lista associata ad una tappa. \n");
        printf("\n<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< || >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
        while (repeat == 1 && selector<4)
        {
            printf("\n<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< || >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
            printf("Premere un tasto: ");
            scanf("%d", &selector);
            switch (selector)
            {
            case 0:
                /* code */
                break;
            case 1:
            
                break;

            case 2:
            
                break;

            case 3:
            
                break;

            case 4:
            
                break;

            case 5:
            
                break;

            case 6:
            
                break;

            case 7:
            
                break;

            case 8:
            
                break;

            case 9:
            
                break;

            default:
                printf("Operazioni terminate.");
                repeat=0; 
                break;
            }

        //aggiornamento dei file
        printf("Continuare? O = No/1 = Si: ");
        scanf("%d",&repeat);
        }
        
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
