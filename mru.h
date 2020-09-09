
#define MAX_MRU 10

int count_MRU = 0;


SpellNode* makeMRUNode(char p[])
{
    SpellNode* ret_val = (SpellNode*)malloc(sizeof(SpellNode));
    if (ret_val)
    {
        strcpy(ret_val->sn, p);
        ret_val->count = 1;
        ret_val->next = NULL;
    }
    return ret_val;
}

void displayMRU(SpellNode* mptr)
{
    if (mptr)
    {
        SpellNode* tptr = mptr;
        while (tptr)
        {
            printf("%s %d\n", tptr->sn, tptr->count);
            tptr = tptr->next;
        }
    }
}

SpellNode* insertNodeMRU(SpellNode* lptr, char* word, int count)
{
    SpellNode* new_node = makeMRUNode(word);
    new_node->count = count;
    if (new_node)
    {
        if (lptr == NULL)
        {
            lptr = new_node;
            new_node->next = NULL;
        }
        else
        {
            SpellNode* tptr = lptr;
            if (strcmp(word, tptr->sn) == -1)
            {
                new_node->next = lptr;
                lptr = new_node;
            }
            else if (strcmp(word, tptr->sn) == 0)
            {

            }
            else
            {
                SpellNode* prev = tptr;
                tptr = tptr->next;
                int flag = 1;
                while (tptr && flag)
                {
                    if (strcmp(word, tptr->sn) != 1)
                    {
                        flag = 0;
                        if (strcmp(word, tptr->sn) == -1)
                        {
                            prev->next = new_node;
                            new_node->next = tptr;
                        }
                    }
                    prev = tptr;
                    tptr = tptr->next;
                }
                if (tptr == NULL && flag && strcmp(word, prev->sn) != 0)
                {
                    prev->next = new_node;
                    new_node->next = NULL;
                }
            }
        }
    }
    return lptr;
}

void displayMRUAsc(SpellNode* mptr)
{

    SpellNode* rptr = NULL;
    SpellNode* tptr = mptr;
    while (tptr)
    {
        rptr = insertNodeMRU(rptr, tptr->sn, tptr->count);
        tptr = tptr->next;
    }
    displayMRU(rptr);
}


SpellNode* incrementMRU(SpellNode* rptr)
{
    if (rptr)
    {
        rptr->count += 1;
    }
    return rptr;
}

SpellNode* checkInMRU(SpellNode* lptr, char p[])
{
    SpellNode* ret_val = NULL;
    SpellNode* tptr = lptr;

    while (tptr && !ret_val)
    {
        if (strcmp(tptr->sn, p) == 0)
        {
            ret_val = tptr;
        }
        tptr = tptr->next;
    }
    return ret_val;
}

//update MRU only increases the count and changes the brings the pointer to the beginning of the list 
//if the node was already present in MRU

SpellNode* updateMRU(SpellNode* mru_ptr, SpellNode* bool_ptr)
{
    SpellNode* ret_val = NULL;
    if (mru_ptr && bool_ptr)
    {
        if (mru_ptr == bool_ptr)
        {
            //bool_ptr->count++;
            incrementMRU(bool_ptr);
            ret_val = mru_ptr;
        }
        else
        {
            SpellNode* prev = mru_ptr;
            SpellNode* present = mru_ptr->next;
            int flag = 1;
            while (present && flag)
            {
                if (bool_ptr == present)
                {
                    flag = 0;
                    //bool_ptr->count++;
                    incrementMRU(bool_ptr);
                    prev->next = present->next;
                    present->next = mru_ptr;
                    mru_ptr = present;
                    ret_val = mru_ptr;
                }
                else
                {
                    prev = present;
                    present = present->next;
                }
            }
        }
    }
    return ret_val;
}

SpellNode* insertMRU(SpellNode* mptr, char p[])
{
    SpellNode* new_Node = makeMRUNode(p);
    SpellNode* ret_val = NULL;

    if (new_Node)
    {
        if (mptr == NULL)
        {
            ret_val = new_Node;
            count_MRU++;
        }
        else
        {
            if (count_MRU < MAX_MRU)
            {
                new_Node->next = mptr;
                ret_val = new_Node;
                count_MRU++;
            }
            else if (count_MRU == MAX_MRU)
            {
                SpellNode* tptr = mptr;
                SpellNode* prev;
                while (tptr->next != NULL)
                {
                    prev = tptr;
                    tptr = tptr->next;
                }
                prev->next = NULL;
                new_Node->next = mptr;
                mptr = new_Node;
                ret_val = new_Node;
            }
        }
    }
    return ret_val;
}
