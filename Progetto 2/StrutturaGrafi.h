#ifndef GRAFI_H
#define GRAFI_H
#define MAX_STRINGHE 1000

struct GrafoCollegamenti {
	int NumeroNodi;
	struct Tappa **ListaAdiacenza;
};

struct Tappa{ 
	int key; //rapresenta la  destinazione dell'arco
	char NomeTappa[MAX_STRINGHE];
	int distanza; //valore associato all'arco
	float costo;
	int visibilità;
	struct Tappa *next;
};

typedef struct Tappa* ArchiGrafo;
typedef struct GrafoCollegamenti* MappaCollegamenti;

MappaCollegamenti crea_grafo_vuoto(int NumeroNodiInput); //possibilmente 6
int getEmpty(MappaCollegamenti Grafo);
void stampa_grafo(MappaCollegamenti GrafoInput);
void DepthFirstSearch(MappaCollegamenti GrafoInput);
void DFS_Visita(MappaCollegamenti GrafoInput, int i, int *VettoreFlag);
void Aggiungi_Arco(MappaCollegamenti graph, int src, int dest, int distanza, float costo); //non orientato  
void Aggiungi_Arco_Orientato(MappaCollegamenti graph, int src, int dest, int distanza, float costo); //orientato 
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
MappaCollegamenti g_insert(MappaCollegamenti GrafoInput);
MappaCollegamenti EliminazioneLogicaNodo(MappaCollegamenti GrafoInput, int NodoInput);

//TODO aggiunta e eliminazione nodi

//TODO lettura e scrittura da file usando substring 
//MappaCollegamenti LetturaDaFILEGrafo (FILE *fp, MappaCollegamenti GrafoInput);

#endif


