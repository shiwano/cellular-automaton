#include <ca.h>

#include <ncurses.h>
#include <iostream>
#include <string>
#include <memory>
#include <random>

void run(int w, int h) {
  std::random_device rand;
  std::mt19937 mt(rand());
  std::uniform_real_distribution<double> rand0_1(0, 1);
  ca::Board b(w - 1, h - 1);

  for (int x = 0; x < w - 1; ++x) {
    for (int y = 0; y < h - 1; ++y) {
      if (rand0_1(mt) <= 0.1) {
        b.MakeCellAlive(x, y);
      }
    }
  }

  int key = 0;
  MEVENT mouse_evt;
  std::string step_label("Step: ");

  while (true) {
    erase();
    mvaddstr(0, 0, step_label.c_str());
    mvaddstr(0, 6, std::to_string(b.Step()).c_str());
    mvaddstr(1, 0, b.ToString().c_str());
    refresh();

    key = getch();
    switch (key) {
      case 'q':
        return;
      case '\n':
        b.ToNextStep();
        break;
      case KEY_MOUSE:
        getmouse(&mouse_evt);
        b.MakeCellAlive(mouse_evt.x, mouse_evt.y - 1);
        break;
    }
  }
}

int main(int argc, char* argv[]) {
  initscr();
  cbreak();
  noecho();
  keypad(stdscr,TRUE);
  mousemask(ALL_MOUSE_EVENTS, NULL);

  int w, h;
  getmaxyx(stdscr, h, w);

  if (w >= 10 && h >= 10) {
    run(w, h);
  } else {
    std::cout << "Screen size is not enough (required 10x10)." << std::endl;
  }

  endwin();
  return 0;
}
