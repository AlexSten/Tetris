#ifndef CELL_H
#define CELL_H
#include "RandomForFig.h"

class Cell
{
private:
  int m_x;
  int m_y;
  RandomForFig::FigureType m_TypeOfFigure;
public:
  Cell();
  Cell(const Cell&);
  Cell(int _x, int _y, RandomForFig::FigureType _type);

  int GetX()const;
  int GetY()const;
  RandomForFig::FigureType GetType()const;

  void SetCoord(const int& _x, const int& _y);
  void SetType(RandomForFig::FigureType _type);
  void lower();             // Move to down
  Cell& operator++();       // Move to right
  Cell& operator--();       // Move to left
};

#endif