#include "entrypoint.h"
#include "raylib.h"
#include <vector>
#include "grid.h"
#include <utility>
#include <iostream>

//https://www.youtube.com/watch?v=daFYGrXq0aw

void Grid::Draw()
{
    for(int row = 0; row < rows; row++){
        for(int column = 0; column < columns; column++){
                                                //Couleur des cellules vivantes  //Couleur des cellules morte
            Color color = cells[row][column] ? Color{ 0, 121, 241, 155 } : Color{ 0, 0, 0, 255 };
            DrawRectangle(column * cellSize, row * cellSize, cellSize - 1, cellSize - 1, color); //Dessine les cellules avec une grosseur de cellsize - 1 pour pouvoir voir les lignes.
        }
    }
}

void Grid::SetValue(int row, int column, int value)
{
    if(IsWithinBounds(row, column)){
        cells[row][column] = value;
    }
}

int Grid::GetValue(int row, int column)
{
    if(IsWithinBounds(row, column))
    {
        return cells[row][column];
    }
      return 0;
}

bool Grid::IsWithinBounds(int row, int column)
{
     if(row >= 0 && row < rows && column >= 0 && column < columns)
     {
        return true;
     }
    return false;
}

void Grid::FillRandom()
{
    for(int row = 0; row < rows; row++)
    {
        for(int column = 0; column < columns; column++)
        {
            int RandomValue = GetRandomValue(0, 4);
            cells[row][column] = (RandomValue == 4) ? 1 : 0;
        }
    }
}

void Simulation::Draw()
{
    grid.Draw();
}

void Simulation::SetCellValue(int row, int column, int value)
{
    grid.SetValue(row, column, value);
}

int Simulation::CountLiveNeighbors(int row, int column)
{
    int LiveNeighbors = 0;
    std::vector<std::pair<int, int>> neighborOffsets = 
    {
        {-1, 0},    //cellule en haut
        {1, 0},     //cellule en bas
        {0, -1},    //cellule à gauche
        {0, 1},     //cellule à droite
        {-1, -1},   //cellule en haut à gauche
        {-1, 1},    //cellule en haut à droit
        {1, -1},    //cellule en bas à gauche
        {1, 1}      //cellule en bas à droite
    };

    for(const auto& offset : neighborOffsets)
    {
        int neighborRow = (row + offset.first + grid.GetRows()) % grid.GetRows();
        int neighborColumn = (column + offset.second + grid.GetColumns()) % grid.GetColumns();
        LiveNeighbors += grid.GetValue(neighborRow, neighborColumn);
    }
    return LiveNeighbors;
}

void Simulation::Update()
{
        for(int row = 0; row < grid.GetRows(); row++)
        {
            for(int column = 0; column < grid.GetColumns(); column++)
            {
                int LiveNeighbors = CountLiveNeighbors(row, column);
                int CellValue = grid.GetValue(row, column);

                if(CellValue == 1)
                {
                    if(LiveNeighbors > 3 || LiveNeighbors < 2)
                    {
                        TempGrid.SetValue(row, column, 0);
                    }
                    else
                    {
                        TempGrid.SetValue(row, column, 1);
                    }
                }
                else
                {
                    if(LiveNeighbors == 3)
                    {
                        TempGrid.SetValue(row, column, 1);
                    }
                    else 
                    {
                        TempGrid.SetValue(row, column, 0);
                    }
                }
            }
        }
        grid = TempGrid;
}

void raylib_start(void)
{
    Color LINE_COLOR = {112, 31, 126, 255}; //Couleur des lignes de la grille
    const int CELL_SIZE = 25; // Grosseur des cellules 25 pixels par 25 pixels
  
     
    InitWindow(750,750, "Game of Life"); //Initiation de la fenêtre avec les dimensions et le titre
    SetTargetFPS(15); //Déclaration du nombre de fps que la fenêtre auras
    Simulation simulation{750, 750, CELL_SIZE}; //Déclaration des dimensions de la fenêtre avec la taille des cellules


    while(!WindowShouldClose()){
        if(IsKeyDown(KEY_ESCAPE)){ //Si la touche escape est appuyer la fenêtre se ferme
        break;
        }

        simulation.Update(); //Updater les cellules selon les règles

        BeginDrawing(); //Début du dessin
        ClearBackground(LINE_COLOR); // Clear le background et mettre la couleur du background la couleur des lignes
        simulation.Draw(); //Dessiner la grille avec l'état des cellules généré aléatoirement
        EndDrawing(); //Fin du dessin
    }
}