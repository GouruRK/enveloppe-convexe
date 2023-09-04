#ifndef __INIT_STRUCT__
#define __INIT_STRUCT__

#define ALLOCATION_PATERN 100
#define INFORMATION_HEIGHT 50

typedef struct {
    int x;
    int y;
} Point;

typedef struct _vrtx {
    Point point;
    struct _vrtx* next;
    struct _vrtx* prev;
} Vertex, *Polygon;

typedef struct {
    Polygon poly;
    int curlen;
} Convex, Array;

typedef struct {
    Convex* tab_convex;
    int maxlen;
    int curlen;
    int total_points;
} InceptionConvex;

typedef struct {
    Point min;
    Point max;
    int width;
    int height;
} Section;

typedef struct {
    Section information;
    Section clickable;
    int width;
    int height;
} Window;

typedef Point function(int* stop, int nb_points, Window* win);

/**
 * @brief Create a point object.
 *
 * @param x point's abscissa
 * @param y point's ordinate
 * @return Point
 */
Point create_point(int x, int y);

/**
 * @brief Fill a point object with its coordinates.
 *
 * @param point point to be filled
 * @param x point's abscissa
 * @param y point's ordinate
 */
void fill_point(Point* point, int x, int y);

/**
 * @brief Create a vertex object. Vertex->Point is NULL.
 *
 * @return Vertex*, NULL in case of allocation error
 */
Vertex* create_vertex(void);

/**
 * @brief Create a vertex with a point
 *
 * @param point point to be add to the vertex
 * @return Vertex*, NULL in case of allocation error
 */
Vertex* create_filled_vertex(Point point);

/**
 * @brief Fill a vertex with a point object.
 *
 * @param vrtx vertex to be filled
 * @param point point to add
 */
void fill_vertex(Vertex* vrtx, Point point);

/**
 * @brief Create a polygon object.
 *
 * @return Polygon, NULL by default
 */
Polygon create_polygon(void);

/**
 * @brief Create a convex object with all data set to 0.
 *
 * @return Convex object
 */
Convex create_convex(void);

/**
 * @brief Create a array object with all data set to 0.
 *
 * @return Array object
 */
Array create_array(void);

Section create_section(int xmin, int ymin, int xmax, int ymax);

Window create_window(Section information, Section clickable, int width, int height);

Window create_window_data(int width, int height);

/**
 * @brief Create a inception convex object for self-contained convex hulls.
 *
 * @return InceptionConvex
 */
InceptionConvex create_inception_convex(int nb_hulls);

/**
 * @brief Resize the maximum length of an InceptionConvex object.
 *
 * @param incepconv object to resize
 */
void resize_inception_convex(InceptionConvex* incepconv);

/**
 * @brief Free allocated memory for a Vertex object
 *        and the Point object it contains.
 *
 * @param vrtx vertex to free
 */
void free_vertex(Vertex* vrtx);

/**
 * @brief Free allocated memory for a Polygon object and
 *        the vertexes it contains.
 *
 * @param polygon polygon to free
 */
void free_polygon(Polygon* polygon);

/**
 * @brief Free allocated memory for a Convex object and
 *        the polygon it contains.
 *
 * @param convex convex to free
 */
void free_convex(Convex* convex);

/**
 * @brief Free allocated memory for a Convex object and
 *        the polygon it contains.
 *
 * @param array array to free
 */
void free_array(Array* array);

/**
 * @brief Free allocated memory for a InceptionConvex object and
 *        the convexes it contains.
 *
 * @param incepconv self-contained convex hulls to free
 */
void free_inception_convex(InceptionConvex* incepconv);

#endif
