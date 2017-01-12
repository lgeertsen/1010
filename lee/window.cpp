#include "window.h"

void init_colors(void)
{
  start_color();
  init_pair(WBLACK,   COLOR_WHITE, COLOR_BLACK);
  init_pair(WCYAN,    COLOR_WHITE, COLOR_CYAN);
  init_pair(WBLUE,    COLOR_WHITE, COLOR_BLUE);
  init_pair(WYELLOW,  COLOR_WHITE, COLOR_YELLOW);
  init_pair(WGREEN,   COLOR_WHITE, COLOR_GREEN);
  init_pair(WMAGENTA, COLOR_WHITE, COLOR_MAGENTA);
  init_pair(WRED,     COLOR_WHITE, COLOR_RED);
  init_pair(BWHITE,   COLOR_BLACK, COLOR_WHITE);
  init_pair(BCYAN,    COLOR_BLACK, COLOR_CYAN);
  init_pair(BBLUE,    COLOR_BLACK, COLOR_BLUE);
  init_pair(BYELLOW,  COLOR_BLACK, COLOR_YELLOW);
  init_pair(BGREEN,   COLOR_BLACK, COLOR_GREEN);
  init_pair(BMAGENTA, COLOR_BLACK, COLOR_MAGENTA);
  init_pair(BRED,     COLOR_BLACK, COLOR_RED);

  init_color(11, 925,941,945);
  init_pair(CLOUD, COLOR_BLACK, 11);

  init_color(12, 172, 243, 313);
  init_pair(MIDNIGHT, COLOR_WHITE, 12);

  init_color(13, 717, 109, 109);
  init_color(14, 956, 262, 211);
  init_pair(RED, 13, 14);

  init_color(15, 533, 54, 309);
  init_color(16, 913, 117, 388);
  init_pair(PINK, 15, 16);

  init_color(17, 290, 78, 549);
  init_color(18, 611, 152, 690);
  init_pair(PURPLE, 17, 18);

  init_color(19, 192, 105, 572);
  init_color(20, 403, 227, 717);
  init_pair(DEEPPURPLE, 19, 20);

  init_color(21, 101, 137, 494);
  init_color(22, 247, 317, 709);
  init_pair(INDIGO, 21, 22);

  init_color(23, 50, 278, 631);
  init_color(24, 129, 588, 952);
  init_pair(BLUE, 23, 24);

  init_color(25, 3, 341, 607);
  init_color(26, 11, 662, 956);
  init_pair(LIGHTBLUE, 25, 26);

  init_color(27, 0, 376, 392);
  init_color(28, 0, 737, 831);
  init_pair(CYAN, 27, 28);

  init_color(29, 0, 301, 250);
  init_color(30, 0, 588, 533);
  init_pair(TEAL, 29, 30);

  init_color(31, 105, 368, 125);
  init_color(32, 298, 686, 313);
  init_pair(GREEN, 31, 32);

  init_color(33, 200, 411, 117);
  init_color(34, 545, 764, 290);
  init_pair(LIGHTGREEN, 33, 34);

  init_color(35, 509, 466, 90);
  init_color(36, 803, 977, 223);
  init_pair(LIME, 35, 36);

  init_color(37, 960, 498, 90);
  init_color(38, 1000, 921, 231);
  init_pair(YELLOW, 37, 38);

  init_color(39, 1000, 435, 0);
  init_color(40, 1000, 756, 27);
  init_pair(AMBER, 39, 40);

  init_color(41, 901, 317, 0);
  init_color(42, 1000, 596, 0);
  init_pair(ORANGE, 41, 42);

  init_color(43, 749, 211, 47);
  init_color(44, 1000, 341, 133);
  init_pair(DEEPORANGE, 43, 44);

  init_pair(REDT, 13, 12);
  init_pair(YELLOWT, 37, 12);
  init_pair(GREENT, 34, 12);
}


void startProgramX() {
  initscr();             // initialize curses
  cbreak();              // pass key presses to program, but not signals
  noecho();              // don't echo key presses to screen
  keypad(stdscr, TRUE);  // allow arrow keys
  timeout(0);            // no blocking on getch()
  curs_set(0);           // set the cursor to invisible
  init_colors();
}

void stopProgramX() {
  refresh();
  getch();
  endwin();
}



void Window::update() const{
  wrefresh(win);
  wrefresh(frame);
  refresh();
}

Window::Window() {}

Window::Window(int h,int w, int x, int y, char c)
  : height(h), width(w), startx(x), starty(y)
{
  colorwin=WCYAN;
  colorframe=WBLACK;
  frame=newwin(h+2,w+2,y,x);
  win=subwin(frame,h,w,y+1,x+1);
  wbkgd(frame,COLOR_PAIR(colorwin));
  wbkgd(win,COLOR_PAIR(colorframe));
  wborder(frame, c,c,c,c,c,c,c,c);
  wattron(win,COLOR_PAIR(colorwin));
  wattron(frame,COLOR_PAIR(colorframe));
  update();
}

Window::~Window(){
  wborder(frame, ' ', ' ', ' ',' ',' ',' ',' ',' ');
  wattroff(win,COLOR_PAIR(colorwin));
  wattroff(win,COLOR_PAIR(colorframe));
  werase(win);
  update();
  delwin(win);
}

void Window::print(int x, int y, std::string s, Color c) const {
  wattron(win,COLOR_PAIR(c));
  mvwprintw(win,y,x,s.c_str());
  wattroff(win,COLOR_PAIR(c));
  update();
}
void Window::printBold(int x, int y, std::string s, Color c) const {
  wattron(win,COLOR_PAIR(c));
  mvwprintw(win,y,x,s.c_str());
  wattroff(win,COLOR_PAIR(c));
  update();
}
void Window::print(int x, int y, char s, Color c) const{
  wattron(win,COLOR_PAIR(c));
  mvwaddch(win,y,x,s | A_BOLD);
  wattroff(win,COLOR_PAIR(c));
  update();
}
void Window::print(int x, int y, Color c) const{
  wattron(win,COLOR_PAIR(c));
  mvwaddch(win,y,x,' ');
  wattroff(win,COLOR_PAIR(c));
  update();
}
void Window::print(int x, int y, int z, Color c) const{
  wattron(win,COLOR_PAIR(c));
  switch(z) {
  case 1:
     mvwaddch(win,y,x,ACS_ULCORNER | A_BOLD);
     break;
  case 2:
    mvwaddch(win,y,x,ACS_URCORNER | A_BOLD);
    break;
  case 3:
    mvwaddch(win,y,x,ACS_LLCORNER | A_BOLD);
    break;
  case 4:
    mvwaddch(win,y,x,ACS_LRCORNER | A_BOLD);
    break;
  case 5:
    mvwaddch(win,y,x,ACS_HLINE | A_BOLD);
    break;
  }
  wattroff(win,COLOR_PAIR(c));
  update();
}
void Window::print(int x, int y, std::string s) const{
  mvwprintw(win,y,x,s.c_str());
  update();
}
void Window::print(int x, int y, char s) const{
  mvwaddch(win,y,x,s);
  update();
}


int Window::getX() const { return startx;}
int Window::getY() const { return starty;}
int Window::getHauteur() const { return height;}
int Window::getLargeur() const { return width;}
Color Window::getCouleurBordure() const{ return colorframe;}
Color Window::getCouleurFenetre() const{ return colorwin;}
void Window::setCouleurBordure(Color c){
  colorframe=c;
  wattron(frame,COLOR_PAIR(colorframe));
  wborder(frame, bord,bord,bord,bord,bord,bord,bord,bord);
  update();
}
void Window::setCouleurFenetre(Color c){
  colorwin=c;
  wattron(win,COLOR_PAIR(colorwin));
  wbkgd(win,COLOR_PAIR(colorwin));
  update();
}

void Window::clear() const{  werase(win); update(); }
