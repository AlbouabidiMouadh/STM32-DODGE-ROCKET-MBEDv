#include "runner.h"

Runner::Runner() {}

void Runner::init(int size, int speed) {
  _size = size;
  _x = 20 - _size / 2;
  _y = 31;
  _velocity.x = speed;
  _velocity.y = speed;
  _score = 0;
  bool _jump = false;
  int _i = 0;
}

void Runner::draw(N5110 &lcd) {
  // draw the runner function we are using the rectqngle for the prototype
  lcd.drawRect(_x, _y, _size / 2, _size, FILL_BLACK);
}

void Runner::update() {
  // updating the runner position

  // update score

  add_score();
}


void Runner::set_velocity(Position2D v) {
  printf("Runner: Velocity\n");
  _velocity.x = v.x;
  _velocity.y = v.y;
}

void Runner::set_pos(Position2D p) {
  printf("Runner: Set Position\n");
  _x = p.x;
  _y = p.y;
}

void Runner::add_score() { _score++; }

int Runner::get_score() { return _score; }

Position2D Runner::get_velocity() { return {_velocity.x, _velocity.y}; }

Position2D Runner::get_pos() { return {_x, _y}; }

int Runner::get_size() { return _size; }
