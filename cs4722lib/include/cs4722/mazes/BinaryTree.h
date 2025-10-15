//
// Created by Ben on 5/27/2023.
//

#ifndef MAZE_FOR_PROGRAMMERS_BINARYTREE_H
#define MAZE_FOR_PROGRAMMERS_BINARYTREE_H

#include "Grid.h"
#include <random>
#include "ctime"

class BinaryTree {
public:
    static void on(Grid &grid, unsigned int seed = 0) {
        srand(seed ? seed : time(NULL));
        for(auto row : grid.cells) {
            for(auto cell : row) {
                if(cell->north->cellNW != nullptr) {
                    if(cell->east->cellSE != nullptr) {
                        (rand() % 2 == 0 ? cell->north : cell->east)->set_open();
                    } else {
                        cell->north->set_open();
                    }
                } else {
                    if(cell->east->cellSE != nullptr) {
                        cell->east->set_open();
                    } else {
                        // upper right cell, no links
                    }
                }
            }
        }
//        return grid;
    }

};



#endif //MAZE_FOR_PROGRAMMERS_BINARYTREE_H
