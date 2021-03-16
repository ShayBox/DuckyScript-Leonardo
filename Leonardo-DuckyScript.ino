/*
   Author: Shayne Hartford (ShayBox)
           https://shaybox.com
           https://github.com/shaybox
   GIT:
           https://github.com/shaybox/leonardo-duckyscript
           https://github.com/Seytonic/Duckduino-microSD
*/

#define HID_CUSTOM_LAYOUT
#define LAYOUT_US_ENGLISH

#include <HID-Project.h>
#include <SD.h>

int led = 13;

void setup() {
  //  Serial.begin(9600);
  //  while (!Serial);

  pinMode(led, OUTPUT);

  if (!SD.begin(4)) {
    while (true) {
      digitalWrite(led, HIGH);
    }
  }

  File file = SD.open("payload.txt");
  if (file) {
    Keyboard.begin();
    delay(10);

    String line;
    while (file.available()) {
      char c = file.read();
      if (c == '\n') {
        process(line);
        line = "";
        continue;
      } else if ((int) c != 13) {
        line += c;
      }
    }
    process(line);

    file.close();
  } else {
    digitalWrite(led, HIGH);
  }

  delay(10);
  Keyboard.end();
}

int defaultDelay;
String previousLine;
void process(String line) {
  int space = line.indexOf(" ");
  if (space == -1) {
    press(line);
    return;
  }

  String inst = line.substring(0, space);
  String args = line.substring(space + 1);

  if (inst == "REM") {
    return;
  }


  if (defaultDelay > 0) {
    delay(defaultDelay);
  }

  if (inst == "DEFAULT_DELAY" || inst == "DEFAULTDELAY") {
    defaultDelay = (int) args.toInt();
  } else if (inst == "DELAY") {
    delay((int) args.toInt());
  } else if (inst == "STRING_DELAY" || inst == "STRINGDELAY") {
    int space_1 = args.indexOf(" ");
    if (space_1 == -1) {
      return;
    }

    int stringDelay = args.substring(0, space_1).toInt();
    String string = args.substring(space_1 + 1);
    for (int i = 0; i < string.length(); i++) {
      Keyboard.write(string[i]);
      delay(stringDelay);
    }
  } else if (inst == "STRING") {
    Keyboard.print(line.substring(space + 1));
  } else if (inst == "REPEAT") {
    for (int i = args.toInt(); i > 0; i--) {
      process(previousLine);
    }
  } else {
    press(inst);
    press(args);
  }

  previousLine = line;

  Keyboard.releaseAll();
}

void press(String k) {
  if (k.length() == 1) Keyboard.press((char) k[0]);
  else if (k == "ENTER" || k == "RETURN") Keyboard.press(KEY_ENTER);
  else if (k == "ESC" || k == "ESCAPE") Keyboard.press(KEY_ESC);
  else if (k == "BACKSPACE") Keyboard.press(KEY_BACKSPACE);
  else if (k == "TAB") Keyboard.press(KEY_TAB);
  else if (k == "SPACE") Keyboard.press(KEY_SPACE);
  else if (k == "MINUS") Keyboard.press(KEY_MINUS);
  else if (k == "EQUAL" || k == "EQUALS") Keyboard.press(KEY_EQUAL);
  else if (k == "LEFT_BRACE") Keyboard.press(KEY_LEFT_BRACE);
  else if (k == "RIGHT_BRACE") Keyboard.press(KEY_RIGHT_BRACE);
  else if (k == "BACKSLASH") Keyboard.press(KEY_BACKSLASH);
  else if (k == "SEMICOLON") Keyboard.press(KEY_SEMICOLON);
  else if (k == "QUOTE") Keyboard.press(KEY_QUOTE);
  else if (k == "TILDE") Keyboard.press(KEY_TILDE);
  else if (k == "COMMA") Keyboard.press(KEY_COMMA);
  else if (k == "PERIOD") Keyboard.press(KEY_PERIOD);
  else if (k == "SLASH") Keyboard.press(KEY_SLASH);
  else if (k == "CAPS_LOCK" || k == "CAPSLOCK") Keyboard.press(KEY_CAPS_LOCK);
  else if (k == "PRINT" || k == "PRINT_SCREEN" || k == "PRINTSCREEN") Keyboard.press(KEY_PRINT);
  else if (k == "SCROLL" || k == "SCROLL_LOCK" || k == "SCROLLLOCK") Keyboard.press(KEY_SCROLL_LOCK);
  else if (k == "PAUSE" || k == "BREAK") Keyboard.press(KEY_PAUSE);
  else if (k == "INSERT") Keyboard.press(KEY_INSERT);
  else if (k == "HOME") Keyboard.press(KEY_HOME);
  else if (k == "PAGE_UP" || k == "PAGEUP") Keyboard.press(KEY_PAGE_UP);
  else if (k == "DELETE") Keyboard.press(KEY_DELETE);
  else if (k == "END") Keyboard.press(KEY_END);
  else if (k == "PAGE_DOWN" || k == "PAGEDOWN") Keyboard.press(KEY_PAGE_DOWN);
  else if (k == "RIGHT_ARROW" || k == "RIGHTARROW" || k == "RIGHT") Keyboard.press(KEY_RIGHT_ARROW);
  else if (k == "LEFT_ARROW" || k == "LEFTARROW" || k == "LEFT") Keyboard.press(KEY_LEFT_ARROW);
  else if (k == "DOWN_ARROW" || k == "DOWNARROW" || k == "DOWN") Keyboard.press(KEY_DOWN_ARROW);
  else if (k == "UP_ARROW" || k == "UPARROW" || k == "UP") Keyboard.press(KEY_UP_ARROW);
  else if (k == "NUM" || k == "NUM_LOCK" || k == "NUMLOCK") Keyboard.press(KEY_NUM_LOCK);
  else if (k == "APPLICATION" || k == "MENU") Keyboard.press(KEY_APPLICATION);
  else if (k == "LEFT_CTRL" || k == "CONTROL" || k == "CTRL") Keyboard.press(KEY_LEFT_CTRL);
  else if (k == "LEFT_SHIFT" || k == "SHIFT") Keyboard.press(KEY_LEFT_SHIFT);
  else if (k == "LEFT_ALT" || k == "ALT") Keyboard.press(KEY_LEFT_ALT);
  else if (k == "LEFT_GUI" || k == "GUI") Keyboard.press(KEY_LEFT_GUI);
  else if (k == "LEFT_WINDOWS" || k == "WINDOWS") Keyboard.press(KEY_LEFT_WINDOWS);
  else if (k == "RIGHT_CTRL") Keyboard.press(KEY_RIGHT_CTRL);
  else if (k == "RIGHT_SHIFT") Keyboard.press(KEY_RIGHT_SHIFT);
  else if (k == "RIGHT_ALT") Keyboard.press(KEY_RIGHT_ALT);
  else if (k == "RIGHT_GUI") Keyboard.press(KEY_RIGHT_GUI);
  else if (k == "RIGHT_WINDOWS") Keyboard.press(KEY_RIGHT_WINDOWS);
  else if (k == "F1") Keyboard.press(KEY_F1);
  else if (k == "F2") Keyboard.press(KEY_F2);
  else if (k == "F3") Keyboard.press(KEY_F3);
  else if (k == "F4") Keyboard.press(KEY_F4);
  else if (k == "F5") Keyboard.press(KEY_F5);
  else if (k == "F6") Keyboard.press(KEY_F6);
  else if (k == "F7") Keyboard.press(KEY_F7);
  else if (k == "F8") Keyboard.press(KEY_F8);
  else if (k == "F9") Keyboard.press(KEY_F9);
  else if (k == "F10") Keyboard.press(KEY_F10);
  else if (k == "F11") Keyboard.press(KEY_F11);
  else if (k == "F12") Keyboard.press(KEY_F12);
  else if (k == "F13") Keyboard.press(KEY_F13);
  else if (k == "F14") Keyboard.press(KEY_F14);
  else if (k == "F15") Keyboard.press(KEY_F15);
  else if (k == "F16") Keyboard.press(KEY_F16);
  else if (k == "F17") Keyboard.press(KEY_F17);
  else if (k == "F18") Keyboard.press(KEY_F18);
  else if (k == "F19") Keyboard.press(KEY_F19);
  else if (k == "F20") Keyboard.press(KEY_F20);
  else if (k == "F21") Keyboard.press(KEY_F21);
  else if (k == "F22") Keyboard.press(KEY_F22);
  else if (k == "F23") Keyboard.press(KEY_F23);
  else if (k == "F24") Keyboard.press(KEY_F24);
}

void loop() {
  digitalWrite(led, HIGH);
  delay(500);
  digitalWrite(led, LOW);
  delay(500);
}
