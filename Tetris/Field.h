#ifndef FIELD_H
#define FIELD_H
#include <vector>
#include <Windows.h>
#include "RandomForFig.h"

class Cell;

class Field
{
private:
  const unsigned int m_FieldWidth;
  const unsigned int m_FieldHeight;

  CHAR_INFO *m_Array;
  CHAR_INFO *m_ArrayForDisplay;

  HANDLE m_hStdOut; 
  COORD m_size;
  COORD m_coord;
  SMALL_RECT m_sr;

  std::vector<int> m_vFullLines;
public:
  Field(const int& _width, const int& _height);
  ~Field();
  void DisplayYourself();
  void DisplayYourself(const std::vector<Cell>&);
  void HideFullLines();
  void AcceptFigure(const std::vector<Cell>&);

  bool DetectedFloorForFig(std::vector<Cell>);
  bool LeftBlock(const std::vector<Cell>&)const;
  bool RightBlock(const std::vector<Cell>&)const;
  bool IsLeftBorder(const std::vector<Cell>&)const;
  bool IsRightBorder(const std::vector<Cell>&)const;
  bool IsAvailableTurn(const std::vector<Cell>&)const;
  bool PlaceForFigure(const std::vector<Cell>&)const;
private:
  void CreateField();
  WORD GetColorForFig(const RandomForFig::FigureType& _type)const;
  bool FindFullLines();
  void DeleteLines();
  void ShiftField();
  void FillingArrayForDisplay();
  void FillingArrayForDisplay(const std::vector<Cell>&);
};

#endif FIELD_H