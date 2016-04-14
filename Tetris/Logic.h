#ifndef LOGIC_H
#define LOGIC_H

#include "Field.h"
#include "Figure.h"

class Logic
{
private:
  Field m_GF;           // game field
  Figure m_figobj;

  const int m_delay;
public:
  Logic(const int& _delay = 400, const int& _width = 10, const int& _height = 20);
  void MainLoop();
  void Control();
  bool FallingOfFigure();
  bool DetectPressedButton();
};

#endif LOGIC_H