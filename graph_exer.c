/*
	Exercise: Vertex Coloring
	1. Complete the basic greedy coloring program below.
	2. Analyze the running time of the program.
	3. Improve the quality of your solution by determining a good starting vertex.
*/

#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>

typedef struct node{
	int x;
	struct node *next;
}graph;

graph **createAdjList(int *, int *);
void viewList(graph **, int);
int * graphColoring(graph **, int);
int getAvailableColor(graph **, int *, int, int);
void viewColor(int *, int);
void deleteGraph(graph **, int);

int main(){
	graph **g;
	int v, e;
	int *color;
	
	g = createAdjList(&v, &e);
	color = graphColoring(g, v);
	viewList(g, v);
    /*
	viewColor(color, v);
	
	free(color);
	deleteGraph(g, v);
    */
}

graph **createAdjList(int *v, int *e){
    FILE *file = fopen("graph.in", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        exit(1);
    }

    // Read number of vertices and edges
    fscanf(file, "%d", v);
    fscanf(file, "%d", e);

    int num_vertices = *v;
    int num_edges = *e;

    // Allocate memory for the adjacency list
    graph **adjList = (graph **)malloc(num_vertices * sizeof(graph *));
    for (int i = 0; i < num_vertices; i++) {
        adjList[i] = NULL;
    }

    // Read adjacency information from the file
    int source, destination;
    while (fscanf(file, "%d %d", &source, &destination) == 2) {
        // Create a new node for the destination vertex
        graph *newNode = (graph *)malloc(sizeof(graph));
        newNode->x = destination;
        newNode->next = NULL;

        // Insert the new node at the beginning of the adjacency list for the source vertex
        newNode->next = adjList[source];
        adjList[source] = newNode;
    }

    fclose(file);
    return adjList;
}

void viewList(graph **g, int v){
	int i;
	graph *p;
	
	for(i = 0; i < v; i++){
		p = g[i];
		printf("%d: ", i);
		//traverse the list connected to vertex i
		while(p != NULL){
			printf("%3d", p->x);
			p = p->next;
		}
		printf("\n");
	}
}

int * graphColoring(graph **g, int v){
	int *color, availCol, i;
	
	//colors are represented as integers starting from 0
	color = (int *)malloc(sizeof(int)*v);
	for(i = 0; i < v; i++)
		color[i] = -1;
	
	color[0] = 0;	//assign first vertex with the first color
	for(i = 1; i < v; i++){
		availCol = getAvailableColor(g, color, v, i);
		color[i] = availCol;
	}
	return color;
}

int getAvailableColor(graph **g, int *color, int v, int curr){
	graph *p;
	int *available, i, availCol;
	
	//keeps track of the colors used on any previously colored vertices adjacent to it
	available = (int *)malloc(sizeof(int)*(v));
	for(i = 0; i < v; i++)
		available[i] = 1;
	
	/*Insert code here for marking the colors that have been used 
	on any previously colored vertices adjacent to it.*/
	

	
	
	for(i = 0; i < v; i++){				//get the smallest color that is available
		if(available[i] == 1){
			availCol = i;
			break;
		}
	}
	
	free(available);
	return availCol;
}

void viewColor(int *color, int v){
	int i;
	
	for(i = 0; i < v; i++){
		printf("Vertex %d -> Color %d\n", i, color[i]);
	}
}

void deleteGraph(graph **g, int v){
	int i;
	graph *p;
	for(i = 0; i < v; i++){
		while(g[i] != NULL){
			p = g[i];
			g[i] = g[i]->next;
			free(p);
		}
	}
	free(g);
}