// GameSnake.h

#ifndef _GAMESNAKE_h
#define _GAMESNAKE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "GameClass.h"

class GameSnake : public GameClass
{
public:
	GameSnake();
	~GameSnake();

	virtual void Update(float deltaTime);
	
private:

	int Snake[MATRIX_SIZE];
	int Walls[MATRIX_SIZE];

	int currentX = 0;
	int currentY = 0;

	uint32_t snakeColor = Color(0, 0, 255);
	uint32_t paikaColor = Color(0, 255, 0);
	uint32_t wallColor = Color(255, 0, 0);

	int current = 0;

	int direction = KEY_RIGHT;

	float maxPaika = 10;
	float maxTime = 0.5;
	float time = 0.1;

	void SetPaika();

	virtual void KeyDown(int keyCode);

	virtual void StartGame();
	virtual void NextLevel();
	virtual void RestartLevel();

	int GetFreePosition(); 

};


#endif

