/*to be done
 * define 2 struct for a node and an edge
 * node includes the list of edges
 * 					 via ,the previous node in tha path
 * 					 distance of that node
 * 					 its position if in heap
 *
 * edge includes node indicating the end point of this edge
 * 				 neigh    included edges
 *				 cost     cost of the edge
 *
 * function to insert or add edges when 2 nodes an distance between is given
 * insert_edge(node source,node destn,double distance)
 * free_edge to remove an edge
 *
 * finding Distance
 * calculate distances
 * show the path
 *
 *
 *
 *
 */#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node node,*heap;
typedef struct edge edge;
struct edge {
	node *end;
	edge *neigh;
	int cost;
};
struct node {
	edge *edge;
	node *thru;
	char label[8];
	double distance;
	int index_heap;
};

#ifdef example
# define BLOCK_SIZE (1024*32-1)
#else
#define BLOCK_SIZE 15
#endif


edge *edge_root=0,*edge_next=0;


void insertEdge(node *a,node *b,double x)
{
	if(edge_next==edge_root){  // at the beginning
		edge_root=malloc(sizeof(edge)*(BLOCK_SIZE+1)); //allocating a block
				edge_root[BLOCK_SIZE].neigh=edge_next;//pointing to itself
		edge_next = edge_root+BLOCK_SIZE;//the next address after edge_root
	}
	//now we have a root edge whose next edge is edge_next
--edge_next;
edge_next -> end = b; //setting pointer to next node
edge_next -> cost = x;//setting cost to the edge
edge_next -> neigh = a;//node of the edge or the origin of the edge
a ->edge = edge_next;//edge corresponding to node a


}

void release_edge()
{
	for(;edge_root;edge_root=edge_next){  //until edge_root=edge_next
		edge_next = edge_root[BLOCK_SIZE].neigh;//find edge_next from edge_root
		free(edge_root);// remove edge_root
		//go on deleting the new root

	}


	heap *heap_n;
	int heap_len;

	void set_cost(node *end,node *thru,double dist){
		int l,m;
		//if the shortest path is known before i.e the node via is
		//known and its distance is less than he new one
		if(end->thru && dist>=end->distance) return;
		/*set the new  min distance,thru path,change the heap */
		end->distance=dist;
			end->thru = thru;
			// take the previous index
			l=end->index_heap;
			if(!l)
				l=++heap_len;//increment l;
			/*else heapify ; take the parent node in the heap and compare till the root */
			for(;l>1&&end->distance<heap_n[m=l/2]->distance;l=m)
				(heap_n[l]=heap_n[m])->index_heap=l;//updating the new index of the child node
			heap_n[l]=end; // updating the new node once it reached its position
			end->index_heap=l;//updating node with its edge in heap
	}
	node *pop_que(){
		node *end,*temp;
		int l,m;
		if(!heap_len)
			return 0;  //no heap
		// remove the root element and put the tail there
		end = heap[1];
		temp=heap[heap_len--];

		for(l=1;l<heap_len&&(m=2*l)<=heap_len;l=m)
		{
			if(m<heap_len&&heap_n[m]->distance>heap_n[m+1]->distance)m++;
			if(heap_n[m]->distance>temp->distance)break;
			}
		heap_n[l]=temp;
		temp->index_heap=l;
		return end;
	}
void calc_all(node *start){
	node *lead;
	edge *e;

	set_dist(start, start, 0);
	while ((lead = pop_queue()))
		for (e = lead->edge; e; e = e->neigh)
			set_dist(e->end, lead, lead->distance + e->cost);
}


void show_path(node *end)
{
	if (end->thru == end)
		printf("%s", end->label);
	else if (!end->thru)
		printf("%s(unreached)", end->label);
	else {
		show_path(end->thru);
		printf("-> %s(%g) ", end->label, end->distance);
	}

}
//main function
int main(void)
{
#ifndef BIG_EXAMPLE
	int i;

#	define N_NODES ('f' - 'a' + 1)  //number of nodes
	node *nodes = calloc(sizeof(node), N_NODES);//creating nodes

	for (i = 0; i < N_NODES; i++) //set the names for each node
		sprintf(nodes[i].label, "%c", 'a' + i);

#	define E(a, b, c) insertEdge(nodes + (a - 'a'), nodes + (b - 'a'), c)
	E('a', 'b', 7);	E('a', 'c', 9); E('a', 'f', 14);
	E('b', 'c', 10);E('b', 'd', 15);E('c', 'd', 11);
	E('c', 'f', 2); E('d', 'e', 6);	E('e', 'f', 9);
#	undef E


	heap = calloc(sizeof(heap), N_NODES + 1);
	heap_len = 0;

	calc_all(nodes);
	for (i = 0; i < N_NODES; i++) {
		show_path(nodes + i);
		putchar('\n');
	}

#if 0

	free_edges();
	free(heap);
	free(nodes);
#endif
	return 0;
}}
