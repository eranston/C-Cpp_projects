#include <string.h> // For strlen(), strcmp(), strcpy()
#include "markov_chain.h"

#define MAX(X, Y) (((X) < (Y)) ? (Y) : (X))
#define DECIMAL_BASE 10
#define EMPTY -1
#define BOARD_SIZE 100
#define MAX_GENERATION_LENGTH 60
#define ARGUMENTS_ERROR_MSG "USAGEneed to have 2 arguments"
#define LAST_CELL 100
#define DICE_MAX 6
#define NUM_OF_TRANSITIONS 20
#define ALLOCATION_MSG "Allocation failure: "

 /**
  * @breif check if the g_data is a last in chain , if cell is last (number
  * 100 cell)
  * @param g_data void* that is a pointer to cell struct
  * @return true if is last cell , false if not
  */
static bool is_last_cell(void* g_data);

/**
 * @breif function the copy a given void* (that is a pointer to cell)
 * (allocate memory)
 * @param g_data void* that is a pointer to cell struct
 * @return void* a pointer to allocated cell , and Null if allocation problem
 */
static void* copy_func_cell(void* g_data);

/**
 * @brief fucntion that free pointer to cell
 * @param g_data void* that is a pointer to cell struct
 * @return void
 */
static void free_data_cell(void* g_data);

/**
 * @brief function that compare 2 cells to check if they are identical
 * @param g_data_1 pointer to cell struct
 * @param g_data_2 pointer to cell struct
 * @return 0 if are the same , double otherwise
 */
static double comp_func_cell(void* g_data_1 , void* g_data_2);

/**
 * @brief function that print a cell
 * @param g_data pointer to cell
 * @return void
 */
static void print_cell(void* g_data);

/**
 * @brief inistilaze the srand function
 * @param argv the arguments that the main gets , there is the seed
 * @return void
 */
static void inisilaize(char* argv[]);

/**
 * @brief function that create markov_chain allocate the memory needed
 * @return pointer to markov_chain that go allocated
 */
static MarkovChain* create_markov_chain_snl();

/**
 * @brief function that create n random sqequences and print them
 * @param num_of_tweets the number of random sequnces
 * @param i the number of sequnces that got created so far
 * @param markov_chain the markovchain we get the sequnces from
 */
static void create_random_sequence_snl(int* num_of_tweets , int* i
        , MarkovChain* markov_chain);





/**
 * represents the transitions by ladders and snakes in the game
 * each tuple (x,y) represents a ladder from x to if x<y or a snake otherwise
 */
const int transitions[][2] = {{13, 4},
                              {85, 17},
                              {95, 67},
                              {97, 58},
                              {66, 89},
                              {87, 31},
                              {57, 83},
                              {91, 25},
                              {28, 50},
                              {35, 11},
                              {8,  30},
                              {41, 62},
                              {81, 43},
                              {69, 32},
                              {20, 39},
                              {33, 70},
                              {79, 99},
                              {23, 76},
                              {15, 47},
                              {61, 14}};

/**
 * struct represents a Cell in the game board
 */
typedef struct Cell {
    int number; // Cell number 1-100
    int ladder_to;  // ladder_to represents the jump of the ladder in case
    // there is one from this square
    int snake_to;  // snake_to represents the jump of the snake in case there
    // is one from this square
    //both ladder_to and snake_to should be -1 if the Cell doesn't have them
} Cell;

/** Error handler **/
static int handle_error(char *error_msg, MarkovChain **database)
{
    printf("%s", error_msg);
    if (database != NULL)
    {
        free_markov_chain(database);
    }
    return EXIT_FAILURE;
}


static int create_board(Cell *cells[BOARD_SIZE])
{
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        cells[i] = malloc(sizeof(Cell));
        if (cells[i] == NULL)
        {
            for (int j = 0; j < i; j++) {
                free(cells[j]);
            }
            handle_error(ALLOCATION_ERROR_MASSAGE,NULL);
            return EXIT_FAILURE;
        }
        *(cells[i]) = (Cell) {i + 1, EMPTY, EMPTY};
    }

    for (int i = 0; i < NUM_OF_TRANSITIONS; i++)
    {
        int from = transitions[i][0];
        int to = transitions[i][1];
        if (from < to)
        {
            cells[from - 1]->ladder_to = to;
        }
        else
        {
            cells[from - 1]->snake_to = to;
        }
    }
    return EXIT_SUCCESS;
}

/**
 * fills database
 * @param markov_chain
 * @return EXIT_SUCCESS or EXIT_FAILURE
 */
static int fill_database(MarkovChain *markov_chain)
{
    Cell* cells[BOARD_SIZE];
    if(create_board(cells) == EXIT_FAILURE)
    {
        return EXIT_FAILURE;
    }
    MarkovNode *from_node = NULL, *to_node = NULL;
    size_t index_to;
    for (size_t i = 0; i < BOARD_SIZE; i++)
    {
        add_to_database(markov_chain, cells[i]);
    }

    for (size_t i = 0; i < BOARD_SIZE; i++)
    {
        from_node = get_node_from_database(markov_chain,cells[i])->data;

        if (cells[i]->snake_to != EMPTY || cells[i]->ladder_to != EMPTY)
        {
            index_to = MAX(cells[i]->snake_to,cells[i]->ladder_to) - 1;
            to_node = get_node_from_database(markov_chain, cells[index_to])
                    ->data;
            add_node_to_counter_list(from_node, to_node, markov_chain);
        }
        else
        {
            for (int j = 1; j <= DICE_MAX; j++)
            {
                index_to = ((Cell*) (from_node->data))->number + j - 1;
                if (index_to >= BOARD_SIZE)
                {
                    break;
                }
                to_node = get_node_from_database(markov_chain, cells[index_to])
                        ->data;
                add_node_to_counter_list(from_node, to_node, markov_chain);
            }
        }
    }
    // free temp arr
    for (size_t i = 0; i < BOARD_SIZE; i++)
    {
        free(cells[i]);
    }
    return EXIT_SUCCESS;
}

/**
 * @param argc num of arguments
 * @param argv 1) Seed
 *             2) Number of sentences to generate
 * @return EXIT_SUCCESS or EXIT_FAILURE
 */
int main(int argc, char *argv[])
{
    if(argc != 3)
    {
        printf(ARGUMENTS_ERROR_MSG);
        return EXIT_FAILURE;
    }
    else
    {
    int number_of_pathes = strtol(argv[2], NULL , DECIMAL_BASE);
    inisilaize(argv);
    MarkovChain* markov_chain = create_markov_chain_snl();
    if(!markov_chain)
    {
        free_markov_chain(&markov_chain);
        printf(ALLOCATION_ERROR_MASSAGE);
        return EXIT_FAILURE;
    }
    fill_database(markov_chain);
    int i = 1;
    while(number_of_pathes > 0)
    {
        create_random_sequence_snl(&number_of_pathes , &i , markov_chain);
    }
    free_markov_chain(&markov_chain);
    }

    return EXIT_SUCCESS;
}


static void inisilaize(char* argv[])
{
    unsigned long seed = strtol(argv[1], NULL , DECIMAL_BASE);
    srand(seed);
}



static LinkedList* create_new_linked_list_snl()
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


static MarkovChain* create_markov_chain_snl()
{
    MarkovChain * markov_chain = malloc(sizeof(MarkovChain));

    if(!markov_chain)
    {
        return NULL;
    }
    markov_chain->database = create_new_linked_list_snl();

    if(!markov_chain->database)
    {
        return NULL;
    }
    markov_chain->comp_func = comp_func_cell;
    markov_chain->copy_func = copy_func_cell;
    markov_chain->free_data = free_data_cell;
    markov_chain->print_func = print_cell;
    markov_chain->is_last = is_last_cell;
    return markov_chain;
}



static void print_cell(void* g_data)
{
    Cell* cell = g_data;
    printf("[%d]" , cell->number);
    if(cell->snake_to != -1)
    {
        printf("-snake to %d" , cell->snake_to);
    }
    else if(cell->ladder_to != -1)
    {
        printf("-ladder to %d" , cell->ladder_to);
    }

    if(!is_last_cell(cell))
    {
        printf(" -> ");
    }
}

static double comp_func_cell(void* g_data_1 , void* g_data_2)
{
    Cell * c_data_1 =  g_data_1;
    Cell * c_data_2 =  g_data_2;
    return c_data_1->number - c_data_2->number;

}

static void free_data_cell(void* g_data)
{
    Cell * s_data = g_data;
    free(s_data);
}

static void* copy_func_cell(void* g_data)
{
    Cell* s_data = g_data;
    Cell* copy_cell = malloc(sizeof(Cell));
    if(!copy_cell)
    {
        return NULL;
    }
    copy_cell->number = s_data->number;
    copy_cell->snake_to = s_data->snake_to;
    copy_cell->ladder_to  = s_data->ladder_to;
    return copy_cell;
}

static bool is_last_cell(void* g_data)
{
    Cell* cell = g_data;
    if(cell->number == LAST_CELL)
    {
        return true;
    }
    return false;
}

static void create_random_sequence_snl(int* num_of_tweets , int* i
        , MarkovChain* markov_chain)
{
    printf("Random Walk %d: ", *i);
    generate_random_sequence(markov_chain,
                             markov_chain->database->first->data
                             , MAX_GENERATION_LENGTH);
    printf("\n");
    (*i)++;
    (*num_of_tweets)--;
}

