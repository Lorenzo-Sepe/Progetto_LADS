#include "StrutturaAlberoUtente.h"
#include <stdlib.h>
#include <stdio.h>

//Funzioni Gestione Albero Utenti

/**
 * @brief Funzione che restituisce il minimo di tutto l'albero degli utenti in ordine lessicografico
 * 
 * @param RadiceInput 
 * @return AlberoUtenti 
 */
AlberoUtenti RicercaMinimoUtenti( AlberoUtenti RadiceInput){
	while (RadiceInput->SX!=NULL)
	{
		RadiceInput=RadiceInput->SX;
	}
	return RadiceInput;
}

//ricorda di fare sempre la ricerca prima di un inserimento
/**
 * @brief inserisce gli utenti nell'albero in ordine lessicografico
 * 
 * @param MailInput 
 * @param PasswordInput 
 * @param RADICE 
 */
AlberoUtenti Ins_OrdUtenti(char *MailInput, char *PasswordInput, float SaldoInput, AlberoUtenti RADICE){ //Costruisce un albero binario di ricerca	
    //AlberoUtenti *aux;
    if (RADICE==NULL) { 
		//printf("SIGNAL2");         
        RADICE=(AlberoUtenti)malloc(sizeof(struct Utente)); //chiede una cella di memoria
	   	if (RADICE!=NULL){
		strcpy(RADICE->Mail,MailInput);
        strcpy(RADICE->Password,PasswordInput);
        RADICE->Saldo=SaldoInput;
   	    RADICE->SX=NULL;
   	    RADICE->DX=NULL;
        return RADICE;   
	   	}
		else{
            printf("Errore, memoria non allocata");
        }   
    }
    else {
	   	if(strcmp(MailInput,RADICE->Mail)<0) {
    		RADICE->SX=Ins_OrdUtenti(MailInput,PasswordInput,SaldoInput,RADICE->SX);
		    return RADICE;
	    }
	   	else {
    		RADICE->DX=Ins_OrdUtenti(MailInput,PasswordInput,SaldoInput,RADICE->DX);
		    return RADICE;
	    }
	} 
}   

/**
 * @brief crea un albero utenti a partire da un file testo di input
 * 
 * @param fp 
 * @param RADICE 
 * @return  AlberoUtenti 
 */
AlberoUtenti LetturaDaFileUtenti(FILE *fp, AlberoUtenti RADICE)
{
	//printf("SIGNAL3");
	char MaiInput[MAX_STRINGHE];
	char PasswordInput[MAX_STRINGHE];
    float SaldoInput;
	//AlberoUtenti nodo;
	while (fscanf(fp,"%s %s %f", MaiInput, PasswordInput, &SaldoInput) == 3) 
	{
		RADICE = Ins_OrdUtenti(MaiInput, PasswordInput, SaldoInput, RADICE);                                                                                                                                                                                                                                                                                      
	}
	
	return RADICE;
}

/**
 * @brief Salva in un file apposito la visita in order dell'albero utenti
 * 
 * @param fp 
 * @param RADICE 
 */
void CreazioneFILERisultatoUtenti(FILE *fp, AlberoUtenti RADICE){
	if (RADICE!=NULL) {
		CreazioneFILERisultatoUtenti(fp,RADICE->SX);
		CreazioneFILERisultatoUtenti(fp,RADICE->DX); 

		fprintf(fp,"%s ", RADICE->Mail);
		fprintf(fp,"%s ", RADICE->Password);
		fprintf(fp,"%f ", RADICE->Saldo);
		fprintf(fp,"\n");
    } 
}

/**
 * @brief dealloca la memoria occupata dall'albero utente
 * 
 * @param Radice 
 */
void DeallocaAlberoUtenti(AlberoUtenti Radice){
   //post-order like FatalError hinted at
       if (Radice != NULL) {
        DeallocaAlberoUtenti(Radice->DX);
        DeallocaAlberoUtenti(Radice->SX);
        free(Radice);
     }
}

/**
 * @brief stampa le informazioni dell'albero In ordine
 * 
 * @param RADICE 
 */
 void InorderUtenti(AlberoUtenti RADICE)   // visita in ordine simmetrico o inorder
 {	if (RADICE!=NULL) {
		InorderUtenti(RADICE->SX);
		printf("Informazioni Utente: \nMail: %s.\nSaldo: %.2f.\n",RADICE->Mail,RADICE->Saldo);
        stampaListaDeiDesideri(RADICE->ListaDesideri);
		InorderUtenti(RADICE->DX); 
    }    
}

/**
 * @brief aggiunge la quantità di input al saldo dell'utente
 * 
 * @param NodoInput 
 * @param ValoreInput 
 */
AlberoUtenti AggiungiAlSaldo(AlberoUtenti NodoInput, float ValoreInput){
    NodoInput->Saldo = (NodoInput->Saldo) + ValoreInput;
	printf("Importo aggiornato.");
	return NodoInput;
}

/**
 * @brief sottrae al
 * 
 * @param NodoInput 
 * @param ValoreInput 
 */
AlberoUtenti SottraiAlSaldo(AlberoUtenti NodoInput, float ValoreInput){
    NodoInput->Saldo = (NodoInput->Saldo) - ValoreInput;
	printf("Importo aggiornato.");
	return NodoInput;
}

/**
 * @brief 
 * 
 * @param MailInput 
 * @param RADICE 
 * @return  AlberoUtenti 
 */
AlberoUtenti RicercaBinariaUtenti(char * MailInput, char *PasswordInput,AlberoUtenti RADICE){ //Ricerca dicotomica (binaria) su ABR
	if (RADICE==NULL) return RADICE;
	else {
		if (strcmp(MailInput,RADICE->Mail)==0 && strcmp(PasswordInput,RADICE->Password)==0) return RADICE;
		else {
			if (strcmp(MailInput,RADICE->Mail)<0)
				return RicercaBinariaUtenti(MailInput, PasswordInput ,RADICE->SX) ;
			else 
				return RicercaBinariaUtenti(MailInput, PasswordInput ,RADICE->DX);
		}
	}
}