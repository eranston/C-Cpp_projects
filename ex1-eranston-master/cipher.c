#include "cipher.h"
#include "string.h"
#define LOWER_CASE 2
#define UPPER_CASE 3
#define NONEALPHBET 4
#define RIGHT 5
#define LEFT 6
#define LOWER_CASE_A 97
#define UPPER_CASE_A 65
#define UPPER_CASE_Z 90
#define LOWWER_CASE_Z 122
#define ALPHABET_LENGTH 26

/// IN THIS FILE, IMPLEMENT EVERY FUNCTION THAT'S DECLARED IN cipher.h.

int check_capital_or_lower_case(char c);
char change_letter(char s[] , int k , int i , int side);

// See full documentation in header file
void encode (char s[], int k)

{
    int side = RIGHT;
    size_t i = 0;
    size_t n = strlen(s);
    if(k <0)
    {
        k = ((k*(-1)) % ALPHABET_LENGTH) * (-1);
        side = LEFT;
    }
    else
    {
        k = k%ALPHABET_LENGTH;
    }
    while(i < n)
    {

        char new_letter = change_letter(s , k , i , side);
        s[i] = new_letter;
        i++;
        }



}

// See full documentation in header file
void decode (char s[], int k)
{
    int side = LEFT;
    size_t i = 0;
    size_t n = strlen(s);

    if(k <0)
    {
        k = ((k * (-1)) % ALPHABET_LENGTH) * (-1);
        side = RIGHT;
    }
    else
    {
        k = k%ALPHABET_LENGTH;
    }
    k = -k;
    while(i < n)
    {

        char new_letter = change_letter(s , k , i , side);
        s[i] = new_letter;
        i++;
    }

}

char change_letter(char s[] , int k , int i , int side)
{
    //encode a letter to the letter that represent her after k moves

    int type_of_char = check_capital_or_lower_case(s[i]);
    // check if the char in index i is capital case ,
    // lower case or none alphabet

    if (type_of_char == UPPER_CASE || type_of_char == LOWER_CASE)
    {

        char new_char = (s[i] + k);
        // change the char in index i to the encoded char
        int new_type_of_char = check_capital_or_lower_case(new_char);
        // check if the new encoded char is in upper case ,
        // lower case or none alphabet
        if (new_type_of_char != type_of_char)
        {
            // if the new encoded char suppressed the alphabet cycle
            if(side == RIGHT)
            {
                new_char = new_char - ALPHABET_LENGTH;
            }
            if(side == LEFT)
            {
                new_char = new_char + ALPHABET_LENGTH;
            }


        }


        return new_char;
    }

    // if the char isnt in the alphabet then return the same char
    return s[i];
}


int check_capital_or_lower_case(char c)
{
    // check if a given char is lowercase or appercase in the alphabet
    if (c >= UPPER_CASE_A && c <=UPPER_CASE_Z)
    {
        return UPPER_CASE;
    }
    if (c>= LOWER_CASE_A && c<=LOWWER_CASE_Z)
    {
        return LOWER_CASE;
    }
    return NONEALPHBET;
}

