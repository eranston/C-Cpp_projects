#include "test_bus_lines.h"
#include <stdlib.h>
#include "sort_bus_lines.h"
#define DISTANCE 0
#define DURATION 1
//TODO add implementation here


int is_sorted(BusLine* start, BusLine* end , int mode);
int is_busline_are_equal(BusLine* b1 , BusLine* b2);




int is_equal(BusLine *start_sorted, BusLine *end_sorted,
             BusLine *start_original, BusLine
*end_original)
{
  if(end_original-start_original != end_sorted-start_sorted)
  {
    return EXIT_FAILURE;
  }
  BusLine * current_original = start_original;
  while (current_original != end_original)
  {
    BusLine* current_sorted = start_sorted;
    while (current_sorted != end_sorted)
    {
      if(!is_busline_are_equal(current_sorted , current_original))
      {
        break;
      }
      current_sorted = (current_sorted+1);
    }
    if(current_sorted == end_sorted)
    {
      return EXIT_FAILURE;
    }
    current_original = (current_original+1);
  }
  return EXIT_SUCCESS;
}

int is_sorted_by_distance (BusLine *start, BusLine *end)
{
  bubble_sort (start , end);
  return is_sorted(start, end ,DISTANCE );
}

int is_sorted_by_duration(BusLine *start, BusLine *end)
{
  quick_sort (start , end);
  return is_sorted (start , end , DURATION);
}


int is_busline_are_equal(BusLine* b1 , BusLine* b2)
{
  if(b1->distance != b2 ->distance)
  {
    return EXIT_FAILURE;
  }
  if(b1 ->line_number != b2->line_number)
  {
    return EXIT_FAILURE;
  }
  if(b1->duration != b2->duration)
  {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}


int is_sorted(BusLine* start, BusLine* end , int mode)
{
  BusLine* current = start;
    while((current+1) != end)
    {
      if (mode == DISTANCE)
      {
        if (current->distance > (current + 1)->distance)
        {
          return EXIT_FAILURE;
        }
        current = (current + 1);
      }
      if (mode == DURATION)
      {
        if (current->duration > (current + 1)->duration)
        {
          return EXIT_FAILURE;
        }
        current = (current + 1);
      }
    }
    return EXIT_SUCCESS;
}