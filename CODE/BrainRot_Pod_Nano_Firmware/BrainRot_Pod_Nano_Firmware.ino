// Sample firmware for Brain_Rot_Pod_Nano
// Overengineered Firmware for Overengineered project

#include <SPI.h>
#include <SD.h>
#include <TFT_eSPI.h>
#include "AudioFileSourceSD.h"
#include "AudioGeneratorWAV.h"
#include "AudioOutputI2S.h"

#define I2S_BCLK       4
#define I2S_LRC        5
#define I2S_DOUT       6

#define SD_CS          42
#define SD_MOSI        35
#define SD_MISO        37
#define SD_CLK         36

#define ENC_A          14
#define ENC_B          15
#define ENC_SW         16

#define BTN_ABORT      1

enum SystemState {
  STATE_MENU,
  STATE_MUSIC_PLAYING,
  STATE_MEME_SETUP,
  STATE_MEME_ARMED,
  STATE_MEME_PLAYING
};

SystemState currentState = STATE_MENU;

AudioGeneratorWAV *wav;
AudioFileSourceSD *file;
AudioOutputI2S *out;

float currentVolume = 0.6;

uint32_t memeStartTime = 0;
uint32_t memeDelayMs = 60000;
bool memeArmed = false;

uint32_t lastButtonPress = 0;
int lastEncoderState = HIGH;

uint32_t lastUIUpdate = 0;
bool uiNeedsUpdate = true;

TFT_eSPI tft = TFT_eSPI();

void setup() {

  Serial.begin(115200);

  pinMode(ENC_A, INPUT_PULLUP);
  pinMode(ENC_B, INPUT_PULLUP);
  pinMode(ENC_SW, INPUT_PULLUP);

  pinMode(BTN_ABORT, INPUT_PULLUP);

  // Initialize TFT
  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);

  // Initialize SPI
  SPI.begin(SD_CLK, SD_MISO, SD_MOSI, SD_CS);

  // Initialize SD card
  if (!SD.begin(SD_CS, SPI, 40000000)) {

    tft.drawString("SD CARD FAILED", 10, 10, 2);

    while (1) {
      delay(100);
    }
  }

  // Initialize audio system
  audioLogger = &Serial;

  file = new AudioFileSourceSD();
  out = new AudioOutputI2S();
  wav = new AudioGeneratorWAV();

  // Configure I2S
  out->SetPinout(I2S_BCLK, I2S_LRC, I2S_DOUT);

  // Set initial volume
  out->SetGain(currentVolume);

  uiNeedsUpdate = true;
}


void loop() {

  handleInputs();
  handleAudio();
  handleMemeTimer();
  updateUI();

}


void handleAudio() {

  if (wav && wav->isRunning()) {

    if (!wav->loop()) {

      wav->stop();

      file->close();

      if (currentState == STATE_MEME_PLAYING) {

        currentState = STATE_MENU;
        uiNeedsUpdate = true;

      }
    }
  }
}


void playFile(const char *filename) {

  if (wav->isRunning()) {

    wav->stop();
    file->close();

  }

  if (!file->open(filename)) {

    Serial.print("Failed to open: ");
    Serial.println(filename);

    currentState = STATE_MENU;
    uiNeedsUpdate = true;

    return;
  }

  if (!wav->begin(file, out)) {

    Serial.println("Failed to start WAV playback");

    file->close();

    currentState = STATE_MENU;
    uiNeedsUpdate = true;

    return;
  }
}


void handleInputs() {

  uint32_t now = millis();

  // Button handling
  if (now - lastButtonPress > 50) {

    // Encoder push button
    if (digitalRead(ENC_SW) == LOW) {

      if (currentState == STATE_MUSIC_PLAYING) {

        // Mute / unmute audio
        if (wav->isRunning()) {

          if (currentVolume > 0.0) {
            out->SetGain(0.0);
          }
          else {
            out->SetGain(0.6);
          }

        }

      }

      else if (currentState == STATE_MEME_SETUP) {

        memeArmed = true;
        memeStartTime = now;

        currentState = STATE_MEME_ARMED;

        uiNeedsUpdate = true;

      }

      else if (currentState == STATE_MENU) {

        playFile("/music/song.wav");

        currentState = STATE_MUSIC_PLAYING;

        uiNeedsUpdate = true;

      }

      lastButtonPress = now;
    }


    // Abort button
    if (digitalRead(BTN_ABORT) == LOW) {

      if (wav->isRunning()) {
        wav->stop();
      }

      if (file) {
        file->close();
      }

      memeArmed = false;

      currentState = STATE_MENU;

      uiNeedsUpdate = true;

      lastButtonPress = now;
    }
  }


  // Rotary encoder
  int currentEncoderState = digitalRead(ENC_A);

  if (currentEncoderState != lastEncoderState &&
      currentEncoderState == LOW) {

    if (digitalRead(ENC_B) != currentEncoderState) {

      currentVolume += 0.05;

      if (currentVolume > 1.0) {
        currentVolume = 1.0;
      }

    }
    else {

      currentVolume -= 0.05;

      if (currentVolume < 0.0) {
        currentVolume = 0.0;
      }
    }

    out->SetGain(currentVolume);

    uiNeedsUpdate = true;
  }

  lastEncoderState = currentEncoderState;
}


void handleMemeTimer() {

  if (currentState == STATE_MEME_ARMED && memeArmed) {

    uint32_t now = millis();

    uint32_t elapsed = now - memeStartTime;


    // Update countdown once per second
    if (now - lastUIUpdate >= 1000) {

      uiNeedsUpdate = true;
      lastUIUpdate = now;

    }


    // Timer expired
    if (elapsed >= memeDelayMs) {

      memeArmed = false;

      currentState = STATE_MEME_PLAYING;

      uiNeedsUpdate = true;

      playFile("/memes/faaaah.wav");
    }
  }
}


void updateUI() {

  if (!uiNeedsUpdate) {
    return;
  }

  uiNeedsUpdate = false;

  tft.fillScreen(TFT_BLACK);


  switch (currentState) {

    case STATE_MENU:

      tft.drawString("BRAINROT POD NANO", 10, 10, 4);

      tft.drawString("> MUSIC", 10, 50, 2);

      tft.drawString("  MEME SETUP", 10, 70, 2);

      break;


    case STATE_MUSIC_PLAYING:

      tft.drawString("MUSIC PLAYING", 10, 10, 4);

      tft.drawString("> song.wav", 10, 50, 2);

      tft.drawString("Volume:", 10, 90, 2);

      tft.drawNumber(
        (int)(currentVolume * 100),
        80,
        90,
        2
      );

      break;


    case STATE_MEME_SETUP:

      tft.drawString("MEME SETUP", 10, 10, 4);

      tft.drawString("FAAAAAH.wav", 10, 50, 2);

      tft.drawString("Delay:", 10, 80, 2);

      tft.drawNumber(
        memeDelayMs / 1000,
        80,
        80,
        2
      );

      tft.drawString("SECONDS", 120, 80, 2);

      break;


    case STATE_MEME_ARMED: {

      tft.drawString("MEME TIMER", 10, 10, 4);

      tft.drawString("FAAAAAH.wav", 10, 40, 2);

      uint32_t elapsed = millis() - memeStartTime;

      uint32_t remainingMs = 0;

      if (elapsed < memeDelayMs) {
        remainingMs = memeDelayMs - elapsed;
      }

      uint32_t remaining = remainingMs / 1000;

      tft.drawString("T-MINUS:", 10, 80, 4);

      tft.drawNumber(
        remaining,
        120,
        80,
        4
      );

      break;
    }


    case STATE_MEME_PLAYING:

      tft.fillScreen(TFT_RED);

      tft.setTextColor(TFT_WHITE, TFT_RED);

      tft.drawString("💀", 40, 50, 4);
      tft.drawString("FAAAAAAH", 40, 100, 4);

      tft.setTextColor(TFT_WHITE, TFT_BLACK);

      break;
  }
}