#include "akinator.h"

void start_print()
{
    graphic_printf(BLUE, BOLD, "Hello\nThis is the Akinator\n");
    graphic_printf(GREEN, BOLD, "\n\n");
}

void options_print()
{
    graphic_printf(BLUE, BOLD, "Choose option\n");

    graphic_printf(MAGENTA, BOLD, "  Guess object: g        \n");
    graphic_printf(MAGENTA, BOLD, "  Read base: r           \n");
    graphic_printf(MAGENTA, BOLD, "  Show base: b           \n");
    graphic_printf(MAGENTA, BOLD, "  Give definition: d     \n");
    graphic_printf(MAGENTA, BOLD, "  Compare definitions: c \n");
    graphic_printf(MAGENTA, BOLD, "  Exit: e                \n");
}

void end_print()
{
    graphic_printf(BLUE, BOLD, "Goodbye :-(\n");
}

AKINATOR_ERROR parse_user_choice(TREE* tree, NODE* node)
{
    char user_choice = 0;

    scanf(" %c", &user_choice);

    switch(user_choice)
    {
        case 'G':
        case 'g':
        {
            game(tree, tree->root);
            break;
        }

        case 'B':
        case 'b':
        {
            tree_graphic_dump(tree);
            break;
        }

        case 'R':
        case 'r':
        {
            graphic_printf(YELLOW, BOLD, "Enter file name with base for your tree:\n");

            char file_name[MaxFileNameSize] = {};
            scanf("%s", file_name);

            FILE* file = fopen(file_name, "r");
            tree_read(file, tree, tree->root);
            tree_graphic_dump(tree);

            fclose(file);
            break;
        }

        case 'D':
        case 'd':
        {

            break;
        }

        case 'C':
        case 'c':
        {
            break;
        }

        case 'E':
        case 'e':
        {
            return AKINATOR_NONE;
            break;
        }

        default:
        {
            graphic_printf(RED, BOLD, "Invalid option. Try again\n");
            static int tries = 0;
            tries++;

            if (tries == TriesQuantity)
            {
                graphic_printf(RED, BOLD, "To much tries. Goodbye\n");
                break;
            }

            __fpurge(stdin); // maybe UB (fflush(stdin) - abs UB)
            parse_user_choice(tree, node);
            break;
        }
    }

    return AKINATOR_NONE;
}

AKINATOR_ERROR game(TREE* tree, NODE* node)
{printf("in game\n");
    assert(tree);

    while (node->right && node->left)
    {printf("\tin while cycle\n");
        graphic_printf(YELLOW, BOLD, "%s?\n", node->element);
        graphic_printf(BLUE,   BOLD, "Enter (Y/N): ");

        char user_answer = 0;
        scanf(" %c", &user_answer);

        if (is_answer_yes(user_answer))
        {
            node = node->right;
        }
        else if (is_answer_no(user_answer))
        {
            node = node->left;
        }
        else
        {
            graphic_printf(RED, BOLD, "Invalid user answer =_=\n");
        }
    }
    if (tree->capacity == 0)
    {printf("\t !tree->root\n");
        graphic_printf(CYAN, BOLD, "Wanna add element?\n");
        graphic_printf(CYAN, BOLD, "Enter (Y/N): ");

        char user_wish_add_answer = 0;
        scanf(" %c", &user_wish_add_answer);

        if (is_answer_yes(user_wish_add_answer))
        {
            graphic_printf(CYAN, BOLD, "Enter new statement\n");

            char new_statement[MaxElementSize] = {};
            scanf(" %s[^\n]", new_statement);

            tree_add(tree, tree->root, ROOT, new_statement);
        }
        else
        {
            graphic_printf(CYAN, BOLD, "Nu kak hochesh\n");
        }
    }
    else
    {
        graphic_printf(YELLOW, BOLD, "%s?\n", node->element);
        graphic_printf(BLUE,   BOLD, "Enter (Y/N): ");

        char user_answer = 0;
        scanf(" %c", &user_answer);

        if (is_answer_yes(user_answer))
        {
            graphic_printf(YELLOW, BOLD, "I guessed\n%s\n", node->element);
        }
        else if (is_answer_no(user_answer))
        {
            graphic_printf(YELLOW, BOLD, "Wanna add new statement?\n");
            graphic_printf(YELLOW, BOLD, "Enter (Y/N): ");

            char user_wanna_add_answer = 0; printf("error here here here\n");
            scanf(" %c", &user_wanna_add_answer); printf("error after this this this\n");

            if (is_answer_yes(user_wanna_add_answer))
            {
                graphic_printf(CYAN, BOLD, "Enter new statement\n");

                char new_statement[MaxElementSize] = {};
                scanf(" %s[^\n]", new_statement);

                tree_add(tree, node, LEFT, node->element); // TODO ebanaya huynya
                node->element = new_statement;
            }
            else if (is_answer_no(user_wanna_add_answer))
            {
                graphic_printf(CYAN, BOLD, "nu kak hochesh, clown\n");
            }
            else
            {
                graphic_printf(RED, BOLD, "zaebal\n");
            }
        }
    }

    options_print();
    parse_user_choice(tree, tree->root);

    return AKINATOR_NONE;
}

bool is_answer_yes(char answer)
{
    return (answer == 'y' || answer == 'Y');
}

bool is_answer_no(char answer)
{
    return (answer == 'n' || answer == 'N');
}

bool is_last_node(NODE* node)
{
    return (!node->left || !node->right);
}

TREE_UTILS which_side(char answer)
{
    if (is_answer_yes(answer))
    {
        return RIGHT;
    }
    else if (is_answer_no(answer))
    {
        return LEFT;
    }
    else
    {
        return TREE_POISON;
    }
}
