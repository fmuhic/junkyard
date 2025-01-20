#include "graph.h"
#include <stdio.h>

int main(void) {
    graph g = create_graph(5);
    add_edge(&g, 0, 1, 4);
    add_edge(&g, 0, 2, 4);
    add_edge(&g, 0, 4, 10);

    add_edge(&g, 1, 2, 5);
    add_edge(&g, 1, 3, 7);
    add_edge(&g, 1, 4, 1);

    add_edge(&g, 2, 1, 11);
    add_edge(&g, 2, 3, 71);
    add_edge(&g, 2, 4, 33);

    print_graph(&g);
    int cost = path_cost(&g, (int[]) {0, 1, 2, 3}, 4);
    printf("Path cost is %d\n", cost);

    free_graph(&g);
    return 1;
}
