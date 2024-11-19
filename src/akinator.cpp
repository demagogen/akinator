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
            char* file_name = NULL;
            scanf("%s", file_name);
            FILE* file = fopen(file_name, "r");
            tree_read(file, tree, tree->root);
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
{
    char user_answer = 0;
    printf("in game\n");
    while(true)
    {
        printf("\tin cycle\n");
        if (node->left || node->right)
        {
            printf("%s?\n", node->element);
            printf("Enter (y/n):\n");
            scanf("%c", user_answer);

            switch(user_answer)
            {
                case 'Y':
                case 'y':
                    if (node->right)
                    {
                        node = node->right;
                    }
                    else
                    {
                        return AKINATOR_NULL_POINTER_ON_RIGHT;
                    }
                    break;

                case 'N':
                case 'n':
                    if (node->left)
                    {
                        node = node->left;
                    }
                    else
                    {
                        return AKINATOR_NULL_POINTER_ON_LEFT;
                    }
                    break;

                default:
                    return AKINATOR_INVALID_ANSWER_SIDE;
            }

            game(tree, node);
        }
        else
        {
            graphic_printf(BLUE, BOLD, "No suitable objects\n");
            graphic_printf(BLUE, BOLD, "Add new object (write question-like definition):\n");

            char new_object[MaxObjectLength] = "";
            scanf(" %s[^\n]", new_object);

            if (tree->capacity == 0)
            {
                printf("tree->capacity = %d\n", tree->capacity);
                tree_add(tree, NULL, ROOT, new_object);
                printf("tree->capacity = %d\n", tree->capacity);
            tree_graphic_dump(tree); exit(0);
                printf("\t\tended tree_add\n");
            }
            else
            {
                switch(user_answer)
                {
                    case 'y':
                        tree_add(tree, node, RIGHT, new_object);
                    case 'n':
                        tree_add(tree, node, LEFT, new_object);
                }
            }
            tree_graphic_dump(tree);
            __fpurge(stdin);

            break;
        }
    }

    options_print();
    parse_user_choice(tree, node);

    return AKINATOR_NONE;
}
