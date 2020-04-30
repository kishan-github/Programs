/**********************************************************************************************************************
Lexicographical order is often known as alphabetical order when dealing with strings. A string is greater than another string if it comes later in a lexicographically sorted list.

Given a word, create a new word by swapping some or all of its characters. This new word must meet two criteria:

    It must be greater than the original word
    It must be the smallest word that meets the first condition

Sample Input 0

5
ab
bb
hefg
dhck
dkhc

Sample Output 0

ba
no answer
hegf
dhkc
hcdk

*******************************************************************************************************************************/

#define SWAP(x,y){   \
    char temp = x;  \
    x = y;          \
    y = temp;       \
}

int8_t checkIfInOrder(char* str)
{
    int8_t i = 0;
    int8_t j = 0;
    int8_t temp_idx = -1;
    int8_t start_idx = 0;
    int8_t length = strlen(str);

    for(i = length - 1; i > 0; i--)
    {
        if(i <= temp_idx)
            break;
        
        for(j = i - 1; j > temp_idx; j--)
        {
            if(str[i] > str[j])
            {
                start_idx = i;
                temp_idx = j;
                break;
            }
        }
    }
    
    if(temp_idx != -1)
        SWAP(str[start_idx], str[temp_idx]);

    return temp_idx;
}

void sortString(char* str, int8_t startIdx)
{
    int8_t length = strlen(str) - startIdx;
    int8_t i = startIdx;
    int8_t j = 0;
    char temp = '\0';

    for(; i < strlen(str) - 1; i++)
    {
        for(j = i + 1; j < strlen(str); j++)
        {
            if(str[i] > str[j])
            {
                temp = str[i];
                str[i] = str[j];
                str[j] = temp;
            }
        }
    }
}

char* biggerIsGreater(char* w) 
{
    int8_t updateIdx = 0;
    static char noOutput[] = "no answer";

    if( (updateIdx = checkIfInOrder(w)) == -1)
        return noOutput;

    sortString(w, updateIdx + 1);

    return w;
}
