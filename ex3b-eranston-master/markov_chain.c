//
// Created by 1eran on 17/04/2022.
//



#include "markov_chain.h"
#include <stdlib.h>
#include <string.h>
#include "linked_list.h"
#define WORD_BUFFER 1000




 /**
  * @breif free a given node and all other items in node that need to be free
  * @param pointer to Node
  * @return void
  */
void free_node(Node* node , MarkovChain* markov_chain);

/**
  * @breif free markov node and all its content
  * @param pointer to markovnode
  * @return void
  */
void free_markov_node(MarkovNode* m_node , MarkovChain* markov_chain);

/**
  * @breif get a pointer to markov node and return the sum of all the
  * frequencys of the nextnodecoubnter list
  * @param pointer to markov node
  * @return sum of all the frequencys
  */
int add_all_frequency(MarkovNode* m_node);

/**
  * @breif create markove node , allocate memory for him and set list_counter
  * to Null and list_len to 0
  * @param void, no parameters needed
  * @return pointer allocated memory for markov node
  */
MarkovNode* create_markov_node();

/**
  * @breif create NewNodeCounter , add the second node to it , and add the
  * NewNodeCounter to the NewNodeCounter list of the first node.
  * aware the function allocate/reallocate memory as needed to add the node
  * @param second_node the node we want to add to the NewNodeCounter list of
  * the first_node
  * @return true if succeded and false if memory allocation error
  */
bool add_new_next_node_counter(MarkovNode *first_node
                               , MarkovNode *second_node);

/**
* Get random number between 0 and max_number [0, max_number).
* @param max_number maximal number to return (not including)
* @return Random number
*/
int get_random_number(int max_number)
{
    return rand() % max_number;
}

void free_list_counter(NextNodeCounter* list);


MarkovNode* get_first_random_node(MarkovChain *markov_chain)
{
    if(markov_chain->database->first == NULL)
    {
        return NULL;
    }
    int rand_number =
            get_random_number(markov_chain->database->size);
    bool bad_string = true;
    while (bad_string)
    {
        Node* node_runner = markov_chain->database->first;
        while (rand_number > 0)
        {
            node_runner = node_runner->next;
            rand_number--;
        }
        MarkovNode *m_node = node_runner->data;
        if (!m_node->last)
        {
            return m_node;
        }
        rand_number =
                get_random_number(markov_chain->database->size);
    }
    return NULL;
}



MarkovNode* get_next_random_node (MarkovNode
                                  *state_struct_ptr)
{

    NextNodeCounter* list = state_struct_ptr->list_counter;
    if(list == NULL)
    {
        return NULL;
    }
    int rand_number = get_random_number
            (add_all_frequency(state_struct_ptr));
    int index = 0;
    while(rand_number>=0)
    {
        NextNodeCounter* node_c = (list+index);
        rand_number -= node_c->frequency;
        index++;
    }
    if(rand_number == 0&& index == 0)
    {
        return list->node_markov;
    }

    return (list+index-1)->node_markov;
}

void generate_random_sequence (MarkovChain *markov_chain,
                               MarkovNode *first_node, int max_length)
{
    if(first_node == NULL)
    {
        first_node = get_first_random_node(markov_chain);
    }
    while(markov_chain->is_last(first_node->data))
    {
        first_node = get_first_random_node(markov_chain);
    }
    MarkovNode * next_node = first_node;

    while(max_length > 0 &&  next_node != NULL)
    {
        markov_chain->print_func(next_node->data);
        next_node = get_next_random_node(next_node);
        max_length--;
    }
}


bool add_node_to_counter_list(MarkovNode *first_node, MarkovNode *second_node,
                              MarkovChain * markov_chain)
{
    if(first_node->list_counter == NULL)
    {
        bool result = add_new_next_node_counter(first_node, second_node);
        return result;
    }
    NextNodeCounter* n_n_c_list = first_node->list_counter;
    int index = 0;
    while(index < first_node->list_len)
    {
        void* data_1 = (n_n_c_list+index)->node_markov->data;
        void* data_2 = second_node->data;
        if(markov_chain->comp_func(data_1 , data_2) == 0)
        {
            (n_n_c_list+index)->frequency++;
            return true;
        }
        index++;
    }

    return add_new_next_node_counter(first_node, second_node);
}

bool add_new_next_node_counter(MarkovNode *first_node, MarkovNode *second_node)
{
    NextNodeCounter* n_n_c_list = first_node->list_counter;
    int list_len = first_node->list_len;
    if(n_n_c_list == NULL)
    {
        n_n_c_list  = malloc(sizeof(NextNodeCounter));
        if(!n_n_c_list)
        {
            return false;
        }
    }
    else
    {
        NextNodeCounter* temp_p = realloc(n_n_c_list
                ,((list_len + 1) * sizeof(NextNodeCounter)));
        if(!temp_p)
        {
            free(n_n_c_list);
            return false;
        }
        n_n_c_list = temp_p;
    }
    list_len++;
    first_node->list_len = list_len;
    (n_n_c_list + list_len - 1) ->node_markov = second_node;
    (n_n_c_list + list_len - 1) -> frequency = 1;
    first_node->list_counter = n_n_c_list;
    return true;
}



Node* add_to_database(MarkovChain *markov_chain, void *data_ptr)
{
   Node * result = get_node_from_database(markov_chain , data_ptr);
   if(result != NULL)
   {
       return result;
   }
    LinkedList *p = markov_chain->database;

    void* data = markov_chain->copy_func(data_ptr);
    if(!data)
    {
        return NULL;
    }

    MarkovNode* m_node = create_markov_node();
    if(!m_node)
    {
        return NULL;
    }
    m_node->data = data;
    int result_1 = add(p, m_node);
    if(result_1)
    {
        return NULL;
    }

    return p->last;

}

Node* get_node_from_database(MarkovChain *markov_chain, void *data_ptr)
{
    LinkedList* linked_list = markov_chain->database;
    Node* temp_node = linked_list->first;
    if(temp_node == NULL)
    {
        return NULL;
    }

    while(temp_node != NULL)
    {
        MarkovNode* markov_node = temp_node->data;
        if(!markov_chain->comp_func(data_ptr , markov_node->data))
        {
            return temp_node;
        }
        temp_node= temp_node->next;
    }
    return NULL;
}

void free_markov_chain(MarkovChain ** ptr_chain)
{
    if(*ptr_chain != NULL)
    {
      if((*ptr_chain)->database == NULL)
      {
          free((*ptr_chain));
          return;
      }
      Node* cur_node = (*ptr_chain)->database->first;

      while(cur_node != NULL)
      {
        Node* temp_node = cur_node->next;
        free_node(cur_node , *ptr_chain);
        cur_node= temp_node;
      }
    }
    free((*ptr_chain)->database);
    (*ptr_chain)->database = NULL;
    free(*ptr_chain);
    *ptr_chain =NULL;

}

void free_node(Node* node , MarkovChain* markov_chain)
{
    free_markov_node(node->data , markov_chain);
    free(node);
}

void free_markov_node(MarkovNode* m_node, MarkovChain* markov_chain)
{
    markov_chain->free_data(m_node->data);
    m_node->data = NULL;
    NextNodeCounter* m_node_list_counter = m_node->list_counter;
    free_list_counter(m_node_list_counter);
    free(m_node);
    m_node = NULL;
}

void free_list_counter(NextNodeCounter* list)
{
  free(list);
}

MarkovNode* create_markov_node()
{
    MarkovNode* m_node = malloc(sizeof(MarkovNode));
    if(!m_node)
    {
        return NULL;
    }
    m_node->list_counter = NULL;

    m_node->list_len = 0;
    return m_node;
}

int add_all_frequency(MarkovNode* m_node)
{

    int index = 0;
    NextNodeCounter * runner = m_node->list_counter;
    int sum_frequency = 0;
    while(index < m_node->list_len)
    {
        sum_frequency += (runner+index)->frequency;
        index++;
    }
    return sum_frequency;
}
