#ifndef FIGURE_H
#define FIGURE_H
#include "Cell.h"
#include "RandomForFig.h"
#include <vector>

class Figure : private Cell, RandomForFig
{
private:
  Cell cell1;
  Cell cell2;
  Cell cell3;
  Cell cell4;
  std::vector<Cell> m_vCells;
  FigureType m_TypeOfFigure;
  int m_iCurrentStateFigure;
public:
  Figure();
  std::vector<Cell> GetCoordinates();
  std::vector<Cell> GetCoordinatesForTurn();            // отправляет координаты, которые будет иметь фигура, после поврота
  void GenerateNewFig();

  void Turn();
  void LoweringFig();
  void MoveLeft();
  void MoveRight();
private:
  void TurnI();
  void TurnT();
  void TurnZ();
  void TurnS();
  void TurnL();
  void TurnJ();

  void SetCoordinates();
};

#endif FIGURE_H