#include "StrutturaGrafi.h"
#include "StrutturaHeap.h"
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#define INT_MAX 9999
#define bianco 0 
#define grigio 1 
#define nero 2 

/**
 * @brief 
 * 
 * @param g 
 * @param nodo 
 * @return int 
 */
int nodo_isolato(MappaCollegamenti g, int nodo)
{
	if(g==NULL)
		return 1;
	if(g->ListaAdiacenza[nodo].head == NULL)
		return 1;
	
	return 0;
}

/**
 * @brief funzione che controlla ogni nodo di un grafo e controlla se è isolato dal resto
 * 
 * @param grafoInput 
 * @return int 
 */
int grafoSconnesso(MappaCollegamenti grafoInput){
    if (grafoInput == NULL)
    {
        printf("Grafo vuoto. Impossibile eseguire l'operazione\n");
        return 1;
    }
    int i;
    int check = 0;
    char ris[MAX_STRINGHE];
    for ( i = 0; i < grafoInput->NumeroNodi; i++)
    {
        check = nodo_isolato(grafoInput,i);
        if (check == 1)
        {
            strcpy(ris,get_Nome_from_Indice(grafoInput,i));
            printf("La Tappa %s e' isolata\n", ris);
        }
        
    }

    return check;
}

/**
 * @brief legge da file il numero di nodi e il nome dei nodi
 * 
 * @param fp 
 * @param GrafoInput 
 * @return MappaCollegamenti 
 */
MappaCollegamenti LetturaDaFILEGrafoNodi (FILE *fp){
    int i, NumeroNodi;
    char NomeInput[MAX_STRINGHE];
    MappaCollegamenti grafo;
    
    if (fscanf(fp,"%d",&NumeroNodi)==1)
    {
        grafo=crea_grafo_vuoto(NumeroNodi);
        for ( i = 0; i < NumeroNodi; i++)
        {
            if (fscanf(fp,"%s",NomeInput)==1)
            {
                nomina_nodo(grafo,i,NomeInput);
            }
            
        }
        
    }
    
    return grafo;
}

/**
 * @brief legge da file una lista degli archi e i loro pesi e li aggiunge al grafo
 * 
 * @param fp 
 * @param GrafoInput 
 * @return MappaCollegamenti 
 */
MappaCollegamenti LetturaDaFILEGrafoCollegamenti (FILE *fp, MappaCollegamenti GrafoInput){
    int sorgente, destinazione, distanza, visibility;
    float costo;
    ArchiGrafo p=NULL;
    //char Nome[MAX_STRINGHE];

    while (fscanf(fp, "%d %d %d %f %d", &sorgente, &destinazione, &distanza, &costo, &visibility) == 5)
    {
		p = GrafoInput->ListaAdiacenza[sorgente].head;
		while(p!=NULL){
			if(p->key == destinazione)
				return GrafoInput;
			p = p->next;
        }Aggiungi_Arco(GrafoInput,sorgente,destinazione,distanza,costo,visibility);
    }
    
    return    GrafoInput;
}


/**

 * @brief funzione ausiliaria che stampa gli archi e i loro pesi

 *

 * @param fpArchi

 * @param GrafoInput

 */
void CreazioneFILEGrafoArchi(FILE *fpArchi, MappaCollegamenti GrafoInput){

    int i;

    ArchiGrafo edge;

    if (!getEmpty(GrafoInput))
    {

        for ( i = 0; i < GrafoInput->NumeroNodi; i++)
        {
            edge=GrafoInput->ListaAdiacenza[i].head;

            while (edge!=NULL)
            {
                fprintf(fpArchi, "%d %d %d %g %d\n", i, edge->key, edge->distanza, edge->costo, edge->visibilita);

                edge=edge->next;
            }
        }
    }
}

/**

 * @brief funzione ausiliaria che stampa in un file il numero dei nodi e la lista dei nomi delle tappe

 *

 * @param fpNodi

 * @param GrafoInput

 */

void CreazioneFILEGrafoNodi(FILE *fpNodi, MappaCollegamenti GrafoInput){

    int i;

    fprintf(fpNodi,"%d\n", GrafoInput->NumeroNodi);

    for ( i = 0; i < GrafoInput->NumeroNodi; i++)

    {

        fprintf(fpNodi,"%s\n", GrafoInput->ListaAdiacenza[i].NomeTappa);

    }

}

/**

 * @brief combina le due funzioni qui sopra per leggere il file in modo corretto

 *

 * @param fpNodi

 * @param fpArchi

 * @param GrafoInput

 * @return MappaCollegamenti

 */
MappaCollegamenti LetturaDaFILEGrafo(FILE *fpNodi, FILE *fpArchi, struct GrafoCollegamenti *GrafoInput)
{
	GrafoInput = LetturaDaFILEGrafoNodi(fpNodi);
	if(fpArchi!=NULL)
		GrafoInput = LetturaDaFILEGrafoCollegamenti(fpArchi,GrafoInput);

    return GrafoInput;
}

/**
 * @brief funzione usata per formattare le stringhe delle tappe in modo tale che abbiano l'iniziale maiuscola
 * 
 * @param TappaInput 
 * @return char* 
 */
char* FormattazioneTappe(char* TappaInput){
    int i;
    
    //formatta la stringa per avere solo la prima lettera maiuscola
    for (i=0; i < MAX_STRINGHE; i++)
    {
        TappaInput[i]=tolower(TappaInput[i]);
    }
    TappaInput[0]=toupper(TappaInput[0]);  

    return TappaInput;
}

/**
 * @brief verifica se un grafo è vuoto
 * 
 * @param Grafo 
 * @return int 1 se il grafo è vuoto, 0 altrimenti
 */
int getEmpty(MappaCollegamenti Grafo){
    return (Grafo==NULL);
}

/**
 * @brief crea un grafo di dato numoro nodi senza archi. da sosotituire con lettura da file, è incompleta perché i nodi sono senza nome
 * 
 * @param NumeroNodiInput 
 * @return MappaCollegamenti 
 */
MappaCollegamenti crea_grafo_vuoto(int NumeroNodiInput){
    MappaCollegamenti Grafo;
    int i;
    Grafo = (MappaCollegamenti)malloc(sizeof (struct GrafoCollegamenti) );
    if (Grafo == NULL)
    {
        printf("Errore, impossibile allocare momoria.");
    }
    else
    {
        Grafo->ListaAdiacenza=(struct AdjList *)calloc(NumeroNodiInput,sizeof(struct AdjList));
        if (Grafo->ListaAdiacenza == NULL)
        {
            printf("Errore, impossibile allocare memoria.");
            free(Grafo);
        }
        else
        {
            Grafo->NumeroNodi = NumeroNodiInput;
            for ( i = 0; i < NumeroNodiInput; i++)
            {
               Grafo->ListaAdiacenza[i].head = NULL;
               Grafo->ListaAdiacenza[i].visibilita=1;
            }

        }
    }
    return Grafo;
}

// Function to print shortest path from source to j using
// parent array
void printPath(int parent[], int j)
{
    // Base Case : If j is source
    if (parent[j] == -1)
        return;
    printPath(parent, parent[j]);
    printf("%d ", j);
}

/**
 * @brief A utility function used to print the solution
 * 
 * @param dist 
 * @param n 
 */
void printArr(int dist[], int n)
{
    printf("Vertex   Distance from Source\n");
    for (int i = 0; i < n; ++i)
		if(dist[i]==INT_MAX)
			printf("Nodo Irraggiungibile\n");
		else
			printf("%d \t\t %d\n", i, dist[i]);
}

/**
 * @brief A utility function used to print the solution
 * 
 * @param dist 
 * @param n 
 */
void printArrFloat(float cost[], int n)
{
    printf("Vertex   Distance from Source\n");
    for (int i = 0; i < n; ++i)
		if(cost[i]==INT_MAX)
			printf("Nodo Irraggiungibile\n");
		else
			printf("%d \t\t %.2f\n", i, cost[i]);
}

/**
 * @brief da un nome al nodo di indice dato
 * 
 * @param GrafoInput 
 * @param NodoInput 
 * @param NomeInput 
 */
void nomina_nodo(MappaCollegamenti GrafoInput,int NodoInput, char *NomeInput){
    if (GrafoInput == NULL)
    {
        printf("Grafo Vuoto, impossibile completare l'operazione");
        return;
    }
    
    strcpy(GrafoInput->ListaAdiacenza[NodoInput].NomeTappa, NomeInput);
    return;
}

/**
 * @brief aggiunge un nuovo nodo al grafo e aggiorna il vettore di liste
 * 
 * @param GrafoInput 
 * @return MappaCollegamenti 
 */
MappaCollegamenti g_insert(MappaCollegamenti GrafoInput, char* NomeInput) {
struct AdjList *NuovaLista;

if (GrafoInput == NULL){
	 printf("Grafo vuoto.");
	 return NULL;
 }

NuovaLista = realloc(GrafoInput->ListaAdiacenza, (GrafoInput->NumeroNodi+1) * sizeof(ArchiGrafo));

if (NuovaLista == NULL)  
    printf("\nERRORE: impossibile reallocare memoria \n");
else
{     
GrafoInput->ListaAdiacenza=NuovaLista;
GrafoInput->ListaAdiacenza[GrafoInput->NumeroNodi].head = NULL;
GrafoInput->ListaAdiacenza[GrafoInput->NumeroNodi].visibilita=1;
strcpy(GrafoInput->ListaAdiacenza[GrafoInput->NumeroNodi].NomeTappa, NomeInput);
GrafoInput->NumeroNodi = GrafoInput->NumeroNodi+1;
}

  return GrafoInput;
}

/**
 * @brief cancellazione fisica di un nodo di un grafo
 * 
 * @param GrafoInput 
 * @param IndexInput 
 * @return MappaCollegamenti 
 */
MappaCollegamenti g_delete(MappaCollegamenti GrafoInput, int IndexInput)
{
    int i;
    struct AdjList *NuovaLista;
    ArchiGrafo Target;

    if (GrafoInput == NULL) {
       printf("Grafo vuoto.");
       return NULL;
    }

    NuovaLista = realloc(GrafoInput->ListaAdiacenza, (GrafoInput->NumeroNodi-1) * sizeof(ArchiGrafo));
    if (NuovaLista ==NULL)  
    printf("ERRORE: impossibile reallocare memoria \n");
    else
    {
        if (i != IndexInput)
        {
            NuovaLista[i].head = GrafoInput->ListaAdiacenza[i].head;
            strcpy(NuovaLista[i].NomeTappa, GrafoInput->ListaAdiacenza[i].NomeTappa);
            NuovaLista[i].visibilita = GrafoInput->ListaAdiacenza[i].visibilita;
        }    
    }
    GrafoInput->NumeroNodi--;
    for ( i = 0; i < GrafoInput->NumeroNodi; i++)
    {
        Target = Ricerca_Vertice_In_Adj(GrafoInput->ListaAdiacenza[i].head, IndexInput);
        eliminaNodoListaAdj(GrafoInput->ListaAdiacenza[i].head,Target);
    }
    
    GrafoInput->ListaAdiacenza=NuovaLista;
    return GrafoInput;
}

/**
 * @brief rende il nodo designato invisibile e dealloca la sua lista di adiacenza
 * 
 * @param GrafoInput 
 * @return MappaCollegamenti 
 */
MappaCollegamenti EliminazioneLogicaNodo(MappaCollegamenti GrafoInput, int NodoInput){
    if (GrafoInput == NULL)
    {
        printf ("Il grafo e' vuoto, impossibile eseguire l'operazione.");
        return NULL;
    }
    int i;    
    for ( i = 0; i < GrafoInput->NumeroNodi; i++)
    {
        if (i == NodoInput)
        {
            GrafoInput->ListaAdiacenza[i].visibilita=0;
        }else{
			ArchiGrafo a=GrafoInput->ListaAdiacenza[i].head;
			while(a!=NULL){
				if(a->key == NodoInput)
					a->visibilita = 0;
				a=a->next;
			}
		}
    }
    
    free(GrafoInput->ListaAdiacenza[NodoInput].head);
    return GrafoInput;
}

/**
 * @brief Stampa il Grafo in input
 * 
 * @param GrafoInput 
 */
void stampa_grafo(MappaCollegamenti GrafoInput){
    int i;
    ArchiGrafo edge;
    if (!getEmpty(GrafoInput))
    {
        printf("Ci sono %d Tappe\n", GrafoInput->NumeroNodi);
        for ( i = 0; i < GrafoInput->NumeroNodi; i++)
        {
			if(GrafoInput->ListaAdiacenza[i].visibilita != 0){
//				printf("Tappe adiacenti a %s->",GrafoInput->ListaAdiacenza[i].NomeTappa);
				printf("%s -> ",GrafoInput->ListaAdiacenza[i].NomeTappa);
				edge=GrafoInput->ListaAdiacenza[i].head;
				while (edge!=NULL)
				{
					if(edge->visibilita != 0)
						printf("%s -> ",edge->NomeTappa);
					
					edge=edge->next;
				}
				printf("NULL\n");
			}
        }
    }
}

/**
 * @brief visita del grafo per profondità
 * 
 * @param GrafoInput 
 */
void DepthFirstSearch(MappaCollegamenti GrafoInput) {
    if (GrafoInput == NULL){
        printf("Errore, grafo vuoto.");
        return;
    }
    int i;
    int *VettoreFlag=calloc(GrafoInput->NumeroNodi,sizeof(int));
    if (!VettoreFlag) {
        printf("Errore di allocazione.");
    }
    else {
        for ( i = 0; i < GrafoInput->NumeroNodi; i++)
        {
            if(VettoreFlag[i] == bianco){
                printf("\n%d",i);
                //GrafoInput-> ListaAdiacenza[i]-> NomeTappa;
                DFS_Visita(GrafoInput,i,VettoreFlag);
            }
        }
    }
    free(VettoreFlag);
}

/**
 * @brief visita dei singoli nodi. bianco = 0 = nodo non scoperto, grigio = 1 = nodo scoperto ma non visitato, nero = 2 = nodo visitato
 * 
 * @param GrafoInput 
 * @param i 
 * @param VettoreFlag 
 */
void DFS_Visita(MappaCollegamenti GrafoInput, int i, int *VettoreFlag){
    ArchiGrafo edge;
    VettoreFlag[i]=grigio;
    for (edge = GrafoInput->ListaAdiacenza[i].head; edge ; edge=edge->next)
    {
        if (VettoreFlag[edge->key]==bianco)
        {
            printf("%d ",edge->key);
            DFS_Visita(GrafoInput,edge->key,VettoreFlag);
        }
    }
    VettoreFlag[i]=nero;
}


/**
 * @brief Create a Node in the graph
 * 
 * @param v 
 * @return * Create struct* 
 */
ArchiGrafo createNode(int v) {
  ArchiGrafo newNode = malloc(sizeof(struct Tappa));
  newNode->key = v;
  newNode->next = NULL;
  return newNode;
}

/**
 * @brief Add edge to the graph non oriented
 * 
 * @param graph 
 * @param src 
 * @param dest 
 */

void Aggiungi_Arco(MappaCollegamenti graph, int src, int dest, int distanza, float costo, int visibilitaInput) {
  // Add edge from src to dest
  struct Tappa* newNode = createNode(dest);
  newNode->next = graph->ListaAdiacenza[src].head;
  strcpy(newNode->NomeTappa,get_Nome_from_Indice(graph,dest));
  newNode->visibilita=visibilitaInput;
  newNode->costo=costo;
  newNode->distanza=distanza;
  graph->ListaAdiacenza[src].head = newNode;

  newNode = createNode(src);
  newNode->next = graph->ListaAdiacenza[dest].head;
  strcpy(newNode->NomeTappa,get_Nome_from_Indice(graph,src));
  newNode->visibilita=visibilitaInput;
  newNode->costo=costo;
  newNode->distanza=distanza;
  graph->ListaAdiacenza[dest].head = newNode;
}

/**
 * @brief restituisce la lunghezza della lista di adiacenza
 * 
 * @param head 
 * @return int 
 */
int lunghezzaListaAdj(ArchiGrafo head)
{
	if (head == NULL) return 0;
	return 1 + lunghezzaListaAdj(head->next);
}

/**
 * @brief calcola il grado uscente di un nodo di un grafo orientato (è possibile usarlo per grafi non orientati senza cambiamenti) 
 * 
 * @param GrafoInput 
 * @param VerticeInput 
 * @return int 
 */
int GradoUscita (MappaCollegamenti GrafoInput,int VerticeInput) {
    if (GrafoInput==NULL)
    {
        printf("Grafo non esistente");
        return -1;
    }
    else{
        int ris;
        ris = lunghezzaListaAdj(GrafoInput->ListaAdiacenza[VerticeInput].head);
        return ris;
    }
	
}

/**
 * @brief restituisce 1 se il vertice di input appartiene all lista di adiacenza, 0 altrimenti, e NULL se la lista è vuota
 * 
 * @param ListaInput 
 * @param VerticeInput 
 * @return int 
 */
int Ricerca_Vertice_In_Adj (ArchiGrafo ListaInput, int VerticeInput){
    if (ListaInput == NULL)
    {
        printf("Lista finita, risultato non trovato.");
        return 0;
    }

    if (ListaInput->key == VerticeInput)
    {
        return 1;
    }
    
    return Ricerca_Vertice_In_Adj(ListaInput->next,VerticeInput);
    
}

/**
 * @brief funzione ausiliaria che elimina un nodo da una lista diu adiacenza
 * 
 * @param head 
 * @param nodo 
 * @return ArchiGrafo 
 */
ArchiGrafo eliminaNodoListaAdj(ArchiGrafo head, ArchiGrafo nodo)
{
	ArchiGrafo tmp;
	
	if (head == NULL || nodo == NULL) return head;
	
	if (head == nodo) {
		tmp = head->next;
		free(head);
		return tmp;
	}
	
	head->next = eliminaNodoListaAdj(head->next, nodo);
	
	return head;
}

/**
 * @brief calcola il grado di ingresso di un vertice in un grafo orientato (non usabile in grafi non orientati)
 * 
 * @param GrafoInput 
 * @param VerticeInput 
 * @return int 
 */
int GradoIngresso (MappaCollegamenti GrafoInput, int VerticeInput){
    int i = 0, ris = 0 ;
    if (GrafoInput == NULL)
    {
        printf("Grafo non esistente");
        return -1;
    }
    else{
        
            for (i = 0; i < GrafoInput->NumeroNodi; i++)
            {
                ris = ris + Ricerca_Vertice_In_Adj(GrafoInput->ListaAdiacenza[i].head,VerticeInput);
            }
            return ris;    
    }   
}

/**
 * @brief aggiunge al vettore predecessore
 * 
 * @param GrafoInput 
 * @param i 
 * @param VettoreFlag 
 * @param VettorePred 
 */
static void VGC_Visita(MappaCollegamenti GrafoInput,int i,int *VettoreFlag, ArchiGrafo *VettorePred){
    ArchiGrafo edge;
    VettoreFlag[i]=grigio;
    for (edge = GrafoInput->ListaAdiacenza[i].head; edge ; edge=edge->next)
    {
        if (VettoreFlag[edge->key]==bianco)
        {
            VettorePred[edge->key]=GrafoInput->ListaAdiacenza[i].head; 
            VGC_Visita(GrafoInput,edge->key,VettoreFlag,VettorePred);
        }
    }
    VettoreFlag[i]=nero;
}

/**
 * @brief usando da DFS, verifica se un grafo è connesso, cioè se ogni vertice è raggiungibile da qualunque altro vertice. 1 = grafo connesso, 0 altrimenti.
 * 
 * @param GrafoInput 
 * @return int 
 */
int VerificaGrafoConnesso(MappaCollegamenti GrafoInput)
{
    int ris = 1;
    if (GrafoInput == NULL)
    {
        printf("grafo inserito e' vuoto.");
        return 0;
    }
    else
    {
        int i;
        int *VettoreFlag=calloc(GrafoInput->NumeroNodi,sizeof(int));
        ArchiGrafo *VettorePred = malloc(GrafoInput->NumeroNodi*sizeof(struct Tappa));
        for ( i = 0; i < GrafoInput->NumeroNodi; i++)
        {
            VettorePred[i] = NULL; //inizializzazione vettore predecessore
        }
        
        if (!VettoreFlag || !VettorePred) {
            printf("Errore di allocazione.");
        }
        else {
            for ( i = 0; i < GrafoInput->NumeroNodi; i++)
            {
                if(VettoreFlag[i] == bianco){
                    VGC_Visita(GrafoInput,i,VettoreFlag,VettorePred);
                }
            }
        }

        for ( i = 0; i < GrafoInput->NumeroNodi; i++)
        {
            if(VettorePred[i] == NULL) {
                ris=0;
            }
        }

    free(VettoreFlag);
    free(VettorePred);
    return ris;
    }
}

 
/**
 * @brief The main function that calculates distances of shortest paths from src to all vertices. It is a O(ELogV) function
 * 
 * @param graph 
 * @param src: la key del nodo sorgente
 */
float dijkstraDistanza(MappaCollegamenti graph, int src, int dest)
{     
    if (graph == NULL)
    {
        printf("Errore, Grafo vuoto.");
        return 0;
    }
    int i;
    // dist values used to pick
    // minimum weight edge in cut
    int dist[graph->NumeroNodi];     
    int parent[graph->NumeroNodi];
    float cost[graph->NumeroNodi];
    // minHeap represents set E
    HeapMinimo minHeap = createMinHeap(graph->NumeroNodi);
  
    // Initialize min heap with all vertices. dist value of all vertices, cost array and parent array
    for (i = 0; i < graph->NumeroNodi; ++i)
    {
        parent[i]=-1;
        cost[i] = 0;
        dist[i] = INT_MAX;
        minHeap->array[i] = newMinHeapNode(i, dist[i]);
        minHeap->pos[i] = i;
    }
    
    // Make dist value of src vertex 
    // as 0 so that it is extracted first
    minHeap->array[src] = newMinHeapNode(src, dist[src]);
    minHeap->pos[src] = src;
    dist[src] = 0;
    decreaseKey(minHeap, src, dist[src]);
  
    // Initially size of min heap is equal to NumeroNodi
    minHeap->size = graph->NumeroNodi;
  
    // In the followin loop, 
    // min heap contains all nodes
    // whose shortest distance 
    // is not yet finalized.
    while (!HeapisEmpty(minHeap))
    {
        // Extract the vertex with 
        // minimum distance value
        NodoHeap minHeapNode = extractMin(minHeap);
        
        // Store the extracted vertex number
        int NodoInVisita = minHeapNode->v; 
  
        // Traverse through all adjacent 
        // vertices of u (the extracted
        // vertex) and update 
        // their distance values
        ArchiGrafo VisitatorePercorso = graph->ListaAdiacenza[NodoInVisita].head;
        while (VisitatorePercorso != NULL)
        {
            int i = VisitatorePercorso->key;
  
            // If shortest distance to v is
            // not finalized yet, and distance to v
            // through u is less than its 
            // previously calculated distance
            if (isInMinHeap(minHeap, i) && dist[NodoInVisita] != INT_MAX && VisitatorePercorso->distanza + dist[NodoInVisita] < dist[i])
            {
                parent[i] = NodoInVisita;
                dist[i] = dist[NodoInVisita] + VisitatorePercorso->distanza;
                cost[i] = cost[NodoInVisita] + VisitatorePercorso->costo;
                // update distance 
                // update cost
                // value in min heap also
                decreaseKey(minHeap, i, dist[i]);
            }
            VisitatorePercorso = VisitatorePercorso->next;
        }
    }
  
    // print the calculated shortest distances
    printArrFloat(cost, graph->NumeroNodi);
    printArr(dist, graph->NumeroNodi);
    printPath(parent,dest);
    return cost[dest];
}

/**
 * @brief The main function that calculates distances of shortest paths from src to all vertices. It is a O(ELogV) function
 * 
 * @param graph 
 * @param src: la key del nodo sorgente
 */
float dijkstraCosto(MappaCollegamenti graph, int src, int dest)
{     
    if (graph == NULL)
    {
        printf("Errore, Grafo vuoto.");
        return 0;
    }
    
    // Get the number of vertices in graph
    int V = graph->NumeroNodi;
    int i;
    // dist values used to pick
    // minimum weight edge in cut
    float cost[graph->NumeroNodi];     
  
    // minHeap represents set E
    HeapMinimoFloat minHeap = createMinHeapFloat(graph->NumeroNodi);
  
    // Initialize min heap with all 
    // vertices. dist value of all vertices 
    for (i = 0; i < graph->NumeroNodi; ++i)
    {
        cost[i] = INT_MAX;
        minHeap->array[i] = newMinHeapNode(i, cost[i]);
        minHeap->pos[i] = i;
    }
  
    // Make cost value of src vertex 
    // as 0 so that it is extracted first
    minHeap->array[src] = newMinHeapNode(src, cost[src]);
    minHeap->pos[src] = src;
    cost[src] = 0;
    decreaseKey(minHeap, src, cost[src]);
  
    // Initially size of min heap is equal to V
    minHeap->size = graph->NumeroNodi;
  
    // In the followin loop, 
    // min heap contains all nodes
    // whose shortest distance 
    // is not yet finalized.
    while (!HeapisEmpty(minHeap))
    {
        // Extract the vertex with 
        // minimum distance value
        NodoHeapFloat MinHeapNode = extractMinFloat(minHeap);
        
        // Store the extracted vertex number
        int u = MinHeapNode->v; 
  
        // Traverse through all adjacent 
        // vertices of u (the extracted
        // vertex) and update 
        // their distance values
        ArchiGrafo VisitatorePercorso = graph->ListaAdiacenza[u].head;
        while (VisitatorePercorso != NULL)
        {
            int v = VisitatorePercorso->key;
  
            // If shortest distance to v is
            // not finalized yet, and distance to v
            // through u is less than its 
            // previously calculated distance
            if (isInMinHeap(minHeap, v) && cost[u] != INT_MAX && VisitatorePercorso->costo + cost[u] < cost[v])
            {
                cost[v] = cost[u] + VisitatorePercorso->costo;
  
                // update distance 
                // value in min heap also
                decreaseKey(minHeap, v, cost[v]);
            }
            VisitatorePercorso = VisitatorePercorso->next;
        }
    }
  
    // print the calculated cheapest path
    printArrFloat(cost, graph->NumeroNodi);
    return cost[dest];
}

/**
 * @brief stampa il nome delle tappe raggiungibili. Fnziona se il grafo ha un cappio per ogni nodo
 * 
 * @param GrafoInput 
 */
void stamapVettoreAdiacenza(MappaCollegamenti GrafoInput){
    if (GrafoInput == NULL)
    {
        printf("Grafo vuoto. Impossibile completare l'operazione.\n");
        return;
    }
    int i;
    printf("Lista di possibili destinazioni: \n");
    for ( i = 0; i < GrafoInput->NumeroNodi; i++)
    {
        if (GrafoInput->ListaAdiacenza[i].visibilita!=0)
        {
            printf("%s \n", GrafoInput->ListaAdiacenza[i].NomeTappa);
        }    
    }
}

/**
 * @brief Get the Indice del nodo from Nome della tappa
 * 
 * @param GrafoInput 
 * @param NomeInput 
 * @return int 
 */
int get_Indice_from_Nome (MappaCollegamenti GrafoInput, char *NomeInput) {
    int ris;
    int i;
    strcpy(NomeInput,FormattazioneTappe(NomeInput));          

    if (getEmpty(GrafoInput))
    {
        printf("Grafo vuoto, impossibile completare l'operazione.");
        return -1;
    }

    for ( i = 0; i < GrafoInput->NumeroNodi; i++)
    {

        if (strcmp(GrafoInput->ListaAdiacenza[i].NomeTappa,NomeInput)==0)
        {
            ris = i;
        }
        
    }
    return ris;
}

/**
 * @brief Get the Nome della tappa from Indice del nodo
 * 
 * @param GrafoInput 
 * @param IndiceInput 
 * @return char* 
 */
char* get_Nome_from_Indice(MappaCollegamenti GrafoInput, int IndiceInput){
    char *ris=NULL;
    
    
    if (getEmpty(GrafoInput))
    {
        printf("Grafo vuoto, impossibile completare l'operazione.");
        return NULL;
    }

	ris=(char*)malloc(100*sizeof(char));
	if(ris!=NULL)
		strcpy(ris, GrafoInput->ListaAdiacenza[IndiceInput].NomeTappa);
    return ris;
}


/**
 * @brief funzione ausiliaria che dealloca liste di adiacenza del grafo
 * 
 * @param head 
 */
void deallocaListaAdiacenza(ArchiGrafo head)
{
	
	if (head != NULL) {
		deallocaListaAdiacenza(head->next);
		free(head);
	}
}

/**
 * @brief dealloca la struttura del grafo
 * 
 * @param GrafoInput 
 */
void deallocaGrafo(MappaCollegamenti GrafoInput){
    int i;
    for ( i = 0; i < GrafoInput->NumeroNodi; i++)
    {
        deallocaListaAdiacenza(GrafoInput->ListaAdiacenza[i].head);
    }
    free(GrafoInput->ListaAdiacenza);
    free(GrafoInput);
}
