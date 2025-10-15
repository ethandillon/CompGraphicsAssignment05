//
// Created by Ben on 7/7/2023.
//

#ifndef MAZES_FOR_PROGRAMMERS_DISTANCES_H
#define MAZES_FOR_PROGRAMMERS_DISTANCES_H

#include "vector"
#include "cstdio"
#include "Grid.h"

class Distances {
public:
    std::vector<std::vector<int>> distances;
    Grid *gr;
    const int fill_value = 9999;

    static Distances* for_grid(Grid &gr) {
        auto dst = new Distances;
        dst->gr = &gr;
//        dst->distances = new std::vector(gr.num_rows,
//                                         std::vector(gr.num_columns, fill_value));
        for(auto r = 0; r < gr.num_rows; r++) {
            std::vector<int> row;
            for(auto c = 0; c < gr.num_columns; c++ ) {
                row.push_back(dst->fill_value);
            }
            dst->distances.push_back(row);
        }
        return dst;
    }

    int get(int row, int column) {
        return distances[row][column];
    }

    /**
     * \brief Fill in the distances starting at the given cell.
     */
    void dijkstra(int row0, int column0) {
        std::vector<std::pair<int,int>> stack;
        distances[row0][column0] = 0;
        stack.push_back(std::pair(row0,column0));
        while(!stack.empty()) {
            auto p = stack.back();
            auto r = p.first;
            auto c = p.second;
            stack.pop_back();
            auto cell = gr->cells[r][c];
            auto val = distances[r][c];
            if(cell->west->is_open() && distances[r][c-1] == fill_value) {
                distances[r][c-1] = val+1;
                stack.push_back(std::pair(r,c-1));
            }
            if(cell->east->is_open() && distances[r][c+1] == fill_value) {
                distances[r][c+1] = val+1;
                stack.push_back(std::pair(r,c+1));
            }
            if(cell->north->is_open() && distances[r-1][c] == fill_value) {
                distances[r-1][c] = val+1;
                stack.push_back(std::pair(r-1,c));
            }
            if(cell->south->is_open() && distances[r+1][c] == fill_value) {
                distances[r+1][c] = val+1;
                stack.push_back(std::pair(r+1,c));
            }
        }
    }



    std::string to_string() {
        const std::string space(" ");
        const std::string hyphen("-");
        const std::string space6("      ");
        const std::string hyphen6("------");
        const std::string corner("+");
        const std::string vbar("|");
        std::string output("+");
        for(auto i = 0; i < gr->num_columns; i++) {
            output += std::string("------+");
        }
        output += "\n";
        for(auto r = 0; r < gr->num_rows; r++) {
//        for(auto row : gr->cells) {
            auto row = gr->cells[r];
            auto top = std::string("|");
            auto mid = std::string("|");
            auto bottom = std::string("+");
            for(auto c = 0; c < gr->num_columns; c++ ) {
//            for(auto* cell : row) {
                auto cell = row[c];
                auto body = space6;  // three spaces
                char val[32];
                snprintf(val, 32, " %4d ", distances[r][c]);
                auto east_boundary = cell->east->is_closed() ? vbar : space;
                mid += std::string(val) + east_boundary;
                top += body + east_boundary;
                auto south_boundary = cell->south->is_closed() ? hyphen6 : space6;
                bottom += south_boundary + corner;
            }
//            output += top + "\n";
            output += mid + "\n";
//            output += top + "\n";
            output += bottom + "\n";
        }

        return output;
    }


};




#endif //MAZES_FOR_PROGRAMMERS_DISTANCES_H
