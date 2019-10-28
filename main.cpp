#include<iostream>

using namespace std;#include<conio.h>

#include<windows.h>

#define uparr 72
#include<stdio.h>

void game();
void menu();
void rules();
void gameover();
int main();
int out = 0, score = 0;

void gotoxy(short x, short y) {
  COORD coor {
    x,
    y
  };
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coor);
}

void clr(int x1, int x2, int y1, int y2) {
  for (int i = x1; i <= x2; i++) {
    for (int j = y1; j <= y2; j++) {
      gotoxy(i, j);
      cout << " ";
    }
  }
}

class bird;

// for obstacles
class o {
  int x1;
  int x2;
  int y1;
  int y2;

  public:
    o(int a, int b) {
      x1 = a;
      x2 = x1 + 5;
      y1 = b;
      y2 = y1 + 5;
    }

  inline void disp() {
    int l;
    char ch;
    if (out == 0) {
      for (int l = 0; l < 25; l++) {
        if (l < y1 || l > y2) {
          ch = '|';
          gotoxy(x1, l);
          cout << ch;
          gotoxy(x2, l);
          cout << ch;
        }
      }

      for (int y = 0; y < 6; y++) {
        gotoxy(x1 + y, y1);
        cout << "-";
        gotoxy(x1 + y, y2);
        cout << "-";
      }
    }
  }

  void del() {
    clr(x1, x2 + 2, 0, 25);
  }

  o operator++(int dummy = 0) {
    if (x1 > 0 && x1 < 80 && out == 0) {
      x1--;
      x2--;
    } else if (x1 == 0 && out == 0) {
      x1 = 75;
      x2 = 80;
      y1 = rand() % 10 + 5;
      y2 = y1 + 5;
    }
  }

  friend void check(o, bird);
};

class bird {
  int x;
  int y;

  public:
    bird(int a = 25, int b = 15) {
      x = a;
      y = b;
    }

  void disp(char c) {
    if (out == 0) {
      gotoxy(x, y);

      cout << "#" << c << ">";
    }
  }

  bird operator++(int dummy = 1) {
    if (y > 0 && y < 25 && out == 0) {
      y = y - 3;
    } else {
      gameover();
    }
  }

  bird operator--(int dummy = 1) {
    if (y > 0 && y < 25 && out == 0) {
      y++;
    } else {
      gameover();
    }
  }

  void del() {
    clr(x - 1, x + 3, y - 1, y + 1);
  }

  friend void check(o, bird);
};

inline void check(o o1, bird b) {
  if (o1.x2 >= 24 || o1.x1 <= 28) {
    if (((25 >= o1.x1) || (26 >= o1.x1) || (27 >= o1.x1)) && ((25 <= o1.x2) || (26 <= o1.x2) || (27 <= o1.x2)) && (b.y <= o1.y1 || b.y >= o1.y2)) {
      out = 1;
      gameover();
    } else if (o1.x2 == 23) {
      score++;
    }
  }
}

void boundary(int x1, int x2, int y1, int y2) {
  for (int i = y1; i <= y2; i++) {
    gotoxy(x1, i);
    cout << "|";
    gotoxy(x2, i);
    cout << "|";
  }

  for (int i = x1; i <= x2; i++) {
    gotoxy(i, y1);
    cout << "_";
    gotoxy(i, y2);
    cout << "-";
  }
}

void gameover() {
  clr(33, 55, 10, 18);
  boundary(33, 55, 10, 19);
  gotoxy(35, 11);
  cout << "GAME OVER";
  gotoxy(38, 12);
  cout << "Score:" << score;
  gotoxy(35, 13);
  cout << "Choose your option:";
  gotoxy(37, 15);
  cout << "1.New Game";
  gotoxy(37, 16);
  cout << "2.Main menu";
  gotoxy(37, 17);
  cout << "3.Exit";

  gotoxy(40, 18);

  char ch;
  cin >> ch;

  if (ch == '1')
    game();
  else if (ch == '2')
    menu();
  else
    exit(0);
}

void menu() {
  system("cls");
  cout << "FFFFF   L       AAA    PPP   PPP   Y   Y        BBB   IIIII  RRR    DDD \n";
  cout << "F       L      A   A   P  P  P  P   Y Y         B  B    I    R  R   D  D\n";
  cout << "FFFF    L      AAAAA   PPP   PPP     Y          BBB     I    RRR    D  D\n";
  cout << "F       L      A   A   P     P       Y          B  B    I    R R    D  D\n";
  cout << "F       LLLLL  A   A   P     P       Y          BBB   IIIII  R   R  DDD \n";

  gotoxy(30, 10);
  cout << "What would you like to do?";

  gotoxy(33, 11);
  cout << "1.Play game";

  gotoxy(33, 12);
  cout << "2.Read Rules";

  gotoxy(33, 13);
  cout << "3.Exit";

  gotoxy(35, 15);

  int rep;
  cin >> rep;

  if (rep == 1)
    game();
  else if (rep == 2)
    rules();
  else if (rep == 3)
    exit(0);
  else {
    gotoxy(33, 16);
    cout << "Incorrect index entered.";
    getch();
    menu();
  }
}

void rules() {
  system("cls");

  gotoxy(5, 5);
  printf("1.The main objective of the game is to escape the square bracket shaped\n      obstacle.");

  gotoxy(5, 8);
  printf("2.Use space bar to move the bird upwards.");

  gotoxy(5, 9);
  printf("3.The score keeps increasing as the player keeps escaping the obstacle.");

  gotoxy(5, 11);
  printf("To start game, press 1.");

  gotoxy(30, 18);
  printf("For main menu, press 2.");

  int rey;
  cin >> rey;

  if (rey == 1)
    game();
  else
    menu();
}

int main() {
  menu();
  return 0;
}

void game() {
  system("cls");
  out = 0;
  score = 0;

  bird b(25, 15);
  int j = 0;
  char c = ' ';
  o ob1(15, 10), ob2(35, 15), ob3(55, 5), ob4(75, 14);

  char ch = 'g';

  gotoxy(40, 13);
  cout << 3;
  Sleep(450);
  gotoxy(40, 13);
  cout << 2;
  Sleep(450);
  gotoxy(40, 13);
  cout << 1;
  Sleep(450);
  gotoxy(39, 13);
  cout << "GO!!!";
  Sleep(450);

  do {
    if (kbhit() != 0) {
      ch = getch();
      if (ch == ' ')
        b++;
    }

    j++;

    if (j % 2 == 0)
      c = '^';
    else
      c = 'v';

    if (out != 0)
      break;
    b--;
    ob2++;
    ob4++;
    ob1++;
    ob3++;

    system("cls");

    ob2.disp();
    ob4.disp();
    ob1.disp();
    ob3.disp();
    b.disp(c);

    gotoxy(0, 0);

    cout << "SCORE";
    gotoxy(0, 1);
    cout << score;

    check(ob2, b);
    check(ob4, b);
    check(ob1, b);
    check(ob3, b);
    Sleep(200);
  } while (ch != 'o' && out == 0);
  getch();
}
