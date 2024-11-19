#include "binary_tree.h"
#include "../lib/kalatushkin/text_data.h"

TREE_ERROR tree_ctor(TREE* treeInfo)
{
    assert(treeInfo);

    treeInfo->capacity = StartCapacity;

    treeInfo->root = (NODE* ) calloc(1, sizeof(NODE));

    treeInfo->root->left   = NULL;
    treeInfo->root->right  = NULL;
    treeInfo->root->parent = NULL;
    treeInfo->root->side   = CLEAR;

    treeInfo->error = TREE_NONE;

    return treeInfo->error;
}

TREE_ERROR tree_dtor(TREE* treeInfo)
{
    assert(treeInfo);

    treeInfo->capacity = TREE_POISON;

    treeInfo->root->left   = NULL;
    treeInfo->root->right  = NULL;
    treeInfo->root->parent = NULL;

    treeInfo->error = TREE_DED_INSIDE;

    return treeInfo->error;
}

NODE* tree_node_ctor(NodeElem_t element)
{
    assert(element);

    NODE* newNodeInfo = (NODE* ) calloc(1, sizeof(NODE));

    newNodeInfo->element = element;

    newNodeInfo->parent  = NULL;
    newNodeInfo->left    = NULL;
    newNodeInfo->right   = NULL;

    return newNodeInfo;
}

TREE_ERROR tree_add(TREE* treeInfo, NODE* parentNodeInfo, TREE_UTILS add_rule, NodeElem_t element)
{
    assert(treeInfo);
    // assert(parentNodeInfo);

    if (parentNodeInfo == NULL)
    {
        treeInfo->error = TREE_NODE_ALLOCATION_ERROR;

        return treeInfo->error;
    }

    switch(add_rule)
    {
        case(RIGHT):
            parentNodeInfo->right = tree_node_ctor(element);
            parentNodeInfo->right->parent = parentNodeInfo;
            parentNodeInfo->right->side   = RIGHT;
            break;

        case(LEFT):
            parentNodeInfo->left = tree_node_ctor(element);
            parentNodeInfo->left->parent = parentNodeInfo;
            parentNodeInfo->left->side   = LEFT;
            break;

        case(ROOT):
            treeInfo->root->element = element;
            treeInfo->root->side    = ROOT;

        default:
            return TREE_ERROR_SIDE;
    }

    treeInfo->capacity++;

    return treeInfo->error;
}

TREE_ERROR tree_node_dtor(NODE* nodeInfo)
{
    assert(nodeInfo);

    if (!nodeInfo)
    {
        return TREE_NODE_ALLOCATION_ERROR;
    }

    nodeInfo->right   = NULL;
    nodeInfo->left    = NULL;
    nodeInfo->parent  = NULL;
    nodeInfo->element = NULL;

    return TREE_NONE;
}

TREE_ERROR tree_save(FILE* file, TREE* treeInfo, NODE* nodeInfo)
{
    assert(treeInfo);

    if (!nodeInfo)
    {
        treeInfo->error = TREE_NULL_NODE;

        return treeInfo->error;
    }

    fprintf(file, "{\n");
    fprintf(file, "%s\n", nodeInfo->element);

    if (nodeInfo->left)
    {
        tree_save(file, treeInfo, nodeInfo->left);
    }
    if (nodeInfo->right)
    {
        tree_save(file, treeInfo, nodeInfo->right);
    }

    fprintf(file, "}\n");

    return treeInfo->error;
}

TREE_ERROR tree_read(FILE* file, TREE* treeInfo, NODE* nodeInfo)
{
    assert(treeInfo);

    TEXT_DATA textInfo = {};
    count_symbols(file, &textInfo);
    fill_text    (file, &textInfo);

    char* element = NULL;
    char* base_ip = textInfo.text;
    char* end_base_pointer = textInfo.text + textInfo.digits - 1;

    while (base_ip < end_base_pointer)
    {
        if (*base_ip == '{')
        {
            base_ip++;
            read_line(&element, &base_ip);
            base_ip++;

            if (!nodeInfo)
            {
                tree_add(treeInfo, nodeInfo, ROOT, element);
                nodeInfo = treeInfo->root;
            }
            else if (!nodeInfo->left)
            {
                tree_add(treeInfo, nodeInfo, LEFT, element);
                nodeInfo = nodeInfo->left;
            }
            else
            {
                tree_add(treeInfo, nodeInfo, RIGHT, element);
                nodeInfo = nodeInfo->right;
            }
        }
        else if (*base_ip == '}')
        {
            base_ip++;

            if (nodeInfo == treeInfo->root)
            {
                break;
            }

            nodeInfo = nodeInfo->parent;
        }
    }

    return treeInfo->error;
}

int read_line(char** line, char** base_ip)
{
    if (!base_ip)
    {
        return -1;
    }

    *line = *base_ip;
    size_t offset = 0;
    while (*(*base_ip + 1) != '{' && *(*base_ip + 1) != '}')
    {
        (*line)[offset] = **base_ip;
        (*base_ip)++;
        offset++;
    }
    *(*line + offset) = '\0';

    return 0;
}
