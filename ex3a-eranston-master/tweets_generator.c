//
// Created by 1eran on 17/04/2022.
//
#include "markov_chain.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#define NUM_OF_PARAM_ERROR_MSG "Usage: the number of paramaters need to"\
"be 3 or 4."
#define FILE_ERROR_MSG "Error: there is a problem with openinng the file."
#define MEMORY_ERROR_MSG "Allocation failure: memory failure"
#define WORD_BUFFER 1000
#define DECIEMAL_BASE 10
#define THREE_PARAM 4
#define FOUR_PARAM 5
#define ALL_FILE -2
#define MAX_WORDS_IN_TWEETS 20

/**
  * @breif prints if there is error in the number of arguments that are given,
  * and run the correct program to the given arguments
  * @param argc number of arguments that are given
  * @param argv the arguments that are given
  * @return 0 if everything is ok 1 if there is a problem
  */
int check_input_correct(int argc ,char* argv[]);

/**
  * @breif the program that need to be ran if given 4 parameters
  * @param argv the paramaters that are given from users
  * @return 0 if everything is ok , 1 if there is a problem
  */
int four_param_input (char* argv[]);

/**
  * @breif the program that need to be ran if given 3 parameters
  * @param argv the parameters that are given from the user
  * @return 0 if everything is ok , 1 if there is a problem
  */
int three_param_input(char* argv[]);

/**
  * @breif enter a given line from the input file to the database
  * @param input the line that need to be entered to the database
  * @param n pointer to a int of how much words need to be read from the file
  * in total
  * @param markov_chain pointer to MarkovChain that contains the database
  * @param all_file flag if need to read all the file or not
  * @return 0 if everthing is fine, 1 if there is a problem
  */
int enter_line_to_database(char* input ,int* n , MarkovChain* markov_chain
                           , bool all_file);

/**
  * @breif fill the database markovchain , from a given file
  * @param fp file to read from and enter the data to the database
  * @param words_to_read how much words to read from the file
  * @param markov_chain the database we put the data from the file
  * @return void
  */
void fill_database (FILE *fp, int words_to_read, MarkovChain
*markov_chain);

/**
  * @breif create a markovchain
  * @param void
  * @return pointer to allocated markovchain if succeded , NULL if there was
  * memory allocation problem
  */
MarkovChain* create_markov_chain();


/**
  * @breif create linked list
  * @param void
  * @return pointer to allocated linked list is succeded , NULL if there was
  * memory allcoation problem
  */
LinkedList* create_new_linked_list();


/**
  * @breif create random tweet and print it to stdout
  * @param num_of_tweets pointer to num of tweets need to be printed to
  * decrease when print a tweet
  * @param i pointer to the current number of tweet
  * @param markov_chain the database
  * @return void
  */
void create_random_sequence(int* num_of_tweets , int* i
        , MarkovChain* markov_chain);


int main(int argc , char* argv[])
{
    int is_ok = check_input_correct(argc , argv);
    if(is_ok)
    {
        return EXIT_FAILURE;
    }


    return EXIT_SUCCESS;
}



int check_input_correct(int argc ,char* argv[])
{
    if(argc == THREE_PARAM)
    {
        // return EXIT_FAILURE if there is a problem and EXIT_SUCSSES
        // if everything went fine
        return three_param_input(argv);
    }
    if (argc == FOUR_PARAM)
    {
        // return EXIT_FAILURE if there is a problem and EXIT_SUCSSES
        // if everything went fine
        return four_param_input(argv);
    }
    printf(NUM_OF_PARAM_ERROR_MSG);
    return EXIT_FAILURE;
}

int three_param_input(char* argv[])
{
    unsigned int seed = strtol(argv[1], NULL, DECIEMAL_BASE );
    int num_of_tweets = strtol(argv[2], NULL, DECIEMAL_BASE);
    srand(seed);
    char* path = argv[3];
    int num_of_words_read = ALL_FILE;
    MarkovChain * markov_chain = create_markov_chain();
    if(!markov_chain)
    {
        printf(MEMORY_ERROR_MSG);
        return EXIT_FAILURE;
    }
    FILE * ptr = fopen(path , "r");

    if(!ptr)
    {
        free_markov_chain(&markov_chain);
        printf(FILE_ERROR_MSG);
        return EXIT_FAILURE;
    }
    fill_database(ptr , num_of_words_read , markov_chain);
    fclose(ptr);
    if(!markov_chain->database)
    {
        printf(MEMORY_ERROR_MSG);
        return EXIT_FAILURE;
    }
    int i =1;
    while(num_of_tweets > 0)
    {
        create_random_sequence(&num_of_tweets , &i , markov_chain);
    }
    free_markov_chain(&markov_chain);
    free(markov_chain);
    return EXIT_SUCCESS;
}

void create_random_sequence(int* num_of_tweets , int* i
                            , MarkovChain* markov_chain)
{
    printf("Tweet %d: " , *i);
    generate_random_sequence(markov_chain,
    NULL, MAX_WORDS_IN_TWEETS);
    printf("\n");
    (*i)++;
    (*num_of_tweets)--;
}

int four_param_input (char* argv[])
{
    unsigned int seed = strtol(argv[1], NULL, DECIEMAL_BASE );
    int num_of_tweets = strtol(argv[2], NULL, DECIEMAL_BASE);
    srand(seed);
    char* path = argv[3];
    int num_of_words_read = strtol(argv[4],
                                   NULL, DECIEMAL_BASE);;
    MarkovChain * markov_chain = create_markov_chain();
    if(!markov_chain)
    {
        printf(MEMORY_ERROR_MSG);
        return EXIT_FAILURE;
    }
    FILE * ptr = fopen(path , "r");
    if(!ptr)
    {
        free_markov_chain(&markov_chain);
        printf(FILE_ERROR_MSG);
        return EXIT_FAILURE;
    }
    fill_database(ptr , num_of_words_read , markov_chain);
    fclose(ptr);
    if(!markov_chain->database)
    {
      free (markov_chain);
      printf(MEMORY_ERROR_MSG);
      return EXIT_FAILURE;
    }
    int i =1;
    while(num_of_tweets > 0)
    {
      create_random_sequence(&num_of_tweets , &i , markov_chain);
    }
    free_markov_chain(&markov_chain);
    free (markov_chain);
    return EXIT_SUCCESS;
}



LinkedList* create_new_linked_list()
{
    LinkedList* new_linked = malloc(sizeof (LinkedList));
    if(!new_linked)
    {
        return NULL;
    }
    new_linked->first=NULL;
    new_linked->last=NULL;
    new_linked->size=0;
    return new_linked;
}



MarkovChain* create_markov_chain()
{
    MarkovChain * markov_chain = malloc(sizeof(MarkovChain));

    if(!markov_chain)
    {
        return NULL;
    }
    markov_chain->database = create_new_linked_list();

    if(!markov_chain->database)
    {
        free(markov_chain);
        return NULL;
    }
    return markov_chain;
}


void fill_database (FILE *fp, int words_to_read, MarkovChain
*markov_chain)
{
    bool all_file = false;
    char* ptr = NULL;
    char input[WORD_BUFFER];
    ptr = fgets(input ,WORD_BUFFER , fp );
    while(ptr != NULL)
    {
        if(words_to_read == ALL_FILE)
        {
            all_file= true;
        }
        int result = enter_line_to_database(input , &words_to_read
                               , markov_chain ,all_file);
        if(result)
        {
            free_markov_chain(&markov_chain);
            break;
        }
        ptr = fgets(input ,WORD_BUFFER , fp );
    }
}





int enter_line_to_database(char* input ,int* n
                           , MarkovChain* markov_chain, bool all_file)
{
    char word[WORD_BUFFER] ;
    Node* last_node = NULL;
    char* last_node_string = "";
    int index = 0;
    if(all_file)
    {
        *n = 1;
    }
    while ((*input) && (*n)>0)
    {
        while((*input) != ' ' && (*input) != '\n')
        {
            word[index] = (*input);
            input++;
            index++;
        }
        if(index != 0)
        {
            word[index] = '\0';
            if(!all_file)
            {
                *n = (*n) -1;
            }
            Node* new_node = add_to_database(markov_chain , word);
            if(!new_node)
            {
                return 1;
            }
            if(last_node != NULL &&
            (last_node_string[strlen(last_node_string) -1] != '.'))
            {
                bool result = add_node_to_counter_list(last_node->data
                                         , new_node->data);
                if(!result)
                {
                    return 1;
                }
            }
            last_node = new_node;
             last_node_string = last_node->data->data;
            index = 0;
        }
        input++;
    }
    return 0;
}





Node* create_new_node()
{
    Node* new_node = malloc(sizeof(Node));
    if(!new_node)
    {
        return NULL;
    }
    new_node->next = NULL;
    return new_node;
}


