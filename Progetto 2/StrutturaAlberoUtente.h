#ifndef STRUTTURE_H
#define STRUTTURE_H
#define MAX_STRINGHE 1000

//Definizione struttura albero per gli Utenti
struct Utente {
   char Mail[MAX_STRINGHE];
   char Password[MAX_STRINGHE]; 
   int Saldo;        
   struct NodoListaDesideri *ListaDesideri;
   struct Utente *DX; //puntatore al sottoalbero destro
   struct Utente *SX; //puntatore al sottoalbero sinistro
};

typedef struct Utente* AlberoUtenti;

//Funzioni gestione Albero Utenti
AlberoUtenti RicercaMinimoUtenti(AlberoUtenti RadiceInput);
AlberoUtenti Ins_OrdUtenti(char *MailInput, char *PasswordInput, int SaldoInput,AlberoUtenti RADICE);
void InorderUtenti(AlberoUtenti RADICE);
AlberoUtenti AggiungiAlSaldo(AlberoUtenti NodoInput, int ValoreInput);
AlberoUtenti SottraiAlSaldo(AlberoUtenti NodoInput, int ValoreInput);
AlberoUtenti RicercaBinariaUtenti(char * MailInput, char *PasswordInput,AlberoUtenti RADICE);
AlberoUtenti LetturaDaFileUtenti(FILE *fp, AlberoUtenti RADICE);
void CreazioneFILERisultatoUtenti(FILE *fp, AlberoUtenti RADICE);
void DeallocaAlberoUtenti(AlberoUtenti Radice);

#endif