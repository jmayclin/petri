#include "conway.h"

using namespace std;

Conway::Conway(std::set<loc> &initialCells)
{
    cells = initialCells;
    iteration = 0;
}

int Conway::evaluate(int iterations)
{
    int count = cells.size();
    int streak = 0;
    for (int i = 0; i < iterations; i++)
    {
        tick();
        if (cells.size() == count)
        {
            streak++;
        }
        else
        {
            count = cells.size();
            streak = 0;
        }

        if (count == 0 || streak == maxStreak)
        {
            return count;
        }
    }
    return count;
}

void Conway::play(int ticks)
{
    for (int i = 0; i < ticks; i++)
    {
        Conway::printState();
        tick();
        sleep(1);
    }
}

int Conway::countNeighbors(loc cell, set<loc> &cells)
{
    int count = 0;
    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            if (cells.find(loc(cell.row + i, cell.col + j)) != cells.end())
            {
                count++;
            }
        }
    }
    return count;
}

bool Conway::alive(loc cell, set<loc> &previousCells)
{
    int neighbors = countNeighbors(cell, previousCells);
    bool wasAlive = previousCells.find(cell) != previousCells.end();
    if (wasAlive && (neighbors == 2 || neighbors == 3))
    {
        return true;
    }
    else if (!wasAlive && neighbors == 3)
    {
        return true;
    }
    return false;
}

void Conway::addNeighbors(loc cell, set<loc> &candidates)
{
    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            candidates.emplace(loc(cell.row + i, cell.col + j));
        }
    }
}

void Conway::tick()
{
    set<loc> candidates;
    set<loc> next;
    for (auto &cell : cells)
    {
        addNeighbors(cell, candidates);
    }

    for (auto &cell : candidates)
    {
        if (alive(cell, cells))
        {
            next.insert(cell);
        }
    }
    cells = next;
}

void Conway::printState()
{
    int minRow = cells.begin()->row;
    int maxRow = cells.begin()->row;
    int minCol = cells.begin()->col;
    int maxCol = cells.begin()->col;
    for (auto &cell : cells)
    {
        minRow = min(cell.row, minRow);
        maxRow = max(cell.row, maxRow);
        minCol = min(cell.col, minCol);
        maxCol = max(cell.col, maxCol);
    }
    maxRow = max(maxRow, minRow + MIN_PRINT);
    maxCol = max(maxCol, minCol + MIN_PRINT);

    cout
        << cells.size() << " cells"
        << "\n"
        << minRow << "," << minCol
        << "*********************"
        << maxRow << "," << maxCol << endl;
    for (int r = minRow; r < maxRow; r++)
    {
        for (int c = minCol; c < maxCol; c++)
        {
            bool found = cells.find(loc(r, c)) != cells.end();
            cout << (found ? "X" : "-");
        }
        cout << endl;
    }
}