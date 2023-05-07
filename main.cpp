
///////////// includes /////////////////////
#include "Joystick.h"
#include "N5110.h"
#include "RunnerEngine.h"
#include "Utils.h"
#include "mbed.h"

///////////// defines /////////////////////

#define ROCK_SIZE 4
#define ROCK_SPEED 2
#define RUNNER_SIZE 4
#define RUNNER_SPEED 4

///////////// objects ///////////////////

N5110 lcd(PC_7, PA_9, PB_10, PB_5, PB_3, PA_10);
Joystick joystick(PC_1, PC_0);
DigitalIn buttonA(BUTTON1); // onboard user button
RunnerEngine Runner;

///////////// prototypes ///////////////

void init();
void render();
void welcome();
void game_over();

////////////////////////////////////////

int main() {
  init();    // initialise devices and objects
  welcome(); // waiting for the user to start
  render();  // first draw the initial frame
  int fps = 10;
  int scores;
  thread_sleep_for(1000 / fps); // and wait for one frame period - millseconds
  while (!Runner.check_rock_collision()) {
    UserInput input = {joystick.get_direction(), joystick.get_mag()};
    scores = Runner.update(input, lcd); // update the game engine based on input
    render();                     // draw frame on screen
    thread_sleep_for(1000 / fps); // and wait for one frame period - ms
  }

  game_over();
}

void init() {
  lcd.init(LPH7366_1);
  lcd.setContrast(0.5);
  joystick.init();
  Runner.init(RUNNER_SIZE, RUNNER_SPEED, ROCK_SIZE, ROCK_SPEED);
}

void render() { // clear screen, re-draw and refresh
  lcd.clear();
  Runner.draw(lcd);
  lcd.refresh();
}

void welcome() { // splash screen
  lcd.printString("     ROCK DODGE    ", 0, 1);
  lcd.printString("Press Nucleo", 0, 3);
  lcd.printString("Blue button", 0, 4);
  lcd.refresh();

  while (buttonA.read() == 1) {

    ThisThread::sleep_for(100ms);
  }
}

void game_over() { // splash screen
  while (1) {
    lcd.clear();
    lcd.printString("  Game Over ", 0, 2);
    lcd.refresh();
    ThisThread::sleep_for(250ms);
    lcd.clear();
    lcd.refresh();
    ThisThread::sleep_for(250ms);
  }
}