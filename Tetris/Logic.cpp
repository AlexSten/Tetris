#include "Logic.h"
#include "Field.h"
#include "Figure.h"
#include <Windows.h>
#include <time.h>
#include <iostream>

#define Figure m_figobj.GetCoordinates()


Logic::Logic(const int& _delay, const int& _width, const int& _height) : m_delay(_delay), m_GF(_width, _height){}

bool Logic::FallingOfFigure()
{
  if (m_GF.DetectedFloorForFig(Figure))
  {
    m_GF.AcceptFigure(Figure);

    m_figobj.GenerateNewFig();
    if (!m_GF.PlaceForFigure(Figure))
      return false;
  }
  else
    m_figobj.LoweringFig();
  return true;
}

bool Logic::DetectPressedButton()
{
  bool isDetected = false;
  if (GetAsyncKeyState(VK_UP))
  {
    keybd_event(VK_UP, 0, KEYEVENTF_KEYUP, 0);                      //Отжимаем кнопку
    if (m_GF.IsAvailableTurn(m_figobj.GetCoordinatesForTurn()))
    {
      m_figobj.Turn();
      isDetected = true;
    }
  }
  if (GetAsyncKeyState(VK_DOWN))
  {
    keybd_event(VK_DOWN, 0, KEYEVENTF_KEYUP, 0);                    //Отжимаем кнопку
    while (!m_GF.DetectedFloorForFig(Figure))
    {
      m_figobj.LoweringFig();
      isDetected = true;
    }
  }
  if (GetAsyncKeyState(VK_LEFT))
  {
    keybd_event(VK_LEFT, 0, KEYEVENTF_KEYUP, 0);                    //Отжимаем кнопку
    if (!m_GF.LeftBlock(Figure) && !m_GF.IsLeftBorder(Figure))
    {
      m_figobj.MoveLeft();
      isDetected = true;
    }
  }
  if (GetAsyncKeyState(VK_RIGHT))
  {
    keybd_event(VK_RIGHT, 0, KEYEVENTF_KEYUP, 0);                   //Отжимаем кнопку
    if (!m_GF.RightBlock(Figure) && !m_GF.IsRightBorder(Figure))
    {
      m_figobj.MoveRight();
      isDetected = true;
    }
  }
  return isDetected;
}

void Logic::Control()
{
  if (DetectPressedButton())
    m_GF.DisplayYourself(Figure);
}

void Logic::MainLoop()
{
  clock_t start = clock();
  while (true)
  {
    clock_t deltaTime = clock() - start;
    
    Control();

    if (deltaTime > m_delay)
    {
      if (!FallingOfFigure())             // checking on game over
        break;
      m_GF.HideFullLines();

      m_GF.DisplayYourself(Figure);

      start = clock();
    }
  }
}