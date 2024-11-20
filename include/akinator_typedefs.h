#ifndef AKINATOR_TYPEDEFS_H_
#define AKINATOR_TYPEDEFS_H_

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdio_ext.h> // Vova hate (P.S. maybe)

#include "binary_tree_typedefs.h"
#include "binary_tree.h"
#include "binary_tree_log.h"
#include "color_scheme_changer.h"

const size_t MaxObjectLength = 30;
const char   TriesQuantity   =  3;

const size_t MaxFileNameSize = 30;

enum AKINATOR_UTILS
{
    YES = 1,
    NO  = 2,
};

enum AKINATOR_ERROR
{
    AKINATOR_NONE                  = 0,
    AKINATOR_TREE_ALLOCATION_ERROR = 1,
    AKINATOR_INVALID_INSERT        = 2,
    AKINATOR_INVALID_OPTION        = 3,
    AKINATOR_INVALID_ANSWER        = 4,
    AKINATOR_INVALID_ANSWER_SIDE   = 5,
    AKINATOR_NULL_POINTER_ON_RIGHT = 6,
    AKINATOR_NULL_POINTER_ON_LEFT  = 7,
};

#endif
