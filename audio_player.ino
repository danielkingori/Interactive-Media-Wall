/*
 * An audio player which plays a specific audio file from a micro SD card when a specific button is pressed
 */
// #define DECODE_NEC // IR decoding protocol
#include <SD.h>     // SD card library
#include <TMRpcm.h> //Arduino library for asynchronous playback of PCM/WAV files
#include <SPI.h>
#include <IRremote.hpp> // IR Remote library

/*
 * Player config
 */
const uint8_t sdPin = 53;
TMRpcm player;
bool goTo(bool isNext);
// The current song to be played
int currentSong = 0;
char song[8] = "001.wav";

/*
 * Song list
 */
char song1[] = "001.wav";
char song2[] = "002.wav";
char song3[] = "003.wav";
char song4[] = "004.wav";
char song5[] = "005.wav";
char song6[] = "006.wav";
char song7[] = "007.wav";
char song8[] = "008.wav";
char song9[] = "009.wav";
char song10[] = "010.wav";
char song11[] = "011.wav";
char song12[] = "012.wav";
char song13[] = "013.wav";
char song14[] = "014.wav";

/*
 * For IR callback
 */
const uint8_t irReceivePin = 2;
#define PROCESS_IR_RESULT_IN_MAIN_LOOP
#if defined(PROCESS_IR_RESULT_IN_MAIN_LOOP) || defined(ARDUINO_ARCH_MBED) || defined(ESP32)
volatile bool irDataJustReceived = false;
#endif
void irCallbackHandler();
String resolveIRKey(uint32_t data);
void applyCommand(char *key);
uint32_t irData;
String currentKey;
const uint8_t keyLength = 4;
byte dataCount = 0;

// buttons
#define debounce 10
const int button1 = 22;
const int button2 = 24;
const int button3 = 26;
const int button4 = 28;
const int button5 = 30;
const int button6 = 32;
const int button7 = 34;
const int button8 = 36;
const int button9 = 38;
const int button10 = 40;
const int button11 = 42;
const int button12 = 44;
const int button13 = 46;
const int button14 = 48;

// button states
bool button1State = LOW;
bool button2State = LOW;
bool button3State = LOW;
bool button4State = LOW;
bool button5State = LOW;
bool button6State = LOW;
bool button7State = LOW;
bool button8State = LOW;
bool button9State = LOW;
bool button10State = LOW;
bool button11State = LOW;
bool button12State = LOW;
bool button13State = LOW;
bool button14State = LOW;

void setup()
{
  Serial.begin(115200);

  // IR setup
  IrReceiver.begin(irReceivePin, ENABLE_LED_FEEDBACK);
  IrReceiver.registerReceiveCompleteCallback(irCallbackHandler);

  Serial.print(F("Ready to receive IR signals of protocols: "));
  printActiveIRProtocols(&Serial);
  Serial.println();

  // Setting up buttons as input
  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
  pinMode(button3, INPUT_PULLUP);
  pinMode(button4, INPUT_PULLUP);
  pinMode(button5, INPUT_PULLUP);
  pinMode(button6, INPUT_PULLUP);
  pinMode(button7, INPUT_PULLUP);
  pinMode(button8, INPUT_PULLUP);
  pinMode(button9, INPUT_PULLUP);
  pinMode(button10, INPUT_PULLUP);
  pinMode(button11, INPUT_PULLUP);
  pinMode(button12, INPUT_PULLUP);
  pinMode(button13, INPUT_PULLUP);
  pinMode(button14, INPUT_PULLUP);

  // player configuration
  player.speakerPin = 11;
  player.setVolume(5);

  if (!SD.begin(sdPin))
  {
    Serial.println("SD fail");
    exit(0);
  }
}

void loop()
{
  if (dataCount == keyLength - 1) {
    int songNumber = atoi(song);
    if (songNumber > 192) {
      Serial.println("Sorry, there is no song with that name");
    } else {
      Serial.println(song);
      player.play(song);
    }
    dataCount = 0;
  }
  // read button states
  bool button1Value = !(digitalRead(button1));
  bool button2Value = !(digitalRead(button2));
  bool button3Value = !(digitalRead(button3));
  bool button4Value = !(digitalRead(button4));
  bool button5Value = !(digitalRead(button5));
  bool button6Value = !(digitalRead(button6));
  bool button7Value = !(digitalRead(button7));
  bool button8Value = !(digitalRead(button8));
  bool button9Value = !(digitalRead(button9));
  bool button10Value = !(digitalRead(button10));
  bool button11Value = !(digitalRead(button11));
  bool button12Value = !(digitalRead(button12));
  bool button13Value = !(digitalRead(button13));
  bool button14Value = !(digitalRead(button14));

  if (button1Value != button1State) {
    button1State = !button1State;
    if (button1State == HIGH) {
      if (currentSong == 1) {
        player.pause();
      } else {
        currentSong = 1;
        player.play(song1);
      }
    } else {
      Serial.println("button 1 OFF");
      if (currentSong == 1) {
        player.pause();
      }
    }
  }

  if (button2Value != button2State) {
    button2State = !button2State;
    if (button2State == HIGH) {
      if (currentSong == 2) {
        player.pause();
      } else {
        currentSong = 2;
        player.play(song2);
      }
    } else {
      Serial.println("button 2 OFF");
      if (currentSong == 2) {
        player.pause();
      }
    }
  }

  if (button3Value != button3State) {
    button3State = !button3State;
    if (button3State == HIGH) {
      if (currentSong == 3) {
        player.pause();
      } else {
        currentSong = 3;
        player.play(song3);
      }
    } else {
      Serial.println("button 3 OFF");
      if (currentSong == 3) {
        player.pause();
      }
    }
  }

  if (button4Value != button4State) {
    button4State = !button4State;
    if (button4State == HIGH) {
      if (currentSong == 4) {
        player.pause();
      } else {
        currentSong = 4;
        player.play(song4);
      }
    } else {
      Serial.println("button 4 OFF");
      if (currentSong == 4) {
        player.pause();
      }
    }
  }

  if (button5Value != button5State) {
    button5State = !button5State;
    if (button5State == HIGH) {
      if (currentSong == 5) {
        player.pause();
      } else {
        currentSong = 5;
        player.play(song5);
      }
    } else {
      Serial.println("button 5 OFF");
      if (currentSong == 5) {
        player.pause();
      }
    }
  }

  if (button6Value != button6State) {
    button6State = !button6State;
    if (button6State == HIGH) {
      if (currentSong == 6) {
        player.pause();
      } else {
        currentSong = 6;
        player.play(song6);
      }
    } else {
      Serial.println("button 6 OFF");
      if (currentSong == 6) {
        player.pause();
      }
    }
  }

  if (button7Value != button7State) {
    button7State = !button7State;
    if (button7State == HIGH) {
      if (currentSong == 7) {
        player.pause();
      } else {
        currentSong = 7;
        player.play(song7);
      }
    } else {
      Serial.println("button 7 OFF");
      if (currentSong == 7) {
        player.pause();
      }
    }
  }

  if (button8Value != button8State) {
    button8State = !button8State;
    if (button8State == HIGH) {
      if (currentSong == 8) {
        player.pause();
      } else {
        currentSong = 8;
        player.play(song8);
      }
    } else {
      Serial.println("button 8 OFF");
      if (currentSong == 8) {
        player.pause();
      }
    }
  }

  if (button9Value != button9State) {
    button9State = !button9State;
    if (button9State == HIGH) {
      if (currentSong == 9) {
        player.pause();
      } else {
        currentSong = 9;
        player.play(song9);
      }
    } else {
      Serial.println("button 9 OFF");
      if (currentSong == 9) {
        player.pause();
      }
    }
  }

  if (button10Value != button10State) {
    button10State = !button10State;
    if (button10State == HIGH) {
      if (currentSong == 10) {
        player.pause();
      } else {
        currentSong = 10;
        player.play(song10);
      }
    } else {
      Serial.println("button 10 OFF");
      if (currentSong == 10) {
        player.pause();
      }
    }
  }

  if (button11Value != button11State) {
    button11State = !button11State;
    if (button11State == HIGH) {
      if (currentSong == 11) {
        player.pause();
      } else {
        currentSong = 11;
        player.play(song11);
      }
    } else {
      Serial.println("button 11 OFF");
      if (currentSong == 11) {
        player.pause();
      }
    }
  }

  if (button12Value != button12State) {
    button12State = !button12State;
    if (button12State == HIGH) {
      if (currentSong == 12) {
        player.pause();
      } else {
        currentSong = 12;
        player.play(song12);
      }
    } else {
      Serial.println("button 12 OFF");
      if (currentSong == 12) {
        player.pause();
      }
    }
  }
  
  if (button13Value != button13State) {
    button13State = !button13State;
    if (button13State == HIGH) {
      if (currentSong == 13) {
        player.pause();
      } else {
        currentSong = 13;
        player.play(song13);
      }
    } else {
      Serial.println("button 13 OFF");
      if (currentSong == 13) {
        player.pause();
      }
    }
  }

  if (button14Value != button14State) {
    button14State = !button14State;
    if (button14State == HIGH) {
      if (currentSong == 14) {
        player.pause();
      } else {
        currentSong = 14;
        player.play(song14);
      }
    } else {
      Serial.println("button 14 OFF");
      if (currentSong == 14) {
        player.pause();
      }
    }
  }
}

/*
 * Callback function
 * Here we know, that data is available.
 * This function is executed in ISR (Interrupt Service Routine) context (interrupts are blocked here).
 * Make it short and fast and keep in mind, that you can not use delay(), prints longer than print buffer size etc.,
 * because they require interrupts enabled to return.
 * In order to enable other interrupts you can call sei() (enable interrupt again) after evaluating/copying data.
 * Good practice, but somewhat more complex, is to copy relevant data and signal receiving to main loop.
 */
#if defined(ESP32) || defined(ESP8266)
IRAM_ATTR
#endif
void irCallbackHandler()
{
  if (IrReceiver.decode())
  {
    irData = IrReceiver.decodedIRData.decodedRawData;
    currentKey = resolveIRKey(irData);
    if (currentKey != "Q")
    {
      if (isDigit(currentKey[0]))
      {
        song[dataCount] = currentKey[0];
        dataCount++;
      }
      else
      {
        applyCommand(currentKey[0]);
      }
    }
    irDataJustReceived = true;
    IrReceiver.resume();
  }
}

/*
 * Returns a char for a given uint32_t value
 */
String resolveIRKey(uint32_t data)
{
  switch (data)
  {
  case 3910598400:
    return "0";
  case 4077715200:
    return "1";
  case 3877175040:
    return "2";
  case 2707357440:
    return "3";
  case 4144561920:
    return "4";
  case 3810328320:
    return "5";
  case 2774204160:
    return "6";
  case 3175284480:
    return "7";
  case 2907897600:
    return "8";
  case 3041591040:
    return "9";
  case 3158572800:
    return "P";
  case 3141861120:
    return "<";
  case 3208707840:
    return ">";
  case 4161273600:
    return "-";
  case 3927310080:
    return "+";
  default:
    return "Q";
  }
}

/*
 * Takes action after IR message decoded
 */
void applyCommand(char key)
{
  const int asciiValue = int(key);
  if (asciiValue == 80)
  {
    Serial.println("Pause");
    player.pause();
  }
  else if (asciiValue == 60)
  {
    Serial.println("Previous");
    const bool shouldPlayPrevious = goTo(false);
    if (shouldPlayPrevious)
    {
      player.play(song);
    }
    else
    {
      Serial.println("You can't select a song below 1");
    }
  }
  else if (asciiValue == 62)
  {
    Serial.println("Next");
    const bool shouldPlayNext = goTo(true);
    if (shouldPlayNext)
    {
      player.play(song);
    }
    else
    {
      Serial.println("Song is unavailable");
    }
  }
  else if (asciiValue == 45)
  {
    Serial.println("Volume down");
    player.volume(0);
  }
  else if (asciiValue == 43)
  {
    Serial.println("Volume up");
    player.volume(1);
  }
  else
  {
    Serial.println("Invalid command");
  }
}

/*
 * Enables going to the next or previous audio file
 */
bool goTo(bool isNext)
{
  Serial.println("Current Song:");
  Serial.println(song);
  char currentSongName[4];
  strncpy(currentSongName, song, 3);
  currentSongName[3] = '\0';
  int currentSongNumber = atoi(currentSongName);
  Serial.println("Current Song Number:");
  Serial.println(currentSongNumber);
  if (currentSongNumber == 1 && !isNext)
  {
    return false;
  }
  if (currentSongNumber == 192 && isNext)
  {
    return false;
  }
  int nextSong;
  if (isNext)
  {
    nextSong = currentSongNumber + 1;
  }
  else
  {
    nextSong = currentSongNumber - 1;
  }
  char nextSong_str[sizeof nextSong];
  itoa(nextSong, nextSong_str, 10);
  if (nextSong > 99)
  {
    song[0] = nextSong_str[0];
    song[1] = nextSong_str[1];
    song[2] = nextSong_str[2];
  }
  else if (nextSong > 9)
  {
    song[1] = nextSong_str[0];
    song[2] = nextSong_str[1];
  }
  else
  {
    song[2] = nextSong_str[0];
  }
  return true;
}
