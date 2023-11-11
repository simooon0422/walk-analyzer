// select reading channel pins
#define selectAr 53
#define selectBr 51
#define selectCr 49

// select writing channel pins
#define selectAw 12
#define selectBw 11
#define selectCw 10

//analog reading pin
#define readingPin A15

//writing pin
#define writingPin 9

// matrix size
#define rowNum 24
#define colNum 24

// inhibit pins
#define winh1 6
#define winh2 7
#define winh3 8

#define rinh1 43
#define rinh2 45
#define rinh3 47

// array storing matrix readings
int touch_list[rowNum][colNum];

String  message = "";

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
  
  pinMode(selectAr, OUTPUT);
  pinMode(selectBr, OUTPUT);
  pinMode(selectCr, OUTPUT);

  pinMode(selectAw, OUTPUT);
  pinMode(selectBw, OUTPUT);
  pinMode(selectCw, OUTPUT);

  pinMode(writingPin, OUTPUT);
  digitalWrite(writingPin, HIGH);

  pinMode(winh1, OUTPUT);
  pinMode(winh2, OUTPUT);
  pinMode(winh3, OUTPUT);
  pinMode(rinh1, OUTPUT);
  pinMode(rinh2, OUTPUT);
  pinMode(rinh3, OUTPUT);

  for (int i = 0; i < rowNum; i++)
  {
    for (int j = 0; j < colNum; j++)
    {
      touch_list[i][j] = 255;
    }
  }
}

void loop() {
//  printArray(touch_list);
//  readValues();
//  delay(1000);

    
  if (Serial.available() > 0)
  {
    message = Serial.readStringUntil('\n');
    if (message == "ok")
    {
      readValues();
      sendValues();
      message = "done";
//      Serial.println("ok");
    }
  }
}

void printArray( const int a[][colNum]) {
   // loop through array's rows
   for ( int i = 0; i < rowNum; i++ ) {
      // loop through columns of current row
      for ( int j = 0; j < colNum; j++ ){
        Serial.print(a[ i ][ j ]);
        Serial.print(", ");
      }
      Serial.println (" ") ; // start new line of output
   } 
   Serial.println (" ") ; // space between outputs
}

void sendValues()
{
  for (int i = 0; i < rowNum; i++)
  {
    for (int j = 0; j < colNum; j++)
    {
      Serial.println(touch_list[i][j]);
    }
  }
}

void readValues()
{
  for (int i = 0; i < rowNum; i++)
  {
    if (i == 0)
    {
      digitalWrite(winh1, LOW);
      digitalWrite(winh2, HIGH);
      digitalWrite(winh3, HIGH);
    }
    else if (i == 8)
     {
       digitalWrite(winh1, HIGH);
       digitalWrite(winh2, LOW);
       digitalWrite(winh3, HIGH);
     }
    else if (i == 16)
     {
       digitalWrite(winh1, HIGH);
       digitalWrite(winh2, HIGH);
       digitalWrite(winh3, LOW);
     }
     
    if (i >= 16)
    {
      select_write_channel(i-16);
    }
    else if (i >= 8)
    {
      select_write_channel(i-8);
    }
    else  select_write_channel(i);
   
    for (int j = 0; j < colNum; j++)
    {
      if (j == 0)
      {
        digitalWrite(rinh1, LOW);
        digitalWrite(rinh2, HIGH);
        digitalWrite(rinh3, HIGH);
      }
      else if (j == 8)
       {
         digitalWrite(rinh1, HIGH);
         digitalWrite(rinh2, LOW);
         digitalWrite(rinh3, HIGH);
       }
      else if (j == 16)
       {
         digitalWrite(rinh1, HIGH);
         digitalWrite(rinh2, HIGH);
         digitalWrite(rinh3, LOW);
       }

      if (j >= 16)
      {
        select_read_channel(j-16);
      }
      else if (j >= 8)
      {
        select_read_channel(j-8);
      }
      else select_read_channel(j);
      
      touch_list[i][j] = analogRead(readingPin) / 4;
    }
  }
}

void select_write_channel(byte channel)
{
    switch (channel)
    {
      case 0:
        digitalWrite(selectAw, LOW);
        digitalWrite(selectBw, LOW);
        digitalWrite(selectCw, LOW);
        break;
      case 1:
        digitalWrite(selectAw, HIGH);
        digitalWrite(selectBw, LOW);
        digitalWrite(selectCw, LOW);
        break;
      case  2:
        digitalWrite(selectAw, LOW);
        digitalWrite(selectBw, HIGH);
        digitalWrite(selectCw, LOW);
        break;
      case  3:
        digitalWrite(selectAw, HIGH);
        digitalWrite(selectBw, HIGH);
        digitalWrite(selectCw, LOW);
        break;
      case  4:
        digitalWrite(selectAw, LOW);
        digitalWrite(selectBw, LOW);
        digitalWrite(selectCw, HIGH);
        break;
      case 5:
        digitalWrite(selectAw, HIGH);
        digitalWrite(selectBw, LOW);
        digitalWrite(selectCw, HIGH);
        break;
      case 6:
        digitalWrite(selectAw, LOW);
        digitalWrite(selectBw, HIGH);
        digitalWrite(selectCw, HIGH);
        break;
      case 7:
        digitalWrite(selectAw, HIGH);
        digitalWrite(selectBw, HIGH);
        digitalWrite(selectCw, HIGH);
        break;
      default:
       break;
    }
}

void select_read_channel(byte channel)
{
    switch (channel)
    {
      case 0:
        digitalWrite(selectAr, LOW);
        digitalWrite(selectBr, LOW);
        digitalWrite(selectCr, LOW);
        break;
      case 1:
        digitalWrite(selectAr, HIGH);
        digitalWrite(selectBr, LOW);
        digitalWrite(selectCr, LOW);
        break;
      case  2:
        digitalWrite(selectAr, LOW);
        digitalWrite(selectBr, HIGH);
        digitalWrite(selectCr, LOW);
        break;
      case  3:
        digitalWrite(selectAr, HIGH);
        digitalWrite(selectBr, HIGH);
        digitalWrite(selectCr, LOW);
        break;
      case  4:
        digitalWrite(selectAr, LOW);
        digitalWrite(selectBr, LOW);
        digitalWrite(selectCr, HIGH);
        break;
      case 5:
        digitalWrite(selectAr, HIGH);
        digitalWrite(selectBr, LOW);
        digitalWrite(selectCr, HIGH);
        break;
      case 6:
        digitalWrite(selectAr, LOW);
        digitalWrite(selectBr, HIGH);
        digitalWrite(selectCr, HIGH);
        break;
      case 7:
        digitalWrite(selectAr, HIGH);
        digitalWrite(selectBr, HIGH);
        digitalWrite(selectCr, HIGH);
        break;
      default:
        break;
    }
}
        
