
///////////// includes /////////////////////
#include "Joystick.h"
#include "N5110.h"
#include "RunnerEngine.h"
#include "Utils.h"
#include "mbed.h"
#include <string>

///////////// defines /////////////////////

#define btn1 PB_0
#define btn2 PA_4

///////////// objects ///////////////////

N5110 lcd(PC_7, PA_9, PB_10, PB_5, PB_3, PA_10);
Joystick joystick(PC_1, PC_0);
DigitalIn buttonA(BUTTON1); // onboard user button
RunnerEngine Runner;
InterruptIn buttonOne(btn1);
InterruptIn buttonTwo(btn2);

///////////// prototypes ///////////////

void init();
void render();
void welcome();
void main_menu();
void game();
void game_over();
void settings();
void score();

///////////// variables /////////////////

int ROCK_SIZE = 4;
int ROCK_SPEED = 2;
int RUNNER_SIZE = 6;
int RUNNER_SPEED = 4;
long int SCORES[3] = {0, 0, 0};
int fps = 10;
int playerScore = 0;

////////////////////////////////////////

int main() {
  init();    // initialise devices and objects
  welcome(); // waiting for the user to start
  main_menu();
  game_over();
}

void init() {
  buttonOne.mode(PullNone);
  buttonTwo.mode(PullNone);
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
  lcd.printString("ROCK DODGE    ", 0, 1);
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
    lcd.printString("press button one", 4, 0);
    lcd.printString("to play again", 4, 1);
    lcd.printString("press button two", 4, 3);
    lcd.printString("to go to main menu", 4, 4);
    lcd.refresh();
    ThisThread::sleep_for(250ms);
    if (buttonOne.read()) {
      game();
      game_over();
    } else if (buttonTwo.read()) {
      main_menu();
    }
    ThisThread::sleep_for(100ms);
  }
}

void game() {
  render();                     // first draw the initial frame
  thread_sleep_for(1000 / fps); // and wait for one frame period - millseconds
  while (!Runner.check_rock_collision()) {
    Polar polar = {joystick.get_mag(), joystick.get_angle()};
    UserInput input = {joystick.get_direction(), joystick.get_mag()};
    if (buttonA.read() == 0) {
      ThisThread::sleep_for(100ms);
      while (buttonA.read() == 1) {
        lcd.clear();
        lcd.printString("Game Paused", 10, 1);
        lcd.printString("press blue button to resume", 10, 3);
        lcd.refresh();
        ThisThread::sleep_for(100ms);
      }
    }
    playerScore =
        Runner.update(input, lcd); // update the game engine based on input
    render();                      // draw frame on screen
    thread_sleep_for(1000 / fps);  // and wait for one frame period - ms
  }
  int aux1, aux2;
  for (int j = 0; j < 3; j++) {
    if (playerScore > SCORES[j]) {
      aux1 = SCORES[j];
      SCORES[j] = playerScore;
      if (j == 0) {
        aux2 = SCORES[j + 1];
        SCORES[j + 1] = aux1;
        SCORES[j + 2] = aux2;
      } else if (j == 1) {
        aux2 = SCORES[j + 1];
        SCORES[j + 1] = aux1;
      }
    }
  }
};
int Brightness = 50;
string Level = "normal";
int choosedSetting = 1;
void settings() {
  while (true) {
    lcd.clear();
    lcd.printString(">", 0, choosedSetting);
    lcd.printString("SETTINGS", 4, 1);
    lcd.printString(("Level: " + Level).c_str(), 4, 3);
    lcd.printString(("Brightness: " + to_string(Brightness)).c_str(), 4, 5);
    lcd.refresh();
    ThisThread::sleep_for(100ms);
    if (buttonOne.read() == 0) {
      if (choosedSetting == 5) {
        choosedSetting = 1;
      } else {
        choosedSetting += 2;
      }
    }
    ThisThread::sleep_for(100ms);
    if (buttonTwo.read() == 0) {
      if (choosedSetting == 3) {
        // change the level of the game by changing the rock speed
        if (Level == "normal") {
          Level = "hard";
          ROCK_SPEED += 2;
          Runner.set_rock_speed(ROCK_SPEED);
        } else if (Level == "hard") {
          Level = "easy";
          ROCK_SPEED -= 4;
          Runner.set_rock_speed(ROCK_SPEED);
        } else if (Level == "easy") {
          Level = "normal";
          ROCK_SPEED += 2;
          Runner.set_rock_speed(ROCK_SPEED);
        }
        ThisThread::sleep_for(100ms);
      } else if (choosedSetting == 5) {
        // change the brightness of the lcd by using the built in function
        switch (Brightness) {
        case 25: {
          Brightness = 50;
          lcd.setBrightness(float(Brightness) / 100);
          break;
        }
        case 50: {
          Brightness = 75;
          lcd.setBrightness(float(Brightness) / 100);
          break;
        }
        case 75: {
          Brightness = 100;
          lcd.setBrightness(float(Brightness) / 100);
          break;
        }
        case 100: {
          Brightness = 25;
          lcd.setBrightness(float(Brightness) / 100);
          break;
        }
        default:
          break;
        }
        ThisThread::sleep_for(100ms);
      }
    }
    if (buttonA.read() == 0) {
      break;
    }
    ThisThread::sleep_for(100ms);
  }
};

void score() {
  while (true) {
    lcd.clear();
    lcd.printString("scores", 4, 0);
    lcd.printString(to_string(SCORES[0]).c_str(), 4, 2);
    lcd.printString(to_string(SCORES[1]).c_str(), 4, 3);
    lcd.printString(to_string(SCORES[2]).c_str(), 4, 4);
    lcd.refresh();
    if (buttonA.read() == 0) {
      break;
    }
  }
};

int choosedLine = 1;
void main_menu() {
  while (true) {
    lcd.clear();
    lcd.printString(">", 0, choosedLine);
    lcd.printString("START", 4, 1);
    lcd.printString("SCORES", 4, 3);
    lcd.printString("SETTINGS", 4, 5);
    lcd.refresh();
    // waiting for the press of the 1st button to change the choosed one
    if (buttonOne.read() == 0) {
      if (choosedLine > 3) {
        choosedLine = 1;
      } else {
        choosedLine += 2;
      }
    }
    ThisThread::sleep_for(100ms);
    // waiting for the press of the 2nd button to choose
    if (buttonTwo.read() == 0) {
      if (choosedLine == 1) {
        game();
      } else if (choosedLine == 3) {
        score();
      } else if (choosedLine == 5) {
        settings();
      }
    }
    ThisThread::sleep_for(100ms);
  }
}
