#include "shortestPath.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

// Driver program to test above functions
int main()
{
    // create the graph given in above fugure
    int V = 5;
    struct Graph* graph = createGraph(V);
        addEdge(graph, 0, 1, 7);
        addEdge(graph, 0, 2, 9);
        addEdge(graph, 0, 5, 14);
        addEdge(graph, 1, 2, 10);
        addEdge(graph, 1, 3, 15);
        addEdge(graph, 2, 3, 11);
        addEdge(graph, 2, 5, 2);
        addEdge(graph, 3, 4, 6);
        addEdge(graph, 4, 5, 9);
        int i,j=0;
        int **y;
        y = malloc(5 * sizeof *y);
              for (i=0; i<5; i++)
              {
                y[i] = malloc(5 * sizeof *y[i]);
              }
        //int y[5][5]={0};
        int *a;
        for(j=0;j<V;j++){
        a = dijkstra(graph, j);
        for(i=0;i<V;i++){
        y[j][i]=(*(a+i));}}
        for(i=0;i<V;i++)
        {        for(j=0;j<V;j++)
        printf("%d\t",y[i][j]);
        printf("\n");
        }
        int x[10]={1,1,2,3,4,4,5,5,2,1};
        int *b;
        int c[10]={0};
        b = quicksort(x,0,9);
        i=0,j=*b;
        int count =0;
        for(i=0;i<10;i++)
        	printf("%d\t",*(b+i));
        i=1;

        while(i<10){
        	if((*(b+i)-*(b+i-1))==0){
c[j]++;
        	i++;}
        	else
        	{c[j]++;
        		j=j+(*(b+i)-*(b+i-1));
        		i++;
        		}
        	}c[j]++;


     for (i=0;i<=j;i++)
    		printf("%d\n",c[i]);
//insert to structure all the arrays make it a array of structures
//for every position sort according to interval time
//
//find the interval where we can fit in maximum reqs.
//i.e suppos position a has x reqs in interval of y unit time ,then on its way to destn if there are
//z more reqs and in the interval l +d*1
//also suppose the shortest path is p units and then we can deviate from shortest path
//so that he dont incur a loss
     AddReq(1,4,600,645,1);
     AddReq(3,1,642,623,2);
     AddReq(3,5,639,672,3);
     AddReq(4,2,625,739,4);
     sortReq(1,4);
     printReq(4);
//provide taxi to every Passenger, pass array c,
//compute revenue generated based on distance travelled, reduce the respective counter based on shortest
//distance
    findTaxi(y,5,5,c,4);
   //without crossing the wait time of a passenger
    //and capacity also taken into account..
        return 0;
		}


