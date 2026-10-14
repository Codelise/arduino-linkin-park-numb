#include <Arduino.h>

int playBtn = 12;
int pauseBtn = 11;

int buzzerPin = 9;
#define LED_A4   2
#define LED_C5   3
#define LED_D5   4
#define LED_E5   5
#define LED_F5   6
#define LED_FS5  7
#define LED_GS5  8

// Note frequencies (Hz)
#define A4   440
#define C5   523
#define D5   587
#define E5   659
#define F5   698
#define Fs4  370
#define Gs4  415
#define Cs5  554
#define Fs5  740
#define Gs5  831
#define REST 0

// ===== INTRO =====
int melody[] = {
  A4, C5, A4, D5, F5, E5,
  A4, C5, A4, F5, E5, C5
};
int duration[] = {
  1, 1, 1, 3, 2, 3,
  1, 1, 1, 3, 2, 3
};
int noteCount = 12;

// ===== CHORUS =====
// "I've become so numb, I can't feel you there"
// "Become so tired, so much more aware"
// "I'm becoming this, all I want to do"
// "Is be more like me and be less like you"
int chorusMelody[] = {
  Fs5, Fs5, Fs5, E5, Fs5, Fs5, Fs5, Gs5, E5,
  Fs5, Fs5, E5, Fs5, Fs5, Fs5, E5, Fs5, Fs5,
  Fs5, E5, Fs5, Fs5, Fs5, Gs5, E5,
  Fs5, Fs5, E5, Fs5, Fs5, Fs5,  E5, Fs5
};
int chorusDuration[] = {
  2, 2, 2, 2, 2, 2, 2, 2,
  2, 2, 2, 2, 2, 2, 2, 2,
  2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
  2, 2, 2, 2, 2, 2, 2, 2
};   
int chorusNoteCount = 33;   
int chorusBeatLength = 300; // 1 = eighth note at 120 BPM   

int beatLength = 300; // ms per beat (~120 BPM)

// put function declarations here:

//lightLED = "Given a note, light the right bulb."
void lightLED(int freq){
  digitalWrite(LED_A4, LOW);
  digitalWrite(LED_C5, LOW);
  digitalWrite(LED_D5, LOW);
  digitalWrite(LED_E5, LOW);
  digitalWrite(LED_F5, LOW);
  digitalWrite(LED_FS5, LOW);
  digitalWrite(LED_GS5, LOW);

  switch(freq){
    case A4: digitalWrite(LED_A4, HIGH); break;
    case C5: digitalWrite(LED_C5, HIGH); break;
    case D5: digitalWrite(LED_D5, HIGH); break;
    case E5: digitalWrite(LED_E5, HIGH); break;
    case F5: digitalWrite(LED_F5, HIGH); break;
    case Fs5: digitalWrite(LED_FS5, HIGH); break;
    case Gs5: digitalWrite(LED_GS5, HIGH); break;
    default: break;
  } 
}

//playSection = "Go through the list of notes one by one. For each one: light the bulb, buzz it, wait, move to the next."
void playSection(int *melody, int *duration, int count) {
  Serial.println(count);
  for (int i = 0; i < count; i++) {       // go through each note
    lightLED(melody[i]);                   // light the matching LED
    if (melody[i] != REST)                 // is it a real note?
      tone(buzzerPin, melody[i], duration[i] * beatLength);  // buzz it
    else
      noTone(buzzerPin);                   // or silence
    delay(duration[i] * beatLength);       // wait that long before next note
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(buzzerPin, OUTPUT);
  pinMode(LED_A4, OUTPUT);
  pinMode(LED_C5, OUTPUT);
  pinMode(LED_D5, OUTPUT);
  pinMode(LED_E5, OUTPUT);
  pinMode(LED_F5, OUTPUT);
  pinMode(LED_FS5, OUTPUT);
  pinMode(LED_GS5, OUTPUT);

  pinMode(playBtn, INPUT_PULLUP);
  pinMode(pauseBtn, INPUT_PULLUP);
}

void loop() {
   if(digitalRead(playBtn) == LOW){
    playSection(melody, duration, noteCount);
    delay(500);
    playSection(chorusMelody, chorusDuration, chorusNoteCount);
    delay(200);
  }
}

