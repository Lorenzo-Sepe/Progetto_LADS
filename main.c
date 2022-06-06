#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "StrutturaAlberoUtente.h"
#include "StrutturaGrafi.h"
#include "StrutturaHeap.h"

int main(int argc, char *argv[])
{
    AlberoUtenti Clienti = NULL, ClienteCorrente = NULL;
    MappaCollegamenti CollegamentiTreno = NULL, CollegamentiAereo = NULL, CollegamentiAlberghi = NULL;
    FILE *fpInClienti=NULL, *fpOutClienti=NULL;
    FILE *fpOutTappe;
    FILE *fpInCollegamentiAereoNodi, *fpInCollegamentiAereoArchi;
    //FILE *fpOutCollegamentiAereoNodi;
    FILE *fpOutCollegamentiAereoArchi;
    FILE *fpInCollegamentiTrenoNodi, *fpInCollegamentiTrenoArchi;
    //FILE *fpOutCollegamentiTrenoNodi;
    FILE *fpOutCollegamentiTrenoArchi;
    FILE *fpInCheck, *fpOutCheck;
    char Scelta[MAX_STRINGHE], MailInput[MAX_STRINGHE], PasswordInput[MAX_STRINGHE],NomeInput[MAX_STRINGHE], TappaInput[MAX_STRINGHE],SRCInput[MAX_STRINGHE],DESTInput[MAX_STRINGHE];
    //char FileAlberghiNodi[MAX_STRINGHE];
    //char FileAlberghiArchi[MAX_STRINGHE];
    //int i;
    int selector=0, DistanzaInput,IndexInput, repeat = 1, checkIsolatoAereo, checkIsolatoTreno;
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
    if (fpInCollegamentiAereoArchi != NULL && fpInCollegamentiAereoNodi != NULL)
    {
        CollegamentiAereo = LetturaDaFILEGrafoNodi(fpInCollegamentiAereoNodi);
        CollegamentiAereo = LetturaDaFILEGrafoCollegamenti(fpInCollegamentiAereoArchi,CollegamentiAereo);
        printf("Caricamento dati Aereoporti.\n");
        //******************************************************************
        //stamapVettoreAdiacenza(CollegamentiAereo);
    }
    else
    {
		printf("lettura non effettuata\n");
        CollegamentiAereo = crea_grafo_vuoto(1);
    }
    fclose(fpInCollegamentiAereoArchi);
    fclose(fpInCollegamentiAereoNodi);
    
	//lettura treni   
    fpInCollegamentiTrenoArchi = fopen ("TreniDisponibili.txt","r");
    fpInCollegamentiTrenoNodi = fopen ("MappaTappe.txt","r");
    if (fpInCollegamentiTrenoArchi != NULL && fpInCollegamentiTrenoNodi != NULL)
    {
        CollegamentiTreno = LetturaDaFILEGrafoNodi(fpInCollegamentiTrenoNodi);
        CollegamentiTreno = LetturaDaFILEGrafoCollegamenti(fpInCollegamentiTrenoArchi,CollegamentiTreno);
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
    scanf("%s", Scelta);
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
    	//stampa_grafo(CollegamentiAereo);
    	//stampa_grafo(CollegamentiTreno);
        fpInCheck = fopen("CheckAereo.txt","r");
        if (fpInCheck==NULL) printf("File non trovato");
        fscanf(fpInCheck,"%d",&checkIsolatoAereo);
        fclose(fpInCheck);
        if (checkIsolatoAereo==1)
        {   printf("\nPer il grafo degli Aerei:");
            checkIsolatoAereo = grafoSconnesso(CollegamentiAereo);
        }

        fpInCheck = fopen("CheckTreno.txt","r");
        if (fpInCheck==NULL) printf("File non trovato");
        fscanf(fpInCheck,"%d",&checkIsolatoTreno);
        fclose(fpInCheck);
        if (checkIsolatoTreno==1)
        {   printf("\nPer il grafo degli Treni:");
            checkIsolatoTreno = grafoSconnesso(CollegamentiTreno);
        }

        //check per aggiungere i collegamenti necessari
        printf("\nBenvenuto nella sezione amministrativa del applicazione.\nInserire il corrispettivo codice per eseguire una delle azioni qui riportate:\n");
        printf("\n<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< || >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
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
                while (getchar()!='\n') ; 
                scanf("%s", TappaInput);
                strcpy(TappaInput,FormattazioneTappe(TappaInput));
                CollegamentiAereo=g_insert(CollegamentiAereo, TappaInput);
                CollegamentiTreno=g_insert(CollegamentiTreno, TappaInput);
                //check grafo connesso per i collegamenti
                checkIsolatoAereo = 1;
                break;
            case 1:
                printf("\n<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< || >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
                printf("Scrivere il nome della Tappa da rimuovere: ");
                scanf("%s", TappaInput);
                IndexInput=get_Indice_from_Nome(CollegamentiAereo, TappaInput);
                CollegamentiAereo=EliminazioneLogicaNodo(CollegamentiAereo,IndexInput); 
                CollegamentiTreno=EliminazioneLogicaNodo(CollegamentiTreno,IndexInput); 
                //check grafo connesso per i collegamenti 
                //checkIsolatoAereo = grafoSconnesso(CollegamentiAereo);               
                break;

            case 2:
                printf("\n<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< || >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
                printf("Scrivere il nome della Tappa iniziale: ");   
                while (getchar()!='\n') ; 
                scanf("%s", SRCInput);
                strcpy(SRCInput,FormattazioneTappe(SRCInput));
                printf("Scrivere il nome della Tappa destinazione: ");   
                //while (getchar()! ='\n') ; 
                scanf("%s", DESTInput);  
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
                while (getchar()!='\n') ; 
                scanf("%s", SRCInput);
                strcpy(SRCInput,FormattazioneTappe(SRCInput));
                printf("Scrivere il nome della Tappa destinazione: ");   
                scanf("%s", DESTInput);  
                strcpy(DESTInput,FormattazioneTappe(DESTInput));

                Rimuovi_Arco(CollegamentiAereo, get_Indice_from_Nome(CollegamentiAereo, SRCInput), get_Indice_from_Nome(CollegamentiAereo, DESTInput));
                break;

            case 4:
                printf("\n<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< || >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
                printf("Scrivere il nome della Tappa iniziale: ");   
                while (getchar()!='\n') ; 
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
                printf("Scrivere il nome della Tappa iniziale (inserire il carattere '_' al posto dello spazio): ");   
                while (getchar()!='\n');
                gets(SRCInput);
                strcpy(SRCInput,FormattazioneTappe(SRCInput));
                printf("Scrivere il nome della Tappa  (inserire il carattere '_' al posto dello spazio): ");   
                gets(DESTInput);  
                strcpy(DESTInput,FormattazioneTappe(DESTInput));

                Rimuovi_Arco(CollegamentiTreno, get_Indice_from_Nome(CollegamentiTreno, SRCInput), get_Indice_from_Nome(CollegamentiTreno, DESTInput));
                break;

            case 6:
                printf("\n<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< || >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
                printf("Inserire la Tappa a cui aggiungere un albergo (inserire il carattere '_' al posto dello spazio): ");
                while (getchar()!='\n');
                gets(TappaInput);
                strcpy(TappaInput,FormattazioneTappe(TappaInput));

                //Load albergo giusto in memoria
                CollegamentiAlberghi=LoadAlberghi(CollegamentiAlberghi,TappaInput); 
                
                printf("Scegliere il nome dell'albergo (inserire il carattere '_' al posto dello spazio): ");
                gets(NomeInput);
                strcpy(NomeInput,FormattazioneTappe(NomeInput));

                g_insert(CollegamentiAlberghi,NomeInput);
                SaveAlberghi(CollegamentiAlberghi,TappaInput);
                deallocaGrafo(CollegamentiAlberghi);
                break;

            case 7:
                printf("\n<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< || >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
                printf("Inserire la Tappa a cui rimuovere un albergo (inserire il carattere '_' al posto dello spazio): ");   
                while (getchar()!='\n');
                gets(TappaInput);
                strcpy(TappaInput,FormattazioneTappe(TappaInput));

                //Load albergo giusto in memoria
                CollegamentiAlberghi=LoadAlberghi(CollegamentiAlberghi,TappaInput); 
                
                printf("Scegliere il nome dell'albergo (inserire il carattere '_' al posto dello spazio): ");
                gets(NomeInput);
                strcpy(NomeInput,FormattazioneTappe(NomeInput));

                //da sostituire con g_delete una volta che è funzionante
                CollegamentiAlberghi = EliminazioneLogicaNodo(CollegamentiAlberghi,get_Indice_from_Nome(CollegamentiAlberghi,NomeInput));
                SaveAlberghi(CollegamentiAlberghi,TappaInput);
                deallocaGrafo(CollegamentiAlberghi);
                break;

            case 8:
                printf("\n<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< || >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
                printf("Inserire la Tappa di cui modificare gli alberghi (inserire il carattere '_' al posto dello spazio): ");
                while (getchar()!='\n');
                gets(TappaInput);
                strcpy(TappaInput,FormattazioneTappe(TappaInput));

                //Load albergo giusto in memoria
                CollegamentiAlberghi=LoadAlberghi(CollegamentiAlberghi,TappaInput); 

                printf("Scrivere il nome della Tappa iniziale (inserire il carattere '_' al posto dello spazio): ");   
                gets(SRCInput);
                printf("Scrivere il nome della Tappa destinazione (inserire il carattere '_' al posto dello spazio): ");   
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
                printf("Scrivere il nome della Tappa di cui modificare gli alberghi (inserire il carattere '_' al posto dello spazio).");
                while (getchar()!='\n');
                gets(TappaInput);
                strcpy(TappaInput,FormattazioneTappe(TappaInput));

                //Load albergo giusto in memoria
                CollegamentiAlberghi=LoadAlberghi(CollegamentiAlberghi,TappaInput);

                printf("Scrivere il nome della Tappa iniziale (inserire il carattere '_' al posto dello spazio): ");   
                gets(SRCInput);
                strcpy(SRCInput,FormattazioneTappe(SRCInput));
                printf("Scrivere il nome della Tappa destinazione (inserire il carattere '_' al posto dello spazio): ");   
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
                printf("Inserire la citta' di cui visionare gli Alberghi (inserire il carattere '_' al posto dello spazio): ");
                while (getchar()!='\n');
                gets(TappaInput);
            
                strcpy(TappaInput,FormattazioneTappe(TappaInput));            

                //Load albergo giusto in memoria
                CollegamentiAlberghi=LoadAlberghi(CollegamentiAlberghi,TappaInput);
				stamapVettoreAdiacenza(CollegamentiAlberghi, 2);
                deallocaGrafo(CollegamentiAlberghi);                       
                break;  
                                
            case 13:
                printf("\n<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< || >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
                printf("Scegli il grafo di cui nominare una tappa.\n0 - Aereoporti. 1 - Stazioni Ferroviarie. 2 - Alberghi.\n");
                scanf("%d",&selector);
                if (selector==0)
                {
                    printf("Scegliere il nodo da nominare (Inserire l''indice): ");
                    scanf("%d",&IndexInput);
                    printf("\nScegliere il nome: ");
                    while (getchar()!='\n');
                    gets(TappaInput);
                    nomina_nodo(CollegamentiAereo,IndexInput,TappaInput);
                }
                else if (selector==1)
                {
                    printf("Scegliere il nodo da nominare (inserire il carattere '_' al posto dello spazio): ");
                    scanf("%d",&IndexInput);
                    printf("\nScegliere il nome: ");
                    while (getchar()!='\n');
                    gets(TappaInput);
                    nomina_nodo(CollegamentiTreno,IndexInput,TappaInput);
                }
                else
                {
                    printf("Scegliere la citta' di cui nominare l'albergo (inserire il carattere '_' al posto dello spazio): ");
                    while (getchar()!='\n');
                    gets(TappaInput);
                    printf("Scegliere il nodo da nominare (inserire l'indice'): ");
                    scanf("%d",&IndexInput);
                    printf("Scegliere il nome dell'albergo (inserire il carattere '_' al posto dello spazio): ");
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
        

        
        printf("Continuare? O = No/1 = Si: ");
        scanf("%d",&repeat);
        }
    }
    else
    {
		
        printf("Benvenuto nella sezione cliente dell'applicazione.\nInserire il corrispettivo codice per eseguire una delle azioni qui riportate:\n");
        printf("(inserire il carattere '_' al posto dello spazio)\n");
		//printf("0 - Uscire.\n");
        
        while (repeat == 1 && selector<6)
        {
			printf("0 - Visualizza mete dsponibili.\n");
			printf("1 - Visualizza albergi per Tappa.\n");
			printf("2 - Prenota viaggio in Aereo.\n");
			printf("3 - Prenota viaggio in Treno.\n");
			printf("4 - Aggiungere al Saldo.\n");
			printf("5 - Visualizzare il saldo.\n");
            printf("\n<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< || >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
            printf("Inserire il codice: ");
            scanf("%d", &selector);
            switch (selector){
                case 0:
                    printf("\n<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< || >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
                    stamapVettoreAdiacenza(CollegamentiAereo, 0);
                    break;
                case 1:   
                    printf("\n<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< || >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");//                ***************************************
                    printf("Selezionare la Tappa di cui visualizzare gli Alberghi.\n");
                    while (getchar()!='\n'); 
                    scanf("%s", TappaInput);
                    strcpy(TappaInput,FormattazioneTappe(TappaInput));

                    //Load albergo giusto in memoria
                    CollegamentiAlberghi=LoadAlberghi(CollegamentiAlberghi,TappaInput);

                    stamapVettoreAdiacenza(CollegamentiAlberghi, 2);

                    deallocaGrafo(CollegamentiAlberghi);
                    break;
                case 2:
                    printf("\n<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< || >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
                    printf("Scrivere la citta' di partenza: ");
                    while (getchar()!='\n') ; 
                    scanf("%s", SRCInput);
                    strcpy(SRCInput,FormattazioneTappe(SRCInput));
                    printf("Scrivere la citta' di arrivo: ");
                    while (getchar()!='\n') ; 
                    scanf("%s", DESTInput);
                    strcpy(DESTInput,FormattazioneTappe(DESTInput));
                    
                    checkIsolatoAereo = nodo_isolato(CollegamentiAereo,get_Indice_from_Nome(CollegamentiAereo,DESTInput));
                    if (checkIsolatoAereo == 1)
                    {
                        printf("La Tappa da lei selezionata non è raggiungibile.\n");
                        updateCheckAereo(CollegamentiAereo);

                    }
                    else
                    {
                        printf("Vuoi prenotare il viaggio in base al Costo o la Distanza? C - costo, D - distanza\n");
                        scanf("%s",Scelta);
                        //Load albergo giusto in memoria
                        CollegamentiAlberghi=LoadAlberghi(CollegamentiAlberghi,DESTInput);

                        if (strcmp(Scelta,"C") == 0 || strcmp(Scelta,"c") == 0)
                        {   //Costo
                            PrezzoFinale=dijkstraCosto(CollegamentiAereo, get_Indice_from_Nome(CollegamentiAereo,SRCInput), get_Indice_from_Nome(CollegamentiAereo,DESTInput));
                        }
                        else
                        {
                          PrezzoFinale=dijkstraDistanza(CollegamentiAereo,get_Indice_from_Nome(CollegamentiAereo, SRCInput), get_Indice_from_Nome(CollegamentiAereo,DESTInput));
                        }
						
						if(PrezzoFinale != MAX_DIJKSTRA){
                        stamapVettoreAdiacenza(CollegamentiAlberghi, 2);

                        printf("In quale Albergo si desidera fermare?\n");
                        while (getchar()!='\n') ; 
                        scanf("%s", TappaInput);
                        int dest = 0;
						dest = get_Indice_from_Nome(CollegamentiAlberghi,TappaInput); 
						
                        PrezzoFinale += dijkstraDistanza(CollegamentiAlberghi,0,dest);
						printf("Prezzo totale biglietto: %.2f euro.\n",PrezzoFinale);
													
                        printf("Vuoi procedere all'aquisto? [Y/n]"); 
                        scanf("%s", Scelta);
                        if (strcmp(Scelta,"y")==0 || strcmp(Scelta,"Y") == 0){
                            if (ClienteCorrente->Saldo>PrezzoFinale)
                            {
                                Clienti = SottraiAlSaldo(ClienteCorrente,PrezzoFinale);
                        
					    	    printf("Operazione completata.\n");
                            }
                            else
                            {
                                printf("Operazione non riuscita perche' il saldo e' troppo basso. Aggiornare il saldo? [Y/n]");
                                scanf("%s", Scelta);
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
                    }
                    
                    printf("\n<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< || >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
                break;

                case 3:
                    printf("\n<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< || >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
                    printf("Scrivere la citta' di partenza: ");
                    while (getchar()!='\n') ; 
                    scanf("%s", SRCInput);
                    strcpy(SRCInput,FormattazioneTappe(SRCInput));
                    printf("Scrivere la citta' di arrivo: ");
                    while (getchar()!='\n') ; 
                    scanf("%s", DESTInput);
                    strcpy(DESTInput,FormattazioneTappe(DESTInput));
                    CollegamentiAlberghi=LoadAlberghi(CollegamentiAlberghi, DESTInput);
                    checkIsolatoTreno = nodo_isolato(CollegamentiTreno, get_Indice_from_Nome(CollegamentiTreno,DESTInput));
                    if (checkIsolatoTreno == 1)
                    {
                        printf("La tappa da lei selezionata non è raggiungibile in Treno.\n");
                        updateCheckTreno(CollegamentiTreno);
                        //    *******************************************************
                    }
                    else
                    {
                        printf("Vuoi prenotare il viaggio in base al Costo o la Distanza? C - costo, D - distanza\n");
                        scanf("%s",Scelta);
                        if (strcmp(Scelta,"C") == 0 || strcmp(Scelta,"c") == 0)
                        {
                            PrezzoFinale = dijkstraCosto(CollegamentiTreno, get_Indice_from_Nome(CollegamentiTreno,SRCInput), get_Indice_from_Nome(CollegamentiTreno,DESTInput));
                        }
                        else
                        {
                            PrezzoFinale = dijkstraDistanza(CollegamentiTreno,get_Indice_from_Nome(CollegamentiTreno, SRCInput), get_Indice_from_Nome(CollegamentiTreno,DESTInput));
                        }

						if(PrezzoFinale != MAX_DIJKSTRA){
							stamapVettoreAdiacenza(CollegamentiAlberghi, 2);

							printf("In quale Albergo si desidera fermare? (inserire '_' invece dello spazio)\n");
							while (getchar() != '\n') ; 
							scanf("%s", TappaInput);
							
							PrezzoFinale = PrezzoFinale + dijkstraDistanza(CollegamentiAlberghi,1,get_Indice_from_Nome(CollegamentiAlberghi,TappaInput));
							
							printf("Prezzo totale biglietto: %.2f euro.\n",PrezzoFinale);
							printf("Vuoi procedere all'aquisto? [Y/n]"); 
							scanf("%s", Scelta);
							if (strcmp(Scelta,"y")==0 || strcmp(Scelta,"Y") == 0){
								if (ClienteCorrente->Saldo>PrezzoFinale)
								{
									Clienti = SottraiAlSaldo(ClienteCorrente,PrezzoFinale);
                        
									printf("Operazione completata.\n");
								}
								else
                            {
                                printf("Operazione non riuscita perche' il saldo e' troppo basso. Aggiornare il saldo? [Y/n]");
                                scanf("%s", Scelta);
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

            updateCheckAereo(CollegamentiAereo);
            updateCheckTreno(CollegamentiTreno);

            printf("Continuare? O = No   1 = Si: ");
            scanf("%d",&repeat);
        }
    }
    
    

    //update files
    
    updateCheckAereo(CollegamentiAereo);
    updateCheckTreno(CollegamentiTreno);
    
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

