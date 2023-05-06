#include "rock.h"

Rock::Rock() {}

void Rock::init(int size, int speed) {
  _size = size;
  _x = 75 - _size / 2;
  _y = 35 - _size / 2;
  _velocity.x = speed;
  _velocity.y = speed;
}

void Rock::draw(N5110 &lcd) {
  // draw the rock as a circle as a prototype
  lcd.drawCircle(_x, _y, _size / 2, FILL_BLACK);
}

void Rock::update() {
  if (_x > 1) {
    _x -= _velocity.x;
  } else {
    _x = 75 - _size / 2;
  }
}

void Rock::set_velocity(Position2D v) {
  printf("Ball: Velocity\n");
  _velocity.x = v.x;
  _velocity.y = v.y;
}

void Rock::set_pos(Position2D p) {
  printf("Ball: Set Position\n");
  _x = p.x;
  _y = p.y;
}

Position2D Rock::get_velocity() { return {_velocity.x, _velocity.y}; }

Position2D Rock::get_pos() { return {_x, _y}; }

int Rock::get_size() { return _size; }
