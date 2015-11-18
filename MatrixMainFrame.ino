#include "GameSnake.h"
#include "GameRainbow.h"
#include "GameClass.h"
#include <Adafruit_NeoPixel.h>

#define MATRIXPIN      8

Adafruit_NeoPixel Matrix = Adafruit_NeoPixel(MATRIX_SIZE, MATRIXPIN, NEO_GRB + NEO_KHZ800);

unsigned long MainTime;

GameClass* GAME;

void setup() {
	randomSeed(analogRead(0));

	Matrix.begin();
	Matrix.clear();
	Matrix.show();

	Serial.begin(115200);
	delay(200);
	Serial.println("Start");

	GAME = new GameSnake();
	DrawGame();

	MainTime = millis();
}

void loop() {
	
	if (GAME) GAME->CheckKey(digitalRead(7) == 0, digitalRead(6) == 0, digitalRead(5) == 0, digitalRead(4) == 0);

	unsigned long delta = millis() - MainTime;
	if (delta > 16) {
		MainTime = millis();
		if (GAME) {
			GAME->Loop((float)delta / 1000.0);
			DrawGame();
		}
	}
}

void DrawGame() {
	if (GAME) {
		if (GAME->updated) {
			for (int i = 0; i < MATRIX_SIZE; i++) Matrix.setPixelColor(i, GAME->Matrix[i]);
			Matrix.show();
			GAME->updated = false;
		}
	}

}