 #ifndef Heap_H
 #define Heap_H
 #include <stdlib.h>
 #include <stdio.h>
 
// Structure to represent a min heap node
struct MinHeapNode
{
    int  v;
    int dist;
};
  
typedef struct MinHeapNode* NodoHeap;  

// Structure to represent a min heap with an array
struct MinHeap
{
    // Number of heap nodes present currently
    int size;     
    
    // Capacity of min heap
    int capacity;  
    
    // This is needed for decreaseKey()
    int *pos;    
    NodoHeap *array;
};
 
typedef struct MinHeap* HeapMinimo;

NodoHeap newMinHeapNode(int v, int dist);
HeapMinimo createMinHeap(int capacity);
void swapMinHeapNode(NodoHeap* a, NodoHeap* b);
void minHeapify(HeapMinimo minHeap, int idx);
int HeapisEmpty(HeapMinimo minHeap);
NodoHeap extractMin(HeapMinimo minHeap);
void decreaseKey(HeapMinimo minHeap, int v, int dist);
int isInMinHeap(HeapMinimo minHeap, int v);

// Structure to represent a min heap node using float type
struct MinHeapNodeFloat
{
    int  v;
    float cost;
};
  
typedef struct MinHeapNodeFloat* NodoHeapFloat;

// Structure to represent a min heap with an array
struct MinHeapFloat
{
    // Number of heap nodes present currently
    int size;     
    
    // Capacity of min heap
    int capacity;  
    
    // This is needed for decreaseKey()
    int *pos;    
    NodoHeapFloat *array;
};
 
typedef struct MinHeapFloat* HeapMinimoFloat;

NodoHeapFloat newMinHeapNodeFloat(int v, float cost);
HeapMinimoFloat createMinHeapFloat(int capacity);
void swapMinHeapNodeFloat(NodoHeapFloat* a, NodoHeapFloat* b);
void minHeapifyFloat(HeapMinimoFloat minHeap, int idx);
int HeapisEmptyFloat(HeapMinimoFloat minHeap);
NodoHeapFloat extractMinFloat(HeapMinimoFloat minHeap);
void decreaseKeyFloat(HeapMinimoFloat minHeap, int v, float cost);
int isInMinHeapFloat(HeapMinimoFloat minHeap, int v);

#endif
  
