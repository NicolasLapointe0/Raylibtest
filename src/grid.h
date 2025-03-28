#pragma once
#include <vector>

class Grid // Fonctions pour la grille
{
    public:
    
        Grid(int width, int height, int cellSize)
        : rows(height/cellSize), columns(width/cellSize), cellSize(cellSize), cells(rows, std::vector<int>(columns, 0)){}; //construction de la grille avec la hauteur la largeur et la grosseur des cellules
        void Draw();
        void SetValue(int row, int column, int values);
        int GetValue(int row, int column);
        bool IsWithinBounds(int row, int column);
        int GetRows(){return rows;}
        int GetColumns(){return columns;} 
        void FillRandom();

    private:

        int rows; //Déclaration des rangées
        int columns; //Déclaration des collonnes
        int cellSize; //Déclaration de la taille des cellules
        std::vector<std::vector<int>> cells; 
};

class Simulation //Fonctions pour la simulation (jeu)
{
    public:
        
        Simulation(int width, int height, int cellSize)
        : grid(width, height, cellSize), TempGrid(width, height, cellSize) {grid.FillRandom();}
        void Draw();
        void SetCellValue(int row, int column, int value);
        int CountLiveNeighbors(int row, int column);
        void Update();
       
        

    private:
        
        Grid grid;
        Grid TempGrid;
        bool Run;
};

#ifdef __cplusplus
extern "C"{
#endif

void raylib_start(void);

#ifdef __cplusplus
}
#endif