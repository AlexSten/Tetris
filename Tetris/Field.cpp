#include "Field.h"
#include "Figure.h"
#include <vector>
#include <algorithm>
#include <iostream>
#define _X (iter.GetX())
#define _Y (iter.GetY())
#define BufSize ((m_FieldHeight + 1)*(m_FieldWidth + 2))
#define Array(x, y) (m_Array[((y) * (m_FieldWidth + 2) + (x))])
#define ArrForDispl(x, y) (m_ArrayForDisplay[((y) * (m_FieldWidth + 2) + (x))])

Field::Field(const int& _width, const int& _height) : m_FieldWidth(_width), m_FieldHeight(_height)
{
  m_hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
  m_coord.X = 0;
  m_coord.Y = 0;
  m_size.X = m_FieldWidth + 2;
  m_size.Y = m_FieldHeight + 1;
  m_sr.Left = 0; m_sr.Top = 0; m_sr.Right = m_FieldWidth + 2; m_sr.Bottom = m_FieldHeight + 1;

  CONSOLE_CURSOR_INFO cursor = { 1, false };
  SetConsoleCursorInfo(m_hStdOut, &cursor);
  
  m_Array = new CHAR_INFO[BufSize];
  m_ArrayForDisplay = new CHAR_INFO[BufSize];
  
  CreateField();
  
  DisplayYourself();
}

Field::~Field()
{
  delete[] m_Array;
  delete[] m_ArrayForDisplay;
}

void Field::DisplayYourself()
{
  FillingArrayForDisplay();

  WriteConsoleOutput(
    m_hStdOut,
    m_ArrayForDisplay,
    m_size,
    m_coord,
    &m_sr);
}

void Field::DisplayYourself(const std::vector<Cell>& _SourceOfCoordinates)
{
  FillingArrayForDisplay(_SourceOfCoordinates);

  WriteConsoleOutput(
    m_hStdOut,
    m_ArrayForDisplay,
    m_size,
    m_coord,
    &m_sr);
}

void Field::HideFullLines()
{
  if (FindFullLines())
  {
    DeleteLines();
    ShiftField();
    DisplayYourself();
  }
}

void Field::DeleteLines()
{
  for (auto iterator : m_vFullLines)
  for (size_t i = 1; i <= m_FieldWidth; i++)
    Array(i, iterator).Char.UnicodeChar = ' ';

}

bool Field::FindFullLines()
{
  bool flag = true;
  bool detected = false;
  m_vFullLines.clear();
  for (size_t j = 0; j < m_FieldHeight; j++)
  {
    for (size_t i = 0; i <= m_FieldWidth; i++)
    if (Array(i, j).Char.UnicodeChar == ' ')
      flag = false;

    if (flag)
    {
      m_vFullLines.push_back(j);
      detected = true;
    }
    flag = true;
  }
  return detected;
}

void Field::ShiftField()
{
  std::vector<int> tempRevVec;
  tempRevVec.resize(m_vFullLines.size());
  std::reverse_copy(m_vFullLines.begin(), m_vFullLines.end(), tempRevVec.begin());

  for (auto iter : m_vFullLines)
  for (size_t y = iter; y > 0; y--)
  for (size_t x = 1; x <= m_FieldWidth; ++x)
  {
    Array(x, y) = Array(x, y - 1);
    Array(x, y - 1).Char.UnicodeChar = ' ';
  }
}

void Field::FillingArrayForDisplay()
{
  for (size_t x = 0; x < BufSize; x++)  
    m_ArrayForDisplay[x] = m_Array[x];
}


void Field::FillingArrayForDisplay(const std::vector<Cell>& _SourceOfCoordinates)
{
  for (size_t x = 0; x < BufSize; x++)
    m_ArrayForDisplay[x] = m_Array[x];
  
  for (auto iter: _SourceOfCoordinates)
  {
    ArrForDispl(_X, _Y).Char.UnicodeChar = '#';
    ArrForDispl(_X, _Y).Attributes = GetColorForFig(iter.GetType());
  }
}

void Field::AcceptFigure(const std::vector<Cell>& _SourceOfCoordinates)
{
  for (auto iter : _SourceOfCoordinates)
  {
    Array(_X, _Y).Char.UnicodeChar = '#';
    Array(_X, _Y).Attributes = GetColorForFig(iter.GetType());
  }
}

void Field::CreateField()
{
  for (size_t i = 0; i < BufSize; i++)
  {
    if (i % (m_FieldWidth + 2) == 0)
    {
      m_Array[i].Char.UnicodeChar = '#';
      m_Array[i].Attributes = BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE;
    }
    else if (i % (m_FieldWidth + 2) == (m_FieldWidth + 1))
    {
      m_Array[i].Char.UnicodeChar = '#';
      m_Array[i].Attributes = BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE;
    }
    else if (i > ((m_FieldWidth + 2) * m_FieldHeight))
    {
      m_Array[i].Char.UnicodeChar = '#';
      m_Array[i].Attributes = BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE;
    }
    else
    {
      m_Array[i].Char.UnicodeChar = ' ';
      m_Array[i].Attributes = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY;
    }
  }
}

WORD Field::GetColorForFig(const RandomForFig::FigureType& _type)const
{
  WORD wAttribute;
  switch (_type)
  {
  case RandomForFig::FigureType::I:
    wAttribute = BACKGROUND_BLUE | BACKGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
    break;
  case RandomForFig::FigureType::O:
    wAttribute = BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY;
    break;
  case RandomForFig::FigureType::L:
    wAttribute = BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
    break;
  case RandomForFig::FigureType::J:
    wAttribute = BACKGROUND_BLUE | FOREGROUND_BLUE;
    break;
  case RandomForFig::FigureType::S:
    wAttribute = BACKGROUND_GREEN | BACKGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
    break;
  case RandomForFig::FigureType::Z:
    wAttribute = BACKGROUND_RED | BACKGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_INTENSITY;
    break;
  case RandomForFig::FigureType::T:
    wAttribute = BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY;
    break;
  default:
    break;
  }
  return wAttribute;
}

bool Field::DetectedFloorForFig(std::vector<Cell> _SourceOfCoordinates)
{
  for (auto iter : _SourceOfCoordinates)
    if (Array(_X, _Y + 1).Char.UnicodeChar == '#')
      return true;
  
  return false;
}

bool Field::LeftBlock(const std::vector<Cell>& _SourceOfCoordinates)const
{
  for (auto iter : _SourceOfCoordinates)
    if (Array(_X - 1, _Y).Char.UnicodeChar == '#')
      return true;

  return false;
}

bool Field::RightBlock(const std::vector<Cell>& _SourceOfCoordinates)const
{
  for (auto iter : _SourceOfCoordinates)
    if (Array(_X + 1, _Y).Char.UnicodeChar == '#')
      return true;

  return false;
}

bool Field::IsLeftBorder(const std::vector<Cell>& _SourceOfCoordinates)const
{
  for (auto iter : _SourceOfCoordinates)
    if (_X == 1)
      return true;

  return false;
}

bool Field::IsRightBorder(const std::vector<Cell>& _SourceOfCoordinates)const
{
  for (auto iter : _SourceOfCoordinates)
    if (_X == m_FieldWidth)
      return true;
  
  return false;
}

bool Field::IsAvailableTurn(const std::vector<Cell>& _SourceOfCoordinates)const
{
  for (auto iter : _SourceOfCoordinates)
    if (Array(_X, _Y).Char.UnicodeChar != ' ')
      return false;
  
  return true;
}

bool Field::PlaceForFigure(const std::vector<Cell>& _SourceOfCoordinates)const
{
  for (auto iter : _SourceOfCoordinates)
    if (Array(_X, _Y).Char.UnicodeChar == '#')
      return false;
  
  return true;
}