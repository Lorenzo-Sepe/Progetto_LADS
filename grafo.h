#ifndef GRAFI_H
#define GRAFI_H
#define MAX_STRINGHE 1000
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct GrafoCollegamenti {
	int NumeroNodi;
	struct AdjList *ListaAdiacenza;
};

struct AdjList
{
	char NomeTappa[MAX_STRINGHE];
	int visibilita;
    struct Tappa *head; // Pointer to head node of list
};
  
struct Tappa{
	int key; //rapresenta la  destinazione dell'arco
	char NomeTappa[MAX_STRINGHE];
	int distanza; //valori associati all'arco per differenziare gli archi
	float costo; //
	int visibilita; //se il nodo è visibile/esistente. 1 = vero, 0 = falso
	struct Tappa *next;
};

typedef struct Tappa* ArchiGrafo;
typedef struct GrafoCollegamenti* MappaCollegamenti;

MappaCollegamenti crea_grafo_vuoto(int NumeroNodiInput); //possibilmente 6
void nomina_nodo(MappaCollegamenti GrafoInput,int NodoInput, char *NomeInput);
int getEmpty(MappaCollegamenti Grafo);
void stampa_grafo(MappaCollegamenti GrafoInput);
void DepthFirstSearch(MappaCollegamenti GrafoInput);
void DFS_Visita(MappaCollegamenti GrafoInput, int i, int *VettoreFlag);
void Aggiungi_Arco(MappaCollegamenti graph, int src, int dest, char *NomeInput, int distanza, float costo, int visibilitaInput); //non orientato   
ArchiGrafo createNode(int v);
int GradoUscita (MappaCollegamenti GrafoInput, int VerticeInput);
int GradoIngresso(MappaCollegamenti GrafoInput, int VerticeInput);
int Ricerca_Vertice_In_Adj (ArchiGrafo ListaInput, int VerticeInput);
int lunghezzaListaAdj(ArchiGrafo head);
MappaCollegamenti CreaGrafoTrasposto (MappaCollegamenti GrafoInput);
int VerificaGrafoConnesso(MappaCollegamenti GrafoInput);
int VerificaSottografo (MappaCollegamenti GrafoInput, MappaCollegamenti GrafoPadre);
void dijkstraDistanza(MappaCollegamenti graph, int src);
void dijkstraCosto(MappaCollegamenti graph, int src);
void stamapVettoreAdiacenza(MappaCollegamenti GrafoInput);
MappaCollegamenti g_insert(MappaCollegamenti GrafoInput, char* NomeInput);
MappaCollegamenti EliminazioneLogicaNodo(MappaCollegamenti GrafoInput, int NodoInput);
MappaCollegamenti aggiungiAListaDiAdiacenza(MappaCollegamenti GrafoInput, int i, int keyInput,char* NomeInput, int distanzaInput,float costoInput,int visibilitaInput);

//TODO aggiunta e eliminazione nodi

//TODO lettura e scrittura da file usando substring 
MappaCollegamenti LetturaDaFILEGrafoCollegamenti (FILE *fp, MappaCollegamenti GrafoInput);

#endif
