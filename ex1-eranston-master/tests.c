#include "tests.h"
#include <string.h>
#include <stdio.h>

#define K_1 3
#define K_2 2
#define K_3 -1
#define K_4 -3
#define K_5 29

// See full documentation in header file
int test_encode_non_cyclic_lower_case_positive_k ()
{
   char in[] = "abc";
   char out[] = "def";
   encode (in, K_1);

   return (strcmp(in, out) != 0);
}

// See full documentation in header file
int test_encode_cyclic_lower_case_special_char_positive_k ()
{
    char in[] = "abz, abz!";
    char out[] = "cdb, cdb!";
    encode (in, K_2);
    return (strcmp(in, out) != 0);

}

// See full documentation in header file
int test_encode_non_cyclic_lower_case_special_char_negative_k ()
{
    char in[] = "def!. , ";
    char out[] = "cde!. , ";
    encode (in, K_3);
    return (strcmp(in, out) != 0);
}

// See full documentation in header file
int test_encode_cyclic_lower_case_negative_k ()
{
    char in[] = "bce!. , ";
    char out[] = "yzb!. , ";
    encode (in, K_4);
    return (strcmp(in, out) != 0);
}

// See full documentation in header file
int test_encode_cyclic_upper_case_positive_k ()
{
    char in[] = "DEF!. , ";
    char out[] = "GHI!. , ";
    encode (in, K_5);
    return (strcmp(in, out) != 0);
}


// See full documentation in header file
int test_decode_non_cyclic_lower_case_positive_k ()
{
    char out[] = "abc";
    char in[] = "def";
    decode (in, K_1);

    return (strcmp(in, out) != 0);
}

// See full documentation in header file
int test_decode_cyclic_lower_case_special_char_positive_k ()
{
    char out[] = "abz, abz!";
    char in[] = "cdb, cdb!";
    decode (in, K_2);
    return (strcmp(in, out) != 0);
}

// See full documentation in header file
int test_decode_non_cyclic_lower_case_special_char_negative_k ()
{
    char out[] = "def!. , ";
    char in[] = "cde!. , ";
    decode (in, K_3);
    return (strcmp(in, out) != 0);
}

// See full documentation in header file
int test_decode_cyclic_lower_case_negative_k ()
{
    char out[] = "bce!. , ";
    char in[] = "yzb!. , ";
    decode (in, K_4);
    return (strcmp(in, out) != 0);
}

// See full documentation in header file
int test_decode_cyclic_upper_case_positive_k ()
{
    char out[] = "DEF!. , ";
    char in[] = "GHI!. , ";
    decode (in, K_5);
    return (strcmp(in, out) != 0);
}
