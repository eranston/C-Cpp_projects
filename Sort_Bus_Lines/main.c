#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "sort_bus_lines.h"
#include "test_bus_lines.h"
#define LINE_NUMBER_UPPER_LIMIT 999
#define LINE_NUMBER_LOWER_LIMIT 1
#define DURATION_LOWER_LIMIT 10
#define DURATION_UPPER_LIMIT 100
#define DISTANCE_LOWER_LIMIT 0
#define DISTANCE_UPPER_LIMIT 1000
#define TEST_4_FAIL_MSG "TEST 4 FAILED: there is a problem ,some item "\
                        "been added or missing from the array\n"
#define TEST_4_PASS_MSG "TEST 4 PASSED: testing the array have same items\n"
#define TEST_3_PASS_MSG "TEST 3 PASSED: everything is fine :D\n"
#define TEST_3_FAIL_MSG "TEST 3 FAILED: there is a "\
                        "problem in the sorting algoritem\n"
#define TEST_2_FAIL_MSG "TEST 2 FAILED: there are missing items or some "\
                        "been added to the array\n"
#define TEST_2_PASS_MSG "TEST 2 PASSED: testing ""the array have the "\
                        "same items"" after sorting\n"
#define TEST_1_PASS_MSG "TEST 1 PASSED: testing the "\
                        "array is sorted by distance\n"
#define TEST_1_FAIL_MSG "TEST 1 FAILED: there is a problem with the sorting"\
                        "algoritem\n"
#define DECIMAL_BASE 10
#define INPUT_SIZE 60


/*
 * @brief function that get from the user input until it gets a valid input for
 * number of lines and put the input in the param number_of_lines
 * @params pointer to long that the input from user will put into
 * @return 0 when succeeded and 1 when failed
 * */
int get_number_of_lines(long* number_of_lines);

/*
 * @brief function that run when user input is "bubble" , get from user the
 * input of the busline array and sort it with bubble sort algorithm, print the
 * array after the sorting.
 * by distance
 * @params no param
 * @return 0 when succeeded with no issues 1 otherwise
 * */
int bubble_sort_input();

/*
 * @brief function the main calls when getting from user "test" as input, get
 * from user the input of the busline array and run tests that checks if the
 * bubble sorting and quick sort work well
 * @params no param
 * @return 0 when succeeded with no issues and 1 if there is an issue
 * */
int test_input();

/*
 * @brief function the main calls when getting from user "quick" as input, get
 * from user the input of the busline array and sort the array by duration with
 * quick sort algorithm, print in the end the array after the sorting.
 * @params
 * @return
 * */
int quick_sort_input();
/*
 * @brief check if the user input for a single busline is valid
 * @params line number , distance and duration of a given busline
 * @return 0 if the input is valid , 1 if not
 * */
int check_input(int line_number , int distance ,int duration);

/*
 * @brief function that test if the bubble sorting is correct and really
 * sorting the array by distance
 * @params pointer to the start of the array and the length of the array
 * array
 * @return void(no return) but print to stdout if the test passed or failed
 * */
void run_test_1(BusLine* copied_array , long number_of_lines);

/*
 * @brief function that test if the same busline in the original array are
 * in the array that been sorted , the function use a copy of the orginal array
 * after delete it
 * @params pointer to the start of the original array , pointer to
 * the start of the sorted array and the length of the original array
 * @return void(no return) but print to stdout if the test passed or failed
 * */
void run_test_2(BusLine* array , BusLine* copied_array , long number_of_lines);

/*
 * @brief function that test after the quick sort on a given array really sort
 * it by the duration
 * @params pointer to the start of the array and the length of the array
 * @return void(no return) but print if the test passed or failed
 * */
void run_test_3(BusLine* copied_array , long number_of_lines);

/*
 * @brief
 * @params
 * @return
 * */
void run_test_4(BusLine* array , BusLine* copied_array , long number_of_lines);

/*
 * @brief
 * @params
 * @return
 * */
int run_tests(BusLine* array , long number_of_lines);

/*
 * @brief
 * @params
 * @return
 * */
BusLine* get_input(int * line_number , int * distance , int* duration
                   ,  long* number_of_lines);

/*
 * @brief
 * @params
 * @return
 * */
int get_a_single_input(int* line_number , int* distance , int*duration);

/*
 * @brief
 * @params
 * @return
 * */
void enter_busline_to_array(BusLine* array , int index , int distance
                            , int duration ,int line_number);





int main(int argc , char* argv[])
{
  if (argc != 2)
  {
    printf("USAGE: the program get 1 input and its 'test'"
           " , 'bubble_sort' or quick_sort'");
    return EXIT_FAILURE;
  }
  if(!strcmp(argv[1], "test"))
  {
      return test_input();
  }
  if(!strcmp(argv[1] , "bubble"))
  {
    return bubble_sort_input();
  }
  if(!strcmp(argv[1] , "quick"))
  {
      return quick_sort_input();
  }
  return EXIT_FAILURE;
}



int bubble_sort_input()
{
  BusLine* array;
  int line_number , distance , duration ;
  long number_of_lines;
  array = get_input(&line_number , &distance , &duration , &number_of_lines);
  if (array == NULL)
  {
    return EXIT_FAILURE;
  }
  bubble_sort (array , (array + number_of_lines));
  print_busline_array (array , (array+number_of_lines));
  free(array);
  array = NULL;
  return EXIT_SUCCESS;
}

int test_input()
{
  BusLine* array;
  int line_number , distance , duration ;
  long number_of_lines;
  array = get_input(&line_number , &distance , &duration , &number_of_lines);
  if (array == NULL)
  {
    return EXIT_FAILURE;
  }

  int result = run_tests(array , number_of_lines);
  free(array);
  array = NULL;
  return result;
}

int quick_sort_input()
{
  BusLine* array;
  int line_number , distance , duration ;
  long number_of_lines;
  array = get_input(&line_number , &distance , &duration , &number_of_lines);
  if (array == NULL)
  {
    return EXIT_FAILURE;
  }
  quick_sort (array , (array+number_of_lines));
  print_busline_array (array , (array+number_of_lines));
  free(array);
  array = NULL;
  return EXIT_SUCCESS;
}


BusLine* get_input(int * line_number , int * distance , int* duration ,
                   long* number_of_lines)
{
  int index = 0;
  get_number_of_lines(number_of_lines);
  BusLine *array = malloc (sizeof(BusLine) * (*number_of_lines));
  if(array ==NULL)
  {
    return NULL;
  }
  while (index < (*number_of_lines))
  {
    int is_ok = get_a_single_input (line_number , distance , duration);

    if (!is_ok)
    {
      enter_busline_to_array(array , index , *distance , *duration ,
                             *line_number);
      index++;
    }

  }
  return array;
}


int get_number_of_lines(long* number_of_lines)
{
  char input[INPUT_SIZE];
  while(1)
  {
    printf("Enter number of lines. Then enter\n");
    fgets (input,INPUT_SIZE,stdin);
    *number_of_lines = strtol (input , NULL , DECIMAL_BASE);
    if(*number_of_lines > 0)
    {
      return EXIT_SUCCESS;
    }
    printf("ERROR: the number of line need to be positive\n");
  }
}

int get_a_single_input(int* line_number , int* distance , int*duration)
{
  char input[INPUT_SIZE];
  printf("Enter line info. Then enter\n");
  fgets(input , INPUT_SIZE , stdin);
  sscanf(input , "%d,%d,%d" , line_number , distance , duration);
  int is_ok_input = check_input (*line_number , *distance , *duration);
  if (is_ok_input)
  {
      return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}

int check_input(int line_number , int distance ,int duration)
{
  if (line_number < LINE_NUMBER_LOWER_LIMIT ||
        line_number > LINE_NUMBER_UPPER_LIMIT)
  {
    printf("ERROR: Number of lines need to be a positive "
           "integer between 1 to 999\n");
    return EXIT_FAILURE;
  }
  if ((DISTANCE_LOWER_LIMIT >distance) || (distance>DISTANCE_UPPER_LIMIT))
  {
      printf ("ERROR: the distance need to be integer "
              "between 0 and 1000\n");
      return EXIT_FAILURE;
  }
  if ((DURATION_LOWER_LIMIT > duration) || (duration > DURATION_UPPER_LIMIT))
  {
      printf ("ERROR: the duration need to be integer "
              "between 10 to 100\n");
      return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}



void enter_busline_to_array(BusLine* array , int index , int distance ,
                            int duration ,int line_number)
{

    (array + index)->duration = duration;
    (array + index)->distance = distance;
    (array + index)->line_number = line_number;

}



int run_tests(BusLine* array , long number_of_lines)
{
  size_t array_size = sizeof(BusLine) * number_of_lines;
  BusLine* copied_array = malloc(array_size);
  if (copied_array == NULL)
  {
    return EXIT_FAILURE;
  }
  memcpy (copied_array , array , array_size );
  run_test_1 (copied_array , number_of_lines);
  run_test_2 (array , copied_array , number_of_lines);
  run_test_3 (copied_array , number_of_lines);
  run_test_4 (array , copied_array , number_of_lines);
  free (copied_array);
  copied_array = NULL;
  return EXIT_SUCCESS;
}



void run_test_1(BusLine* copied_array , long number_of_lines)
{
  int result_1 = is_sorted_by_distance (copied_array ,
                                        (copied_array + number_of_lines));
  printf(result_1 ? TEST_1_FAIL_MSG : TEST_1_PASS_MSG);
}

void run_test_2(BusLine* array , BusLine* copied_array , long number_of_lines)
{
  int result_2 = is_equal(array , (array+number_of_lines) ,
                          copied_array ,
                          (copied_array+number_of_lines));
  printf(result_2 ? TEST_2_FAIL_MSG :TEST_2_PASS_MSG);

}


void run_test_3(BusLine* copied_array , long number_of_lines)
{
  int result_3 = is_sorted_by_duration(copied_array ,
                                       (copied_array + number_of_lines));
  printf(result_3 ? TEST_3_FAIL_MSG: TEST_3_PASS_MSG);
}


void run_test_4(BusLine* array , BusLine* copied_array , long number_of_lines)
{

  int result_4 = is_equal(array , (array+number_of_lines) ,
                          copied_array ,
                          (copied_array+number_of_lines));
  printf(result_4 ? TEST_4_FAIL_MSG : TEST_4_PASS_MSG );

}