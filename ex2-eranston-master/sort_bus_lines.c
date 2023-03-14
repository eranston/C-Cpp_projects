#include "sort_bus_lines.h"
#include <stdio.h>
void swap(BusLine *current , BusLine * end );
//TODO add implementation here

void bubble_sort (BusLine *start, BusLine *end)
{
    int n = end - start;

    int i =0;

    while(i < n)
    {
        int j = 0;
        BusLine *current = start;
        while (j < n-1)
        {
            if (current->distance > (current + 1)->distance)
            {
                swap(current, (current + 1));
            }
            current = (current+1);
            j++;
        }
        i++;
    }
}


void swap(BusLine *current , BusLine * end )
{
  BusLine temp_p = *current;
  *current = *end;
  *end = temp_p;
}

void print_busline_array(BusLine* start , BusLine* end)
{
  BusLine * current = start;
  while(current != end)
  {
    printf("%d,%d,%d\n" , current->line_number ,
           current->distance, current->duration);
    current = (current+1);
  }

}

void quick_sort (BusLine *start, BusLine *end)
{
  if(start < end)
  {
    BusLine *pivot = partition(start , end);
    quick_sort (start , pivot);
    quick_sort ((pivot + 1) , end);
  }
}



BusLine* partition (BusLine *start, BusLine *end)
{
  int pivot_index = end - start - 1;
  int current_index = 0;
  int smaller_index = -1;
  while(current_index < pivot_index)
  {
    if((start+current_index)->duration < (start + pivot_index)->duration)
    {
      smaller_index = (smaller_index+1);
      swap ((start+current_index),(start+smaller_index));
    }
    current_index++;
  }
  swap ((start + pivot_index) , (start + smaller_index + 1));
  return (start + smaller_index + 1);
}
