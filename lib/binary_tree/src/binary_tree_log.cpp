#include "binary_tree_log.h"

void tree_graphic_dump(TREE* treeInfo)
{
    assert(treeInfo);

    FILE* dotfile = fopen("dotfile.gv", "wb");

    fprintf(dotfile, "digraph {bgcolor=\"#696969\" rankdir = TB\n");

    fprintf(dotfile, "Info[shape=Mrecord,"
                     "style=filled,"
                     "fillcolor=\"grey\","
                     "label=\"capacity: %d\","
                     "fontcolor = \"black\","
                     "fontsize = 14];\n\n",
                      treeInfo->capacity);

    size_t index = 0;
    node_graphic_dump(dotfile, &index, treeInfo->root);

    fprintf(dotfile, "\n}");

    fclose(dotfile);
}

void node_graphic_dump (FILE* dotfile, size_t* index, NODE* nodeInfo)
{
    assert(nodeInfo);
    assert(dotfile);

    node_print_node(dotfile, index, nodeInfo);

    size_t current_node_index = *index;

    if (nodeInfo->left)
    {
        node_print_edge(dotfile, current_node_index, ++(*index), nodeInfo->left);
        node_graphic_dump(dotfile, index, nodeInfo->left);
    }
    if (nodeInfo->right)
    {
        node_print_edge(dotfile, current_node_index, ++(*index), nodeInfo->right);
        node_graphic_dump(dotfile, index, nodeInfo->right);
    }
}

void node_print_node (FILE* dotfile, size_t* index, NODE* nodeInfo)
{
    assert(nodeInfo);
    assert(dotfile);

    fprintf(dotfile, "node%d[shape=Mrecord, "
                     "style=filled, "
                     "fillcolor=\"grey\", "
                     "label=\" "
                     "{address: %p "
                     "| type:   %d "
                     "| parent: %p "
                     "| left:   %p "
                     "| right:  %p "
                     "| element: %s}\"];  \n\n",
                     *index,
                     nodeInfo,
                     nodeInfo->side,
                     nodeInfo->parent,
                     nodeInfo->left,
                     nodeInfo->right,
                     nodeInfo->element);
}

void node_print_edge(FILE* dotfile, size_t first_node_index, size_t second_node_index, NODE* nodeInfo)
{
    assert(dotfile);
    assert(nodeInfo);

    fprintf(dotfile, "node%d->node%d"
                     "[color = \"grey\"];\n",
                      first_node_index,
                      second_node_index);
}
