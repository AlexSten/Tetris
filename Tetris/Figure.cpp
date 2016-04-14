#include "Figure.h"


Figure::Figure()
{
  m_TypeOfFigure = getRandType();
  m_iCurrentStateFigure = 1;
  SetCoordinates();
}

std::vector<Cell> Figure::GetCoordinates()
{
  m_vCells.clear();
  m_vCells.push_back(cell1); 
  m_vCells.push_back(cell2);
  m_vCells.push_back(cell3);
  m_vCells.push_back(cell4);
  return m_vCells;
}

std::vector<Cell> Figure::GetCoordinatesForTurn()
{
  Cell curCell1 = cell1;
  Cell curCell2 = cell2;
  Cell curCell3 = cell3;
  Cell curCell4 = cell4;
  Turn();

  m_vCells.clear();
  m_vCells.push_back(cell1);
  m_vCells.push_back(cell2);
  m_vCells.push_back(cell3);
  m_vCells.push_back(cell4);

  cell1 = curCell1;
  cell2 = curCell2;
  cell3 = curCell3;
  cell4 = curCell4;
  if (m_iCurrentStateFigure != 1)
    --m_iCurrentStateFigure;
  else
    m_iCurrentStateFigure = 4;

  return m_vCells;
}

void Figure::SetCoordinates()
{
  switch (m_TypeOfFigure)
  {
  case I:
  {
          cell1 = Cell(5, 0, m_TypeOfFigure);
          cell2 = Cell(5, 1, m_TypeOfFigure);
          cell3 = Cell(5, 2, m_TypeOfFigure);
          cell4 = Cell(5, 3, m_TypeOfFigure);
          break;
  }
  case O:
  {
          cell1 = Cell(5, 0, m_TypeOfFigure);
          cell2 = Cell(6, 0, m_TypeOfFigure);
          cell3 = Cell(5, 1, m_TypeOfFigure);
          cell4 = Cell(6, 1, m_TypeOfFigure);
          break;
  }
  case L:
  {
          cell1 = Cell(5, 0, m_TypeOfFigure);
          cell2 = Cell(5, 1, m_TypeOfFigure);
          cell3 = Cell(5, 2, m_TypeOfFigure);
          cell4 = Cell(6, 2, m_TypeOfFigure);
          break;
  }
  case J:
  {
          cell1 = Cell(6, 0, m_TypeOfFigure);
          cell2 = Cell(6, 1, m_TypeOfFigure);
          cell3 = Cell(6, 2, m_TypeOfFigure);
          cell4 = Cell(5, 2, m_TypeOfFigure);
          break;
  }
  case S:
  {
          cell1 = Cell(5, 1, m_TypeOfFigure);
          cell2 = Cell(6, 1, m_TypeOfFigure);
          cell3 = Cell(6, 0, m_TypeOfFigure);
          cell4 = Cell(7, 0, m_TypeOfFigure);
          break;
  }
  case Z:
  {
          cell1 = Cell(5, 0, m_TypeOfFigure);
          cell2 = Cell(6, 0, m_TypeOfFigure);
          cell3 = Cell(6, 1, m_TypeOfFigure);
          cell4 = Cell(7, 1, m_TypeOfFigure);
          break;
  }
  case T:
  {
          cell1 = Cell(6, 0, m_TypeOfFigure);
          cell2 = Cell(5, 1, m_TypeOfFigure);
          cell3 = Cell(6, 1, m_TypeOfFigure);
          cell4 = Cell(7, 1, m_TypeOfFigure);
          break;
  }
  default:
    break;
  }
}

void Figure::LoweringFig()
{
  cell1.lower();
  cell2.lower();
  cell3.lower();
  cell4.lower();
}

void Figure::MoveLeft()
{
  --cell1;
  --cell2;
  --cell3;
  --cell4;
}

void Figure::MoveRight()
{
  ++cell1;
  ++cell2;
  ++cell3;
  ++cell4;
}

void Figure::Turn()
{
  switch (m_TypeOfFigure)
  {
  case I:
    TurnI();
    break;
  case O:
    break;
  case L:
    TurnL();
    break;
  case J:
    TurnJ();
    break;
  case S:
    TurnS();
    break;
  case Z:
    TurnZ();
    break;
  case T:
    TurnT();
    break;
  default:
    break;
  }
  ++m_iCurrentStateFigure;

  if (m_iCurrentStateFigure == 5)
    m_iCurrentStateFigure = 1;
}

void Figure::GenerateNewFig()
{
  m_TypeOfFigure = getRandType();
  SetCoordinates();
  m_iCurrentStateFigure = 1;
}

void Figure::TurnI()
{
  int x, y;
  if (m_iCurrentStateFigure%2 != 0)
  {
    x = cell1.GetX() - 1;
    y = cell2.GetY() - 1;
    cell1.SetCoord(x, y);
    cell2.SetCoord(x + 1, y);
    cell3.SetCoord(x + 2, y);
    cell4.SetCoord(x + 3, y);
  }
  else
  {
    x = cell2.GetX();
    y = cell2.GetY();
    cell1.SetCoord(x, y);
    cell2.SetCoord(x, y + 1);
    cell3.SetCoord(x, y + 2);
    cell4.SetCoord(x, y + 3);
  }
}

void Figure::TurnT()
{
  int x = cell3.GetX() - 1;
  int y = cell3.GetY() - 1;
  switch (m_iCurrentStateFigure)
  {
  case 1:
  {
          cell1.SetCoord(x + 2, y + 1);
          cell2.SetCoord(x + 1, y);
          cell3.SetCoord(x + 1, y + 1);
          cell4.SetCoord(x + 1, y + 2);
  }break;
  case 2:
  {
          cell1.SetCoord(x + 1, y + 2);
          cell2.SetCoord(x + 2, y + 1);
          cell3.SetCoord(x + 1, y + 1);
          cell4.SetCoord(x, y + 1);
  }break;
  case 3:
  {
          cell1.SetCoord(x, y + 1);
          cell2.SetCoord(x + 1, y + 2);
          cell3.SetCoord(x + 1, y + 1);
          cell4.SetCoord(x + 1, y);
  }break;
  case 4:
  {
          cell1.SetCoord(x + 1, y);
          cell2.SetCoord(x, y + 1);
          cell3.SetCoord(x + 1, y + 1);
          cell4.SetCoord(x + 2, y + 1);
  }break;
  default:
    break;
  }
}

void Figure::TurnZ()
{
  if (m_iCurrentStateFigure % 2 != 0)
  {
    int x = cell3.GetX() - 1;
    int y = cell3.GetY() - 1;
    cell1.SetCoord(x + 1, y);
    cell2.SetCoord(x + 1, y + 1);
    cell3.SetCoord(x, y + 1);
    cell4.SetCoord(x, y + 2);
  }
  else
  {
    int x = cell2.GetX() - 1;
    int y = cell2.GetY() - 1;
    cell1.SetCoord(x, y);
    cell2.SetCoord(x + 1, y);
    cell3.SetCoord(x + 1, y + 1);
    cell4.SetCoord(x + 2, y + 1);
  }
}

void Figure::TurnS()
{
  if (m_iCurrentStateFigure % 2 != 0)
  {
    int x = cell2.GetX() - 1;
    int y = cell2.GetY() - 1;
    cell1.SetCoord(x + 1, y);
    cell2.SetCoord(x + 1, y + 1);
    cell3.SetCoord(x + 2, y + 1);
    cell4.SetCoord(x + 2, y + 2);
  }
  else
  {
    int x = cell1.GetX();
    int y = cell1.GetY();
    cell1.SetCoord(x - 1, y + 1);
    cell2.SetCoord(x, y + 1);
    cell3.SetCoord(x, y);
    cell4.SetCoord(x + 1, y);
  }
}

void Figure::TurnL()
{
  switch (m_iCurrentStateFigure)
  {
  case 1:
  {
          int x = cell2.GetX() - 1;
          int y = cell2.GetY() - 1;
          cell1.SetCoord(x, y + 1);
          cell2.SetCoord(x + 1, y + 1);
          cell3.SetCoord(x + 2, y + 1);
          cell4.SetCoord(x + 2, y);
  }break;
  case 2:
  {
          int x = cell2.GetX();
          int y = cell2.GetY() - 1;
          cell1.SetCoord(x + 1, y);
          cell2.SetCoord(x + 2, y);
          cell3.SetCoord(x + 2, y + 1);
          cell4.SetCoord(x + 2, y + 2);
  }break;
  case 3:
  {
          int x = cell1.GetX() - 1;
          int y = cell1.GetY();
          cell1.SetCoord(x + 2, y);
          cell2.SetCoord(x + 1, y);
          cell3.SetCoord(x, y);
          cell4.SetCoord(x, y + 1);
  }break;
  case 4:
  {
          int x = cell3.GetX() - 1;
          int y = cell3.GetY();
          cell1.SetCoord(x + 1, y);
          cell2.SetCoord(x + 1, y + 1);
          cell3.SetCoord(x + 1, y + 2);
          cell4.SetCoord(x + 2, y + 2);
  }break;
  default:
    break;
  }
}

void Figure::TurnJ()
{
  switch (m_iCurrentStateFigure)
  {
  case 1:
  {
          int x = cell2.GetX() - 1;
          int y = cell2.GetY() - 1;
          cell1.SetCoord(x + 2, y + 1);
          cell2.SetCoord(x + 1, y + 1);
          cell3.SetCoord(x, y + 1);
          cell4.SetCoord(x, y);
  }break;
  case 2:
  {
          int x = cell2.GetX() - 1;
          int y = cell2.GetY() - 1;
          cell1.SetCoord(x, y + 2);
          cell2.SetCoord(x, y + 1);
          cell3.SetCoord(x, y);
          cell4.SetCoord(x + 1, y);
  }break;
  case 3:
  {
          int x = cell3.GetX();
          int y = cell3.GetY();
          cell1.SetCoord(x, y);
          cell2.SetCoord(x + 1, y);
          cell3.SetCoord(x + 2, y);
          cell4.SetCoord(x + 2, y + 1);
  }break;
  case 4:
  {
          int x = cell1.GetX();
          int y = cell1.GetY();
          cell1.SetCoord(x + 1, y);
          cell2.SetCoord(x + 1, y + 1);
          cell3.SetCoord(x + 1, y + 2);
          cell4.SetCoord(x, y + 2);
  }break;
  default:
    break;
  }
}