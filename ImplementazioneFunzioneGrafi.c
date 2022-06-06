#include "StrutturaGrafi.h"
#include "StrutturaHeap.h"
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define bianco 0 
#define grigio 1 
#define nero 2 

/**
* @brief funzione per aggiornare il file checkAereo che comunica all'amministratore che il grafo degli aerei è sconnesso
*
* param GrafoInput
*/
void updateCheckAereo(MappaCollegamenti GrafoInput){
	FILE *fpOutCheck;
	int checkIsolatoAereo = 0, i;
	
	for(i=0; i<GrafoInput->NumeroNodi; i++){
		if( nodo_isolato(GrafoInput,i) == 1){
			checkIsolatoAereo = 1;
		}
	}

	fpOutCheck = fopen("CheckAereo.txt","w+");
	if (fpOutCheck==NULL) {
		printf("File Non trovato.\n");
		return;
	}
	fprintf(fpOutCheck,"%d\n",checkIsolatoAereo);
	fclose(fpOutCheck);
	return;
}



/**
* @brief funzione per aggiornare il file checkTreno che comunica all'amministratore che il grafo degli treni è sconnesso
*
* param GrafoInput
*/
void updateCheckTreno(MappaCollegamenti GrafoInput){
	FILE *fpOutCheck;
	int checkIsolatoTreno = 0, i;
	
	for(i=0; i<GrafoInput->NumeroNodi; i++){
		if( nodo_isolato(GrafoInput,i) == 1){
			checkIsolatoTreno = 1;
		}
	}

	fpOutCheck = fopen("CheckTreno.txt","w+");
	if (fpOutCheck==NULL) {
		printf("File Non trovato.\n");
		return;
	}
	fprintf(fpOutCheck,"%d\n",checkIsolatoTreno);
	fclose(fpOutCheck);
	return;
}

/**
 * @brief 
 * 
 * @param g 
 * @param nodo 
 * @return int 
 */
int nodo_isolato(MappaCollegamenti g, int nodo)
{
	if(g == NULL)
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
        printf("Grafo vuoto. Impossibile eseguire l'operazione.\n");
        return 1;
    }
    int i;
    int check = 0;
    char ris[MAX_STRINGHE];
    for ( i = 0; i < grafoInput->NumeroNodi; i++)
    {
        check = nodo_isolato(grafoInput,i);
        if (check == 1 && (grafoInput->ListaAdiacenza[i].visibilita) == 1)
        {
            strcpy(ris,get_Nome_from_Indice(grafoInput,i));
            printf("\nLa Tappa %s e' isolata.", ris);
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
    int i, NumeroNodi, visibilita;
    char NomeInput[100];
    MappaCollegamenti grafo;
    
    if ( fscanf(fp,"%d",&NumeroNodi) == 1)
    {
        grafo = crea_grafo_vuoto(NumeroNodi);
        for ( i = 0; i < NumeroNodi; i++)
        {
            if ( fscanf(fp,"%s %d",NomeInput, &visibilita) == 2)
            {
            	//segmentation fault                                               ***************************************************************
                nomina_nodo(grafo, i, NomeInput);
                grafo->ListaAdiacenza[i].visibilita = visibilita; 
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
    int sorgente, destinazione, distanza, visibility, n=1;
    float costo;
    ArchiGrafo p=NULL;
    //char Nome[MAX_STRINGHE];

    while (fscanf(fp, "%d %d %d %f %d", &sorgente, &destinazione, &distanza, &costo, &visibility) == 5)
    {
		p = GrafoInput->ListaAdiacenza[sorgente].head;
		n=1;
		//scorre in modo da non avere archi duplicati
		while(p != NULL){
			if(p->key == destinazione)
				n=0;
			p = p->next;
        }
        if (n==1)
			Aggiungi_Arco(GrafoInput,sorgente,destinazione,distanza,costo,visibility);
    }
    
    return GrafoInput;
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
                fprintf(fpArchi, "%d %d %d %.2f %d\n", i, edge->key, edge->distanza, edge->costo, edge->visibilita);

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

    int i,ris=0;
    for ( i = 0; i < GrafoInput->NumeroNodi; i++)
    {
    	if (GrafoInput->ListaAdiacenza[i].visibilita == 1)
    		ris++;
	}
	
    fprintf(fpNodi,"%d\n", ris);

    for ( i = 0; i < GrafoInput->NumeroNodi; i++)

    {
		if (GrafoInput->ListaAdiacenza[i].visibilita == 1)
	        fprintf(fpNodi,"%s %d\n", GrafoInput->ListaAdiacenza[i].NomeTappa, GrafoInput->ListaAdiacenza[i].visibilita);

    }

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
void printPath(int parent[], int j, MappaCollegamenti GrafoInput)
{
    // Base Case : If j is source
    if (parent[j] == -1)
    {
    	printf("%s -> ",get_Nome_from_Indice(GrafoInput,j));
    	return;
	}
    
	printPath(parent, parent[j], GrafoInput);
    
    printf("%s -> ", get_Nome_from_Indice(GrafoInput,j) );
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
		if(dist[i]==MAX_DIJKSTRA)
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
		if(cost[i]==MAX_DIJKSTRA)
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
void nomina_nodo(MappaCollegamenti GrafoInput, int NodoInput, char NomeInput[]){
    if (GrafoInput == NULL)
    {
        printf("Grafo Vuoto, impossibile completare l'operazione");
        return;
    }
    
    //segmentation fault
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
 * @brief rimuove un arco dal grafo
 * 
 * @param graph 
 * @param src 
 * @param dest 
 */
void Rimuovi_Arco(MappaCollegamenti graph, int src, int dest){
    if (graph == NULL)
    {
        printf("Impossibile completare l'operazione, grafo Vuoto.");
        return;
    }
    
    ArchiGrafo NodoTarget;
    NodoTarget = Ricerca_Vertice_In_Adj(graph->ListaAdiacenza[src].head, dest);
    graph->ListaAdiacenza[src].head = eliminaNodoListaAdj(graph->ListaAdiacenza[src].head, NodoTarget);
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
 * @brief restituisce 1 se il vertice di input appartiene all lista di adiacenza, 0 altrimenti, e NULL se la lista è vuota
 * 
 * @param ListaInput 
 * @param VerticeInput 
 * @return int 
 */
ArchiGrafo Ricerca_Vertice_In_Adj (ArchiGrafo ListaInput, int VerticeInput){
    if (ListaInput == NULL)
    {
        printf("Lista finita, risultato non trovato.");
        return NULL;
    }

    if (ListaInput->key == VerticeInput)
    {
        return ListaInput;
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
	
	if (head->key == nodo->key) {
		tmp = head->next;
		free(head);
		return tmp;
	}
	
	head->next = eliminaNodoListaAdj(head->next, nodo);
	
	return head;
}





 
/**
 * @brief The main function that calculates distances of shortest paths from src to all vertices. It is a O(ELogV) function
 * 
 * @param graph 
 * @param src: la key del nodo sorgente
 */
float dijkstraDistanza(MappaCollegamenti graph, int src, int destinazione)
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
    
    // minHeap represents set of Edges
    printf("inizio");
    HeapMinimo minHeap = createMinHeap(graph->NumeroNodi);
  
    // Initialize min heap with all vertices. dist value of all vertices, cost array and parent array
    for (i = 0; i < graph->NumeroNodi; ++i)
    {
        parent[i]=-1;
        cost[i] = 0;
        dist[i] = MAX_DIJKSTRA;
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
            if (isInMinHeap(minHeap, i) && dist[NodoInVisita] != MAX_DIJKSTRA && VisitatorePercorso->distanza + dist[NodoInVisita] < dist[i])
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
    //printArrFloat(cost, graph->NumeroNodi);
    //printArr(dist, graph->NumeroNodi);
    printf("\n");
	printPath(parent,destinazione,graph);
    printf("Arrivo \n");
    if(dist[destinazione] == MAX_DIJKSTRA){
		printf("Nodo non raggiungibile");
		return MAX_DIJKSTRA;
	}else
		printf("La scelta piu' veloce e' %d km\n", dist[destinazione]);
    
    return cost[destinazione];
}

/**
 * @brief The main function that calculates distances of shortest paths from src to all vertices. It is a O(ELogV) function
 * 
 * @param graph 
 * @param src: la key del nodo sorgente
 */
float dijkstraCosto(MappaCollegamenti graph, int src, int destinazione)
{     
    if (graph == NULL)
    {
        printf("Errore, Grafo vuoto.");
        return 0;
    }
    
    // Get the number of vertices in graph
    //int V = graph->NumeroNodi;
    int i;
    // dist values used to pick
    // minimum weight edge in cut
    int parent[graph->NumeroNodi];
    float cost[graph->NumeroNodi]; 
        
  
    // minHeap represents set E
    HeapMinimoFloat minHeap = createMinHeapFloat(graph->NumeroNodi);
  
    // Initialize min heap with all 
    // vertices. dist value of all vertices 
    for (i = 0; i < graph->NumeroNodi; ++i)
    {
        cost[i] = MAX_DIJKSTRA;
        parent[i] = -1;
        minHeap->array[i] = newMinHeapNodeFloat(i, cost[i]);
        minHeap->pos[i] = i;
    }
  
    // Make cost value of src vertex 
    // as 0 so that it is extracted first
    minHeap->array[src] = newMinHeapNodeFloat(src, cost[src]);
    minHeap->pos[src] = src;
    cost[src] = 0;
    decreaseKeyFloat(minHeap, src, cost[src]);
  
    // Initially size of min heap is equal to V
    minHeap->size = graph->NumeroNodi;
  
    // In the followin loop, 
    // min heap contains all nodes
    // whose shortest distance 
    // is not yet finalized.
    while (!HeapisEmptyFloat(minHeap))
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
            if (isInMinHeapFloat(minHeap, v) && cost[u] != MAX_DIJKSTRA && VisitatorePercorso->costo + cost[u] < cost[v])
            {
				parent[v] = u;
                cost[v] = cost[u] + VisitatorePercorso->costo;
  
                // update distance 
                // value in min heap also
                decreaseKeyFloat(minHeap, v, cost[v]);
            }
            VisitatorePercorso = VisitatorePercorso->next;
        }
    }
  
    // print the calculated cheapest path
    printArrFloat(cost, graph->NumeroNodi);
    printf("\n");
	printPath(parent, destinazione, graph);
    printf("Destinazione \n");
	if(cost[destinazione] == MAX_DIJKSTRA){
		printf("Nodo non raggiungibile");
		return MAX_DIJKSTRA;
	}else
		printf("La scelta piu' economica e' %.2f euro\n", cost[destinazione]);
    
    return cost[destinazione];
}

/**
 * @brief stampa il nome delle tappe raggiungibili. Fnziona se il grafo ha un cappio per ogni nodo
 * 
 * @param GrafoInput 
 */
void stamapVettoreAdiacenza(MappaCollegamenti GrafoInput, int inizio){
    if (GrafoInput == NULL)
    {
        printf("Grafo vuoto. Impossibile completare l'operazione.\n");
        return;
    }
    int i;
    printf("Lista di possibili destinazioni: \n");
    for ( i = inizio; i < GrafoInput->NumeroNodi; i++)
    {
        if (GrafoInput->ListaAdiacenza[i].visibilita==1)
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
    int ris = 0;
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

/**
 * @brief Load albergo giusto in memoria
 * 
 * @param Grafo 
 * @param TappaInput 
 * @return MappaCollegamenti 
 */
MappaCollegamenti LoadAlberghi(MappaCollegamenti Grafo, char *TappaInput){
    FILE *fpInAlberghiNodi,*fpInAlberghiArchi;
    char FileAlberghiNodi[MAX_STRINGHE],FileAlberghiArchi[MAX_STRINGHE];

    sprintf(FileAlberghiNodi, "%sAlberghiNodi.txt", TappaInput);
    sprintf(FileAlberghiArchi, "%sAlberghiArchi.txt", TappaInput);
    fpInAlberghiNodi = fopen(FileAlberghiNodi,"r");
    fpInAlberghiArchi = fopen (FileAlberghiArchi, "r");
    if(FileAlberghiNodi!=NULL && fpInAlberghiArchi!=NULL){
        Grafo = LetturaDaFILEGrafoNodi(fpInAlberghiNodi);
        Grafo = LetturaDaFILEGrafoCollegamenti(fpInAlberghiArchi,Grafo);
    }
    fclose(fpInAlberghiNodi);
    fclose(fpInAlberghiArchi);

    return Grafo;
}

/**
 * @brief salvataggio in FILE degli alberghi
 * 
 * @param Grafo 
 * @param TappaInput 
 */
void SaveAlberghi(MappaCollegamenti Grafo, char *TappaInput){
    FILE *fpOutAlberghiNodi,*fpOutAlberghiArchi;
    char FileAlberghiNodi[MAX_STRINGHE],FileAlberghiArchi[MAX_STRINGHE];
    
    sprintf(FileAlberghiNodi, "%sAlberghiNodi.txt", TappaInput);
    sprintf(FileAlberghiArchi, "%sAlberghiArchi.txt", TappaInput);
    fpOutAlberghiArchi= fopen (FileAlberghiArchi, "w+");
    fpOutAlberghiNodi = fopen(FileAlberghiNodi,"w+");

    CreazioneFILEGrafoNodi(fpOutAlberghiNodi,Grafo);
    CreazioneFILEGrafoArchi(fpOutAlberghiArchi,Grafo);
    fclose(fpOutAlberghiNodi);
    fclose(fpOutAlberghiArchi);
}
