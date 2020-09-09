
typedef struct spell_node_tag {
    char sn[20];
    int count;
    struct spell_node_tag* next;
}SpellNode;


//returns 1 if present in dictionary else 0

int checkInDict(WordNode* dptr, char p[])
{
    int ret_val = 0;
    WordNode* tptr = dptr;
    while (tptr)
    {
        if (strcmp(p, tptr->s) == -1 || strcmp(p, tptr->s) == 0)
        {
            if (strcmp(p, tptr->s) == 0)   ret_val = 1;
            break;
        }
        tptr = tptr->next;
    }
    return ret_val;
}

SpellNode* makeCirNode(char* word)
{

    SpellNode* new_node = (SpellNode*)malloc(sizeof(SpellNode));

    if (new_node)
    {
        new_node->count = 1;
        strcpy(new_node->sn, word);
        new_node->next = new_node;
    }

    return new_node;
}

SpellNode* checkInSpellNode(SpellNode* lptr, char p[])
{
    SpellNode* ret_val = NULL;
    if (lptr)
    {
        SpellNode* tptr = lptr->next;
        int flag = 1;
        while (tptr != lptr && flag)
        {
            if (strcmp(tptr->sn, p) == 0)
            {
                ret_val = tptr;
                flag = 0;
            }
            tptr = tptr->next;
        }
        if (flag == 1 && (strcmp(tptr->sn, p) == 0))
        {
            ret_val = tptr;
        }
    }
    return ret_val;
}

SpellNode* insertSpellNode(SpellNode* lptr, char p[])
{
    SpellNode* new_node = makeCirNode(p);
    
    if (new_node)
    {
        if (lptr == NULL)
        {
            lptr = new_node;
            lptr->next = lptr;
        }
        else
        {
            SpellNode* found = checkInSpellNode(lptr, p);
            if (found == NULL)
            {
                //new_node->next = lptr->next;
                SpellNode* kptr = lptr->next;
                lptr->next = new_node;
                new_node->next = kptr;
                lptr = new_node;
            }
            else
            {
                //delete the found node
                //one node case success
                new_node->count = ++found->count;
                SpellNode* prev = lptr;                                   //two node case success
                while (prev->next!=found)
                {
                    prev = prev->next;
                }
                if (prev->next != found->next)
                {
                    prev->next = found->next;
                    found->next = NULL;
                    if (found == lptr)
                    {
                        lptr = prev;
                    }
                }
                else
                {
                    lptr = NULL;
                }

                //insert in the list 
                prev = lptr;
                if (prev == NULL)
                {
                    lptr = new_node;
                }
                else
                {
                    if (prev->next != lptr)
                    {
                        int flag = 1;
                        while (new_node->count - prev->next->count < 0 && flag)
                        {
                            prev = prev->next;
                            if (prev == lptr)
                            {
                                flag = 0;
                            }
                        }

                        new_node->next = prev->next;
                        prev->next = new_node;

                        if (flag == 0)   lptr = new_node;

                    }
                    else
                    {
                        if (new_node->count - prev->next->count >= 0)
                        {
                            new_node->next = prev;
                            prev->next = new_node;
                        }
                        else
                        {
                            prev->next = new_node;
                            new_node->next = prev;
                            lptr = new_node;
                        }
                    }

                }
            }
        }
    }
    return lptr;
}


void displayCirList(SpellNode* lptr)
{
    if (lptr)
    {
        SpellNode* tptr = lptr->next;
        while (tptr != lptr)
        {
            printf("%s %d\n", tptr->sn, tptr->count);
            tptr = tptr->next;
        }
        printf("%s %d\n", tptr->sn, tptr->count);
    }
}