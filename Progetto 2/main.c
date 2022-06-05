#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "StrutturaAlberoUtente.h"
#include "StrutturaGrafi.h"

#define INT_MAX 9999

int main(int argc, char const *argv[])
{
    AlberoUtenti Clienti = NULL, ClienteCorrente = NULL;
    MappaCollegamenti CollegamentiTreno = NULL, CollegamentiAereo = NULL, CollegamentiAlberghi = NULL;
    FILE *fpInClienti, *fpOutClienti;
    FILE *fpOutTappe;
    FILE *fpInCollegamentiAereoNodi, *fpInCollegamentiAereoArchi;
    FILE *fpOutCollegamentiAereoNodi, *fpOutCollegamentiAereoArchi;
    FILE *fpInCollegamentiTrenoNodi, *fpInCollegamentiTrenoArchi;
    FILE *fpOutCollegamentiTrenoNodi, *fpOutCollegamentiTrenoArchi;
    FILE *fpInCheck, *fpOutCheck;
    char Scelta[MAX_STRINGHE], MailInput[MAX_STRINGHE], PasswordInput[MAX_STRINGHE],NomeInput[MAX_STRINGHE], TappaInput[MAX_STRINGHE],SRCInput[MAX_STRINGHE],DESTInput[MAX_STRINGHE];
    char FileAlberghiNodi[MAX_STRINGHE],FileAlberghiArchi[MAX_STRINGHE];
    int i, selector=0, DistanzaInput,IndexInput,repeat = 1,checkIsolatoAereo,checkIsolatoTreno;
    float CostoInput,PrezzoFinale,ImportoInput;

    fpInClienti = fopen("ClientiRegistrati.txt","r");
    if(fpInClienti != NULL){
        Clienti = LetturaDaFileUtenti(fpInClienti, Clienti);
    }else{ 
        printf("\n<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< 0 >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");   
        Clienti = Ins_OrdUtenti("ADMIN","ADMIN",0,Clienti);
    }
    fclose(fpInClienti);

//lettura aereoporti
    fpInCollegamentiAereoArchi = fopen("VoliDisponibili.txt","r");
    fpInCollegamentiAereoNodi = fopen("MappaTappe.txt","r");
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
        fpInCheck = fopen("CheckAereo.txt","r");
        if (fpInCheck==NULL) exit(-1);
        fscanf(fpInCheck,"%d",checkIsolatoAereo);
        fclose(fpInCheck);
        if (checkIsolatoAereo==1)
        {   printf("Per il grafo degli Aerei:");
            checkIsolatoAereo = grafoSconnesso(CollegamentiAereo);
        }

        fpInCheck = fopen("CheckTreno.txt","r");
        if (fpInCheck==NULL) exit(-1);
        fscanf(fpInCheck,"%d",checkIsolatoTreno);
        fclose(fpInCheck);
        if (checkIsolatoTreno==1)
        {   printf("Per il grafo degli Treni:");
            checkIsolatoTreno = grafoSconnesso(CollegamentiTreno);
        }

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
        printf("13 - Dai un nome ad una Tappa.\n");

        while (repeat == 1 && selector<14)
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
                checkIsolatoAereo = grafoSconnesso(CollegamentiAereo);
                break;
            case 1:
                printf("\n<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< || >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
                printf("Scrivere il nome della Tappa da rimuovere: ");
                gets(TappaInput);
                IndexInput=get_Indice_from_Nome(CollegamentiAereo, TappaInput);
                CollegamentiAereo=EliminazioneLogicaNodo(CollegamentiAereo,IndexInput); 
                CollegamentiTreno=EliminazioneLogicaNodo(CollegamentiTreno,IndexInput); 
                //check grafo connesso per i collegamenti 
                checkIsolatoAereo = grafoSconnesso(CollegamentiAereo);               
                break;

            case 2:
                printf("\n<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< || >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
                printf("Scrivere il nome della Tappa iniziale: ");   
                gets(SRCInput);
                strcpy(SRCInput,FormattazioneTappe(SRCInput));
                printf("Scrivere il nome della Tappa destinazione: ");   
                gets(DESTInput);  
                strcpy(DESTInput,FormattazioneTappe(DESTInput));
                printf("Scrivere la distanza tra i le Tappe: ");
                scanf("%d",&DistanzaInput);
                printf("Scrivere il costo del biglietto tra i le Tappe: ");
                scanf("%f",&CostoInput);
                Aggiungi_Arco(CollegamentiAereo,get_Indice_from_Nome(CollegamentiAereo,SRCInput),get_Indice_from_Nome(CollegamentiAereo,DESTInput),DistanzaInput,CostoInput,1);       
                break;

            case 3:
                printf("\n<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< || >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
                printf("Scrivere il nome della Tappa iniziale: ");   
                gets(SRCInput);
                strcpy(SRCInput,FormattazioneTappe(SRCInput));
                printf("Scrivere il nome della Tappa destinazione: ");   
                gets(DESTInput);  
                strcpy(DESTInput,FormattazioneTappe(DESTInput));

                Rimuovi_Arco(CollegamentiAereo, get_Indice_from_Nome(CollegamentiAereo, SRCInput), get_Indice_from_Nome(CollegamentiAereo, DESTInput));
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
                printf("\n<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< || >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
                printf("Scrivere il nome della Tappa iniziale: ");   
                gets(SRCInput);
                strcpy(SRCInput,FormattazioneTappe(SRCInput));
                printf("Scrivere il nome della Tappa destinazione: ");   
                gets(DESTInput);  
                strcpy(DESTInput,FormattazioneTappe(DESTInput));

                Rimuovi_Arco(CollegamentiTreno, get_Indice_from_Nome(CollegamentiTreno, SRCInput), get_Indice_from_Nome(CollegamentiTreno, DESTInput));
                break;

            case 6:
                printf("\n<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< || >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
                printf("Inserire la Tappa a cui aggiungere un albergo: ");
                gets(TappaInput);
                strcpy(TappaInput,FormattazioneTappe(TappaInput));

                //Load albergo giusto in memoria
                CollegamentiAlberghi=LoadAlberghi(CollegamentiAlberghi,TappaInput); 
                
                printf("Scegliere il nome dell'albergo: ");
                gets(NomeInput);
                strcpy(NomeInput,FormattazioneTappe(NomeInput));

                g_insert(CollegamentiAlberghi,NomeInput);
                SaveAlberghi(CollegamentiAlberghi,TappaInput);
                deallocaGrafo(CollegamentiAlberghi);
                break;

            case 7:
                printf("\n<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< || >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
                printf("Inserire la Tappa a cui rimuovere un albergo: ");   
                gets(TappaInput);
                strcpy(TappaInput,FormattazioneTappe(TappaInput));

                //Load albergo giusto in memoria
                CollegamentiAlberghi=LoadAlberghi(CollegamentiAlberghi,TappaInput); 
                
                printf("Scegliere il nome dell'albergo: ");
                gets(NomeInput);
                strcpy(NomeInput,FormattazioneTappe(NomeInput));

                //da sostituire con g_delete una volta che è funzionante
                CollegamentiAlberghi = EliminazioneLogicaNodo(CollegamentiAlberghi,get_Indice_from_Nome(CollegamentiAlberghi,NomeInput));
                SaveAlberghi(CollegamentiAlberghi,TappaInput);
                deallocaGrafo(CollegamentiAlberghi);
                break;

            case 8:
                printf("\n<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< || >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
                printf("Inserire la Tappa di cui modificare gli alberghi: ");
                gets(TappaInput);
                strcpy(TappaInput,FormattazioneTappe(TappaInput));

                //Load albergo giusto in memoria
                CollegamentiAlberghi=LoadAlberghi(CollegamentiAlberghi,TappaInput); 

                printf("Scrivere il nome della Tappa iniziale: ");   
                gets(SRCInput);
                printf("Scrivere il nome della Tappa destinazione: ");   
                gets(DESTInput);  
                printf("Scrivere la distanza tra i le Tappe: ");
                scanf("%d",&DistanzaInput);
                printf("Scrivere il costo del biglietto tra i le Tappe: ");
                scanf("%f",&CostoInput);
                Aggiungi_Arco(CollegamentiAlberghi,get_Indice_from_Nome(CollegamentiAlberghi,SRCInput),get_Indice_from_Nome(CollegamentiAlberghi,DESTInput),DistanzaInput,CostoInput,1);       
                SaveAlberghi(CollegamentiAlberghi,TappaInput);
                deallocaGrafo(CollegamentiAlberghi);
                break;

            case 9:
                printf("\n<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< || >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
                printf("Scrivere il nome della Tappa di cui modificare gli alberghi.");
                gets(TappaInput);
                strcpy(TappaInput,FormattazioneTappe(TappaInput));

                //Load albergo giusto in memoria
                CollegamentiAlberghi=LoadAlberghi(CollegamentiAlberghi,TappaInput);

                printf("Scrivere il nome della Tappa iniziale: ");   
                gets(SRCInput);
                strcpy(SRCInput,FormattazioneTappe(SRCInput));
                printf("Scrivere il nome della Tappa destinazione: ");   
                gets(DESTInput);  
                strcpy(DESTInput,FormattazioneTappe(DESTInput));

                Rimuovi_Arco(CollegamentiAlberghi, get_Indice_from_Nome(CollegamentiAlberghi, SRCInput), get_Indice_from_Nome(CollegamentiAlberghi, DESTInput));
                SaveAlberghi(CollegamentiAlberghi,TappaInput);
                deallocaGrafo(CollegamentiAlberghi);
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
                CollegamentiAlberghi=LoadAlberghi(CollegamentiAlberghi,TappaInput);

                deallocaGrafo(CollegamentiAlberghi);                       
                break;  
                                
            case 13:
                printf("\n<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< || >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
                printf("Scegli il grafo di cui nominare una tappa.\n0 - Aereoporti. 1 - Stazioni Ferroviarie. 2 - Alberghi.\n");
                scanf("%d",&selector);
                if (selector==0)
                {
                    printf("Scegliere il nodo da nominare: ");
                    scanf("%d",&IndexInput);
                    printf("\nScegliere il nome: ");
                    gets(TappaInput);
                    nomina_nodo(CollegamentiAereo,IndexInput,TappaInput);
                }
                else if (selector==1)
                {
                    printf("Scegliere il nodo da nominare: ");
                    scanf("%d",&IndexInput);
                    printf("\nScegliere il nome: ");
                    gets(TappaInput);
                    nomina_nodo(CollegamentiTreno,IndexInput,TappaInput);
                }
                else
                {
                    printf("Scegliere la citta' di cui nominare l'albergo: ");
                    gets(TappaInput);
                    printf("Scegliere il nodo da nominare: ");
                    scanf("%d",&IndexInput);
                    printf("Scegliere il nome dell'albergo: ");
                    gets(NomeInput);

                    strcpy(TappaInput,FormattazioneTappe(TappaInput));  
                    strcpy(NomeInput,FormattazioneTappe(NomeInput));  

                    //Load albergo giusto in memoria
                    CollegamentiAlberghi=LoadAlberghi(CollegamentiAlberghi,TappaInput);

                    nomina_nodo(CollegamentiAlberghi,IndexInput,NomeInput);

                    SaveAlberghi(CollegamentiAlberghi,TappaInput);
                    deallocaGrafo(CollegamentiAlberghi);
                }
                break;
            default:
                printf("Operazioni terminate.");
                repeat=0; 
                break;
            }

        checkIsolatoAereo=grafoSconnesso(CollegamentiAereo);
        checkIsolatoTreno=grafoSconnesso(CollegamentiTreno);
        
        fpOutCheck = fopen("Check.txt","w+");
        if (fpOutCheck==NULL) exit(-1);
        fprintf(fpOutCheck,"%d\n",checkIsolatoAereo);
        fprintf(fpOutCheck,"%d\n",checkIsolatoTreno);
        
        fclose(fpOutCheck);
        
        printf("Continuare? O = No/1 = Si: ");
        scanf("%d",&repeat);
        }
    }
    else
    {
        printf("Benvenuto nella sezione cliente dell'applicazione.\nInserire il corrispettivo codice per eseguire una delle azioni qui riportate:\n");
        printf("0 - Visualizza mete dsponibili.\n");
        printf("1 - Visualizza albergi per Tappa.\n");
        printf("2 - Prenota viaggio in Aereo.\n");
        printf("3 - Prenota viaggio in Treno.\n");
        printf("4 - Aggiungere al Saldo.\n");
        printf("5 - Visualizzare il saldo.\n");
        while (repeat == 1 && selector<6)
        {
            printf("\n<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< || >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
            printf("Inserire il codice: ");
            scanf("%d", &selector);
            switch (selector){
                case 0:
                    printf("\n<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< || >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
                    stamapVettoreAdiacenza(CollegamentiAereo);
                    break;
                case 1:   
                    printf("\n<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< || >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
                    printf("Selezionare la Tappa di cui visualizzare gli Alberghi.\n");
                    gets(TappaInput);
                    strcpy(TappaInput,FormattazioneTappe(TappaInput));

                    //Load albergo giusto in memoria
                    CollegamentiAlberghi=LoadAlberghi(CollegamentiAlberghi,TappaInput);

                    stamapVettoreAdiacenza(CollegamentiAlberghi);

                    deallocaGrafo(CollegamentiAlberghi);
                    break;
                case 2:
                    printf("\n<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< || >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
                    printf("Scrivere la citta' di partenza: ");
                    gets(SRCInput);
                    strcpy(SRCInput,FormattazioneTappe(SRCInput));
                    printf("Scrivere la citta' di arrivo: ");
                    gets(DESTInput);
                    strcpy(DESTInput,FormattazioneTappe(DESTInput));
                    checkIsolatoAereo = nodo_isolato(CollegamentiAereo,get_Indice_from_Nome(CollegamentiAereo,DESTInput));
                    if (checkIsolatoAereo == 1)
                    {
                        printf("La Tappa da lei selezionata non è raggiungibile.\n");
                    }
                    else
                    {
                        printf("Vuoi prenotare il viaggio in base al Costo o la Distanza? C - costo, D - distanza\n");
                        scanf("%s",&Scelta);
                        //Load albergo giusto in memoria
                        CollegamentiAlberghi=LoadAlberghi(CollegamentiAlberghi,SRCInput);

                        if (strcp(Scelta,"C") == 0 || strcp(Scelta,"c") == 0)
                        {   //Costo
                            PrezzoFinale=dijkstraCosto(CollegamentiAereo, get_Indice_from_Nome(CollegamentiAereo,SRCInput), get_Indice_from_Nome(CollegamentiAereo,DESTInput));
                        }
                        else
                        {
                          PrezzoFinale=dijkstraDistanza(CollegamentiAereo,get_Indice_from_Nome(CollegamentiAereo, SRCInput), get_Indice_from_Nome(CollegamentiAereo,DESTInput));
                        }
                    
                        stamapVettoreAdiacenza(CollegamentiAlberghi);

                        printf("In quale Albergo si desidera fermare?\n");
                        gets(TappaInput);

                        PrezzoFinale += dijkstraDistanza(CollegamentiAlberghi,0,get_Indice_from_Nome(CollegamentiAlberghi,TappaInput));

                        printf("Vuoi procedere all'aquisto? [Y/n]"); 
                        scanf("%s", &Scelta);
                        if (strcmp(Scelta,"y")==0 || strcmp(Scelta,"Y") == 0){
                            if (ClienteCorrente->Saldo>PrezzoFinale)
                            {
                                Clienti = SottraiAlSaldo(ClienteCorrente,PrezzoFinale);
                        
					    	    printf("Operazione completata.\n");
                            }
                            else
                            {
                                printf("Operazione non riuscita perche' il saldo e' troppo basso. Aggiornare il saldo? [Y/n]");
                                scanf("%s", &Scelta);
                                if (strcmp(Scelta,"y")==0 || strcmp(Scelta,"Y") == 0)
                                {
                                    printf("Inserire l'importo: euro ");
                                    scanf("%f", &ImportoInput);
                                    Clienti = AggiungiAlSaldo(ClienteCorrente,ImportoInput); 
                                    Clienti = SottraiAlSaldo(ClienteCorrente,PrezzoFinale);    
							
						    	    printf("Operazione completata.\n"); 
                                }
                            }     
                        }
                        else
                        {
                            printf("Operazione annullata.\n");
                        }
                    }
                    
                    printf("\n<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< || >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
                break;

                case 3:
                    printf("\n<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< || >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
                    printf("Scrivere la citta' di partenza: ");
                    gets(SRCInput);
                    strcpy(SRCInput,FormattazioneTappe(SRCInput));
                    printf("Scrivere la citta' di arrivo: ");
                    gets(DESTInput);
                    strcpy(DESTInput,FormattazioneTappe(DESTInput));
                    checkIsolatoTreno = nodo_isolato(CollegamentiTreno, get_Indice_from_Nome(CollegamentiTreno,DESTInput));
                    if (checkIsolatoTreno == 1)
                    {
                        printf("La tappa da lei selezionata non è raggiungibile in Treno.\n");
                    }
                    else
                    {
                        printf("Vuoi prenotare il viaggio in base al Costo o la Distanza? C - costo, D - distanza\n");
                        scanf("%s",&Scelta);
                        if (strcp(Scelta,"C") == 0 || strcp(Scelta,"c") == 0)
                        {
                            PrezzoFinale = dijkstraCosto(CollegamentiTreno, get_Indice_from_Nome(CollegamentiTreno,SRCInput), get_Indice_from_Nome(CollegamentiTreno,DESTInput));
                        }
                        else
                        {
                            PrezzoFinale = dijkstraDistanza(CollegamentiTreno,get_Indice_from_Nome(CollegamentiTreno, SRCInput), get_Indice_from_Nome(CollegamentiTreno,DESTInput));
                        }

                        stamapVettoreAdiacenza(CollegamentiAlberghi);

                        printf("In quale Albergo si desidera fermare?\n");
                        gets(TappaInput);

                        PrezzoFinale += dijkstraDistanza(CollegamentiAlberghi,1,get_Indice_from_Nome(CollegamentiAlberghi,TappaInput));

                        printf("Vuoi procedere all'aquisto? [Y/n]"); 
                        scanf("%s", &Scelta);
                        if (strcmp(Scelta,"y")==0 || strcmp(Scelta,"Y") == 0){
                            if (ClienteCorrente->Saldo>PrezzoFinale)
                            {
                                Clienti = SottraiAlSaldo(ClienteCorrente,PrezzoFinale);
                        
						        printf("Operazione completata.\n");
                            }
                            else
                            {
                                printf("Operazione non riuscita perche' il saldo e' troppo basso. Aggiornare il saldo? [Y/n]");
                                scanf("%s", &Scelta);
                                if (strcmp(Scelta,"y")==0 || strcmp(Scelta,"Y") == 0)
                                {
                                    printf("Inserire l'importo: euro ");
                                    scanf("%f", &ImportoInput);
                                    Clienti = AggiungiAlSaldo(ClienteCorrente,ImportoInput); 
                                    Clienti = SottraiAlSaldo(ClienteCorrente,PrezzoFinale);    
							
						        	printf("Operazione completata.\n"); 
                                }
                            }     
                        }
                        else
                        {
                            printf("Operazione annullata.\n");
                        }
                    }
                    
                
                printf("\n<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< || >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");

                break; 
            case 4:
                printf("\n<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< || >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
                printf("Inserire l'importo: euro ");
                scanf("%f", &ImportoInput);
                AggiungiAlSaldo(ClienteCorrente,ImportoInput);
                
                printf("\n<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< || >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
                break;
            case 5:
                printf("\n<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< || >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
            	printf("Il saldo corrente del cliente e': %.2f ",ClienteCorrente->Saldo);
            	printf("\n<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< || >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
                
                break;                   
            default:
                printf("Operazioni terminate.");
                repeat=0; 
                break;
            }

            fpOutCheck = fopen("Check.txt","w+");
            if (fpOutCheck==NULL) exit(-1);
            fprintf(fpOutCheck,"%d\n",checkIsolatoAereo);
            fprintf(fpOutCheck,"%d\n",checkIsolatoTreno);
            fclose(fpOutCheck);

            printf("Continuare? O = No/1 = Si: ");
            scanf("%d",&repeat);
        }
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