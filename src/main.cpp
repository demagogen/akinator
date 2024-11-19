#include "akinator.h"

int main()
{
    TREE tree = {};
    tree_ctor(&tree);
    printf("main: tree address: %p\n", tree);

    start_print();
    options_print();

    parse_user_choice(&tree, tree.root);

    return 0;
}
