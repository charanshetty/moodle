#include <stdio.h>
#include "shortestPath.h"
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#define n 1000
#define p 100
#define o 10
#define k 100
#define w 5

// A structure to represent a node in adjacency list
struct AdjListNode
{
    int dest;
    int weight;
    struct AdjListNode* next;
};

// A structure to represent an adjacency list
struct AdjList
{
    struct AdjListNode *head;  // pointer to head node of list
};

// A structure to represent a graph. A graph is an array of adjacency lists.
// Size of array will be V (number of vertices in graph)
struct Graph
{
    int V;
    struct AdjList* array;
};


// Structure to represent a min heap node
struct MinHeapNode
{
    int  v;
    int dist;
};

// Structure to represent a min heap
struct MinHeap
{
    int size;      // Number of heap nodes present currently
    int capacity;  // Capacity of min heap
    int *pos;     // This is needed for decreaseKey()
    struct MinHeapNode **array;
};

struct Request
{
	int reqnumber;
	int source;
	int destn;
	int begin_interval;
	int end_interval;
	int reqstatus ;
};
struct Request requests[n];
struct Cab
{
	int cabnumber;
	int cabSource;
	int cabDestn;
	int Cabcapacity;
	int revenue;
	int cabtime;
};
struct Cab cab[o];

int SetCab(int y,int i)
{
	cab[i].cabnumber=i;
	cab[i].cabSource=y;
	cab[i].revenue=0;
	return 0;
}
// A utility fu        addEdge(graph, 0, 1, 7);nction to create a new adjacency list node
struct AdjListNode* newAdjListNode(int dest, int weight)
{
    struct AdjListNode* newNode =
            (struct AdjListNode*) malloc(sizeof(struct AdjListNode));
    newNode->dest = dest;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

// A utility function that creates a graph of V vertices
struct Graph* createGraph(int V)
{
    struct Graph* graph = (struct Graph*) malloc(sizeof(struct Graph));
    graph->V = V;

    // Create an array of adjacency lists.  Size of array will be V
    graph->array = (struct AdjList*) malloc(V * sizeof(struct AdjList));
int i;
     // Initialize each adjacency list as empty by making head as NULL
    for (i = 0; i < V; ++i)
        graph->array[i].head = NULL;

    return graph;
}

// Adds an edge to an undirected graph
void addEdge(struct Graph* graph, int src, int dest, int weight)
{
    // Add an edge from src to dest.  A new node is added to the adjacency
    // list of src.  The node is added at the begining
    struct AdjListNode* newNode = newAdjListNode(dest, weight);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;

    // Since graph is undirected, add an edge from dest to src also
//    newNode = newAdjListNode(src, weight);
//    newNode->next = graph->array[dest].head;
//    graph->array[dest].head = newNode;
}

void AddReq(int source,int destn,int begin_interval,int end_interval,int requestno)
{

	requests[requestno].reqnumber=requestno;
	requests[requestno].source=source;
	requests[requestno].destn=destn;
	requests[requestno].begin_interval=begin_interval;
	requests[requestno].end_interval=end_interval;
}
void sortReq(int first,int last){
  int pivot,j,i,m;
struct Request temp;
     if(first<last){
         pivot=first;
         i=first;
         j=last;

         while(i<j){
             while(requests[i].begin_interval<=requests[pivot].begin_interval&&i<last)
                 i++;
             while(requests[j].begin_interval>requests[pivot].begin_interval)
                 j--;
             if(i<j){
                 temp=requests[i];
                  requests[i]=requests[j];
                  requests[j]=temp;
}
         }

         temp=requests[pivot];
         requests[pivot]=requests[j];
         requests[j]=temp;

         sortReq(first,j-1);
         sortReq(j+1,last);

    }
}

//given the location and the sorted reqs

//4 reqs take req one by one for its source and calculate revenue
//for taxi driver based on shortest distance
//check if there are any req from same source in the same interval
void findTaxi(int** loc,int** cploc,int** input, int rows, int cols,int* count,int reqs,int capacity,int cabs){
	int i,min2=1000,node=0,node1=0,x=1,y=1,distan=0,distan2=0,r=1,l=1,stat=0,stat1=0,flag1=0,pos=0,firstreq=1;
	int cap[w];
	for(l=0;l<cabs;l++){
		for(i=0;i<capacity;i++)
			cap[i]=0;
		distan=0;
		for(i=0;i<capacity;i++){
		for(y=1;y<=reqs;y++){
if(cab[l].cabtime==0)
		{for(firstreq=1;firstreq<=reqs;firstreq++){
	if(requests[firstreq].reqstatus!=1)
{
	if(2*loc[cab[l].cabSource-1][requests[firstreq].source-1]<=requests[firstreq].end_interval)
	{cab[l].cabSource=requests[firstreq].source;
	cab[l].cabDestn=requests[firstreq].destn;
	cab[l].cabtime=2*loc[cab[l].cabSource-1][requests[firstreq].source-1];
	stat =1;
		y=firstreq;
		break;}
	}
}}
if((stat==1)||((cab[l].cabDestn==requests[y].source)&&(requests[y].reqstatus!=1)&&((requests[y].end_interval-cab[l].cabtime)<50)&&((requests[y].end_interval-cab[l].cabtime)>=0)&&(cab[l].Cabcapacity<capacity)))
{
	for(r=0;r<capacity;r++)//if my new node is a destn of any passenger
	{
		if((cab[l].cabDestn==cap[r])&&(cab[l].cabDestn!=0)){
		cap[r]=0;

		cab[l].Cabcapacity--;
		}	}
	for(r=0;r<capacity;r++){////if my new node there is a passenger pick him up
		if((cap[r]==0))
		{cab[l].Cabcapacity++;

			cap[r]=requests[y].destn;
		break;}
	}

//updating cab time
	if(cab[l].cabtime<requests[y].begin_interval)//cab have to wait at a node
		{cab[l].cabtime=requests[y].begin_interval;}
//finding revenue
	distan=loc[requests[y].source-1][requests[y].destn-1];  // to calculate revenue
	cab[l].revenue=cab[l].revenue+distan;//set revenue
	requests[y].reqstatus=1;//request is now taken
	if(cab[l].Cabcapacity<capacity){
	for(r=0;r<w;r++)// to find my next node to go as per passengers destn
	{
		if(((cap[r]!=0)&&(cab[l].cabDestn!=0)&&(cap[r]!=cab[l].cabDestn)))
		{
			if(min2>loc[cap[r]-1][cab[l].cabDestn-1]){
				min2=loc[cap[r]-1][cab[l].cabDestn-1];
			pos=cap[r];}
		}
		else   //if not pick the req destn
		pos=requests[y].destn;
	}
if((cab[l].cabDestn!=0))  //only if i can pick one more passenger
	{node = findneighbour(cploc,input,rows,cab[l].cabDestn-1,pos-1,cab[l].cabtime,reqs);
}
else if((node==0)&&(pos!=0))
	node=pos;
else
	node=requests[y].destn;
if((node!=0)){
cab[l].cabSource=cab[l].cabDestn;// the previous destn is new cab source
cab[l].cabDestn=node; //the new cab destn

distan2=loc[cab[l].cabSource-1][cab[l].cabDestn-1];
	cab[l].cabtime=cab[l].cabtime+2*distan2;
}
if(stat==1)
stat=0;
}}
else if(cab[l].Cabcapacity==capacity)//cab cant take any more reqs
{
for(r=0;r<capacity;r++)//find closest passenger destn
		{
			if(((cap[r]!=0)&&(cab[l].cabDestn!=0)&&(cap[r]!=cab[l].cabDestn)))
			{
				if(min2>loc[cap[r]-1][cab[l].cabDestn-1]){
					{min2=loc[cap[r]-1][cab[l].cabDestn-1];
				stat1=r;
					pos=cap[r];}
				}}}
cap[stat1]=0;
distan2=loc[cab[l].cabDestn-1][pos-1];
cab[l].cabSource=cab[l].cabDestn;
	while((cab[l].cabDestn!=pos)&&(cab[l].cabDestn!=0)&&(pos!=0))//go node after node to passenger destn
			{node = findnode(cploc,input,rows,cab[l].cabDestn-1,pos-1);
			if(node==0)
				break;
		for(r=0;r<capacity;r++){//check if any passneger is to be dropped
			if(cap[r]==node)
			{cap[r]=0;
			cab[l].Cabcapacity--; //intermediate drop if any
			}
				cab[l].cabDestn=node;
			}
		}
		cab[l].Cabcapacity--;//th destn drop
		cab[l].cabtime=cab[l].cabtime+2*distan2;
		cab[l].cabDestn=pos;
		}

if((y==reqs)&&(cab[l].cabtime<1640))//reached point where cab couldnt find any more reqs
{
	node1 = findnextnode(cploc,rows,cab[l].cabDestn-1,cab[l].cabtime,reqs);//find any node having reqs
	if(node1!=0&&cab[l].cabDestn!=0&&cab[l].cabtime!=0)
	{distan2=loc[cab[l].cabDestn-1][node1-1];
	cab[l].cabtime=cab[l].cabtime+2*distan2;}
	if(node1==0)
		{
		cab[l].cabtime=cab[l].cabtime+100;
		break;
		}
	y=1;
	cab[l].cabSource=cab[l].cabDestn;
	cab[l].cabDestn=node1;
}
}node1=0;
		}
flag1=0;
while(cab[l].Cabcapacity!=0){
	for(r=0;r<w;r++)
	{
		if(cap[r]!=0)
			{distan2=loc[cab[l].cabDestn-1][cap[r]-1];
			cab[l].cabDestn=cap[r];
			cab[l].Cabcapacity--;
		cab[l].cabtime=cab[l].cabtime+2*distan2;
	}
}}
}
int sum=0;
for(l=0;l<=cabs;l++)
{
sum=sum+cab[l].revenue;}
printf("%d\n",sum);

}

int findneighbour(int loc[k][k],int input[k][k],int size,int source,int destn,int time,int reqs){
	int min=1000;
	int dest=-1;
	int next_dest=0,request;
	int i,j;
	for(j=0;j<size;j++)

	{

		for(i=1;i<=reqs;i++)
		{
			if((requests[i].source==j+1 && source!=j && requests[i].reqstatus!=1 && loc[source][j]<loc[source][destn])&&(requests[i].end_interval-time)>0&&(requests[i].end_interval-time)<80)
			{
				dest=j+1;


			if(min>loc[source][j] && dest!=-1&&min!=0&&destn!=dest-1)
								{
									min=loc[source][j];
									next_dest=dest;
							request=requests[i].reqnumber;
								}
								}
		}

	}
		return next_dest;
		}

int findnextnode(int loc[k][k],int size,int source,int time,int reqs){
	int min=1000;
	int dest=-1;
	int next_dest=0,cabtime=0,req=0;
	int i,j;
	for(j=0;j<size;j++)

	{
		if(source==j)
			continue;
		dest=-1;
		for(i=1;i<=reqs;i++)
		{ cabtime=2*loc[source][requests[i].source-1];
			if(requests[i].source==j+1 && requests[i].reqstatus!=1 && (requests[i].end_interval-cabtime-time)>0&& (requests[i].end_interval-time-cabtime)<50)
			{
				dest=j+1;


			if(min>loc[source][j] && dest!=-1&&min!=0)
								{
									min=loc[source][j];
									next_dest=dest;
									req=requests[i].reqnumber;
								}
		}}

	}
		return next_dest;
		}

int findnode(int loc[k][k],int input[k][k],int size,int source,int destn){
int min=1000;
int i,j,u=0;

for(i=0;i<size;i++)
	{if(input[source][i]!=-1){
	if(min>loc[i][destn]){
		min=loc[i][destn];
		if(loc[source][destn]==input[source][i]+min){

			u= i+1;
		}
	}
	}

	}
	return u;
}

// A utility function to create a new Min Heap Node
struct MinHeapNode* newMinHeapNode(int v, int dist)
{
    struct MinHeapNode* minHeapNode =
           (struct MinHeapNode*) malloc(sizeof(struct MinHeapNode));
    minHeapNode->v = v;
    minHeapNode->dist = dist;
    return minHeapNode;
}

// A utility function to create a Min Heap
struct MinHeap* createMinHeap(int capacity)
{
    struct MinHeap* minHeap =
         (struct MinHeap*) malloc(sizeof(struct MinHeap));
    minHeap->pos = (int *)malloc(capacity * sizeof(int));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array =
         (struct MinHeapNode**) malloc(capacity * sizeof(struct MinHeapNode*));
    return minHeap;
}

// A utility function to swap two nodes of min heap. Needed for min heapify
void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b)
{
    struct MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}

// A standard function to heapify at given idx
// This function also updates position of nodes when they are swapped.
// Position is needed for decreaseKey()
void minHeapify(struct MinHeap* minHeap, int idx)
{
    int smallest, left, right;
    smallest = idx;
    left = 2 * idx + 1;
    right = 2 * idx + 2;

    if (left < minHeap->size &&
        minHeap->array[left]->dist < minHeap->array[smallest]->dist )
      smallest = left;

    if (right < minHeap->size &&
        minHeap->array[right]->dist < minHeap->array[smallest]->dist )
      smallest = right;

    if (smallest != idx)
    {
        // The nodes to be swapped in min heap
        struct MinHeapNode *smallestNode = minHeap->array[smallest];
        struct MinHeapNode *idxNode = minHeap->array[idx];

        // Swap positions
        minHeap->pos[smallestNode->v] = idx;
        minHeap->pos[idxNode->v] = smallest;

        // Swap nodes
        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);

        minHeapify(minHeap, smallest);
    }
}

// A utility function to check if the given minHeap is ampty or not
int isEmpty(struct MinHeap* minHeap)
{
    return minHeap->size == 0;
}

// Standard function to extract minimum node from heap
struct MinHeapNode* extractMin(struct MinHeap* minHeap)
{
    if (isEmpty(minHeap))
        return NULL;

    // Store the root node
    struct MinHeapNode* root = minHeap->array[0];

    // Replace root node with last node
    struct MinHeapNode* lastNode = minHeap->array[minHeap->size - 1];
    minHeap->array[0] = lastNode;

    // Update position of last node
    minHeap->pos[root->v] = minHeap->size-1;
    minHeap->pos[lastNode->v] = 0;

    // Reduce heap size and heapify root
    --minHeap->size;
    minHeapify(minHeap, 0);

    return root;
}

// Function to decreasy dist value of a given vertex v. This function
// uses pos[] of min heap to get the current index of node in min heap
void decreaseKey(struct MinHeap* minHeap, int v, int dist)
{
    // Get the index of v in  heap array
    int i = minHeap->pos[v];

    // Get the node and update its dist value
    minHeap->array[i]->dist = dist;

    // Travel up while the complete tree is not hepified.
    // This is a O(Logn) loop
    while (i && minHeap->array[i]->dist < minHeap->array[(i - 1) / 2]->dist)
    {
        // Swap this node with its parent
        minHeap->pos[minHeap->array[i]->v] = (i-1)/2;
        minHeap->pos[minHeap->array[(i-1)/2]->v] = i;
        swapMinHeapNode(&minHeap->array[i],  &minHeap->array[(i - 1) / 2]);

        // move to parent index
        i = (i - 1) / 2;
    }
}

// A utility function to check if a given vertex
// 'v' is in min heap or not
bool isInMinHeap(struct MinHeap *minHeap, int v)
{
   if (minHeap->pos[v] < minHeap->size)
     return true;
   return false;
}

// A utility function used to print the solution
//void printArr(int dist[], int n)
//{
//int i;
//    printf("Vertex   Distance from Source\n");
//    for (i = 0; i < n; ++i)
//        {printf("%d \t\t %d\n", i, dist[i]);
////    save(dist[i]);
//        }
//}

// The main function that calulates distances of shortest paths from src to all
// vertices. It is a O(ELogV) function
float* dijkstra(struct Graph* graph, int src)
{
    int V = graph->V;// Get the number of vertices in graph
    int dist[V];      // dist values used to pick minimum weight edge in cut

    // minHeap represents set E
    struct MinHeap* minHeap = createMinHeap(V);
int v;
    // Initialize min heap with all vertices. dist value of all vertices
    for (v = 0; v < V; ++v)
    {
        dist[v] = INT_MAX;
        minHeap->array[v] = newMinHeapNode(v, dist[v]);
        minHeap->pos[v] = v;
    }

    // Make dist value of src vertex as 0 so that it is extracted first
    minHeap->array[src] = newMinHeapNode(src, dist[src]);
    minHeap->pos[src]   = src;
    dist[src] = 0;
    decreaseKey(minHeap, src, dist[src]);

    // Initially size of min heap is equal to V
    minHeap->size = V;

    // In the followin loop, min heap contains all nodes
    // whose shortest distance is not yet finalized.
    while (!isEmpty(minHeap))
    {
        // Extract the vertex with minimum distance value
        struct MinHeapNode* minHeapNode = extractMin(minHeap);
        int u = minHeapNode->v; // Store the extracted vertex number

        // Traverse through all adjacent vertices of u (the extracted
        // vertex) and update their distance values
        struct AdjListNode* pCrawl = graph->array[u].head;
        while (pCrawl != NULL)
        {
            int v = pCrawl->dest;

            // If shortest distance to v is not finalized yet, and distance to v
            // through u is less than its previously calculated distance
            if (isInMinHeap(minHeap, v) && dist[u] != INT_MAX &&
                                          pCrawl->weight + dist[u] < dist[v])
            {
                dist[v] = dist[u] + pCrawl->weight;

                // update distance value in min heap also
                decreaseKey(minHeap, v, dist[v]);
            }
            pCrawl = pCrawl->next;
        }
    }

    // print the calculated shortest distances
//    printArr(dist, V);
  return dist;
}


int* quicksort(int x[],int first,int last){
    int pivot,j,temp,i,m;

     if(first<last){
         pivot=first;
         i=first;
         j=last;

         while(i<j){
             while(x[i]<=x[pivot]&&i<last)
                 i++;
             while(x[j]>x[pivot])
                 j--;
             if(i<j){
                 temp=x[i];
                  x[i]=x[j];
                  x[j]=temp;
}
         }

         temp=x[pivot];
         x[pivot]=x[j];
         x[j]=temp;

         quicksort(x,first,j-1);
         quicksort(x,j+1,last);

    }
     return x;
}
