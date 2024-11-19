#ifndef BINARY_TREE_LOG_H_
#define BINARY_TREE_LOG_H_

#include "binary_tree_typedefs.h"

void tree_graphic_dump (TREE* treeInfo);
void node_graphic_dump (FILE* dotfile, size_t* index, NODE* nodeInfo);
void node_print_node   (FILE* dotfile, size_t*  index, NODE* nodeInfo);
void node_print_edge   (FILE* dotfile, size_t first_node_index, size_t  second_node_index, NODE* nodeInfo);

#endif
