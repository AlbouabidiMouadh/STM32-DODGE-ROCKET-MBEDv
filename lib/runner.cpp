#include "runner.h"

Runner::Runner() {}

void Runner::init(int size, int speed)
{
  _size = size;
  _x = 15 - _size / 2;
  _y = 35 - _size / 2;
  _velocity.x = speed;
  _velocity.y = speed;
  _score = 0;
  bool _jump = false;
  int _i = 0;
}

void Runner::draw(N5110 &lcd)
{
  // draw the runner function we are using the rectqngle for the prototype
  lcd.drawRect(_x, _y, _size, _size, FILL_BLACK);
}

void Runner::update(UserInput input)
{
  // updating the runner position

  if (input.d == N and _jump == false) {_jump = true;}
  if(_jump == true)
  {
    if (_i < 5)
    {
      _i++;
      _x += _i;
    }
    else if( _i < 10) {
      _i++ ;
      _x -= _i-5 ;
    }
    else {
      _i = 0;
      _jump = false;
    }
  }
  

  // update score

  add_score();
}

// void Runner::jump()
// {
//   for (int i = 0; i < 10; i++)
//   {
//     if (i < 5)
//       _x = _x + 1;
//     else
//       _x = _x - 1;
//     thread_sleep_for(100);
//   }
// }

void Runner::set_velocity(Position2D v)
{
  printf("Ball: Velocity\n");
  _velocity.x = v.x;
  _velocity.y = v.y;
}

void Runner::set_pos(Position2D p)
{
  printf("Ball: Set Position\n");
  _x = p.x;
  _y = p.y;
}

void Runner::add_score() { _score++; }

int Runner::get_score() { return _score; }

Position2D Runner::get_velocity() { return {_velocity.x, _velocity.y}; }

Position2D Runner::get_pos() { return {_x, _y}; }

int Runner::get_size() { return _size; }