 #if !defined(Heap_H)
 #define Heap_H
 
// Structure to represent a min heap node for integers
struct MinHeapNode
{
    int  v;
    int dist;
};

// Structure to represent a min heap node for float

struct MinHeapNodeFloat

{
    int  v;
    float cost;
};
  
typedef struct MinHeapNodeFloat* NodoHeapFloat;
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
 
typedef struct MinHeapFloat* HeapFloat;
typedef struct MinHeap* HeapMinimo;

//versione int
NodoHeap newMinHeapNode(int v, int dist);
HeapMinimo createMinHeap(int capacity);
void swapMinHeapNode(NodoHeap* a, NodoHeap* b);
void minHeapify(HeapMinimo minHeap, int idx);
int HeapisEmpty(HeapMinimo minHeap);
NodoHeap extractMin(HeapMinimo minHeap);
void decreaseKey(struct MinHeap* minHeap, int v, int dist);
int isInMinHeap(struct MinHeap *minHeap, int v);

//versione float
NodoHeapFloat newMinHeapNodeFloat(int v, float cost);
HeapFloat createMinHeapFloat(int capacity);
void swapMinHeapNodeFloat(NodoHeapFloat* a, NodoHeapFloat* b)
void minHeapify(HeapFloat minHeap, int idx);
int HeapisEmpty(HeapFloat minHeap);
NodoHeapFloat extractMin(HeapFloat minHeap);
void decreaseKeyFloat(struct MinHeapFloat* minHeap, int v, float cost);
int isInMinHeap(struct MinHeapFloat *minHeap, int v);

//sono uguali cambia solo il tipo di dati che trattano
#endif 
  
