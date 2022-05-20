#ifndef GRAFI_H
#define GRAFI_H

struct GrafoCollegamenti {
	int NumeroNodi;
	struct Città **ListaAdiacenza;
};

struct Città{
	int key; //rapresenta la  destinazione dell'arco
	int distanza; //valore associato all'arco
	float costo;
	struct Città *next;
};

typedef struct Città* ArchiGrafo;
typedef struct GrafoCollegamenti* MappaCollegamenti;

MappaCollegamenti crea_grafo_vuoto(int NumeroNodiInput);
int getEmpty(MappaCollegamenti Grafo);
void stampa_grafo(MappaCollegamenti GrafoInput);
void DepthFirstSearch(MappaCollegamenti GrafoInput);
void DFS_Visita(MappaCollegamenti GrafoInput, int i, int *VettoreFlag);
void Aggiungi_Arco(MappaCollegamenti graph, int src, int dest, int distanza, float costo); //non orientato  
void Aggiungi_Arco_Orientato(MappaCollegamenti graph, int src, int dest, int distanza, float costo); //orientato 
struct Città* createNode(int v);
int GradoUscita (MappaCollegamenti GrafoInput, int VerticeInput);
int GradoIngresso(MappaCollegamenti GrafoInput, int VerticeInput);
int Ricerca_Vertice_In_Adj (ArchiGrafo ListaInput, int VerticeInput);
int lunghezzaListaAdj(ArchiGrafo head);
MappaCollegamenti CreaGrafoTrasposto (MappaCollegamenti GrafoInput);
int VerificaGrafoConnesso(MappaCollegamenti GrafoInput);
int VerificaSottografo (MappaCollegamenti GrafoInput, MappaCollegamenti GrafoPadre);
void dijkstraDistanza(MappaCollegamenti graph, int src);
void dijkstraCosto(MappaCollegamenti graph, int src);

#endif
