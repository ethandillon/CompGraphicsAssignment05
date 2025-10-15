//
// Created by Ben on 5/31/2023.
//

#ifndef MAZE_FOR_PROGRAMMERS_SIDEWINDER_H
#define MAZE_FOR_PROGRAMMERS_SIDEWINDER_H



#include "Grid.h"
#include <random>
#include "ctime"

class Sidewinder {
public:
    static void on(Grid &grid, unsigned int seed = 0) {
        srand(seed ? seed : time(NULL));
        for(auto row : grid.cells) {
            std::vector<Cell*> run;
            for(auto cell : row) {
                run.push_back(cell);
//                bool at_eastern_boundary = cell->east == nullptr;
//                bool at_northern_boundary = cell->north == nullptr;
                if(!cell->east->cellSE || (cell->north->cellNW && rand() % 2 == 0)) {
                    auto member = run[rand() % run.size()];
                    if(cell->north->cellNW) {
                        member->north->set_open();
                    }
                    run.erase(run.begin(), run.end());
                } else {
                    cell->east->set_open();
                }
            }
        }
    }

};




#endif //MAZE_FOR_PROGRAMMERS_SIDEWINDER_H
