 #if !defined(Heap_H)
 #define Heap_H
 
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
void decreaseKey(struct MinHeap* minHeap, int v, int dist);
int isInMinHeap(struct MinHeap *minHeap, int v);

#endif // MACRO
  
