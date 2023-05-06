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
  int update(UserInput input);
  void draw(N5110 &lcd);
  bool check_rock_collision();
private:
  void check_score();
  Rock _rock;
  Runner _runner;
};

#endif