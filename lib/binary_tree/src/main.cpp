#include "binary_tree.h"
#include "binary_tree_log.h"
#include "../lib/kalatushkin/text_data.h"

int main()
{
    TREE treeInfo = {};
    NODE* nodeInfo = {};

    tree_ctor(&treeInfo);
    // tree_add(&treeInfo, treeInfo.root, ROOT, "hello");
    // tree_add(&treeInfo, treeInfo.root, RIGHT, "take it");
    // tree_add(&treeInfo, treeInfo.root, LEFT, "Goblin");
    // nodeInfo = treeInfo.root->left;
    // tree_add(&treeInfo, nodeInfo, LEFT, "Help");
    // tree_add(&treeInfo, nodeInfo, RIGHT, "I can do it my own )");

    FILE* file = fopen("save_base.txt", "r");

    tree_read(file, &treeInfo, treeInfo.root);

    tree_graphic_dump(&treeInfo);

    // FILE* save_file = fopen("save_base.txt", "w+");
    // tree_save(save_file, &treeInfo, treeInfo.root);
    tree_dtor(&treeInfo);

    // fclose(save_file);
    fclose(file);

    return 0;
}
