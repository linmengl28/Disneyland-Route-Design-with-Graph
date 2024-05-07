#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define V 26 // Number of vertices

// Function to print route
void printArray(int route[], int size)
{
    for (int i = size - 1; i >= 0; --i)
    {
        printf("%d ", route[i]);
    }
    printf("\n");
}

// Modified Breadth-First Search (BFS) traversal to find a route through specified vertices
void BFS(int graph[V][V], int start_vertex, int end_vertex, int *specified_vertices, int num_vertices, int *waitingTime)
{
    int *visited = (int *)malloc(V * sizeof(int));
    int *parent = (int *)malloc(V * sizeof(int));
    int *specified_visited = (int *)malloc(num_vertices * sizeof(int));
    int *weights = (int *)malloc(V * sizeof(int));

    for (int i = 0; i < V; ++i)
    {
        visited[i] = 0;
        parent[i] = -1;       // no parent find initially
        weights[i] = INT_MAX; // Initialize weights to maximum value
    }

    for (int i = 0; i < num_vertices; ++i)
    {
        specified_visited[i] = 0;
    }

    visited[start_vertex] = 1;
    weights[start_vertex] = 0;

    int queue[V];
    int front = -1, rear = -1;

    queue[++rear] = start_vertex;

    while (front != rear)
    {
        int current_vertex = queue[++front];
        for (int i = 0; i < V; ++i)
        {
            if (graph[current_vertex][i] != 0 && !visited[i])
            {
                visited[i] = 1;
                parent[i] = current_vertex;
                weights[i] = weights[current_vertex] + graph[current_vertex][i];
                queue[++rear] = i;
            }
        }
    }

    int current_vertex = end_vertex;
    int final_weight = 0;
    int total_waiting_time = 0; // Initialize total waiting time
    int route[50];
    int k = 0;
    while (current_vertex != -1 && num_vertices > 0)
    {
        route[k++] = current_vertex;
        final_weight += weights[current_vertex];
        for (int i = 0; i < num_vertices; ++i)
        {
            if (current_vertex == specified_vertices[i] && !specified_visited[i])
            {
                specified_visited[i] = 1;
                // Calculate waiting time and accumulate
                total_waiting_time += waitingTime[current_vertex];
                --num_vertices;
                break;
            }
        }
        current_vertex = parent[current_vertex];
    }

    for (int i = 0; i < num_vertices; ++i)
    {
        if (!specified_vertices[i])
        {
            printf("Cannot find shortest path through all the selected vertex.\n");
            free(visited);
            free(parent);
            free(specified_visited);
            free(weights);
            return;
        }
    }
    printf("Route:");
    printArray(route, k);
    printf("Total time used: %d\n", total_waiting_time + final_weight);
    free(visited);
    free(parent);
    free(specified_visited);
    free(weights);
}

int main()
{
    int graph[V][V] = {{0, 4, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                       {4, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 2, 0, 0, 4, 0, 0},
                       {6, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                       {0, 0, 0, 0, 1, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                       {0, 0, 1, 1, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                       {0, 0, 0, 0, 4, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                       {0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                       {0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                       {0, 0, 0, 0, 0, 0, 0, 1, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                       {0, 0, 0, 7, 0, 0, 0, 0, 6, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                       {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                       {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0},
                       {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                       {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                       {0, 4, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 2, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0},
                       {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 1, 0, 0, 0, 5, 5, 0, 0, 0, 0},
                       {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 6, 0, 0, 0, 0, 0, 0},
                       {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0},
                       {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 3, 0, 0, 0, 0, 0, 0},
                       {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 3, 0, 0, 0, 0, 0, 0, 0},
                       {0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 5, 0, 0, 0, 0, 0, 3, 0, 1, 3, 0},
                       {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 3, 0, 0, 0, 0, 1},
                       {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 3, 2, 0, 3},
                       {0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 2, 0},
                       {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 3, 2, 0, 3},
                       {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 3, 0, 3, 0}}; // Adjacency matrix
    int waitingTime[26] = {0,
                           25,
                           34,
                           12,
                           6,
                           36,
                           16,
                           12,
                           46,
                           55,
                           27,
                           21,
                           31,
                           22,
                           13,
                           16,
                           68,
                           15,
                           31,
                           55,
                           29,
                           24,
                           84,
                           57,
                           31,
                           5};
    int start_vertex = 0;                  // Starting vertex
    int end_vertex = 23;                   // Ending vertex
    int specified_vertices[] = {0, 1, 23}; // Specified vertices to visit
    int num_vertices = sizeof(specified_vertices) / sizeof(specified_vertices[0]);

    // Find the route through specified vertices using BFS
    BFS(graph, start_vertex, end_vertex, specified_vertices, num_vertices, waitingTime);
    return 0;
}
