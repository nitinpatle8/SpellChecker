#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dict.h"
#include "spell.h"
#include "mru.h"


int main() {

    WordNode* dict = NULL;

    // d for dictionary input

    char d[10001];

    fgets(d, 10000, stdin);

    int i = 0;
    while (d[i] != '\n')
    {
        int k = 0;
        char p[20];
        while (d[i] != ' ' && d[i] != '\n' && d[i] != '-')
        {
            if ((d[i] >= 'A' && d[i] <= 'Z') || (d[i] >= 'a' && d[i] <= 'z'))
            {
                p[k] = d[i];
                k++;
            }
            i++;
        }
        p[k] = '\0';

        //
        dict = insertNode(dict, p);
        if (d[i] != '\n')	i++;
    }
    printf("*******************\n");

    displayList(dict);
    printf("*******************\n");
    /* upto here dictionary List is made
       Now you have to make circular linked list for incorrect word
       and check it in dictionary linked list*/


    SpellNode* spell_mistake = NULL;

    char s[256];

    fgets(s, 255, stdin);

    /* MRU implementation starts here*/

    SpellNode* MRU = NULL;


    i = 0;
    while (s[i] != '\n')
    {
        int k = 0;
        char p[20];
        while (s[i] != ' ' && s[i] != '\n' && s[i] != '-')
        {
            if ((s[i] >= 'A' && s[i] <= 'Z') || (s[i] >= 'a' && s[i] <= 'z'))
            {
                p[k] = s[i];
                k++;
            }
            i++;
        }
        p[k] = '\0';

        //You have to make conditions when to insert in SpellNode
        //Making comparisons with dictionary here

        //CheckInDict becomes check in MRU afterwards

        SpellNode* boolean_mru = checkInMRU(MRU, p);

        //Everything is clear downhere
        int boolean_dict = 1;
        if (boolean_mru == NULL)
        {
            boolean_dict = checkInDict(dict, p);

            if (boolean_dict == 1)
                MRU = insertMRU(MRU, p);
        }
        else
        {
            MRU = updateMRU(MRU, boolean_mru);
        }
        // printf("%d", boolean);
        if (boolean_dict == 0)
        {
            spell_mistake = insertSpellNode(spell_mistake, p);
        }
        if (s[i] != '\n')	i++;
    }
    printf("######## Spell Mistake List is##########\n");
    displayCirList(spell_mistake);

    printf("********************\n");
    printf("######### MRU List is##########\n");
    displayMRU(MRU);

    printf("*******************\n");
    printf("######### MRU List with ASC order###########\n");
    displayMRUAsc(MRU);

    return 0;
}