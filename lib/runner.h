#ifndef RUNNER_H
#define RUNNER_H

#include "N5110.h"
#include "mbed.h"

#include "Utils.h"

class Runner {
public:
  Runner();
  void init(int size, int speed);
  void draw(N5110 &lcd);
  void update(UserInput input);
  void jump();
  void add_score();
  int get_score();
  void set_velocity(Position2D v);
  Position2D get_velocity();
  Position2D get_pos();
  int get_size();
  void set_pos(Position2D p);

private:
  Position2D _velocity;
  int _size;
  int _x;
  int _y;
  int _score ;
  bool _jump = false;
  int _i = 0;
};
#endif