#include <iostream> //cout, endl
#include <set> //set
#include <unistd.h> // sleep

struct loc
{
    int row;
    int col;

    loc(int r, int c) : row(r), col(c) {}

    bool operator==(const loc &rhs)
    {
        return this->row == rhs.row && this->col == rhs.col;
    }

    bool operator<(const loc &rhs) const
    {
        return (this->row < rhs.row) || (this->row == rhs.row && this->col < rhs.col);
    }
};

class Conway
{
public:
    Conway(std::set<loc> &initialCells);
    void tick();
    int evaluate(int iterations);
    void printState();
    void play(int ticks);

private:
    bool alive(loc cell, std::set<loc> &previousCells);
    void addNeighbors(loc cell, std::set<loc> &candidates);
    int countNeighbors(loc cell, std::set<loc> &cells);
    std::set<loc> cells;
    int iteration;
    static const int maxStreak = 10;
    static const int MIN_PRINT = 3;
};