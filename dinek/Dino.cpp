#include "Dino.h"

Dino::Dino(HWND MainWindowHwnd, int X, int Y)
{
	width = X;
	height = Y;
	srand(time(0));
	jumping = false;
	GraphicsDevice = new Graphics();
	GraphicsDevice->InitGraphics(MainWindowHwnd, true);
	InitializeSprites(GraphicsDevice);
	SetRect(&FontRect, 0, 0, X, Y/20);
	D3DXCreateFontA(GraphicsDevice->device, Y/20, Y/20, FW_NORMAL, 1, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FF_DONTCARE, "Arial", &Font);
}
void Dino::InitializeSprites(Graphics *GraphicsDevice)
{
	GameSprite = new Sprite(0, width / 4, 0);
	GameSprite->InitSprite(GraphicsDevice->device, "skok1.png", width / 4, width / 4);
	GameSprite2 = new Sprite(0, width / 4, 0);
	GameSprite2->InitSprite(GraphicsDevice->device, "skok2.png", width / 4, width / 4);
	GameSprite3 = new Sprite(0, width / 4, 0);
	GameSprite3->InitSprite(GraphicsDevice->device, "bieg1.png", width / 4, width / 4);
	GameSprite4 = new Sprite(0, width / 4, 0);
	GameSprite4->InitSprite(GraphicsDevice->device, "bieg2.png", width / 4, width / 4);
	GameSprite5 = new Sprite(width, height/2, 0);
	GameSprite5->InitSprite(GraphicsDevice->device, "przeszkoda.png", width / 5, width / 4);
}
void Dino::Run(Sprite *s1, Sprite *s2, int frequency)
{
	s1->position.z = static_cast<int>(frequency) % 2 + 1;
	s2->position.z = static_cast<int>(frequency) % 2 - 1;
	s1->Draw();
	s2->Draw();
}
bool Dino::Jump(Sprite *s1, Sprite *s2, int Min, int Max, int JumpingSpeed)
{
	if (s1->position.y > Min && JumpingState())
	{
		s1->position.y -= JumpingSpeed;
		s1->Draw();
		if (s1->position.y <= Min)
			JumpingState(1, 0);
	}
	else if (s1->position.y < Max)
	{
		s1->position.y += JumpingSpeed;
		s2->position.y = s1->position.y;
		s2->Draw();

		if (s1->position.y >= Max)
		{
			JumpingState(1, 1);
			return false;
		}
	}
	return true;
}
bool Dino::JumpingState(bool change, bool to) //0 - starting jumping, 1 ending jumping
{
	static bool state = true;
	if (change)
		state = to;
	return state;
}
bool Dino::Main(float GameTime)
{
	float speed = GameTime / 10.0f + 8.0f;
	if (speed > 16.0f)
		speed = 16.0f;

	GraphicsDevice->Clear(D3DCOLOR_XRGB(255, 255, 255));
	GraphicsDevice->Begin();

	Font->DrawTextA(0, (LPCSTR)std::to_string(static_cast<int>(GameTime*speed)).c_str(), -1, &FontRect, DT_RIGHT, D3DCOLOR_XRGB(0, 0, 0));

	for (int i = 0; i < speed; i++)
	{
		GameSprite5->position.x -= 2;
		if (GameSprite5->position.x < width / 9 && GameSprite5->position.x > width / 10 && GameSprite->position.y > height / 3)
		{
			GameSprite5->Draw();
			return 0;
		}
	}
	GameSprite5->Draw();
	if (GameSprite5->position.x < -width / 5)
		GameSprite5->position.x = width + rand() % (width/3);

	if (GetAsyncKeyState(VK_SPACE))
		jumping = true;

	if (jumping)
		jumping = Jump(GameSprite, GameSprite2, width / 19, width / 4, speed);
	else
		Run(GameSprite3, GameSprite4, GameTime*speed);

	GraphicsDevice->End();
	GraphicsDevice->Present();

	if (GameSprite5->position.x < width / 9 && GameSprite5->position.x > width / 10 && GameSprite->position.y > height/3)
		return 0;
	return 1;
}
void Dino::Fail(float &Clock)
{
	MessageBox(0, "Uff, nie udalo ci sie przeskoczyc, ale zawsze mozesz sprobowac znowu", "Przegrana", 0);
	Clock = clock() / CLOCKS_PER_SEC;
	GameSprite5->position.x = width;
	GameSprite->position.y = height/2;
	JumpingState(1, 1);
	jumping = false;
}
void Dino::Delete()
{
	delete GameSprite;
	delete GameSprite2;
	delete GameSprite3;
	delete GameSprite4;
	delete GameSprite5;
	delete GraphicsDevice;
}
