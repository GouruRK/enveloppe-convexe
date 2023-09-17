#ifndef __INIT_LIST__
#define __INIT_LIST__

#include "struct.h"

/**
 * @brief Adds a vertex to the polygon's tail.
 * 
 * @param poly polygon to add the vertex
 * @param vrtx vertex to add
 */
void add_vertex_tail(Polygon* poly, Vertex* vrtx);

/**
 * @brief Adds a vertex to the polygon's head.
 * 
 * @param poly polygon to add the vertex
 * @param vrtx vertex to add
 */
void add_vertex_head(Polygon* poly, Vertex* vrtx);

/**
 * @brief Creates a vertex that contains the given point and add it depending on the given add_function.
 * 
 * @param poly polygon to add the vertex
 * @param point point to add
 * @param add_function function that add the point to the polygon. It can be either :
 *         - 'add_vertex_tail'
 *         - 'add_vertex_head'
 * @return '0' in case of allocation error
 *         else '1', in case of success 
 */
int add_point(Polygon* poly, Point point, void (*add_function)(Polygon*, Vertex*));

/**
 * @brief Extracts the polygon's tail vertex.
 * 
 * @param poly polygon to extract the vertex
 * @return tailed vertex, NULL if not
 */
Vertex* extract_vertex_tail(Polygon* poly);

/**
 * @brief Extracts the polygon's head vertex.
 * 
 * @param poly polygon to extract the vertex
 * @return headed vertex, NULL if not
 */
Vertex* extract_vertex_head(Polygon* poly);

/**
 * @brief Extracts the vertex that contains the given point.
 *        Point comparison is based on its coordinates.
 * 
 * @param poly polygon to extract the polygon
 * @param point point to extract
 * @return vertex that contains the point, 
 *         NULL if the point is not in the polygon
 */
Vertex* extract_point(Polygon* poly, Point point);

#endif
