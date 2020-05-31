#include "conway.h"
#include <stdlib.h>
#include <omp.h>
#include <chrono>
#include <iostream>
using namespace std;

/* brute force solve for maximum infection of board of size n x n
 * need to explore all permutations of nxn grid -> or of length n x n
 * Can just use binary representation of n x n bit number
*/
void brute(int n)
{
    auto start = chrono::steady_clock::now();
    int bestScore = 0;
    set<loc> bestBoard;

    unsigned long long permutations = 1;

    for (int i = 0; i < n * n; i++)
    {
        permutations *= 2;
    }
    #pragma omp parallel for
    for (unsigned long long i = 0; i < permutations; i++)
    {
        set<loc> cells;
        for (int r = 0; r < n; r++)
        {
            for (int c = 0; c < n; c++)
            {
                if (i & (1 << (r * n + c)))
                {
                    cells.insert(loc(r, c));
                }
            }
        }
        Conway game(cells);
        int fitness = game.evaluate(10000);
        #pragma omp critical
        {
            if (fitness > bestScore)
            {
                cout << "new best score" << fitness << endl;
                bestScore = fitness;
                bestBoard = cells;
            }
        }
    }
    
    auto end = chrono::steady_clock::now();
    cout << "Found brute force solution for grid of size:" << n << endl;
    cout << "Took " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " milliseconds" << endl;
    cout << "Fitness:" << bestScore << endl;
    Conway game(bestBoard);
    game.printState();

}

void random_search(int n)
{
    cout << "to start" << endl;
    cout << "hello world" << endl;

    int bestScore = 0;
    set<loc> bestBoard;
    auto start = chrono::steady_clock::now();
#pragma omp parallel for
    for (int i = 0; i < 10000; i++)
    {
        set<loc> cells;
        int population = rand() % 90 + 10;
        for (int j = 0; j < population; j++)
        {
            int r = rand() % n;
            int c = rand() % n;
            cells.emplace(loc(r, c));
        }
        Conway game(cells);

        int fitness = game.evaluate(10000);
#pragma omp critical
        {
            if (fitness > bestScore)
            {
                cout << "new best score" << fitness << endl;
                bestScore = fitness;
                bestBoard = cells;
            }
        }
    }

    auto end = chrono::steady_clock::now();
    cout << "took " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " seconds" << endl;
    cout << "best score was " << bestScore << endl;
    Conway game(bestBoard);
    game.printState();
    //game.play(15);
}
int main()
{

    brute(4);
    return 0;
}