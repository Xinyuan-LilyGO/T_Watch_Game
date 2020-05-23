#include <TTGO.h>
#include "tic2.h"
TTGOClass *ttgo;

void setup()
{
  Serial.begin(115200);
  ttgo = TTGOClass::getWatch();
  ttgo->begin();
  ttgo->openBL();
  ttgo->lvgl_begin();
  ttgo->button->setReleasedHandler(released);

  ttgo->eTFT->fillScreen(TFT_WHITE);
  delay(50);
  ttgo->eTFT->setSwapBytes(true);

  do {
    ttgo->eTFT->pushImage(0, 0, 240, 240, game1);
    delay(400);
    ttgo->eTFT->pushImage(0, 0, 240, 240, game2);
    delay(400);
  } while (ttgo->touch->touched() == 0);

  ttgo->eTFT->pushImage(0, 0, 240, 240, gm);

  while (1) {
    TP_Point p =  ttgo->touch->getPoint();
    delay(50);

    if (p.x > 55  && p.x < 186 && p.y < 151 && p.y > 90) {
      ttgo->eTFT->pushImage(0, 0, 240, 240, gm1);
      delay(500);
      break;
    }
  }
  cinit();
  chess_start();
}

void loop()
{
  ttgo->button->loop();
}
void cinit()
{
  ttgo->eTFT->fillScreen(TFT_WHITE);
  delay(50);
  ttgo->eTFT->fillRect(78, 0, 3, 239, TFT_BLACK);
  delay(100);
  ttgo->eTFT->fillRect(159, 0, 3, 239, TFT_BLACK);
  delay(100);
  ttgo->eTFT->fillRect(0, 78, 239, 3, TFT_BLACK);
  delay(100);
  ttgo->eTFT->fillRect(0, 159, 239, 3, TFT_BLACK);
  delay(100);
}
void chess_start()
{
  while (1) {
    if (ttgo->touch->touched()) {
      TP_Point p =  ttgo->touch->getPoint();
      Serial.print("X=");
      Serial.println(p.x);
      Serial.print("Y=");
      Serial.println(p.y);
      delay(300);
      istouch(p.x, p.y);
    }
    is_win();

    if (win() == 1 ) {
      delay(1000);
      bl = 0; re = 0;
      p_num = 0; q_num = 0;
      memset(p, 0, sizeof(p));
      memset(q, 0, sizeof(q));
      break;
    }
    else  if (win() == 2 ) {
      delay(1000);
      bl = 0; re = 0;
      p_num = 0; q_num = 0;
      memset(p, 0, sizeof(p));
      memset(q, 0, sizeof(q));
      break;
    }
    else if (win() == 3) {
      delay(1000);
      ttgo->eTFT->pushImage(0, 0, 240, 240, draw);
      p_num = 0; q_num = 0;
      bl = 0; re = 0;
      memset(p, 0, sizeof(p));
      memset(q, 0, sizeof(q));
      break;
    }
  }

}
void istouch(int a, int b)
{
  if (a > 0  && a < 78 && b < 78) {
    user(s , 1);
  }
  else if (a > 81 && a < 159 && b < 78) {
    user(s, 2);
  }
  else if (a > 162 && a < 239 && b < 78) {
    user(s, 3);
  }
  else if (a > 0 && a < 79 && b < 159 && b > 81) {
    user(s, 4);
  }
  else if (a > 81 && a < 159 && b < 159 && b > 81) {
    user(s, 5);
  }
  else if (a > 162 && a < 239 && b < 159 && b > 81) {
    user(s, 6);
  }
  else if (a > 0 && a < 78 && b < 239 && b > 162) {
    user(s, 7);
  }
  else if (a > 81 && a < 159 && b < 239 && b > 162) {
    user(s, 8);
  }
  else if (a > 162 && a < 239 && b < 239 && b > 162) {
    user(s, 9);
  }


}
int win()
{
  if (p_num > 0)
  {
    Serial.print("p_num=");
    Serial.println(p_num);
    delay(1000);
    flash();
    return 1;
  }
  else if (q_num > 0)
  {
    Serial.print("q_num=");
    Serial.println(q_num);
    delay(1000);
    flash2();
    return 2;
  }
  else if (bl == 5 && re == 4 || bl == 4 && re == 5)
  {
    return 3;

  }
  else {
    return 0;

  }
}
void is_win()
{
  //  int i, j;
  if (p[0] == 1 && p[1] == 1 && p[2] == 1 )
  {
    ttgo->eTFT->fillRect(0, 39, 240, 3, TFT_BLACK);
    p_num = 1;

  }
  else if (p[3] == 1 && p[4] == 1 && p[5] == 1 )
  {
    ttgo->eTFT->fillRect(0, 120, 240, 3, TFT_BLACK);
    p_num = 2;
  }
  else if (p[6] == 1 && p[7] == 1 && p[8] == 1 )
  {
    ttgo->eTFT->fillRect(0, 201, 240, 3, TFT_BLACK);
    p_num = 3;
  }
  else if (p[0] == 1 && p[3] == 1 && p[6] == 1 )
  {
    ttgo->eTFT->fillRect(39, 0, 3, 240, TFT_BLACK);
    p_num = 4;
  }
  else if (p[1] == 1 && p[4] == 1 && p[7] == 1  )
  {
    ttgo->eTFT->fillRect(120, 0, 3, 240, TFT_BLACK);
    p_num = 5;
  }
  else if (p[2] == 1 && p[5] == 1 && p[8] == 1 )
  {
    ttgo->eTFT->fillRect(201, 0, 3, 240, TFT_BLACK);
    p_num = 6;
  }
  else if (p[0] == 1 && p[4] == 1 && p[8] == 1 )
  {
    p_num = 7;
  }
  else if (p[2] == 1 && p[4] == 1 && p[6] == 1)
  {
    p_num = 8;
  }
  else if (q[0] == 1 && q[1] == 1 && q[2] == 1 )
  {
    ttgo->eTFT->fillRect(0, 39, 240, 3, TFT_BLACK);
    q_num = 1;
  }
  else if (q[3] == 1 && q[4] == 1 && q[5] == 1 )
  {
    ttgo->eTFT->fillRect(0, 120, 240, 3, TFT_BLACK);
    q_num = 2;
  }
  else if (q[6] == 1 && q[7] == 1 && q[8] == 1 )
  {
    ttgo->eTFT->fillRect(0, 201, 240, 3, TFT_BLACK);
    q_num = 3;
  }
  else if (q[0] == 1 && q[3] == 1 && q[6] == 1 )
  {
    ttgo->eTFT->fillRect(39, 0, 3, 240, TFT_BLACK);
    q_num = 4;
  }
  else if (q[1] == 1 && q[4] == 1 && q[7] == 1  )
  {
    ttgo->eTFT->fillRect(120, 0, 3, 240, TFT_BLACK);
    q_num = 5;
  }
  else if (q[2] == 1 && q[5] == 1 && q[8] == 1 )
  {
    ttgo->eTFT->fillRect(201, 0, 3, 240, TFT_BLACK);
    q_num = 6;
  }
  else if (q[0] == 1 && q[4] == 1 && q[8] == 1 )
  {
    q_num = 7;
  }
  else if (q[2] == 1 && q[4] == 1 && q[6] == 1)
  {
    q_num = 8;
  }

}

void flash()
{
  ttgo->eTFT->pushImage(0, 0, 240, 240, o2);
  delay(80);
  ttgo->eTFT->pushImage(0, 0, 240, 240, o3);
  delay(80);
  ttgo->eTFT->pushImage(0, 0, 240, 240, o4);
  delay(80);
  ttgo->eTFT->pushImage(0, 0, 240, 240, o5);
  delay(80);
  ttgo->eTFT->pushImage(0, 0, 240, 240, o6);
  delay(80);
  ttgo->eTFT->pushImage(0, 0, 240, 240, o7);
  delay(80);
  ttgo->eTFT->pushImage(0, 0, 240, 240, o8);

}
void flash2()
{
  ttgo->eTFT->pushImage(0, 0, 240, 240, x2);
  delay(80);
  ttgo->eTFT->pushImage(0, 0, 240, 240, x3);
  delay(80);
  ttgo->eTFT->pushImage(0, 0, 240, 240, x4);
  delay(80);
  ttgo->eTFT->pushImage(0, 0, 240, 240, x5);
  delay(80);
  ttgo->eTFT->pushImage(0, 0, 240, 240, x6);
  delay(80);
  ttgo->eTFT->pushImage(0, 0, 240, 240, x7);
  delay(80);
  ttgo->eTFT->pushImage(0, 0, 240, 240, x8);
}

void user(int u, int n)
{
  int number;
  number = n - 1;

  if (u == 0 && q[number] != 1 && p[number] != 1)
  {
    rec(n);
    bl++;

  }
  else if (u == 1 && p[number] != 1 && q[number] != 1)
  {
    circle(n);
    re++;

  }

}
void released()
{
  ttgo->eTFT->pushImage(0, 0, 240, 240, gm);
  while (1) {
    TP_Point p =  ttgo->touch->getPoint();
    delay(50);

    if (p.x > 55  && p.x < 186 && p.y < 151 && p.y > 90) {
      ttgo->eTFT->pushImage(0, 0, 240, 240, gm1);
      delay(500);
      break;
    }
  }
  cinit();
  chess_start();
}
void rec(int num)
{
  switch (num) {
    case 1:
      ttgo->eTFT->pushImage(0, 0, 78, 78, o);
      p[0] = 1;
      s = 1;
      break;
    case 2:
      ttgo->eTFT->pushImage(81, 0, 78, 78, o);
      p[1] = 1;
      s = 1;
      break;
    case 3:
      ttgo->eTFT->pushImage(162, 0, 78, 78, o);
      p[2] = 1;
      s = 1;
      break;
    case 4:
      ttgo->eTFT->pushImage(0, 81, 78, 78, o);
      p[3] = 1;
      s = 1;
      break;
    case 5:
      ttgo->eTFT->pushImage(81, 81, 78, 78, o);
      p[4] = 1;
      s = 1;

      break;
    case 6:
      ttgo->eTFT->pushImage(162, 81, 78, 78, o);
      p[5] = 1;
      s = 1;
      break;
    case 7:
      ttgo->eTFT->pushImage(0, 162, 78, 78, o);
      p[6] = 1;
      s = 1;
      break;
    case 8:
      ttgo->eTFT->pushImage(81, 162, 78, 78, o);
      p[7] = 1;
      s = 1;
      break;
    case 9:
      ttgo->eTFT->pushImage(162, 162, 78, 78, o);
      p[8] = 1;
      s = 1;
      break;
  }
}

void circle(int num)
{
  switch (num) {
    case 1:
      ttgo->eTFT->pushImage(0, 0, 78, 78, x);

      q[0] = 1;
      s = 0;
      break;
    case 2:
      ttgo->eTFT->pushImage(81, 0, 78, 78, x);
      q[1] = 1;
      s = 0;
      break;
    case 3:
      ttgo->eTFT->pushImage(162, 0, 78, 78, x);
      q[2] = 1;
      s = 0;
      break;
    case 4:
      ttgo->eTFT->pushImage(0, 81, 78, 78, x);
      q[3] = 1;
      s = 0;
      break;
    case 5:
      ttgo->eTFT->pushImage(81, 81, 78, 78, x);
      q[4] = 1;
      s = 0;
      break;
    case 6:
      ttgo->eTFT->pushImage(162, 81, 78, 78, x);
      q[5] = 1;
      s = 0;
      break;
    case 7:
      ttgo->eTFT->pushImage(0, 162, 78, 78, x);
      q[6] = 1;
      s = 0;
      break;
    case 8:
      ttgo->eTFT->pushImage(81, 162, 78, 78, x);
      q[7] = 1;
      s = 0;
      break;
    case 9:
      ttgo->eTFT->pushImage(162, 162, 78, 78, x);
      q[8] = 1;
      s = 0;
      break;
  }
}
