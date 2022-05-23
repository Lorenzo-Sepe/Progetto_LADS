#include "StrutturaGrafi.h"
#include "StrutturaHeap.h"
#include <stdlib.h>
#define INT_MAX 9999
#define bianco 0 
#define grigio 1 
#define nero 2 

/**
 * @brief verifica se un grafo è vuoto
 * 
 * @param Grafo 
 * @return int 
 */
int getEmpty(MappaCollegamenti Grafo){
    return (Grafo==NULL);
}

/**
 * @brief crea un grafo di dato numoro nodi senza archi
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
        Grafo->ListaAdiacenza=(ArchiGrafo)calloc(NumeroNodiInput,sizeof(struct Tappa));
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
               Grafo->ListaAdiacenza[i] = NULL;
            }

            return Grafo;
        }
    }
}

/**
 * @brief aggiunge un nuovo nodo al grafo e aggiorna il vettore di liste
 * 
 * @param GrafoInput 
 * @return MappaCollegamenti 
 */
MappaCollegamenti g_insert(MappaCollegamenti GrafoInput) {
ArchiGrafo *NuovaLista;
if (GrafoInput == NULL) return printf("Grafo vuoto.") ;

NuovaLista = realloc(GrafoInput->ListaAdiacenza, (GrafoInput->NumeroNodi+1) * sizeof(ArchiGrafo));

if (NuovaLista ==NULL)  
    printf("ERRORE: impossibile reallocare memoria \n");
else
{     
GrafoInput->ListaAdiacenza=NuovaLista;
GrafoInput->ListaAdiacenza[GrafoInput->NumeroNodi]=NULL;
GrafoInput->NumeroNodi = GrafoInput->NumeroNodi+1;
}

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
        if (GrafoInput->ListaAdiacenza[i]->key == NodoInput)
        {
            GrafoInput->ListaAdiacenza[i]->visibilità=0;
        }
    }
    free(GrafoInput->ListaAdiacenza[NodoInput]);
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
        printf("Il Grafo ha %d vertici\n", GrafoInput->NumeroNodi);
        for ( i = 0; i < GrafoInput->NumeroNodi; i++)
        {
            printf("Nodi adiacenti al nodo %d->",i);
            edge=GrafoInput->ListaAdiacenza[i];
            while (edge!=NULL)
            {
                printf("%d-> ",edge->key);
                edge=edge->next;
            }
            printf("NULL\n");
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
    for (edge = GrafoInput->ListaAdiacenza[i]; edge ; edge=edge->next)
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

void Aggiungi_Arco(MappaCollegamenti graph, int src, int dest, int distanza, float costo) {
  // Add edge from src to dest
  struct Tappa* newNode = createNode(dest);
  newNode->next = graph->ListaAdiacenza[src];
  newNode->costo=costo;
  newNode->distanza=distanza;
  graph->ListaAdiacenza[src] = newNode;

  // Add edge from dest to src
  newNode = createNode(src);
  newNode->costo=costo;
  newNode->distanza=distanza;
  newNode->next = graph->ListaAdiacenza[dest];
  graph->ListaAdiacenza[dest] = newNode;
}

/**
 * @brief Add edge to the graph oriented from src to dest
 * 
 * @param graph 
 * @param src 
 * @param dest 
 * @param distanza
 */

void Aggiungi_Arco_Orientato(MappaCollegamenti graph, int src, int dest, int distanza, float costo) {
  // Add edge from src to dest
  struct Tappa* newNode = createNode(dest);
  newNode->next = graph->ListaAdiacenza[src];
  newNode->distanza = distanza;
  newNode->costo=costo;
  graph->ListaAdiacenza[src] = newNode;
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
	return 1 + lunghezzaLista(head->next);
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
        return NULL;
    }
    else{
        int ris;
        ris = lunghezzaListaAdj(GrafoInput->ListaAdiacenza[VerticeInput]);
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
        return NULL;
    }
    else{
        if (VerticeInput == NULL) return 0;
        else{
            for (i = 0; i < GrafoInput->NumeroNodi; i++)
            {
                ris = ris + Ricerca_Vertice_In_Adj(GrafoInput->ListaAdiacenza[i],VerticeInput);
            }
            return ris;    
        }
    }   
}

/**
 * @brief crea il grafo trasposto dell
 * 
 * @param GrafoInput deve essere orientato
 * @return MappaCollegamenti 
 */
MappaCollegamenti CreaGrafoTrasposto (MappaCollegamenti GrafoInput)
{
    if (GrafoInput == NULL)
    {
        printf ("Grafo inserito e' vuoto");
        return NULL;
    }
    else
    {
        MappaCollegamenti newGrafo;
        int i;
        newGrafo = (MappaCollegamenti)malloc(sizeof (struct GrafoCollegamenti) );
        if (newGrafo == NULL)
        {
            printf("Errore, impossibile allocare momoria.");
        }
        else
        {
            newGrafo->ListaAdiacenza = (ArchiGrafo)calloc(GrafoInput->NumeroNodi,sizeof(struct Tappa));
            if (newGrafo->ListaAdiacenza==NULL)
            {
                printf("Errore, impossibile allocare memoria.");
                free(newGrafo);
            }
            else
            {
                newGrafo->NumeroNodi=GrafoInput->NumeroNodi;
                for ( i = 0; i < newGrafo->NumeroNodi; i++)
                {
                    while (GrafoInput->ListaAdiacenza[i] != NULL)
                    {
                        //add edge
                        Aggiungi_Arco_Orientato(newGrafo,GrafoInput->ListaAdiacenza[i]->key,i,GrafoInput->ListaAdiacenza[i]->distanza,GrafoInput->ListaAdiacenza[i]->costo);
                    }
               
                }
                return newGrafo;
            }
        }
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
    for (edge = GrafoInput->ListaAdiacenza[i]; edge ; edge=edge->next)
    {
        if (VettoreFlag[edge->key]==bianco)
        {
            VettorePred[edge->key]=GrafoInput->ListaAdiacenza[i]; 
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
        ArchiGrafo *VettorePred=malloc(GrafoInput->NumeroNodi*sizeof(struct Tappa));
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
 * @brief verifica se un array di nodi di input è contenuto in un secodo array di nodi
 * 
 * @param ArchiGrafoInput 
 * @param ArchiGrafoPadre 
 * @param MaxNodi 
 * @return int ritorna 0 se non è sottoinsieme di nodi del padre
 */
static int VerificaNodiSottografo(ArchiGrafo* ArchiGrafoInput, ArchiGrafo* ArchiGrafoPadre,int MaxNodi, int NodiPadre){
    if (ArchiGrafoInput == NULL || ArchiGrafoPadre == NULL)
    {
        printf("Uno o entrambi i grafi non hanno nodi.");
        return 0;
    }
    else
    {
        int i = 0;
        int ris = 1;
        for ( i = 0; i < MaxNodi; i++)
        {
            int j = 0;
            while( ris == 1 || j < NodiPadre)
            {
                if (ArchiGrafoInput[i] != ArchiGrafoPadre[j]){
                       ris = 0; 
                }
                j++;
            }
        }
        
        return ris;
    }
}

/**
 * @brief verifica se un arco del grafo Input esiste anche nel ggrafo padre 
 * 
 * @param ArchiGrafoInput 
 * @param ArchiGrafoPadre 
 * @param MaxNodi 
 * @return int 
 */
static int VerificaArchiSottografo(ArchiGrafo* ArchiGrafoInput, ArchiGrafo* ArchiGrafoPadre, int MaxNodi){
    if (ArchiGrafoInput == NULL || ArchiGrafoPadre == NULL)
    {
        printf("Uno o entrambi i grafi non hanno nodi.");
        return 0;
    }
    else
    {
        int i;
        int ris = 1;
        for ( i = 0; i < MaxNodi; i++ )
        {
            if (Ricerca_Vertice_In_Adj(ArchiGrafoInput,ArchiGrafoInput[i]) != Ricerca_Vertice_In_Adj(ArchiGrafoPadre,ArchiGrafoPadre[i]) ) {
                ris = 0;
                }
            
        }

        return ris;
    }
}

/**
 * @brief verifica che il grafo in input sia sottografo del grafo qua chiamato come grafo padre. 1 = Input è sottografo di Padre, 0 altrimenti
 * 
 * @param GrafoInput 
 * @param GrafoPadre 
 * @return int 
 */
int VerificaSottografo (MappaCollegamenti GrafoInput, MappaCollegamenti GrafoPadre){
    int nodi,archi;
    if (GrafoInput == NULL || GrafoPadre == NULL )
    {
        printf("Uno o entrambi i grafi sono vuoti.");
        return 0;
    }
    else
    {
        if(GrafoInput->NumeroNodi > GrafoPadre->NumeroNodi){
            printf("Numero di nodi del grafo in ingresso e' maggiore del numero di nodi del grafo padre.");
            return 0;
        }
        else
        {
            nodi = VerificaNodiSottografo(GrafoInput->ListaAdiacenza,GrafoPadre->ListaAdiacenza,GrafoInput->NumeroNodi,GrafoPadre->NumeroNodi);
            archi = VerificaArchiSottografo(GrafoInput->ListaAdiacenza,GrafoPadre->ListaAdiacenza,GrafoInput->NumeroNodi);
            return (nodi*archi);
        }
    }
}

 
/**
 * @brief The main function that calculates distances of shortest paths from src to all vertices. It is a O(ELogV) function
 * 
 * @param graph 
 * @param src: la key del nodo sorgente
 */
void dijkstraDistanza(MappaCollegamenti graph, int src)
{     
    if (graph == NULL)
    {
        printf("Errore, Grafo vuoto.");
        return;
    }
    
    // Get the number of vertices in graph
    int V = graph->NumeroNodi;
    int v;
    // dist values used to pick
    // minimum weight edge in cut
    int dist[V];     
  
    // minHeap represents set E
    HeapMinimo minHeap = createMinHeap(V);
  
    // Initialize min heap with all 
    // vertices. dist value of all vertices 
    for (v = 0; v < V; ++v)
    {
        dist[v] = INT_MAX;
        minHeap->array[v] = newMinHeapNode(v, dist[v]);
        minHeap->pos[v] = v;
    }
  
    // Make dist value of src vertex 
    // as 0 so that it is extracted first
    minHeap->array[src] = newMinHeapNode(src, dist[src]);
    minHeap->pos[src] = src;
    dist[src] = 0;
    decreaseKey(minHeap, src, dist[src]);
  
    // Initially size of min heap is equal to V
    minHeap->size = V;
  
    // In the followin loop, 
    // min heap contains all nodes
    // whose shortest distance 
    // is not yet finalized.
    while (!isEmpty(minHeap))
    {
        // Extract the vertex with 
        // minimum distance value
        NodoHeap minHeapNode = extractMin(minHeap);
        
        // Store the extracted vertex number
        int u = minHeapNode->v; 
  
        // Traverse through all adjacent 
        // vertices of u (the extracted
        // vertex) and update 
        // their distance values
        ArchiGrafo pCrawl = graph->ListaAdiacenza[u];
        while (pCrawl != NULL)
        {
            int v = pCrawl->key;
  
            // If shortest distance to v is
            // not finalized yet, and distance to v
            // through u is less than its 
            // previously calculated distance
            if (isInMinHeap(minHeap, v) && dist[u] != INT_MAX && pCrawl->distanza + dist[u] < dist[v])
            {
                dist[v] = dist[u] + pCrawl->distanza;
  
                // update distance 
                // value in min heap also
                decreaseKey(minHeap, v, dist[v]);
            }
            pCrawl = pCrawl->next;
        }
    }
  
    // print the calculated shortest distances
    printArr(dist, V);
}

/**
 * @brief The main function that calculates distances of shortest paths from src to all vertices. It is a O(ELogV) function
 * 
 * @param graph 
 * @param src: la key del nodo sorgente
 */
void dijkstraDistanza(MappaCollegamenti graph, int src)
{     
    if (graph == NULL)
    {
        printf("Errore, Grafo vuoto.");
        return;
    }
    
    // Get the number of vertices in graph
    int V = graph->NumeroNodi;
    int v;
    // dist values used to pick
    // minimum weight edge in cut
    int dist[V];     
  
    // minHeap represents set E
    HeapMinimo minHeap = createMinHeap(V);
  
    // Initialize min heap with all 
    // vertices. dist value of all vertices 
    for (v = 0; v < V; ++v)
    {
        dist[v] = INT_MAX;
        minHeap->array[v] = newMinHeapNode(v, dist[v]);
        minHeap->pos[v] = v;
    }
  
    // Make dist value of src vertex 
    // as 0 so that it is extracted first
    minHeap->array[src] = newMinHeapNode(src, dist[src]);
    minHeap->pos[src] = src;
    dist[src] = 0;
    decreaseKey(minHeap, src, dist[src]);
  
    // Initially size of min heap is equal to V
    minHeap->size = V;
  
    // In the followin loop, 
    // min heap contains all nodes
    // whose shortest distance 
    // is not yet finalized.
    while (!isEmpty(minHeap))
    {
        // Extract the vertex with 
        // minimum distance value
        NodoHeap minHeapNode = extractMin(minHeap);
        
        // Store the extracted vertex number
        int u = minHeapNode->v; 
  
        // Traverse through all adjacent 
        // vertices of u (the extracted
        // vertex) and update 
        // their distance values
        ArchiGrafo pCrawl = graph->ListaAdiacenza[u];
        while (pCrawl != NULL)
        {
            int v = pCrawl->key;
  
            // If shortest distance to v is
            // not finalized yet, and distance to v
            // through u is less than its 
            // previously calculated distance
            if (isInMinHeap(minHeap, v) && dist[u] != INT_MAX && pCrawl->distanza + dist[u] < dist[v])
            {
                dist[v] = dist[u] + pCrawl->distanza;
  
                // update distance 
                // value in min heap also
                decreaseKey(minHeap, v, dist[v]);
            }
            pCrawl = pCrawl->next;
        }
    }
  
    // print the calculated shortest distances
    printArr(dist, V);
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
    for ( i = 0; i < GrafoInput->NumeroNodi; i++)
    printf("Lista di possibili destinazioni: \n");
    {
        if (GrafoInput->ListaAdiacenza[i]->visibilità==1)
        {
            printf("\s \n", GrafoInput->ListaAdiacenza[i]->NomeTappa);
        }    
    }
    return;
}

/**
 * @brief 
 * 
 *
MappaCollegamenti LetturaDaFILEGrafo (FILE *fp, MappaCollegamenti GrafoInput){
    char buffer[MAX_STRINGHE];
    char bufferCategoria[MAX_STRINGHE/6];
    char bufferGenere[MAX_STRINGHE/6];
    char bufferAbito[MAX_STRINGHE/6];
    char bufferMarca[MAX_STRINGHE/6];
    char bufferPrezzo[MAX_STRINGHE/6];
    char bufferTaglie[MAX_STRINGHE/6];
    char *bufferTemp;
    int start = 0;
    int end = 0;

    // sono estrate dal file le informazioni di tutti gli abiti
        while(fgets(buffer, DIMBUFF, fp)) {
            start = 0;
            end = 0;
            // estrazione categoria
            for(; buffer[end]!=';'; end++);
            bufferTemp = substr(buffer, start, end);
            strcpy(bufferCategoria, bufferTemp);
            free(bufferTemp);
            end = end + 2;
            start = end;
            // estrazione genere
            for(; buffer[end]!=';'; end++);
            bufferTemp = substr(buffer, start, end);
            strcpy(bufferGenere, bufferTemp);
            free(bufferTemp);
            end = end + 2;
            start = end;
            // estrazione nome abito
            for(; buffer[end]!=';'; end++);
            bufferTemp = substr(buffer, start, end);
            strcpy(bufferAbito, bufferTemp);
            free(bufferTemp);
            end = end + 2;
            start = end;
            // estrazione marca abito
            for(; buffer[end]!=';'; end++);
            bufferTemp = substr(buffer, start, end);
            strcpy(bufferMarca, bufferTemp);
            free(bufferTemp);
            end = end + 2;
            start = end;
            // estrazione prezzo (stringa più in avanti convertita in float con la funzione "atof")
            for(; buffer[end]!=';'; end++);
            bufferTemp = substr(buffer, start, end);
            strcpy(bufferPrezzo, bufferTemp);
            free(bufferTemp);
            end = end + 2;
            start = end;
            // estrazione taglie (stringa di zero o più singole taglie, estratte in seguito dalla funzione "aggiungiAbito")            
            for(; buffer[end]!='<'; end++);
            bufferTemp = substr(buffer, start, end);
            strcpy(bufferTaglie, bufferTemp);
            free(bufferTemp);
            //creazione della macro struttura di liste di categorie, i cui nodi contengono alberi di abiti, i cui nodi contengono liste di taglie
            headCategoria = aggiungiAbito(headCategoria, bufferCategoria, bufferGenere, bufferAbito, bufferMarca, atof(bufferPrezzo), bufferTaglie);
        }
}
*/