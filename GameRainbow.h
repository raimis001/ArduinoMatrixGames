// GameRainbow.h


#ifndef _GAMERAINBOW_h
#define _GAMERAINBOW_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "GameClass.h"

class  GameRainbow : public GameClass {
public:
	 GameRainbow();
	~GameRainbow();
	virtual void Update(float deltaTime);
private:
	uint32_t c[7];

	int CurrentPixel = 0;
	int CurrentColor = 0;
};


#endif

