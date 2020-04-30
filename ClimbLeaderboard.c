/*****************************************************************************************************************************

Alice is playing an arcade game and wants to climb to the top of the leaderboard and wants to track her ranking. The game uses Dense Ranking, so its leaderboard works like this:

    1. The player with the highest score is ranked number 1 on the leaderboard.
    2. Players who have equal scores receive the same ranking number, and the next player(s) receive the immediately following ranking number.
    
Sample input :-

7
100 100 50 40 40 20 10
4
5 25 50 120

Sample output :-

6
4
2
1

******************************************************************************************************************************/

void setRemainingRanks(int* out, int num, int rank)
{
    int idx = 0;

    for(; idx <= num; idx++)
        *(out + idx) = rank;
}

int* climbingLeaderboard(int scores_count, int* scores, int alice_count, int* alice, int* result_count) 
{
    int score_idx    = 0;
    int alice_idx    = 0;
    int rank         = 0;
    int last_score   = 0;
    int last_score_idx = 0;
    int* output_rank = NULL;
    
    *result_count = alice_count;
    output_rank = malloc(*result_count * sizeof(int));
    if(NULL == output_rank)
    {
        printf("Memory allocation failed.\n");
        return NULL;
    }

    rank = 1;    //Assume the score is highest.
    last_score = *scores;    //Assume to be the best score.
    for ( alice_idx = alice_count - 1; alice_idx >= 0; alice_idx--)
    {
        for ( score_idx = last_score_idx; score_idx < scores_count; score_idx++)
        {
            if(last_score != *(scores + score_idx))
                rank++;

            last_score = *(scores + score_idx);
            if( *(alice + alice_idx) >= *(scores + score_idx) )
            {
                *(output_rank + alice_idx) = rank;
                last_score_idx = score_idx;
                break;
            }
        }

        if (score_idx == scores_count) 
        {
            setRemainingRanks(output_rank, alice_idx, rank + 1);
            break;
        }
    }      
    return output_rank;
}
