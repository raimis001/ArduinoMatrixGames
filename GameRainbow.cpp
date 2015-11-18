#include "GameRainbow.h"

GameRainbow::GameRainbow()
{
	c[0] = Color(50, 0, 100);
	c[1] = Color(0, 255, 0);
	c[2] = Color(0, 0, 255);
	c[3] = Color(0, 255, 255);
	c[4] = Color(250, 250, 0);
	c[5] = Color(250, 50, 0);
	c[6] = Color(250, 0, 0);

	Serial.println("start: Rainbow class");
}

GameRainbow::~GameRainbow()
{
}

void GameRainbow::Update(float deltaTime) {
	SetPixel(CurrentPixel, c[CurrentColor]);
	CurrentPixel++; 
	if (CurrentPixel >= MATRIX_SIZE) {
		CurrentPixel = 0;
		CurrentColor++;
		if (CurrentColor > 6) CurrentColor = 0;
	}
}

