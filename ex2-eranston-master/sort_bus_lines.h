#ifndef EX2_REPO_SORTBUSLINES_H
#define EX2_REPO_SORTBUSLINES_H
// write only between #define EX2_REPO_SORTBUSLINES_H and #endif
// EX2_REPO_SORTBUSLINES_H
/**
 * @brief struct of busline that have a uniqe line number, the distance it
 * travels to the university , the duration it takes to get there.
 * @param None
 * @return None
 */
typedef struct BusLine
{
    int line_number, distance, duration;
} BusLine;

/**
 * @brief function that get pointer to start of an array of buslines and the
 * end of the array and sort the array by the distance of the buslines
 * @param pointer to the start of the array , and a pointer to the end
 * @return void function(no return)
 */
void bubble_sort (BusLine *start, BusLine *end);

/**
 * @brief function that get a pointer to start of array of busline and a
 * pointer to the end of the array and sort the array by the duration of each
 * bus line
 * @param pointer to the start of busline array and a pointer to the end of the
 * busline array
 * @return void function(no return)
 */
void quick_sort (BusLine *start, BusLine *end);

/**
 * @brief a sub function for quick sort to find the pivot index and place
 * the currect busline in this pivot
 * @param pointer to the start of the busline array and a pointer ot the end
 * of the busline array
 * @return a pointer to the pivot busline in the currect place
 */
BusLine *partition (BusLine *start, BusLine *end);
// write only between #define EX2_REPO_SORTBUSLINES_H and #endif
// EX2_REPO_SORTBUSLINES_H



/**
 * @brief function that print a busline array to the stdout
 * @param pointer to the start of the busline array and a pointer to the end
 * of the busline array
 * @return void function(no return)
 */
void print_busline_array(BusLine* start , BusLine* end);
#endif //EX2_REPO_SORTBUSLINES_H
