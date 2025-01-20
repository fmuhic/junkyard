#pragma once

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct edge_t
{
    int vertex;
    int weight;
    struct edge_t *next;
} edge;

typedef struct graph_t
{
    int vertex_count;
    edge **edge_list;
} graph;

extern graph create_graph(int vertex_count);
extern void free_graph(graph* graph);
extern void print_graph(graph* graph);
extern edge* create_edge(int vertex, int weight);
extern void add_edge(graph* graph, int from, int to, int weight);
extern int path_cost(graph* graph, int* vertices, int vertex_count);
