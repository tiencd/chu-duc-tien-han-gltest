/*************************************************************************************************
 * MAIN.CPP                                                    Copyright (c) 2003 Eamonn Doherty *
 *                                                                                               *
 * Textured quad demo in Direct3D 9                                                              *
 *************************************************************************************************/

#include "main.h"
#include "Constrain.h"
#include "Screen.h"
#include "GameScr.h"
#include <string>
using namespace std;

GameScr curScreen;
//Entry point
int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    MSG msg;
    //Start program execution
    bRunning = true;
    //Make a window and initialize DirectX in windowed mode
    MakeWindow(hInstance);
    InitD3D (0, 0, D3DFMT_A8R8G8B8, hWnd, true);
	if(!curScreen.onInit()) {
		bRunning = false;
		MessageBox(hWnd, "Can't load image resource, please check again!", "Error", MB_OK);
	}
	
    //Main application loop
    while (bRunning)
    {
        //Handle messages
        if (PeekMessage (&msg,NULL,0,0,PM_REMOVE))
        {
            TranslateMessage (&msg);
            DispatchMessage (&msg);
        }

        //Clear buffer and draw sample graphic
        ClearBuffer ();
        BeginDrawing ();
		curScreen.onUpdate();
		curScreen.onPaint();
        EndDrawing ();
        Present ();
		curScreen.onCheckGameOver();
    }

    //Cleaup all loaded textures (1 in this case)
    CTexture::CleanupTextures ();

    //Close DirectX
    CloseD3D();

    //Exit
    return 0;
}


//Window procedure
LRESULT CALLBACK WindowProcedure (HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam)
{
	curScreen.WindowProcedure(hWnd, uMessage, wParam, lParam);
   // POINTS coords; //Mouse coords

    //Check message
    switch(uMessage)
    {
    case WM_DESTROY:
        bRunning = false;
        break;
	}
    return DefWindowProc(hWnd,uMessage,wParam,lParam);
}


//Make window
int MakeWindow (HINSTANCE hInstance)
{
    WNDCLASSEX wc;

    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WindowProcedure;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = NULL;
    wc.hCursor = NULL;
    wc.hbrBackground = (HBRUSH) GetStockObject (WHITE_BRUSH);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = "Catching";
    wc.hIconSm = LoadIcon (hInstance, MAKEINTRESOURCE(5));  //IDI_MAINICON == 5

    //Register class
    if(!RegisterClassEx(&wc))
        return false;
	RECT desktop;
   // Get a handle to the desktop window
   const HWND hDesktop = GetDesktopWindow();
   // Get the size of screen to the variable desktop
   GetWindowRect(hDesktop, &desktop);
   // The top left corner will have coordinates (0,0)
   // and the bottom right corner will have coordinates
   // (horizontal, vertical)
   int horizontal = desktop.right;
   int vertical = desktop.bottom;

    //Create window
    hWnd = CreateWindowEx (NULL, "Catching", "Catching Eggs",
        WS_CAPTION | WS_VISIBLE | WS_SYSMENU | WS_MINIMIZEBOX, (horizontal - SCREEN_WIDTH) >> 1,
		(vertical - SCREEN_HEIGHT) >> 1, SCREEN_WIDTH, SCREEN_HEIGHT,
        NULL, NULL, hInstance, NULL);

    //Make sure window was created properly
    if (!hWnd)
        return false;

    //Success
    return true;
}

