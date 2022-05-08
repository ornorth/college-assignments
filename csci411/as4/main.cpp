// CSCI 411 - Fall 2020
// Assignment 4 Skeleton
// Author: Carter Tillquist
// Feel free to use all, part, or none of this code for the coding problem on assignment 4

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*******************************************************************************************
 * A simple struct to describe alignments. Insertions are denoted with an underscore ("_") *
 * a, b - strings - two strings representing an alignment. The strings being aligned may   *
 *                - be extracted by removing underscores                                   *
 * score - float - the score of the alignment given costs associated with insertions,      *
 *                 deletions, and substitutions                                            *
 * *****************************************************************************************/
struct Alignment{
    string a;
    string b;
    float score;
};

/***************************************************************************************
 * A simple struct to keep track of subproblem solutions                               *
 * act - string - the action taken to reach this Cell: "match", "ins", "del", or "sub" *
 * score - float - the score of the alignment of prefixes up to this point given costs *
 *                 associated with insertions, deletions, and substitutions            *
 * *************************************************************************************/
struct Cell{
    string act;
    float score;
};

/*************************************************************************************
 * Given two strings a and b along with costs associated with insertions, deletions, *
 * and substitutions, find an optimal alignment (of minimum cost) of a and b         *
 * a, b - strings - two strings for which we want an alignment                       *
 * ins, del, sub - floats - the cost of performing insertion, deletion, and          *
 *                          substitution opertations respectively on string a        *
 * return - Alignment* - an optimal alignment of a and b given the matrix T along    *
 *                       with the score or cost of the alignment                     *
 * ***********************************************************************************/
Alignment* editDistance(string a, string b, float ins, float del, float sub){
    unsigned Asize = a.size();
    unsigned Bsize = b.size();
    Cell M[Asize+1][Bsize+1];

    //Set up base cases
    M[0][0] = {"", 0};
    for (unsigned i = 1; i <= Asize; i++)
    {
        M[i][0] = {"del", M[i-1][0].score + del};
    }
    for (unsigned i = 1; i <=Bsize; i++)
    {
        M[0][i] = {"ins", M[0][i-1].score + ins};
    }

    //Main loop
    for (unsigned i = 1; i <= Asize; i++)
    {
        for (unsigned j = 1; j <= Bsize; j++)
        {
            Cell tmpSub, tmpOther;

            //Temp Cell with cost of sub, unless chars are a match
            if (a[i-1] == b[j-1])
            {
                tmpSub = {"match", M[i-1][j-1].score};
            }
            else
            {
                tmpSub = {"sub", M[i-1][j-1].score + sub};
            }
            
            //Determine whether ins or del is less, make a temp Cell with that
            if ((M[i-1][j].score + del) <= (M[i][j-1].score + ins)) 
            {
                tmpOther = {"del", M[i-1][j].score + del};
            }
            else
            {
                tmpOther = {"ins", M[i][j-1].score + ins};
            }

            //Push either sub/match Cell or ins/del Cell - sub/match has priority
            M[i][j] = (tmpSub.score <= tmpOther.score ? tmpSub : tmpOther);
        }
    }

    //Calculate the alignment using back pointers
    Alignment* answer = new Alignment{"", "", M[Asize][Bsize].score};
    int i = Asize,
        j = Bsize;
    while (i+j != 0)
    {
        if (M[i][j].act == "ins")
        {
            answer->a = "_" + answer->a;//.insert(0, "_");
            answer->b = b[--j] + answer->b;//.insert(0, b[--j]);
        }
        else if (M[i][j].act == "del")
        {
            answer->b = "_" + answer->b;//.insert(0, "_");
            answer->a = a[--i] + answer->a;//.insert(0, a[--i]);
        }
        else
        {
            answer->a = a[--i] + answer->a;//.insert(0, a[--i]);
            answer->b = b[--j] + answer->b;//.insert(0, b[--j]);
        }
    }

    return answer;
}

int main(){
    //get the number of tests
    int n = -1;
    cin >> n;

    //get the costs associated with insertions, deletions, and substitutions
    int ins = -1, del = -1, sub = -1;
    cin >> ins >> del >> sub;

    //for each test, print the resulting alignment along with its score
    for (int i = 0; i < n; i++){
        string a = "", b = "";
        cin >> a >> b;

        Alignment* align = editDistance(a, b, ins, del, sub);
        cout << align->a << endl;
        cout << align->b << endl;
        cout << align->score << endl;
    }

    return 0;
}
