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


//        addEdge(graph, 1, 0, 10);
//        addEdge(graph, 1, 2, 25);
//        addEdge(graph, 1, 3, 10);
//        addEdge(graph, 2, 1, 25);
//        addEdge(graph, 2, 3, 20);
//        addEdge(graph, 2, 4, 30);
//        addEdge(graph, 3, 1, 10);
//        addEdge(graph, 3, 2, 20);
//        addEdge(graph, 4, 2, 28);
////        addEdge(graph, 2, 5, 2);
//        addEdge(graph, 3, 4, 6);
//        addEdge(graph, 4, 5, 9);
        i=0,j=0;
        int **y;
        y = malloc(locs * sizeof *y);
              for (i=0; i<locs; i++)
              {
                y[i] = malloc(locs * sizeof *y[i]);
              }
        //int y[5][5]={0};
        int *a;
        for(j=0;j<locs;j++){
        a = dijkstra(graph, j);
        for(i=0;i<locs;i++){

        y[j][i]=(*(a+i));}}
        for(i=0;i<locs;i++)
        {        for(j=0;j<locs;j++){
         cploc[i][j]=y[i][j];
         printf("%d\t",cploc[i][j]);}
        printf("\n");
        };
        //        addEdge(graph, 1, 2, 25);
        //        addEdge(graph, 1, 3, 10);
        //        addEdge(graph, 2, 1, 25);
        //        addEdge(graph, 2, 3, 20);
        //        addEdge(graph, 2, 4, 30);
        //        addEdge(graph, 3, 1, 10);
        //        addEdge(graph, 3, 2, 20);
        //        addEdge(graph, 4, 2, 28);
        ////        addEdge(graph, 2, 5, 2);
        //        addEdge(graph, 3, 4, 6);
        //        addEdge(graph, 4, 5, 9);

        int *b;
        int k=locs,l;
        int c[k];
        for(l=0;l<locs;l++)
        c[l]=0;
        b = quicksort(x,0,cabs-1);
        i=0,j=*b;

        for(i=0;i<cabs;i++)
        	printf("%d\t",*(b+i));
        i=1;

        while(i<cabs){
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
  {//c[i]=c[i+1];
    		printf("%d\n",c[i]);}
//     c[i]=0;

////insert to structure all the arrays make it a array of structures
////for every position sort according to interval time
////
////find the interval where we can fit in maximum reqs.
////i.e suppos position a has x reqs in interval of y unit time ,then on its way to destn if there are
////z more reqs and in the interval l +d*1
////also suppose the shortest path is p units and then we can deviate from shortest path
////so that he dont incur a loss
//     for(i=0;i<5;i++)
//     {
//    	 for(j=0;j<5;i++)
//    		 {cploc[i][j]=y[i][j];
//    		 printf("1
     sortReq(1,Reqs);
     printReq(Reqs);
////provide taxi to every Passenger, pass array c,
////compute revenue generated based on distance travelled, reduce the respective counter based on shortest
////distance
printf("tillhere");
     // processReq(y);
    findTaxi(y,cploc,loc,locs,locs,c,Reqs,capacity,cabs);
//   //without crossing the wait time of a passenger
//    //and capacity also taken into account..

        return 0;
		}


