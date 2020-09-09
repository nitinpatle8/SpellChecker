typedef struct node_tag {
    char s[20];
    struct node_tag* next;
}WordNode;

void displayList(WordNode* lptr)
{
    WordNode* tptr = lptr;
    while (tptr != NULL)
    {
        printf("%s ", tptr->s);
        tptr = tptr->next;
    }
    printf("\n");
}



void initialise(WordNode* lptr)
{
    lptr = NULL;
}

WordNode* makeNode(char* word)
{
    WordNode* ret_node = NULL;

    WordNode* newNode = (WordNode*)malloc(sizeof(WordNode));

    if (newNode)
    {
        strcpy(newNode->s, word);
        newNode->next = NULL;
        ret_node = newNode;
    }
    return ret_node;
}

WordNode* insertNode(WordNode* lptr, char* word)
{
    WordNode* new_node = makeNode(word);
    if (new_node)
    {
        if (lptr == NULL)
        {
            lptr = new_node;
            new_node->next = NULL;
        }
        else
        {
            WordNode* tptr = lptr;
            if (strcmp(word, tptr->s) == -1)
            {
                new_node->next = lptr;
                lptr = new_node;
            }
            else if (strcmp(word, tptr->s) == 0)
            {

            }
            else
            {
                WordNode* prev = tptr;
                tptr = tptr->next;
                int flag = 1;
                while (tptr && flag)
                {
                    if (strcmp(word, tptr->s) != 1)
                    {
                        flag = 0;
                        if (strcmp(word, tptr->s) == -1)
                        {
                            prev->next = new_node;
                            new_node->next = tptr;
                        }
                    }
                    prev = tptr;
                    tptr = tptr->next;
                }
                if (tptr == NULL && flag && strcmp(word, prev->s) != 0)
                {
                    prev->next = new_node;
                    new_node->next = NULL;
                }
            }
        }
    }
    return lptr;
}