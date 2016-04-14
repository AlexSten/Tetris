#include "RandomForFig.h"
#include <time.h>
#include <stdlib.h>


RandomForFig::RandomForFig()
{
  srand((unsigned int)time(NULL));
}

RandomForFig::FigureType RandomForFig::getRandType()const
{
  switch (rand() % 7 + 1)
  {
  case 1:
    return I;
  case 2:
    return O;
  case 3:
    return L;
  case 4:
    return J;
  case 5:
    return S;
  case 6:
    return Z;
  case 7:
    return T;
  default:
    return I;
  }
}