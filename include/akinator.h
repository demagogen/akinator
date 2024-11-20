#ifndef AKINATOR_H_
#define AKINATOR_H_

#include "akinator_typedefs.h"

/* Print functions */
void start_print  ();
void end_print    ();
void options_print();

/* parsing functions */
AKINATOR_ERROR parse_user_choice(TREE* tree, NODE* node);

/* Game functions */ /* TODO utils */
AKINATOR_ERROR game          (TREE* tree, NODE* node);
AKINATOR_ERROR game_add      (TREE* tree, NODE* node, char answer, NodeElem_t element);
bool           is_answer_yes (char answer);
bool           is_answer_no  (char answer);
bool           is_last_node  (NODE* node);
TREE_UTILS     which_side    (char answer);

#endif
