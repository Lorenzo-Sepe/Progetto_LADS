#include "heap.h"
#include <stdlib.h>  
/**
 * @brief A utility function to create a new Min Heap Node
 * 
 * @param v 
 * @param dist 
 * @return NodoHeap 
 */
NodoHeap newMinHeapNode(int v, int dist)
{
    NodoHeap minHeapNode =
           (NodoHeap) 
      malloc(sizeof(struct MinHeapNode));
    minHeapNode->v = v;
    minHeapNode->dist = dist;
    return minHeapNode;
}
  
/**
 * @brief A utility function to create a Min Heap
 * 
 * @param capacity 
 * @return HeapMinimo 
 */
HeapMinimo createMinHeap(int capacity)
{
    HeapMinimo minHeap = (HeapMinimo) malloc(sizeof(struct MinHeap));
    minHeap->pos = (int *)malloc(capacity * sizeof(int));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (NodoHeap*) malloc(capacity * sizeof(NodoHeap));
    return minHeap;
}
  
/**
 * @brief  A utility function to swap two nodes of min heap. Needed for min heapify
 * 
 * @param a 
 * @param b 
 */
void swapMinHeapNode(NodoHeap* a, NodoHeap* b)
{
    NodoHeap t = *a;
    *a = *b;
    *b = t;
}
  
/**
 * @brief // A standard function to heapify at given idx This function also updates position of nodes when they are swapped. Position is needed for decreaseKey()
 * 
 * @param minHeap 
 * @param idx 
 */
void minHeapify(HeapMinimo minHeap, int idx)
{
    int smallest, left, right;
    smallest = idx;
    left = 2 * idx + 1;
    right = 2 * idx + 2;
  
    if (left < minHeap->size && minHeap->array[left]->dist < minHeap->array[smallest]->dist )
      smallest = left;
  
    if (right < minHeap->size && minHeap->array[right]->dist < minHeap->array[smallest]->dist )
      smallest = right;
  
    if (smallest != idx)
    {
        // The nodes to be swapped in min heap
        NodoHeap smallestNode = minHeap->array[smallest];
        NodoHeap idxNode = minHeap->array[idx];
  
        // Swap positions
        minHeap->pos[smallestNode->v] = idx;
        minHeap->pos[idxNode->v] = smallest;
  
        // Swap nodes
        swapMinHeapNode(&minHeap->array[smallest], 
                         &minHeap->array[idx]);
  
        minHeapify(minHeap, smallest);
    }
}
  
/**
 * @brief A utility function to check if the given minHeap is ampty or not
 * 
 * @param minHeap 
 * @return int 
 */
int HeapisEmpty(HeapMinimo minHeap)
{
    return minHeap->size == 0;
}
  
/**
 * @brief Standard function to extract minimum node from heap
 * 
 * @param minHeap 
 * @return NodoHeap 
 */
NodoHeap extractMin(HeapMinimo minHeap)
{
    if (HeapisEmpty(minHeap))
        return NULL;
  
    // Store the root node
    NodoHeap root = minHeap->array[0];
  
    // Replace root node with last node
    NodoHeap lastNode = 
         minHeap->array[minHeap->size - 1];
    minHeap->array[0] = lastNode;
  
    // Update position of last node
    minHeap->pos[root->v] = minHeap->size-1;
    minHeap->pos[lastNode->v] = 0;
  
    // Reduce heap size and heapify root
    --minHeap->size;
    minHeapify(minHeap, 0);
  
    return root;
}

/**

 * @brief Function to decreasy dist value of a given vertex v. This function uses pos[] of min heap to get the current index of node in min heap

 *

 * @param minHeap

 * @param v

 * @param dist

 */

void decreaseKey(HeapMinimo minHeap, int v, int dist)

{

    // Get the index of v in  heap array

    int i = minHeap->pos[v];

 

    // Get the node and update its dist value

    minHeap->array[i]->dist = dist;

 

    // Travel up while the complete

    // tree is not hepified.

    // This is a O(Logn) loop

    while (i && minHeap->array[i]->dist < minHeap->array[(i - 1) / 2]->dist)

    {

        // Swap this node with its parent

        minHeap->pos[minHeap->array[i]->v] =

                                      (i-1)/2;

        minHeap->pos[minHeap->array[

                             (i-1)/2]->v] = i;

        swapMinHeapNode(&minHeap->array[i],  

                 &minHeap->array[(i - 1) / 2]);

 

        // move to parent index

        i = (i - 1) / 2;

    }

}

/**

 * @brief // A utility function to check if a given vertex. '1' is in min heap or not

 *

 * @param minHeap

 * @param v

 * @return int

 */

int isInMinHeap(struct MinHeap *minHeap, int v)
{

   if (minHeap->pos[v] < minHeap->size)

     return 1;

   return 0;

}
