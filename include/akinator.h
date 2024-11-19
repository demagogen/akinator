#ifndef AKINATOR_H_
#define AKINATOR_H_

#include "akinator_typedefs.h"

void start_print  ();
void end_print    ();
void options_print();

AKINATOR_ERROR parse_user_choice(TREE* tree, NODE* node);
AKINATOR_ERROR game             (TREE* tree, NODE* node);

#endif
