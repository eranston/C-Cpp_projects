#include "cipher.h"
#include "tests.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define BUFFER_SIZE 10
#define FOUR_ARGUMENTS 5
#define ONE_ARGUMENT 2
#define ASCI_FOR_0 48
#define ASCI_FOR_9 57
#define DECIMAL 10
#define MINUS 45
// your code goes here
int tests();
int check_k(const char k[]);
int check_if_k_negative(const char k[]);
int run_encode_or_decode(char command[] ,long k,
                         char input_file[] , char output_file[]);


int main (int argc, char *argv[])
{
    if (argc == ONE_ARGUMENT)
      // if the there is just 1 argument
        {
        if (strcmp(argv[1] , "test") == 0)
          // check if this argument is "test" run tests
            {
            return tests();
            }
        else
            {
            fprintf(stderr, "Usage: cipher test\n");
            return EXIT_FAILURE;
            }
        }
    if (argc == FOUR_ARGUMENTS)
    {

      int result_1 = (strcmp(argv[1] , "decode"));
      int result_2 = (strcmp(argv[1] , "encode"));
        if (result_2 == 0 || result_1==0)
        {

            if(check_k(argv[2]))
            {
                fprintf (stderr , "The given shift value is invalid.\n" );
                return EXIT_FAILURE;
            }

            long new_k = strtol(argv[2] , NULL , DECIMAL );

            int is_ok = run_encode_or_decode(argv[1] ,new_k
                                             ,argv[3] , argv[4]);
            if (!is_ok)
            {
                return EXIT_FAILURE;
            }

            return EXIT_SUCCESS;
        }
        else
        {
            fprintf(stderr, "The given command is invalid.\n");
            return EXIT_FAILURE;
        }
    }
    fprintf(stderr , "The program receives 1 or 4 arguments only.\n");
    return EXIT_FAILURE;
}

int tests()
{
    int test_result_1 = test_encode_non_cyclic_lower_case_positive_k();
    int test_result_2 =
        test_encode_cyclic_lower_case_special_char_positive_k();
    int test_result_3 =
        test_encode_non_cyclic_lower_case_special_char_negative_k();
    int test_result_4 = test_encode_cyclic_lower_case_negative_k();
    int test_result_5 = test_encode_cyclic_upper_case_positive_k();
    int test_result_6 = test_decode_non_cyclic_lower_case_positive_k ();
    int test_result_7 =
        test_decode_cyclic_lower_case_special_char_positive_k();
    int test_result_8 =
        test_decode_non_cyclic_lower_case_special_char_negative_k ();
    int test_result_9 = test_decode_cyclic_lower_case_negative_k ();
    int test_result_10 = test_decode_cyclic_upper_case_positive_k ();
    if (test_result_1 || test_result_2 || test_result_3 ||
        test_result_4 || test_result_5 || test_result_6 || test_result_7 ||
        test_result_8 || test_result_9 || test_result_10)
    {
      return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

int check_k(const char k[])
{
    size_t i = 0;
    size_t s_len = strlen(k);
    int is_k_negative = check_if_k_negative(k);
    if (is_k_negative)
    {
      i ++;
    }

    for ( ; i< s_len ; i++)
    {


        if(k[i] < ASCI_FOR_0 || k[i] > ASCI_FOR_9)
        {
            return 1;
        }

    }
    return 0;
}

int check_if_k_negative(const char k[])
{
  if(k[0] == MINUS)
  {
    return 1;

  }
  return 0;
}

int run_encode_or_decode(char command[] ,long k , char path_input_file[]
                         , char path_output_file[])
{
    FILE* in_file = fopen(path_input_file , "r");
    FILE* out_file= fopen(path_output_file , "w");
    if ((!in_file) || (!out_file))
    {
        fprintf(stderr , "The given file is invalid.\n");
        return 0;
    }
    char input[BUFFER_SIZE];
    while(fgets(input , BUFFER_SIZE , in_file))
    {
        if(!strcmp(command , "decode"))
        {
            decode(input ,k );
        }
        if(!strcmp(command , "encode"))
        {
            encode(input ,k );
        }
        fprintf(out_file ,"%s" , input );
    }
    fclose(in_file);
    fclose(out_file);
    return 1;
}

