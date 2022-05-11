#include <p6/p6.h>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
#include "./include/menu.hpp"

struct CellCoord {
    int x;
    int y;
};

struct Coord {
    float x;
    float y;
};

std::vector<CellCoord> createCellVector(const int& size)
{
    std::vector<CellCoord> tab;

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            tab.push_back(CellCoord{j, i});
        }
    }

    for (int i = 0; i < size * size; i++) {
        std::cout << i << "x= " << tab[i].x << " y= " << tab[i].y << std::endl;
    }

    return tab;
}

Coord turnCellCordIntoP6Coord(const CellCoord& coord, const float& squareSize, const float& gap, p6::Context& ctx)
{
    Coord P6Coord;
    /* std::cout << "aspectratio: " << ctx.aspect_ratio() << " gap: " << gap << " squareSize: " << squareSize << std::endl; */
    P6Coord.x = -ctx.aspect_ratio() + (squareSize / 2 + (coord.x * squareSize) + (coord.x * gap));
    P6Coord.y = 1.f - (squareSize / 2 + (coord.y * squareSize) + (coord.y * gap));

    /* std::cout << "x= " << P6Coord.x << " y= " << P6Coord.y << std::endl; */

    return P6Coord;
}

bool isHover(p6::Context& ctx, const Coord& cell, const float& squareSize)
{
    if (ctx.mouse().x >= cell.x - (squareSize / 2) && ctx.mouse().x <= cell.x + (squareSize / 2) && ctx.mouse().y >= cell.y - (squareSize / 2) && ctx.mouse().y <= cell.y + (squareSize / 2))
        return true;
    else {
        return false;
    }
}

void draw_nought(p6::Context& ctx, const Coord& coord, const float& square_size)
{
    ctx.circle(p6::Center{coord.x, coord.y}, p6::Radius{(square_size * 0.45f)});
}

void draw_cross(p6::Context& ctx, const Coord& coord, const float& square_size)
{
    /*   triangle(Point2D p1, Point2D p2, Point2D p3) */
    float       radius = square_size * 0.45f;
    p6::Point2D p1((coord.x + radius * 0.866 * cos(p6::PI / 2)), (coord.y + radius * 0.866 * sin(p6::PI / 2)));
    p6::Point2D p2((coord.x + radius * cos((5 * p6::PI) / 4)), (coord.y + radius * sin((5 * p6::PI) / 4)));
    p6::Point2D p3((coord.x + radius * cos((7 * p6::PI) / 4)), (coord.y + radius * sin((7 * p6::PI) / 4)));
    ctx.triangle(p1, p2, p3);
}

void create_grid(p6::Context& ctx, const std::vector<CellCoord> cellVec, const float& square_size, const float& gap)
{
    //faire une fonction qui transforme coord d'une cellule avec en coordonnée P6
    //utiliser le vecteur pour placer correctement les cases
    //dessiner les cases
    ctx.fill = {0.20, 0.49, 0.85};

    ctx.use_stroke = false;
    //std::cout << size << std::endl;
    //DRAWING FIRST LINE
    Coord coord;
    for (auto i = 0; i < static_cast<int>(cellVec.size()); i++) {
        coord = turnCellCordIntoP6Coord(cellVec[i], square_size, gap, ctx);
        if (isHover(ctx, coord, square_size)) {
            ctx.fill = {0.7, 0.49, 0.85};
        }
        else {
            ctx.fill = {0.20, 0.49, 0.85};
        }

        ctx.square(p6::Center{coord.x, coord.y}, p6::Radius{square_size / 2});
        ctx.fill = {0.0, 0.0, 0.0};
        if (isHover(ctx, coord, square_size)) {
            draw_cross(ctx, coord, square_size);
        }
    }
}

int main()
{
    auto                   ctx         = p6::Context{{1000, 1000, "Noughts and Crosses"}};
    const int              nbRows      = 3;
    const float            gap         = ((ctx.aspect_ratio() * 2) / 100);
    const float            square_size = (((ctx.aspect_ratio() * 2) - ((nbRows - 1) * gap)) / nbRows);
    std::vector<CellCoord> cellVector;
    cellVector = createCellVector(nbRows);

    turnCellCordIntoP6Coord(cellVector[0], square_size, gap, ctx);
    turnCellCordIntoP6Coord(cellVector[1], square_size, gap, ctx);
    turnCellCordIntoP6Coord(cellVector[2], square_size, gap, ctx);

    ctx.update = [&]() {
        ctx.background({1.f, 1.f, 1.f});
        std::cout << ctx.mouse().x << ctx.mouse().y << std::endl;
        create_grid(ctx, cellVector, square_size, gap);
    };

    ctx.start();
    //display_menu();

    return 0;
}
