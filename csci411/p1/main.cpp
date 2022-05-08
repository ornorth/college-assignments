#include <iostream>
#include <iomanip>
#include <cmath>
#include <random>
#include <chrono>
#include <time.h>
#include <climits>

using namespace std;

/*  Q_rsqrt
 *
 *  @brief  speedy approximation of inverse square root
 *          as was used in 'Quake III Arena'
 *
 *  @param  number of which to approximate the inverse square root
 *  @return the inverse square root of number
 */
float Q_rsqrt(float number)
{
    long i;
    float /*x2,*/ y;
    //const float threehalfs = 1.5;

    //x2 = number * 0.5;
    y = number;
    i = * ( long * ) &y;
    i = 0x5f3759df - ( i >> 1 );
    y = * ( float * ) &i;
    //y = y * ( threehalfs - ( x2 * y * y ) );
    //y = y * ( threehalfs - ( x2 * y * y ) );

    return y;
}

//Repeat of above function with last line not commented out for additional runtime and accuracy comparison
//It's entirely separate to avoid adding extra operations which might throw off the speed test
float Q_rsqrtD(float number)
{
    long i;
    float x2, y;
    const float threehalfs = 1.5;

    x2 = number * 0.5;
    y = number;
    i = * ( long * ) &y;
    i = 0x5f3759df - ( i >> 1 );
    y = * ( float * ) &i;
    y = y * ( threehalfs - ( x2 * y * y ) );
    y = y * ( threehalfs - ( x2 * y * y ) );

    return y;
}

/*  invsqrt()
 *
 *  @brief  typical implementation of an inverse square root function
 *
 *  @param  number of which to approximate the inverse square root
 *  @return the inverse square root of number
 */
float invsqrt(float number)
{
    return 1.0/sqrt(number);
}


/*  printTime
 *
 *  @brief  given start and end times of type std::chrono::steady_clock::time_point,
 *          print the difference in seconds
 *
 *  @param  start time
 *          end   time
 *  @return none, but prints the time in seconds
 */
void printTime(chrono::steady_clock::time_point start, chrono::steady_clock::time_point end)
{
    chrono::duration<double> time_span = chrono::duration_cast<chrono::duration<double>> (end - start);
    cout << time_span.count();
}


/*  speedTest
 *
 *  @brief  requests an amount of operations to perform,
 *          then prints the time it takes both functions 
 *          to perform those operations
 *
 *  @param  none
 *  @return none
 */
void speedTest(bool runDouble)
{
    //timekeepers
    chrono::steady_clock::time_point startTime;
    chrono::steady_clock::time_point endTime;

    //size of test
    int sampleSize;
    cin >> sampleSize;
    cin.ignore();

    //exact calculation
    startTime = chrono::steady_clock::now();
    //run test
    for (int i = 0; i < abs(sampleSize); i++)
    {
        invsqrt((float)(rand()%100) * sqrt(5)/2);
    }
    //print results
    endTime = chrono::steady_clock::now();
    cout << "Calculations on " << abs(sampleSize) << " elements took ";
    printTime(startTime, endTime);
    cout << " seconds\n";

    //approximation
    //if statement decides whether to run single or double refinement version
    //it's a few blocks too wide to avoid adding false complexity to the test,
    //at the cost of redundant code
    if (runDouble)
    {
        startTime = chrono::steady_clock::now();
        //run test
        for (int i = 0; i < abs(sampleSize); i++)
        {
            Q_rsqrtD((float)(rand()%100)*sqrt(5)/2);
        }
        //print results
        endTime = chrono::steady_clock::now();
        cout << "Approximation on " << abs(sampleSize) << " elements took ";
        printTime(startTime, endTime);
        cout << " seconds\n\n";
    }
    else
    {
        startTime = chrono::steady_clock::now();
        //run test
        for (int i = 0; i < abs(sampleSize); i++)
        {
            Q_rsqrt((float)(rand()%100)*sqrt(5)/2);
        }
        //print results
        endTime = chrono::steady_clock::now();
        cout << "Approximation on " << abs(sampleSize) << " elements took ";
        printTime(startTime, endTime);
        cout << " seconds\n\n";
    }
}

/*  accuracyTest
 *
 *  @brief  tests the accuracy of the inverse square foot approximation
 *          against the exact value
 *          prints a decimal number, its root approximation, its exact root,
 *          the percent variance, and the average variance across all trials
 *          (percent variance: x + ax = y -> x=exact, y=approximation, a=variance)
 *
 *  @param  none
 *  @return none
 */
void accuracyTest(bool printValues, bool runDouble)
{
    //size of test
    int sampleSize;
    cin >> sampleSize;
    cin.ignore();

    float input,                //original inputs - random decimal values between 0 and [roughly] 110.7
          appro,                //values for the invsqrt approximation
          exact;                //precise values calculated with "proper" method

    double variance;            //percent variance between approximated value and actual value
    double avg = 0;             //running average of percent variance
    float largest = 0;          //tracker for the largest variance
    float smallest = INT_MAX;   //tracker for the smallest variance

    for (int i = 0; i < abs(sampleSize); i++)
    {
        //generate random number, ensure nonzero
        input = (float)(rand()%100) * sqrt(5)/2;
        if (input == 0)
        {
            i--;
            continue;
        }

        //run calculations
        
        //approximation with 2 refinements
        if (runDouble)
        {
            appro = Q_rsqrtD(input);
        }
        //approximation with 1 refinement
        else
        {
            appro = Q_rsqrt(input);
        }
        //exact calculation
        exact = invsqrt(input);

        //update statistics
        variance = abs(appro/exact - 1) * 100;
        if (variance > largest)
        {
            largest = variance;
        }
        if (variance < smallest)
        {
            smallest = variance;
        }
        avg += variance;

        //display stats for each run, if requested
        if (printValues)
        {
            if (input < 10)
            {
                cout << fixed << setprecision(11);
            }
            else if (input > 100)
            {
                cout << fixed << setprecision(9);
            }
            else
            {
                cout << fixed << setprecision(10);
            }
            cout << "Original number: "  << input << setw(25);
            cout << fixed << setprecision(10)
                 << "Approximation: "    << appro << setw(25) 
                 << "Exact value: "      << exact << setw(25) 
                 << "Percent variance: " << variance 
                 << endl;
        }
    }

    //global statistics
    cout << "Largest variance: "  << largest            << endl
         << "Smallest variance: " << smallest           << endl
         << "Average variance: "  << (avg / sampleSize) << endl
         << endl;
}

/*
 *  There are 2 tests, speed and accuracy. Speed tracks time but not value, accuracy does the inverse
 *  Input comes in pairs separated by newline. First is the 'command', then the sample size
 *  
 *  COMMANDS:
 *  s  - speed
 *  a  - accuracy
 *  ap - accuracy, plus it prints every computed value - original number, approximation, exact, variance - beware text wall
 *  q  - quit the program
 *  appending 'd' to a command other than q (sd, ad, apd) runs the same test but with a second refinement operation
 *
 *  Any sample size between 0 and INT_MAX is allowed
 *
 *  EXAMPLE INPUT
 *  s
 *  1000
 *  sd
 *  5000
 *  a
 *  900
 *  apd
 *  50
 *  q
 */
int main()
{
    //feed pseudo-random seed to RNG
    srand(time(NULL));
    string input;

    //Menu
    while (true)
    {
        cout << "Home\n";
        getline(cin, input);
        if (input == "s")
        {
            speedTest(false);
        }
        else if (input == "sd")
        {
            speedTest(true);
        }
        else if (input == "a")
        {
            accuracyTest(false, false);
        }
        else if (input == "ad")
        {
            accuracyTest(false, true);
        }
        else if (input == "ap")
        {
            accuracyTest(true, false);
        }
        else if (input == "apd")
        {
            accuracyTest(true, true);
        }
        else if (input == "q")
        {
            break;
        }
    }
    return 0;
}




