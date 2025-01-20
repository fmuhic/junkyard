#include "graph.h"

graph create_graph(int vertex_count)
{
    graph g = { vertex_count, malloc(vertex_count * sizeof(edge*)) };

    for (int i = 0; i < vertex_count; ++i)
    {
        g.edge_list[i] = NULL;
    }

    return g;
}

extern void free_graph(graph* graph) 
{
    for (int i = 0; i < graph->vertex_count; ++i)
    {
        edge* e = graph->edge_list[i];
        while (e != NULL)
        {
            edge* tmp = e;
            e = e->next;
            free(tmp);
        }
    }
    free(graph->edge_list);
}

extern int path_cost(graph* graph, int* vertices, int vertex_count)
{
    int cost = 0;
    for (int i = 0; i < vertex_count - 1; ++i)
    {
        int src = vertices[i];
        int dest = vertices[i + 1];
        edge* e = graph->edge_list[src];
        while (e != NULL)
        {
            if (e->vertex == dest) 
            {
                printf("Vertex found (%d -> %d, w = %d)\n", src, dest, e->weight);
                cost += e->weight;
                break;
            }
            e = e->next;
        }

        if (e == NULL)
        {
            printf("Edge (%d -> %d) not found\n", src, dest);
            return -1;
        }
    }

    return cost;
}

extern void print_graph(graph* graph) {
    for (int i = 0; i < graph->vertex_count; ++i)
    {
        printf("Vertex %d | ", i);
        edge* edge = graph->edge_list[i];
        while (edge != NULL)
        {
            printf(" (%d -> %d, w = %d)", i, edge->vertex, edge->weight);
            edge = edge->next;
        }
        printf("\n");
    }
}

void add_edge(graph* graph, int from, int to, int weight)
{
    assert(from >= 0 && from < graph->vertex_count && "from out of bound");
    assert(to >= 0 && to < graph->vertex_count && "to aout of bounds");

    edge* e = create_edge(to, weight);
    e->next = graph->edge_list[from];
    graph->edge_list[from] = e;
}

edge* create_edge(int vertex, int weight) 
{
    edge* e = malloc(sizeof(edge));
    e->vertex = vertex;
    e->weight = weight;
    e->next = NULL;
    return e;
}
