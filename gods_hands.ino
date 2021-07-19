#include <Servo.h>

Servo servo_13;
float BigA;
float callib[3] = {0, 0, 0};
float ABegin[3] = {0, 0, 0};
int gamemode = -1;
bool way[3] = {true, true, true};
int levels[30];
int levels2[5] = {1, 0, 2, 0, 2};
int turn = 1;

void setup()
{
  randomSeed(analogRead(4));

  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  servo_13.attach(13);
  Serial.begin(9600);

  servo_13.write(90);
  delay(1000);

  if (analogRead(A0) >= analogRead(A1) && analogRead(A0) >= analogRead(A2))
  {
    BigA = analogRead(A0);
  }
  else if (analogRead(A1) >= analogRead(A0) && analogRead(A1) >= analogRead(A2))
  {
    BigA = analogRead(A1);
  }
  else if (analogRead(A2) >= analogRead(A0) && analogRead(A2) >= analogRead(A1))
  {
    BigA = analogRead(A2);
  }

  ABegin[0] = (analogRead(A0) + callib[0]) * 0.95;
  ABegin[1] = (analogRead(A1) + callib[1]) * 0.95;
  ABegin[2] = (analogRead(A2) + callib[2]) * 0.95;

  for (int i = 0; i < 30; i++)
  {
    int randNumber = random(0, 3);
    if ((randNumber == levels[i - 1]) && (i > 0))
    {
      if (randNumber == 0)
      {
        randNumber = 1;
      }
      else if (randNumber == 1)
      {
        randNumber = 2;
      }
      else if (randNumber == 2)
      {
        randNumber = 0;
      }
    }

    levels[i] = randNumber;
    Serial.print(levels[i]);
  }

  gamemode = 1;

  servo_13.write(0);
  delay(350);
  servo_13.write(180);
  delay(3000);
  servo_13.write(90);

  

  if (((analogRead(A0) + callib[0]) < ABegin[0]) && (analogRead(A0) + callib[0]) < (analogRead(A1) + callib[1]) && (analogRead(A0) + callib[0]) < (analogRead(A2) + callib[2]))
  {
    gamemode = 0;
  }
  else if (((analogRead(A1) + callib[1]) < ABegin[1]) && (analogRead(A1) + callib[1]) < (analogRead(A0) + callib[0]) && (analogRead(A1) + callib[1]) < (analogRead(A2) + callib[2]))
  {
    gamemode = 1;
  }
  else if (((analogRead(A2) + callib[2]) < ABegin[2]) && (analogRead(A2) + callib[2]) < ((analogRead(A1) + callib[1]) && analogRead(A2) + callib[2]) < (analogRead(A0) + callib[0]))
  {
    gamemode = 2;
  }

  sprint("Gamemode", gamemode);

  servo_13.write(0);
  delay(2000);

  if (gamemode == 0)
  {
    gamemode0();
  }

  else if (gamemode == 1)
  {
    gamemode1();
  }
  else if (gamemode == 2)
  {
    gamemode2();
  }
}

void loop()
{
}

int turn2 = 0;

void gamemode2()
{
  servo_13.write(0);
  delay(1000);
  servo_13.write(180);
  while (true)
  {
    if (((analogRead(A0) + callib[0]) < ABegin[0]) && (analogRead(A0) + callib[0]) < (analogRead(A1) + callib[1]) && (analogRead(A0) + callib[0]) < (analogRead(A2) + callib[2]))
    {
      if (levels2[turn2] != 0)
      {
        fail();
      }

      turn2 = turn2 + 1;

      servo_13.write(130);
      delay(350);

      servo_13.write(0);
      delay(2000);
    }

    else if (((analogRead(A1) + callib[1]) < ABegin[1]) && (analogRead(A1) + callib[1]) < (analogRead(A0) + callib[0]) && (analogRead(A1) + callib[1]) < (analogRead(A2) + callib[2]))
    {
      if (levels2[turn2] != 1)
      {
        fail();
      }

      turn2 = turn2 + 1;
      servo_13.write(90);
      delay(350);

      servo_13.write(0);
      delay(2000);
    }

    else if (((analogRead(A2) + callib[2]) < ABegin[2]) && (analogRead(A2) + callib[2]) < ((analogRead(A1) + callib[1]) && analogRead(A2) + callib[2]) < (analogRead(A0) + callib[0]))
    {
      if (levels2[turn2] != 2)
      {
        fail();
      }
      turn2 = turn2 + 1;

      servo_13.write(50);
      delay(350);

      servo_13.write(0);
      delay(2000);
    }
  }
}

void gamemode1()
{
  while (true)
  {
    servo_13.write(0);
    delay(2000);
    turn++;
    turn2 = 0;
    way[0] = true;
    way[1] = true;
    way[2] = true;

    for (int x = 0; x <= turn; x++)
    {
      if (levels[x] == 0)
      {
        servo_13.write(130);
        delay(550);
      }
      else if (levels[x] == 1)
      {
        servo_13.write(90);
        delay(550);
      }
      else if (levels[x] == 2)
      {
        servo_13.write(50);
        delay(550);
      }
    }
    servo_13.write(180);

    while (turn2 <= turn)
    {
      if (((analogRead(A0) + callib[0]) < ABegin[0]) && (analogRead(A0) + callib[0]) < (analogRead(A1) + callib[1]) && (analogRead(A0) + callib[0]) < (analogRead(A2) + callib[2]))
      {
        if (way[0] == true)
        {
          if (levels[turn2] != 0)
          {
            fail();
          }

          turn2 = turn2 + 1;

          way[0] = false;
          way[1] = true;
          way[2] = true;

          servo_13.write(130);
          delay(350);
        }
      }

      else if (((analogRead(A1) + callib[1]) < ABegin[1]) && (analogRead(A1) + callib[1]) < (analogRead(A0) + callib[0]) && (analogRead(A1) + callib[1]) < (analogRead(A2) + callib[2]))
      {
        if (way[1] == true)
        {
          if (levels[turn2] != 1)
          {
            fail();
          }

          turn2 = turn2 + 1;

          way[0] = true;
          way[1] = false;
          way[2] = true;

          servo_13.write(90);
          delay(350);
        }
      }

      else if (((analogRead(A2) + callib[2]) < ABegin[2]) && (analogRead(A2) + callib[2]) < ((analogRead(A1) + callib[1]) && analogRead(A2) + callib[2]) < (analogRead(A0) + callib[0]))
      {
        if (way[2] == true)
        {
          if (levels[turn2] != 2)
          {
            fail();
          }
          turn2 = turn2 + 1;

          way[0] = true;
          way[1] = true;
          way[2] = false;

          servo_13.write(50);
          delay(350);
        }
      }
    }
  }
}

void gamemode0()
{
  servo_13.write(90);
  while (true)
  {
    if (((analogRead(A0) + callib[0]) < ABegin[0]) && (analogRead(A0) + callib[0]) < (analogRead(A1) + callib[1]) && (analogRead(A0) + callib[0]) < (analogRead(A2) + callib[2]))
    {
      servo_13.write(130);
    }
    else if (((analogRead(A1) + callib[1]) < ABegin[1]) && (analogRead(A1) + callib[1]) < (analogRead(A0) + callib[0]) && (analogRead(A1) + callib[1]) < (analogRead(A2) + callib[2]))
    {
      servo_13.write(90);
    }
    else if (((analogRead(A2) + callib[2]) < ABegin[2]) && (analogRead(A2) + callib[2]) < ((analogRead(A1) + callib[1]) && analogRead(A2) + callib[2]) < (analogRead(A0) + callib[0]))
    {
      servo_13.write(50);
    }
  }
}

void sprint(String string1, int int1)
{
  Serial.print(string1);
  Serial.println(int1);
}

void fail()
{
  for (int x = 0; x < 100; x++)
  {

    servo_13.write(130);
    delay(100);
    servo_13.write(90);
    delay(100);
    servo_13.write(50);
    delay(100);
  }
}
