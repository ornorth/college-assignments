// CSCI 411 - Spring 2021
// Assignment 5 Skeleton
// Author: Carter Tillquist
// Feel free to use all, part, or none of this code for the coding problem on assignment 5.

#include <iostream>
#include <vector>
#include <limits.h>
#include <algorithm>
using namespace std;

/*****************************************************************************************************
 * A simple struct to keep track of the sequence of hotels visited as well as the associated penalty *
 * seq - vector<int> - the sequence of hotels visited                                                *
 * penalty - int - the penalty associated with the sequence of hotels visited                        *
 * ***************************************************************************************************/
struct TripCost{
    vector<int> seq;
    int penalty;
};


/********************************************************************************************************
 * A simple struct to keep track of the minimum penalty and previous hotel for a potential ending hotel *
 * penalty - int - the minimum penalty associated with reaching this hotel                              *
 * prev - int - the hotel visited before this one                                                       *
 * ******************************************************************************************************/
struct HotelCell{
    int penalty;
    int prev;
};

/************************************************************************************************
 * Given a sequence of hotel distances and an ideal number of miles to travel per day, return a *
 * TripCost pointer representing the sequence of hotels to visit with minimum penalty           *
 * hotels - vector<int> - the number of miles to each hotel from the starting point of the trip *
 * m - int - the ideal number of miles to travel per day                                        *
 * **********************************************************************************************/
TripCost* hotelSequence(vector<int> hotels, int m){
    HotelCell P[hotels.size()];
    P[0] = {0, 0};
    for (unsigned i = 1; i < hotels.size(); i++)
    {
        P[i] = {INT_MAX, 0};
        for (unsigned j = 0; j < i; j++)
        {
            int penalty = m - (hotels[i] - hotels[j]);
            penalty *= penalty;
            penalty += P[j].penalty;
            if (penalty < P[i].penalty)
            {
                P[i] = {penalty, (int)j};
            }
        }
    }

    TripCost *answer = new TripCost;
    answer->penalty = P[hotels.size()-1].penalty;
    unsigned i = hotels.size()-1;
    while (i > 0)
    {
        answer->seq.push_back(i);
        i = (unsigned)P[i].prev;
    }
    sort(answer->seq.begin(), answer->seq.end());
    return answer;
}

int main(){
    //get the total number of hotels and the ideal number of miles traveled per day
    int n = -1, m = -1;
    cin >> n >> m;

    //collect the hotel distances
    vector<int> hotels(n);
    hotels.push_back(0);
    for (int i = 1; i <= n; i++){
        int d = -1;
        cin >> d;
        hotels[i] = d;
    }

    //determine the route that minimizes the overall penalty and print out the results
    TripCost* solution = hotelSequence(hotels, m);
    for (unsigned i = 0; i < solution->seq.size(); i++){
        cout << solution->seq[i] << " ";
    }
    cout << endl;
    cout << solution->penalty << endl;

    return 0;
}

