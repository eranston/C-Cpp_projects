#ifndef EX2_REPO_TESTBUSLINES_H
#define EX2_REPO_TESTBUSLINES_H
#include "sort_bus_lines.h"
// write only between #define EX2_REPO_TESTBUSLINES_H and #endif
// EX2_REPO_TESTBUSLINES_H
/**
 * @brief function that check if a busline array is sorted by distance of the
 * busline
 * @param pointer to the start of the busline array and a pointer to the end
 * of the busline arrray
 * @return return 0 if the array is sorted by distance and 1 if not
 */
int is_sorted_by_distance (BusLine *start, BusLine *end);
/**
 * @brief functiont that check if the busline array is sorted by duration of
 * the busline
 * @param pointer to the start of the array and a pointer to the end of the
 * array
 * @return return 0 if the array is sorted by duration and 1 if not
 */
int is_sorted_by_duration (BusLine *start, BusLine *end);
/**
 * @brief function that check if 2 busline arrays are equal (same busline in
 * each array)
 * @param pointer to the start and the end of array number 1, and a pointer to
 * the start and the end of array number 2
 * @return return 0 if the arrays are equal and 1 if not
 */
int is_equal (BusLine *start_sorted,
              BusLine *end_sorted, BusLine *start_original,
              BusLine *end_original);
// write only between #define EX2_REPO_TESTBUSLINES_H and
// #endif //EX2_REPO_TESTBUSLINES_H
#endif //EX2_REPO_TESTBUSLINES_H
