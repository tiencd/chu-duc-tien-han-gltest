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
	curScreen.onInit();
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
    wc.hbrBackground = (HBRUSH) GetStockObject (BLACK_BRUSH);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = "Quads";
    wc.hIconSm = LoadIcon (hInstance, MAKEINTRESOURCE(5));  //IDI_MAINICON == 5

    //Register class
    if(!RegisterClassEx(&wc))
        return false;

    //Create window
    hWnd = CreateWindowEx (NULL, "Quads", "Textured Quads Demo -- Left-click to exit",
        WS_CAPTION | WS_VISIBLE | WS_SYSMENU, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT,
        NULL, NULL, hInstance, NULL);

    //Make sure window was created properly
    if (!hWnd)
        return false;

    //Success
    return true;
}

