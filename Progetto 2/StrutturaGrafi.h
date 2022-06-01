#ifndef GRAFI_H
#define GRAFI_H
#define MAX_STRINGHE 1000
#include <stdlib.h>
#include <stdio.h>

struct GrafoCollegamenti {
	int NumeroNodi;
	struct AdjList *ListaAdiacenza;
};

struct AdjList
{
	char NomeTappa[MAX_STRINGHE];
	struct Tappa *head;
	int visibilita;
};
  
struct Tappa{
	int key; //rapresenta la  destinazione dell'arco
	char NomeTappa[MAX_STRINGHE];
	int distanza; 		//valori associati all'arco per differenziare gli archi
	int costo; 
	int visibilita; 	//se il nodo è visibile/esistente. 1 = vero, 0 = falso
	struct Tappa *next;
};

typedef struct Tappa* ArchiGrafo;
typedef struct GrafoCollegamenti* MappaCollegamenti;

char *FormattazioneTappe(char *TappaInput);
MappaCollegamenti crea_grafo_vuoto(int NumeroNodiInput); //possibilmente 6
void nomina_nodo(MappaCollegamenti GrafoInput,int NodoInput, char *NomeInput);
int getEmpty(MappaCollegamenti Grafo);
void stampa_grafo(MappaCollegamenti GrafoInput);
void DepthFirstSearch(MappaCollegamenti GrafoInput);
void DFS_Visita(MappaCollegamenti GrafoInput, int i, int *VettoreFlag);
void Aggiungi_Arco(MappaCollegamenti graph, int src, int dest, int distanza, float costo, int visibilitàInput); //orientato   
void Rimuovi_Arco(MappaCollegamenti graph, int src, int dest);
ArchiGrafo createNode(int v);
int GradoUscita (MappaCollegamenti GrafoInput, int VerticeInput);
int GradoIngresso(MappaCollegamenti GrafoInput, int VerticeInput);
int Ricerca_Vertice_In_Adj (ArchiGrafo ListaInput, int VerticeInput);
int lunghezzaListaAdj(ArchiGrafo head);
ArchiGrafo eliminaNodoListaAdj(ArchiGrafo head, ArchiGrafo nodo);

int VerificaGrafoConnesso(MappaCollegamenti GrafoInput);

void dijkstraDistanza(MappaCollegamenti graph, int src);
void dijkstraCosto(MappaCollegamenti graph, int src);
void printArr(int dist[], int n);
void printArrCost(float cost[],int n);

void stamapVettoreAdiacenza(MappaCollegamenti GrafoInput);

MappaCollegamenti g_insert(MappaCollegamenti GrafoInput, char* NomeInput);
MappaCollegamenti g_delete(MappaCollegamenti GrafoInput, int IndexInput);

MappaCollegamenti EliminazioneLogicaNodo(MappaCollegamenti GrafoInput, int NodoInput);

MappaCollegamenti aggiungiAListaDiAdiacenza(MappaCollegamenti GrafoInput, int i, int keyInput,char* NomeInput, int distanzaInput, int costoInput, int visibilitàInput);
int get_Indice_from_Nome(MappaCollegamenti GrafoInput,char *NomeInput);
char* get_Nome_from_Indice(MappaCollegamenti GrafoInput, int IndiceInput);

void CreazioneFILEGrafoNodi(FILE *fpNodi, MappaCollegamenti GrafoInput);
void CreazioneFILEGrafoArchi(FILE *fpArchi, MappaCollegamenti GrafoInput);
void CreazioneFILEGrafo(FILE *fpNodi, FILE *fpArchi, MappaCollegamenti GrafoInput);
MappaCollegamenti LetturaDaFILEGrafo(FILE *fpNodi, FILE *fpArchi, MappaCollegamenti GrafoInput);
MappaCollegamenti LoadAlberghi(MappaCollegamenti Grafo, char *TappaInput);

void deallocaGrafo(MappaCollegamenti GrafoInput);


#endif


