#ifndef BINARY_TREE_TYPEDEFS_H_
#define BINARY_TREE_TYPEDEFS_H_

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef char* NodeElem_t;
const size_t MaxElementSize   = 30;

const size_t StartCapacity = 0;

const size_t IpOffsetWithSpace = 2;

enum TREE_UTILS
{
    TREE_POISON      = -1,
    DEFAULT_CAPACITY =  0,
    LEFT             =  1,
    RIGHT            =  2,
    ROOT             =  3,
    CLEAR            =  4,
};

enum TREE_ERROR
{
    TREE_NODE_DED_INSIDE              = -2,
    TREE_DED_INSIDE                   = -1,
    TREE_NONE                         =  0,
    TREE_STRUCT_ALLOCATION_ERROR      =  1,
    TREE_NODE_ALLOCATION_ERROR        =  2,
    TREE_INVALID_CAPACITY             =  3,
    TREE_OVERSIZE                     =  4,
    TREE_MISSING_IP                   =  5,
    TREE_ROOT_ALLOCATION_ERROR        =  6,
    TREE_LEFT_CHILD_ALLOCATION_ERROR  =  7,
    TREE_RIGHT_CHILD_ALLOCATION_ERROR =  8,
    TREE_PARENT_ALLOCATION_ERROR      =  9,
    TREE_INVALID_NODE                 = 10,
    TREE_NODE_NOT_LEAF                = 11,
    TREE_ERROR_SIDE                   = 12,
    TREE_NULL_NODE                    = 13,
};

struct NODE
{
    TREE_UTILS side;
    NODE*      parent;
    NODE*      left;
    NODE*      right;
    NodeElem_t element;
};

struct TREE
{
    NODE*      root;
    size_t     capacity;
    TREE_ERROR error;
};

#endif
