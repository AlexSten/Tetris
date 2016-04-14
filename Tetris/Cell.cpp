#include "Cell.h"


Cell::Cell()
{

}

Cell::Cell(int _x, int _y, RandomForFig::FigureType _type) : m_x(_x), m_y(_y), m_TypeOfFigure(_type)
{
}

Cell::Cell(const Cell& _sourceCopy)
{
  m_x = _sourceCopy.GetX();
  m_y = _sourceCopy.GetY();
  m_TypeOfFigure = _sourceCopy.GetType();
}

int Cell::GetX()const
{
  return m_x;
}

int Cell::GetY()const
{
  return m_y;
}

RandomForFig::FigureType Cell::GetType()const
{
  return m_TypeOfFigure;
}

void Cell::SetCoord(const int& _x, const int& _y)
{
  m_x = _x;
  m_y = _y;  
}

void Cell::SetType(RandomForFig::FigureType _type)
{
  m_TypeOfFigure = _type;
}

void Cell::lower()
{
  ++m_y;
}

Cell& Cell::operator++()
{
  ++m_x;
  return (*this);
}

Cell& Cell::operator--()
{
  --m_x;
  return (*this);
}