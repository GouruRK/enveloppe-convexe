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

typedef struct {
    int radius;
    int nb_points;
    float factor;
} Settings;

/**
 * @brief Creates a point object.
 *
 * @param x point's abscissa
 * @param y point's ordinate
 * @return created point
 */
Point create_point(int x, int y);

/**
 * @brief Fills a point object with its coordinates.
 *
 * @param point point to be filled
 * @param x point's abscissa
 * @param y point's ordinate
 */
void fill_point(Point* point, int x, int y);

/**
 * @brief Creates a vertex object. Vertex->Point is NULL.
 *
 * @return Vertex*, NULL in case of allocation error
 */
Vertex* create_vertex(void);

/**
 * @brief Creates a vertex with a point
 *
 * @param point point to be add to the vertex
 * @return Vertex*, NULL in case of allocation error
 */
Vertex* create_filled_vertex(Point point);

/**
 * @brief Fills a vertex with a point object.
 *
 * @param vrtx vertex to be filled
 * @param point point to add
 */
void fill_vertex(Vertex* vrtx, Point point);

/**
 * @brief Creates a polygon object.
 *
 * @return Polygon, NULL by default
 */
Polygon create_polygon(void);

/**
 * @brief Creates a convex object with all data set to 0.
 *
 * @return Convex object
 */
Convex create_convex(void);

/**
 * @brief Creates a array object with all data set to 0.
 *
 * @return Array object
 */
Array create_array(void);

/**
 * @brief Create a section object that represent a rectangle.
 *        The rectangle is composed of two points : the top left corner (xmin, ymin)
 *        and the bottom right corner (xmax, ymax).
 * 
 * @param xmin top left abscissa
 * @param ymin top left ordinate
 * @param xmax bottom right abscissa
 * @param ymax bottom right ordinate
 * @return Section created section
 */
Section create_section(int xmin, int ymin, int xmax, int ymax);

/**
 * @brief Creates a window object that contains window's parameters.
 *        A window is divided in two sections :
 *         - the 'clickable' one (where the points are generated),
 *         - the 'information' one (where information about convex hulls are drawn).
 * 
 * @param information section data to draw information
 * @param clickable section data to generate points
 * @param width width of the window
 * @param height height of the window
 * @return Window created window
 */
Window create_window_data(Section information, Section clickable, int width, int height);

/**
 * @brief Creates a window object that contains window's paramters.
 * 
 * @param width with of the window
 * @param height height of the window
 * @return Window created window
 */
Window create_window(int width, int height);

/**
 * @brief Creates a inception convex object for self-contained convex hulls.
 *
 * @return InceptionConvex
 */
InceptionConvex create_inception_convex(int nb_hulls);

/**
 * @brief Sets generation settings.
 * 
 * @param radius maximum radius of the shape to generate
 * @param nb_points maximum number of point
 * @param factor squashing factor
 * @return Settings new settings
 */
Settings set_settings(int radius, int nb_points, float factor);

/**
 * @brief Frees allocated memory for a Vertex object
 *        and the Point object it contains.
 *
 * @param vrtx vertex to free
 */
void free_vertex(Vertex* vrtx);

/**
 * @brief Frees allocated memory for a Polygon object and
 *        the vertexes it contains.
 *
 * @param polygon polygon to free
 */
void free_polygon(Polygon* polygon);

/**
 * @brief Frees allocated memory for a Convex object and
 *        the polygon it contains.
 *
 * @param convex convex to free
 */
void free_convex(Convex* convex);

/**
 * @brief Frees allocated memory for a Convex object and
 *        the polygon it contains.
 *
 * @param array array to free
 */
void free_array(Array* array);

/**
 * @brief Frees allocated memory for a InceptionConvex object and
 *        the convexes it contains.
 *
 * @param incepconv self-contained convex hulls to free
 */
void free_inception_convex(InceptionConvex* incepconv);

#endif
