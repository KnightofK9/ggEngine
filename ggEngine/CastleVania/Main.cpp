#include "../ggEngine/ggEngine.h"
#include "TestStateCastleVania.h"
#include "TestState.h"
#define KEY_DOWN(vk_code) ( (GetAsyncKeyState(vk_code)&0x8000)?1:0 )
using namespace ggEngine;
//Field
Window *window;
Game *game;
//Method declarations
void cleanup();
void quitWithError(LPCTSTR error);
void programLoop();
void update();
void initGame();
void onExit();
LRESULT CALLBACK messageHandler(HWND window, UINT msg, WPARAM wParam, LPARAM lParam);
int main() {
	try {
		window = new Window(messageHandler, TEXT("The Greatest Game Engine"), CW_USEDEFAULT, CW_USEDEFAULT, GAME_WIDTH, GAME_HEIGHT, GameMode_Windowed);
		//game = new Game(window->getHandle(), GAME_WIDTH, GAME_HEIGHT, GameMode_Windowed, D3DCOLOR_XRGB(0,0,0));
		game = new Game(window->getHandle(), GAME_WIDTH, GAME_HEIGHT, GameMode_Windowed, PhysicsMode_AABBSwept, D3DCOLOR_XRGB(177, 177, 177));
	}
	catch (LPCTSTR error) {
		quitWithError(error);
	}
	window->show();
	initGame();
	programLoop();
	cleanup();

	return EXIT_SUCCESS;
}
void cleanup() {
	if (window != NULL) { delete window; window = NULL; }
}
void initGame() {
	TestStateCastleVania *testState = new TestStateCastleVania(game);
	TestState *tState = new TestState(game);
	game->stateManager->Add("TestStateCastleVania", testState, false);
	game->stateManager->Add("TestState", tState, false);
	game->stateManager->Start("TestState", false, false);
}
void quitWithError(LPCTSTR error) {
	HWND parentWindow = NULL;
	if (window != NULL) parentWindow = window->getHandle();
	MessageBox(parentWindow, error, TEXT("Runtime Error!"), MB_OK | MB_ICONERROR);

	cleanup();

	exit(EXIT_FAILURE);
}

void programLoop() {
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	int done = 0;
	while (!done) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			if (msg.message == WM_QUIT) done = 1;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else update();
	}
	onExit();
}
LRESULT CALLBACK messageHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
	case WM_DESTROY:
		PostQuitMessage(EXIT_SUCCESS);
		return 0;
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}
void update() {
	game->GameRun();
	if (KEY_DOWN(VK_ESCAPE))
		PostMessage(window->getHandle(), WM_DESTROY, 0, 0);
}
void onExit() {
	delete game;
}