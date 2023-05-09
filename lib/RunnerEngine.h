#ifndef RUNNERENGINE_H
#define RUNNERENGINE_H

#include "N5110.h"
#include "Utils.h"
#include "mbed.h"
#include "rock.h"
#include "runner.h"

class RunnerEngine {
public:
  RunnerEngine();
  void init(int runnerSize, int runnerSpeed, int rockSize, int rockSpeed);
  int update(UserInput input, N5110 &lcd);
  void draw(N5110 &lcd);
  bool check_rock_collision();
  void set_rock_size(int size);
  void set_rock_speed(int speed);
private:
  void check_score();
  Rock _rock;
  Runner _runner;
};

#endif