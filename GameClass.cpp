#include "GameClass.h"

GameClass::GameClass() {
	Serial.println("Start game class!");
	for (int i = 0; i < MATRIX_SIZE; i++) Matrix[i] = 0;
}

GameClass::~GameClass() {
}


void GameClass::Loop(float deltaTime) {

	switch (GameStatus) {
		case 0:
			Update(deltaTime);
			break;
		case 1:
			Victory(deltaTime);
			break;
		case 2:
			Lose(deltaTime);
			break;
	}
}

uint32_t GameClass::Color(uint8_t r, uint8_t g, uint8_t b) {
	return ((uint32_t)r << 16) | ((uint32_t)g << 8) | b;
}

int GameClass::Position(int x, int y) {
	if (y % 2 == 0) return y * 16 + x;
	return y * 16 + 15 - x;
}

void GameClass::SetPixel(int position, uint32_t color) {
	if (!updated && Matrix[position] != color) updated = true;
	Matrix[position] = color;
}

void GameClass::SetPixel(int x, int y, uint32_t color) {
	SetPixel(Position(x, y),color);
}

uint32_t GameClass::GetPixel(int position) {
	return Matrix[position];
}
uint32_t GameClass::GetPixel(int x, int y) {
	return GetPixel(Position(x, y));
}

void GameClass::Clear() {
	for (int i = 0; i < MATRIX_SIZE; i++) Matrix[i] = 0;
	updated = true;
}

void GameClass::Victory(float deltaTime){
	if (GameStatus == 0) {
		Clear();
		GameStatus = 1;
		waitLevel = 5;
		DrawNumber(Level);
		return;
	}

	//SetPixel(random(MATRIX_SIZE), Color(100, 100, 100));

	waitLevel -= deltaTime;
	if (waitLevel <= 0) {
		waitLevel = 5;
		GameStatus = 0;
		Level++;
		Clear();
		NextLevel();
	}


}
void GameClass::Lose(float deltaTime){
	if (GameStatus == 0) {
		Clear();
		GameStatus = 2;
		DrawMario();
		waitLevel = 5;
		return;
	}
	//SetPixel(random(MATRIX_SIZE), Color(255, 10, 10));

	waitLevel -= deltaTime;
	if (waitLevel <= 0) {
		waitLevel = 5;
		GameStatus = 0;
		Clear();
		RestartLevel();
	}

}

void GameClass::DrawMario() {
	uint32_t clr[4];
	clr[0] = 0;
	clr[1] = Color(0, 255, 0);
	clr[2] = Color(255, 0, 0);
	clr[3] = Color(255, 255, 255);

	for (int i = 0; i < MATRIX_SIDE; i++) {
		for (int j = 0; j < MATRIX_SIDE; j++) {
			SetPixel(j, MATRIX_SIDE - i - 1, clr[Mario[i][j]]);
		}
	}
}
void GameClass::DrawNumber(int num) {
	uint32_t c = Color(0, 0, 255);
	Clear();
	for (int i = 0; i < MATRIX_SIDE; i++) {
		for (int j = 0; j < 8; j++) {
			if (cipari[num][i][j] > 0) SetPixel(j, MATRIX_SIDE - i - 1, c);
		}
	}

}

void GameClass::CheckKey(bool up, bool right, bool down, bool left) {
	if (up) {
		if (!KeyUP) {
			KeyUP = true;
			KeyDown(KEY_UP);
		}
	} else {
		if (KeyUP) {
			KeyUP = false;
			KeyUp(KEY_UP);
		}
	} if (right) {
		if (!KeyRIGHT) {
			KeyRIGHT = true;
			KeyDown(KEY_RIGHT);
		}
	} else {
		if (KeyRIGHT) {
			KeyRIGHT = false;
			KeyUp(KEY_RIGHT);
		}
	}
	if (down) {
		if (!KeyDOWN) {
			KeyDOWN = true;
			KeyDown(KEY_DOWN);
		}
	} else {
		if (KeyDOWN) {
			KeyDOWN = false;
			KeyUp(KEY_DOWN);
		}
	}

	if (left) {
		if (!KeyLEFT) {
			KeyLEFT = true;
			KeyDown(KEY_LEFT);
		}
	} else {
		if (KeyLEFT) {
			KeyLEFT = false;
			KeyUp(KEY_LEFT);
		}
	}

}