#ifndef RANDOM_FOR_FIG_H
#define RANDOM_FOR_FIG_H
class RandomForFig
{
public:
  enum FigureType
  {
    I = 1,
    O,
    L,
    J,
    S,
    Z,
    T
  };
protected:
  RandomForFig();
  FigureType getRandType()const;
};

#endif RANDOM_FOR_FIG_H