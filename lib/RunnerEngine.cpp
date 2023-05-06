#include "RunnerEngine.h"
#include <cstring>
#include <string>

RunnerEngine::RunnerEngine() {  }

void RunnerEngine::init(int runnerSize, int runnerSpeed, int rockSize,
                        int rockSpeed) {
  _rock.init(rockSize, rockSpeed);
  _runner.init(runnerSize, runnerSpeed);
}

int RunnerEngine::update(UserInput input) {
  _runner.update(input);
  _rock.update();
  check_rock_collision();
  return _runner.get_score();
}

void RunnerEngine::draw(N5110 &lcd) {
  lcd.printString(to_string(_runner.get_score()).c_str(), WIDTH / 2, 10);
  lcd.drawLine(0, HEIGHT - 10, WIDTH - 1, HEIGHT - 10, 1);
  _runner.draw(lcd);
  _rock.draw(lcd);
}

bool RunnerEngine::check_rock_collision() {
  Position2D rock_position = _rock.get_pos();
  Position2D rock_velocity = _rock.get_velocity();
  int rock_size = _rock.get_size();

  Position2D runner_position = _runner.get_pos();
  Position2D runner_velocity = _runner.get_velocity();
  int runner_size = _runner.get_size();

  // checking if touched the runner
  if ((rock_position.x == (runner_position.x + runner_size)) and
      (runner_position.y <= rock_position.y + rock_size)) {
    return true;
  } else {
    return false;
  }
}

