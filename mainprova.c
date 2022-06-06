#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "StrutturaHeap.h"
#include "StrutturaAlberoUtente.h"
#include "StrutturaGrafi.h"

int main(int argc, char *argv[])
{
    MappaCollegamenti t=NULL, a=NULL, citta=NULL, milano=NULL;
    FILE *fpnodi, *fptreni, *fpaerei, *milanoA, *milanoN;
    int n;
    //int i=-2;
    
    /*g=crea_grafo_vuoto(6);
    printf("%d\n", g->NumeroNodi);
    i=getEmpty(g);
    printf("%d\n", i);*/
    
	/*Aggiungi_Arco(g, 3, 4, "milano", 500, 50, 1); 
	Aggiungi_Arco(g, 3, 5, "naboli", 500, 50, 1); 
	Aggiungi_Arco(g, 2, 4, "roma", 500, 50, 1); 
	stampa_grafo(g);*/
	
	/*i=GradoUscita(g, 2);
	printf("%d usc\n", i);
	i=GradoIngresso(g, 2);
	printf("%d ing\n", i);
	printf("\n");
	i=GradoUscita(g, 3);
	printf("%d usc\n", i);
	i=GradoIngresso(g, 3);
	printf("\n");
	printf("%d ing\n", i);
	i=GradoUscita(g, 1);
	printf("%d usc\n", i);
	i=GradoIngresso(g, 1);
	printf("%d ing\n", i);
	printf("\n");
	
	i=lunghezzaListaAdj(g->ListaAdiacenza->head);
	printf("%d \n", i);
	i=lunghezzaListaAdj(g->ListaAdiacenza[2].head);
	printf("%d \n", i);
	i=lunghezzaListaAdj(g->ListaAdiacenza[4].head);
	printf("%d \n", i);
	

	nomina_nodo(g, 0, "genova");
	nomina_nodo(g, 1, "pal");
	nomina_nodo(g, 2, "roma");
	nomina_nodo(g, 3, "milano");
	nomina_nodo(g, 4, "napoli");
	nomina_nodo(g, 5, "torino");
	stamapVettoreAdiacenza(g);

	g=g_insert(g, "venezia");
	printf("\nCon aggiunta\n");
	stamapVettoreAdiacenza(g);
	
	g=EliminazioneLogicaNodo(g, 5);
	stampa_grafo(g);
	stamapVettoreAdiacenza(g);*/
	
	fpnodi=fopen("MappaTappe.txt", "r");
	fptreni=fopen("Trenidisponibili.txt", "r");
	//fpaerei=fopen("VoliDisponibili.txt", "r");
	
	t=LetturaDaFILEGrafoNodi(fpnodi);
	t=LetturaDaFILEGrafoCollegamenti(fptreni, t);


	fclose(fpnodi);
	/*fpnodi=fopen("MappaTappe.txt", "r");
	t=LetturaDaFILEGrafoCollegamenti(fptreni);
	
	fclose(fpnodi);
	fpnodi=fopen("MappaTappe.txt", "r");
	a=LetturaDaFILEGrafo(fpnodi, fpaerei, a);
	
	fclose(fpnodi);
	fclose(fpaerei);*/
	fclose(fptreni);

	stamapVettoreAdiacenza(t);
	/*printf("\nTRENI:");
	stamapVettoreAdiacenza(t);
	printf("\nAEREI:");
	stamapVettoreAdiacenza(a);*/
	/*printf("\nTRENI:");
	stampa_grafo(t);
	printf("\nAEREI:");
	stampa_grafo(a);
	milanoN=fopen("MilanoAlberghiNodi.txt", "r");
	milanoA=fopen("MilanoAlberghiArchi.txt", "r");
	milano=LetturaDaFILEGrafo(milanoN, milanoA, milano);
	
	printf("\n\nAlberghi milano");
	stampa_grafo(milano);
	printf("\n\n");
	
	citta=g_insert(citta, "torino");
	a=g_insert(a, "torino");
	t=g_insert(t, "torino");
	Aggiungi_Arco(t, 4, 2, 250, 30, 1);
	printf("\nCon aggiunta\n");
	stamapVettoreAdiacenza(citta);printf("\n");
	stampa_grafo(t);printf("\n");
	stampa_grafo(a);*/
	//stampa_grafo(citta);
	
	/*printf("treno\ndist:\n");
	dijkstraDistanza(t, 0, 3);
	printf("\ncosto:\n");
	dijkstraCosto(t, 0);
	
	printf("aereo\ndist:\n");
	dijkstraDistanza(a, 0, 3);
	printf("\ncosto:\n");
	dijkstraCosto(a, 0);
	
	n=nodo_isolato(a,3);
	if(n==1)
		printf("\nIl nodo 3 è isolato");
	else
		printf("\nIl nodo 3 non e' isolato");

	n=nodo_isolato(a,4);
	if(n==1)
		printf("\nIl nodo 4 è isolato");
	else
		printf("\nIl nodo 4 non e' isolato");
	
	fpnodi=fopen("MappaTappe.txt", "w");
	fptreni=fopen("TreniDisponibili.txt", "w");
	fpaerei=fopen("VoliDisponibili.txt", "w");
	CreazioneFILEGrafoArchi(fptreni, t);
	CreazioneFILEGrafoArchi(fpaerei, a);
	CreazioneFILEGrafoNodi(fpnodi, citta);
	fclose(fpnodi);
	fclose(fptreni);
	fclose(fpaerei);*/

	
	
//okk 		MappaCollegamenti crea_grafo_vuoto(int NumeroNodiInput); //possibilmente 6
//okk		void nomina_nodo(MappaCollegamenti GrafoInput,int NodoInput, char *NomeInput);
//okk  	 	int getEmpty(MappaCollegamenti Grafo);
//okk		void stampa_grafo(MappaCollegamenti GrafoInput);
//okk		aggiunge entrambi	void Aggiungi_Arco(MappaCollegamenti graph, int src, int dest, char *NomeInput, int distanza, float costo, int visibilitaInput); //non orientato   
//okk		ArchiGrafo createNode(int v);
//okk		int GradoUscita (MappaCollegamenti GrafoInput, int VerticeInput);
//okk		int GradoIngresso(MappaCollegamenti GrafoInput, int VerticeInput);
//okk		int Ricerca_Vertice_In_Adj (ArchiGrafo ListaInput, int VerticeInput);
//okk		int lunghezzaListaAdj(ArchiGrafo head);
//okk		void stamapVettoreAdiacenza(MappaCollegamenti GrafoInput);
//okk		MappaCollegamenti g_insert(MappaCollegamenti GrafoInput, char* NomeInput);
//okk		MappaCollegamenti EliminazioneLogicaNodo(MappaCollegamenti GrafoInput, int NodoInput);
//okk		void dijkstraDistanza(MappaCollegamenti graph, int src);
//okk		void dijkstraCosto(MappaCollegamenti graph, int src);
//okk		int nodo_isolato(MappaCollegamenti g, int nodo);


//simile    int VerificaGrafoConnesso(MappaCollegamenti GrafoInput);      
//void DepthFirstSearch(MappaCollegamenti GrafoInput);
//void DFS_Visita(MappaCollegamenti GrafoInput, int i, int *VettoreFlag);
//MappaCollegamenti aggiungiAListaDiAdiacenza(MappaCollegamenti GrafoInput, int i, int keyInput,char* NomeInput, int distanzaInput,float costoInput,int visibilitaInput);

    
    return 0;    
}

