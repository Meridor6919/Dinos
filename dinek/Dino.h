#pragma once
#include "Sprite.h"
#include "Graphics.h"
#include <time.h>

class Dino {

	ID3DXFont *Font;
	RECT FontRect;
	Graphics *GraphicsDevice;
	Sprite *GameSprite, *GameSprite2, *GameSprite3, *GameSprite4, *GameSprite5;
	bool jumping;
	int width;
	int height;

public:
	
	bool JumpingState(bool change = false, bool to = true);
	void Run(Sprite *s1, Sprite *s2, int frequency);
	bool Jump(Sprite *s1, Sprite *s2, int Min, int Max, int JumpingSpeed);
	bool Main(float GameTime);
	void InitializeSprites(Graphics *GraphicsDevice);
	void Fail(float &Clock);
	void Delete();
	Dino(HWND MainWindowHwnd, int X, int Y);
};

