//main program
#include "shortestPath.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

// Driver program to test above functions
int main(int argc, char* argv[])
{
int	source,destn,begin_interval,end_interval;
	int locs,cabs,capacity,Reqs,i,j;
	  FILE *fp = fopen(argv[1], "r");

	      fscanf(fp, "%d %d %d %d", &locs, &cabs, &capacity, &Reqs);
	      int loc[locs][locs],cploc[locs][locs];
	      for(i=0;i<locs;i++)
	      {
	    	  for(j=0;j<locs;j++)
	    	  	      {
	    	  	    	    fscanf(fp,"%d",&loc[i][j]);
	      }
	    }
	  	int x[cabs];
	      for(i=0;i<cabs;i++)
	    	    	  	      {
	    	    	  	    	    fscanf(fp,"%d",&x[i]);
	    	    	  	    	    SetCab(x[i],i);
	    	      }
	      for(j=1;j<=Reqs;j++)
	      	    	  	      {
	      	    	  	    	    fscanf(fp,"%d %d %d %d",&source,&destn,&begin_interval,&end_interval);
	      	    	  	    	AddReq(source,destn,begin_interval,end_interval,j);
	      	    	  	      }



    // create the graph given

    struct Graph* graph = createGraph(locs);
    for(i=0;i<locs;i++)
	      {
	    	  for(j=0;j<locs;j++)
	    	  	      {
	 if(loc[i][j]!=-1)
		 addEdge(graph, i, j,loc[i][j]);
	      }
	    }

        i=0,j=0;
        int **y;
        y = malloc(locs * sizeof *y);
              for (i=0; i<locs; i++)
              {
                y[i] = malloc(locs * sizeof *y[i]);
              }
        int *a;
        for(j=0;j<locs;j++){
        a = dijkstra(graph, j);
        for(i=0;i<locs;i++){

        y[j][i]=(*(a+i));}}
        for(i=0;i<locs;i++)
        {        for(j=0;j<locs;j++){
         cploc[i][j]=y[i][j];
         }

        }

////insert to structure all the arrays make it a array of structures
////for every position sort according to interval time
////
////find the interval where we can fit in maximum reqs.
////i.e suppos position a has x reqs in interval of y unit time ,then on its way to destn if there are
////z more reqs and in the interval l +d*1
////also suppose the shortest path is p units and then we can deviate from shortest path
////so that he dont incur a loss
     sortReq(1,Reqs);
////provide taxi to every Passenger, pass array c,
////compute revenue generated based on distance travelled, reduce the respective counter based on shortest
////distance
     // processReq(y);
    findTaxi(y,cploc,loc,locs,Reqs,capacity,cabs);
//   //without crossing the wait time of a passenger
//    //and capacity also taken into account..
        return 0;
		}


