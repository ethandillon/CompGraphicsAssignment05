//
// Created by Ben on 5/26/2023.
//

#ifndef MAZE_FOR_PROGRAMMERS_GRID_H
#define MAZE_FOR_PROGRAMMERS_GRID_H

#include <set>
#include <vector>
#include <string>
#include "cmath"
#include "cs4722/artifact.h"

class Grid;
class Cell;
class Wall;


class Wall {
public:
    cs4722::Artifact *artifact = nullptr;
    Cell *cellNW = nullptr;
    Cell *cellSE = nullptr;

    explicit Wall(Cell *cellNW, Cell *cellSE)
        : cellNW(cellNW), cellSE(cellSE) {

    }


    void set_closed() {
        closed = true;
        if(artifact != nullptr)
            artifact->visible = true;
    }

    void set_open() {
        if(cellNW != nullptr && cellSE != nullptr) {
            closed = false;
            if (artifact != nullptr)
                artifact->visible = false;
        }
    }

    bool is_closed() {
        return closed;
    }

    bool is_open() {
        return !closed;
    }

private:
    bool closed = true;
};



class Cell {
public:
    int row, column;
    Wall *north = nullptr;
    Wall *south = nullptr;
    Wall *east = nullptr;
    Wall *west = nullptr;

    Cell(int row, int column)
            : row(row), column(column) {
    }



private:
    Cell() {}

friend Grid;
};

class Grid {

public:
    std::vector<std::vector<Cell*>> cells;
    int num_columns;
    int num_rows;


    Grid(int num_rows, int num_columns)
            : num_columns(num_columns), num_rows(num_rows) {
        prepare_grid(cells);
        configure_cells();
        for(auto row = 0; row < num_rows; row++) {
            for(auto col = 0; col < num_columns; col++) {
                auto *c = cells[row][col];
                c->north->artifact = new cs4722::Artifact();
                c->west->artifact = new cs4722::Artifact();
                if(row == num_rows - 1) {
                    c->south->artifact = new cs4722::Artifact();
                }
                if(col == num_columns - 1) {
                    c->east->artifact = new cs4722::Artifact();
                }
            }
        }


    }

//    static Grid* with_artifacts(int width, int height) {
//        auto *gr = new Grid(width, height);
//        for(auto row = 0; row < gr->num_rows; row++) {
//            for(auto col = 0; col < gr->num_columns; col++) {
//                auto *c = gr->cells[row][col];
//                c->north->artifact = new cs4722::artifact();
//                c->west->artifact = new cs4722::artifact();
//                if(row == height-1) {
//                    c->south->artifact = new cs4722::artifact();
//                }
//                if(col == width-1) {
//                    c->east->artifact = new cs4722::artifact();
//                }
//            }
//        }
//        return gr;
//    }


    Cell* get(int row, int col){
        if(0 <= row && row < num_rows && 0 <= col && col < num_columns) {
            return cells[row][col];
        } else {
            return nullptr;
        }
    }

//    Cell* get_random_cell(){
//        int row = rand() % height;
//        int col = rand() % width;
//        return cells[row][col];
//    }

    int size(){
        return num_columns * num_rows;
    }

    std::string to_string() {
        const std::string space(" ");
        const std::string hyphen("-");
        const std::string space3("   ");
        const std::string hyphen3("---");
        const std::string corner("+");
        const std::string vbar("|");
        std::string output("+");
        for(auto i = 0; i < num_columns; i++) {
            output += std::string("---+");
        }
        output += "\n";
        for(auto row : cells) {
            auto top = std::string("|");
            auto bottom = std::string("+");
            for(auto* cell : row) {
                auto body = space3;  // three spaces
                auto east_boundary = cell->east->is_closed() ? vbar : space;
                top += body + east_boundary;
                auto south_boundary = cell->south->is_closed() ? hyphen3 : space3;
                bottom += south_boundary + corner;
            }
            output += top + "\n";
            output += bottom + "\n";
        }

        return output;
    }

    std::string to_string_debug() {
        std::string output;
        for(int row = 0; row < num_rows; row++) {
            std::string top;
            std::string middle;
            std::string bottom;
            for(int col = 0; col < num_columns; col++) {
                auto* c = cells[row][col];
                if(c->north->is_closed()) {
                    top += " *  ";
                } else {
                    top += " .  ";
                }
                if(c->west->is_closed())
                    if(c->east->is_closed())
                        middle += "* * ";
                    else
                        middle += "* . ";
                else
                    if(c->east->is_closed())
                        middle += ". * ";
                    else
                        middle += ". . ";
                if(c->south->is_closed()) {
                    bottom += " *  ";
                } else {
                    bottom += " .  ";
                }

            }
            output += top;
            output += "\n";
            output += middle;
            output += "\n";
            output += bottom;
            output += "\n";
        }
        return output;
    }



    std::vector<int> numeric_list() {
        std::vector<int> rep;
        // auto nr = num_rows;
        // auto nc = num_columns;

        for(int r = 0; r < num_rows; r++) {
            // north wall
            for(int c = 0; c < num_columns; c++) {
                auto cell = cells[r][c];
                rep.push_back(1);
                rep.push_back(cell->north->is_open() ? 0 : 1);
            }
            rep.push_back(1);

            // cell middle
            for(int c = 0; c < num_columns; c++) {
                auto cell = cells[r][c];
                rep.push_back(cell->west->is_open() ? 0 : 1);
                rep.push_back(0);
            }
            rep.push_back(cells[r][num_columns-1]->east->is_open() ? 0 : 1);

        }
        // bottom wall
        for(int c = 0; c < num_columns; c++) {
            auto cell = cells[num_rows-1][c];
            rep.push_back(1);
            rep.push_back(cell->south->is_open() ? 0 : 1);
        }
        rep.push_back(1);
        return rep;
    }



protected:
    void prepare_grid(std::vector<std::vector<Cell*>> &cells) {
//        auto cells = new std::vector<std::vector<Cell*>>();
        for(int r = 0; r < num_rows; r++ ) {
            std::vector<Cell*> row;
            for(int c = 0; c < num_columns; c++ ) {
                Cell *cell = new Cell(r,c);
                row.push_back(cell);
            }
            cells.push_back(row);
        }
//        return cells;
    }

    void configure_cells(){
        // north and east walls on each cell
        for(int row = 0; row < num_rows; row++ ) {
            for(int col = 0; col < num_columns; col++ ) {
                auto* c = cells[row][col];
                auto* cn = get(row-1, col);
                auto* cw = get(row, col-1);
                c->north = new Wall(cn, c);
                if(cn != nullptr)
                    cn->south = c->north;
                c->west = new Wall(cw, c);
                if(cw != nullptr) {
                    cw->east = c->west;
                }
            }
        }
        // east wall of grid
        for(int row = 0; row < num_rows; row++) {
            auto* c =  cells[row][num_columns - 1];
            c->east = new Wall(c, nullptr);
        }
        // south wall of grid
        for(int col = 0; col < num_columns; col++) {
            auto *c = cells[num_rows - 1][col];
            c->south = new Wall(c, nullptr);
        }
    }

};


/**
 * \brief MazeMetrics provides functions that locate walls and cells.
 */
class MazeMetrics {
public:
    int num_columns, num_rows;

    // size is the width and depth of a cell.
    double size = .5;     // s
    // thickness is the thickness of the walls between the cells
    double thickness = .05;  // t
    // wall_height is the height of the walls.
    double wall_height = size;  // g

    // extra amount to move boundary inside the cell
    double extra = 2*thickness;

    double x0 = 0;
    double z0 = 0;

    MazeMetrics(int num_rows, int num_columns, double size, double thickness, double wallHeight)
        : num_columns(num_columns), num_rows(num_rows),
           size(size),
           thickness(thickness),
           wall_height(wallHeight),
           extra(1.3*thickness)
           {}

    /**
     * \brief Return the location of the center of the cell at the given row and column.
     * The y coordinate is 0.
     *
     * @param row Should be in the range from 0 to height-1, inclusive
     * @param col Should be in the range from 0 to width-1, inclusive
     * @return The location of the center of the cell at the given row and column.
     *          The y coordinate is 0.
     */
    [[nodiscard]] glm::vec3 center_of_cell(int row, int col) const {
        auto x = (col + 1) * (size + thickness) - size / 2.0;
        auto z = (row + 1) * (size + thickness) - size / 2.0;
        return {x, 0, z};
    }

    [[nodiscard]] glm::vec3 center_north_wall(int row, int col) const {
        auto cc = center_of_cell(row, col);
        return cc + glm::vec3(0, wall_height / 2, -size/2 - thickness/2);
    }

    [[nodiscard]] glm::vec3 center_west_wall(int row, int col) const {
        auto cc = center_of_cell(row, col);
        return cc + glm::vec3(-size/2 - thickness/2, wall_height / 2, 0);
    }

    [[nodiscard]] glm::vec3 center_nw_pillar(int row, int col) const {
        auto cc = center_of_cell(row, col);
        return cc + glm::vec3(-size/2 - thickness/2, wall_height / 2, -size/2 - thickness/2);
    }



    [[nodiscard]] glm::vec3 scale_north_wall() const {
        return {size, wall_height, thickness};
    }

    [[nodiscard]] glm::vec3 scale_west_wall() const {
        return {thickness, wall_height, size};
    }

    [[nodiscard]] glm::vec3 scale_pillar() const {
        return {thickness, wall_height, thickness};
    }

    [[nodiscard]] glm::vec3 scale_base() const {
        return {num_columns * size + (num_columns + 1) * thickness,
                num_rows * size + (num_rows + 1) * thickness,
                1};
    }



    /**
     * \brief Return the z coordinate of the inside of the north wall of the specified cell.
     *
     * @return The z coordinate of the inside of the north wall of the specified cell.
     */
    [[nodiscard]] double north_z(int row, int col) const {
        auto nc = center_north_wall(row, col);
        return nc.z + thickness/2 + extra;
    }

    /**
     * \brief Return the z coordinate of the inside of the south wall of the specified cell.
     *
     * @return The z coordinate of the inside of the soyth wall of the specified cell.
     */
    [[nodiscard]] double south_z(int row, int col) const {
//        return north_z(row+1, col) - thickness - thickness;
        return north_z(row,col) + size - 2*extra;
    }

    /**
     * \brief Return the x coordinate of the inside of the west wall of the specified cell.
     *
     * @return The x coordinate of the inside of the west wall of the specified cell.
     */
    [[nodiscard]] double west_x(int row, int col) const {
        auto nc = center_west_wall(row, col);
        return nc.x + thickness/2 + extra;
    }

    /**
        * \brief Return the x coordinate of the inside of the east wall of the specified cell.
        *
        * @return The x coordinate of the inside of the east wall of the specified cell.
        */
    [[nodiscard]] double east_x(int row, int col) const {
        return west_x(row, col) + size - 2* extra;
    }

    void get_row_col(double x, double z, int &row, int &col) {
        auto delta = size + thickness;
        row = std::floor((z - z0) / delta);
        col = std::floor((x - x0) / delta);
    }

};


#endif //MAZE_FOR_PROGRAMMERS_GRID_H
