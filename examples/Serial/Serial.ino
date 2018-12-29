#include <Regexp.h>


// Global parameters used to collect a regex selector and command parameters.
String selector = "";
bool selectorRead = false;
String parameters = "";
bool parametersRead = false;

MatchState ms;

void setup()
{ 
    ms.Target("0");
    // Open serial connection at 9600 Bd.
    Serial.begin(9600);
}

void loop()
{
    if (selectorRead && parametersRead) {
      char res = ms.Match(const_cast<char*>(selector.c_str()), 0);
      if (res > 0) {
        reset();
      } else if (res == 0) {
        reset();
      } else {
        reset();
      }
    }
}

void serialEvent() 
{
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    
    if (!selectorRead) {
      addToCommandRegex(inChar);
    } else {
      addToParameters(inChar);
    }
  }
}

void reset(){
  selectorRead = false;
  parametersRead = false;
  selector = "";
  parameters = "";
}

void addToCommandRegex(char inChar) {
  if (inChar != ';') {
    selector += inChar;
  } else {
    selectorRead = true;
  }
}

void addToParameters(char inChar) {
  if (inChar != ';') {
    parameters += inChar;
  } else {
    parametersRead = true;
  }
}
