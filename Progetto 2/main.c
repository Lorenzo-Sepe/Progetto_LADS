#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "StrutturaAlberoUtente.h"
#include "StrutturaGrafi.h"
#include "Miscellanee.h"

int main(int argc, char const *argv[])
{
    AlberoUtenti Clienti = NULL, ClienteCorrente = NULL;
    MappaCollegamenti CollegamentiTreno = NULL, CollegamentiAereo = NULL, CollegamentiAlberghi = NULL;
    FILE *fpInClienti, *fpOutClienti;
    FILE *fpInAlberghiNodi,*fpOutAlberghiNodi;
    FILE *fpOutTappe;
    FILE *fpInCollegamentiAereoNodi;
    FILE *fpInCollegamentiTrenoNodi;
    FILE *fpInAlberghiArchi,*fpOutAlberghiArchi;
    FILE *fpInCollegamentiAereoArchi, *fpOutCollegamentiAereoArchi;
    FILE *fpInCollegamentiTrenoArchi, *fpOutCollegamentiTrenoArchi;
    FILE *fpInCollegamentiAlberghi, *fpOutCollegamentiAlberghi;
    char Scelta[MAX_STRINGHE], MailInput[MAX_STRINGHE], PasswordInput[MAX_STRINGHE], TappaInput[MAX_STRINGHE],SRCInput[MAX_STRINGHE],DESTInput[MAX_STRINGHE];
    char FileAlberghiNodi[MAX_STRINGHE],FileAlberghiArchi[MAX_STRINGHE];
    int i, selector=0, DistanzaInput,IndexInput;
    int repeat = 1;
    float CostoInput;

    fpInClienti = fopen("ClientiRegistrati.txt","r");
    if(fpInClienti != NULL){
        Clienti = LetturaDaFileUtenti(fpInClienti, Clienti);
    }else{ 
        printf("\n<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< 0 >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");   
        Clienti = Ins_OrdUtenti("ADMIN","ADMIN",0,Clienti);
    }
    fclose(fpInClienti);

//lettura aereoporti
    fpInCollegamentiAereoArchi = fopen ("VoliDisponibili.txt","r");
    fpInCollegamentiAereoNodi = fopen ("MappaTappe.txt","r");
    if (fpInCollegamentiAereoArchi != NULL || fpInCollegamentiAereoNodi != NULL)
    {
        CollegamentiAereo = LetturaDaFILEGrafo(fpInCollegamentiAereoNodi,fpInCollegamentiAereoNodi,CollegamentiAereo);
        printf("Caricamento dati Aereoporti.\n");
    }
    else
    {
        CollegamentiAereo = crea_grafo_vuoto(1);
    }
    fclose(fpInCollegamentiAereoArchi);
    fclose(fpInCollegamentiAereoNodi);
    
//lettura treni   
    fpInCollegamentiTrenoArchi = fopen ("TreniDisponibili.txt","r");
    fpInCollegamentiTrenoNodi = fopen ("MappaTappe.txt","r");
    if (fpInCollegamentiTrenoArchi != NULL || fpInCollegamentiTrenoNodi != NULL)
    {
        CollegamentiTreno = LetturaDaFILEGrafo(fpInCollegamentiTrenoNodi,fpInCollegamentiTrenoNodi,CollegamentiTreno);
        printf("Caricamento dati Stazioni.\n");
    }
    else
    {
        CollegamentiTreno = crea_grafo_vuoto(1);
    }
    fclose(fpInCollegamentiTrenoArchi);
    fclose(fpInCollegamentiTrenoNodi);

    
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
        //check per aggiungere i collegamenti necessari
        printf("Benvenuto nella sezione amministrativa del applicazione.\nInserire il corrispettivo codice per eseguire una delle azioni qui riportate:\n");
        printf("0 - Aggiungi una Tappa. \n");
        printf("1 - Rimuovi una Tappa. \n");
        printf("2 - Aggiungi un collegamento tra gli Aereoporti. \n");
        printf("3 - Rimuovi un collegamento tra gli Aereoporti. \n");
        printf("4 - Aggiungi un collegamento tra le Stazioni Ferroviarie. \n");
        printf("5 - Rimuovi un collegamento tra gli le Stazioni Ferroviarie. \n");
        printf("6 - Aggiungi un Hotel associato ad una Tappa. \n");
        printf("7 - Rimuovi un Hotel associato ad una Tappa. \n");
        printf("8 - Aggiungi un collegamento tra gli Hotel associati ad una Tappa. \n");
        printf("9 - Rimuovi un collegamento tra gli Hotel associati ad una Tappa. \n");
        printf("10 - Visualizza Mappa degli Aereoporti.\n");
        printf("11 - Visualizza Mappa delle Stazioni Ferroviarie.\n");
        printf("12 - Visualizza Mappa degli Alberghi in una data citta'.\n");

        printf("\n<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< || >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
        while (repeat == 1 && selector<13)
        {
            printf("\n<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< || >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
            printf("Inserire il codice: ");
            scanf("%d", &selector);
            switch (selector)
            {
            case 0:
                printf("\n<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< || >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
                printf("Scrivere il nome della nuova Tappa da aggiungere: ");
                gets(TappaInput);
                strcpy(TappaInput,FormattazioneTappe(TappaInput));
                CollegamentiAereo=g_insert(CollegamentiAereo, TappaInput);
                CollegamentiTreno=g_insert(CollegamentiTreno, TappaInput);
                //check grafo connesso per i collegamenti
                break;
            case 1:
                printf("\n<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< || >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
                printf("Scrivere il nome della Tappa da rimuovere: ");
                gets(TappaInput);
                IndexInput=get_Indice_from_Nome(CollegamentiAereo, TappaInput);
                CollegamentiAereo=EliminazioneLogicaNodo(CollegamentiAereo,IndexInput); 
                CollegamentiTreno=EliminazioneLogicaNodo(CollegamentiTreno,IndexInput); 
                //check grafo connesso per i collegamenti                
                break;

            case 2:
                printf("\n<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< || >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
                printf("Scrivere il nome della Tappa iniziale: ");   
                gets(SRCInput);
                printf("Scrivere il nome della Tappa destinazione: ");   
                gets(DESTInput);  
                printf("Scrivere la distanza tra i le Tappe: ");
                scanf("%d",&DistanzaInput);
                printf("Scrivere il costo del biglietto tra i le Tappe: ");
                scanf("%f",&CostoInput);
                Aggiungi_Arco(CollegamentiAereo,get_Indice_from_Nome(CollegamentiAereo,SRCInput),get_Indice_from_Nome(CollegamentiAereo,DESTInput),DistanzaInput,CostoInput,1);       
                break;

            case 3:
            printf("\n<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< || >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
            
                break;

            case 4:
             printf("\n<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< || >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
                printf("Scrivere il nome della Tappa iniziale: ");   
                gets(SRCInput);
                printf("Scrivere il nome della Tappa destinazione: ");   
                gets(DESTInput);  
                printf("Scrivere la distanza tra i le Tappe: ");
                scanf("%d",&DistanzaInput);
                printf("Scrivere il costo del biglietto tra i le Tappe: ");
                scanf("%f",&CostoInput);
                Aggiungi_Arco(CollegamentiTreno,get_Indice_from_Nome(CollegamentiTreno,SRCInput),get_Indice_from_Nome(CollegamentiTreno,DESTInput),DistanzaInput,CostoInput,1);       
                break;

            case 5:
            
                break;

            case 6:
            
                break;

            case 7:
            
                break;

            case 8:
                printf("\n<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< || >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
                printf("Inserire la Tappa di cui modificare gli alberghi: ");
                gets(TappaInput);
                strcpy(TappaInput,FormattazioneTappe(TappaInput));

                //Load albergo giusto in memoria
                sprintf(FileAlberghiNodi, "%sAlberghiNodi.txt", TappaInput);
                sprintf(FileAlberghiArchi, "%sAlberghiArchi.txt", TappaInput);
                fpInAlberghiNodi = fopen(FileAlberghiNodi,"r");
                fpInAlberghiArchi = fopen (FileAlberghiArchi, "r");
                if(FileAlberghiNodi!=NULL && fpInAlberghiArchi!=NULL){
                    CollegamentiAlberghi = LetturaDaFILEGrafo(fpInAlberghiNodi,fpInAlberghiArchi,CollegamentiAlberghi);
                }
                fclose(fpInAlberghiNodi);
                fclose(fpInAlberghiArchi); 

                printf("Scrivere il nome della Tappa iniziale: ");   
                gets(SRCInput);
                printf("Scrivere il nome della Tappa destinazione: ");   
                gets(DESTInput);  
                printf("Scrivere la distanza tra i le Tappe: ");
                scanf("%d",&DistanzaInput);
                printf("Scrivere il costo del biglietto tra i le Tappe: ");
                scanf("%f",&CostoInput);
                Aggiungi_Arco(CollegamentiAlberghi,get_Indice_from_Nome(CollegamentiAlberghi,SRCInput),get_Indice_from_Nome(CollegamentiAlberghi,DESTInput),DistanzaInput,CostoInput,1);       
                break;

            case 9:
            
                break;
            case 10:
                printf("\n<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< || >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
                stampa_grafo(CollegamentiAereo);
                break;
            case 11:
                printf("\n<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< || >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
                stampa_grafo(CollegamentiTreno);
                break;                
            case 12:
                printf("\n<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< || >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
                printf("Inserire la citta' di cui visionare gli Alberghi: ");
                gets(TappaInput);
            
                strcpy(TappaInput,FormattazioneTappe(TappaInput));            

                //Load albergo giusto in memoria
                sprintf(FileAlberghiNodi, "%sAlberghiNodi.txt", TappaInput);
                sprintf(FileAlberghiArchi, "%sAlberghiArchi.txt", TappaInput);
                fpInAlberghiNodi = fopen(FileAlberghiNodi,"r");
                fpInAlberghiArchi = fopen (FileAlberghiArchi, "r");
                if(FileAlberghiNodi!=NULL && fpInAlberghiArchi!=NULL){
                    CollegamentiAlberghi = LetturaDaFILEGrafo(fpInAlberghiNodi,fpInAlberghiArchi,CollegamentiAlberghi);
                }
                fclose(fpInAlberghiNodi);
                fclose(fpInAlberghiArchi); 

                stampa_grafo(CollegamentiAlberghi);
                deallocaGrafo(CollegamentiAlberghi);                       
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
        printf("Benvenuto nella sezione cliente dell'applicazione.\nInserire il corrispettivo codice per eseguire una delle azioni qui riportate:\n");
        printf("0 - Visualizza mete dsponibili.\n");
        printf("1 - Prenota viaggio in Aereo.\n");
        printf("2 - Prenota viaggio in Treno.\n");
        printf("");
        /* code */ //modalita utente


    }
    

    //possibilmente da spostare
    fpOutTappe = fopen("MappaTappe.txt","w+");
    if (fpOutTappe == NULL) exit(-1);
    CreazioneFILEGrafoNodi(fpOutTappe,CollegamentiAereo);
    fclose(fpOutTappe);

    fpOutCollegamentiAereoArchi = fopen("VoliDisponibili.txt","w+");
    if (fpOutCollegamentiAereoArchi==NULL) exit(-1);
    CreazioneFILEGrafoArchi(fpOutCollegamentiAereoArchi,CollegamentiAereo);
    fclose(fpOutCollegamentiAereoArchi);


    fpOutCollegamentiTrenoArchi = fopen("TreniDisponibili.txt","w+");
    if (fpOutCollegamentiTrenoArchi==NULL) exit(-1);
    CreazioneFILEGrafoArchi(fpOutCollegamentiTrenoArchi,CollegamentiTreno);
    fclose(fpOutCollegamentiTrenoArchi);


    fpOutClienti = fopen("ClientiRegistrati.txt","w+");
    if (fpOutClienti==NULL) exit(-1);
    CreazioneFILERisultatoUtenti(fpOutClienti,Clienti);
    fclose(fpOutClienti);

    deallocaGrafo(CollegamentiAereo);
    deallocaGrafo(CollegamentiTreno);
    deallocaGrafo(CollegamentiAlberghi);
    DeallocaAlberoUtenti(Clienti);
    return 0;
}
