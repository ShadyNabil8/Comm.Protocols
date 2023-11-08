#include <Arduino.h>
// put function declarations here:
// String readString;
char operation;
void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
}

void loop()
{
  if(Serial.available())
  {
    operation = Serial.read();
    Serial.println(operation);
    if(operation == 'F')
    {
        digitalWrite(LED_BUILTIN, LOW);
    }
    else if(operation == 'N')
    {
      digitalWrite(LED_BUILTIN, HIGH);
    }
  }
  // How to read a string
  // while (Serial.available())
  // {
  //   delay(2); // delay to allow byte to arrive in input buffer
  //   char c = Serial.read();
  //   readString += c;
  // }

  // if (readString.length() > 0)
  // {
  //   Serial.println(readString);

  //   readString = "";
  // }
}
