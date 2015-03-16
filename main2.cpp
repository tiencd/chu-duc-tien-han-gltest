#include "main2.h"


//================================================================================================================================// including stuff //=================//

#include <windows.h>
#include <string>
#include <d3d9.h>
#include <d3dx9.h>
#include <d3dx9tex.h>

//================================================================================================================================// handling windows //================//

//HINSTANCE hInst;
//HWND wndHandle;
//bool stopEverything(false);
//
////================================================================================================================================// handling directx needs //==========//
//
//LPDIRECT3D9                 pD3D;                       // the Direct3D object
//LPDIRECT3DDEVICE9           pd3dDevice;                 // the Direct3D device
//IDirect3DSurface9           *Surface = NULL;            // image surface
//IDirect3DSurface9           *BackBuffer = NULL;         // back buffer surface
//
////================================================================================================================================// declaring functions //=============//
//
//bool initWindow(HINSTANCE hInstance);
//bool initDirect3D(void);
//void cleanUp (void);
//void render(void);
//LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
//
////================================================================================================================================// code starts here //================//
//
//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
//{
//    if (!initWindow(hInstance)) return false;
//
//    if (!initDirect3D())
//    {
//        return false;
//    }
//
//    MSG msg;
//    ZeroMemory(&msg, sizeof(msg));
//
//    while(msg.message!=WM_QUIT){
//        if(PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
//         {
//             TranslateMessage (&msg);
//             DispatchMessage (&msg);
//         } else {
//             render();
//         }
//    }
//
//    return static_cast<int>(msg.wParam);
//}
//
//bool initWindow(HINSTANCE hInstance )
//{
//    WNDCLASSEX wcex;
//
//    wcex.cbSize             = sizeof(WNDCLASSEX);
//    wcex.style              = CS_HREDRAW | CS_VREDRAW;
//    wcex.lpfnWndProc        = WndProc;
//    wcex.cbClsExtra         = 0;
//    wcex.cbWndExtra         = 0;
//    wcex.hInstance          = hInstance;
//    wcex.hIcon              = LoadIcon(0, IDI_APPLICATION);
//    wcex.hCursor            = LoadCursor(0, IDC_ARROW);
//    wcex.hbrBackground      = static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
//    wcex.lpszMenuName       = 0L;
//    wcex.lpszClassName      = "DirectXTemplate";
//    wcex.hIconSm            = 0;
//
//    RegisterClassEx(&wcex);
//
//    wndHandle = CreateWindow("DirectXTemplate", "DirectX Template", WS_EX_TOPMOST | WS_POPUP | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, 640, 480, NULL, NULL, hInstance, NULL);
//
//    if (!wndHandle) return false;
//
//    ShowWindow(wndHandle, SW_SHOW);
//    UpdateWindow(wndHandle);
//
//    return true;
//}
//
//LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
//{
//    switch (message)
//    {
//        case WM_DESTROY:
//            PostQuitMessage(0);
//            break;
//
//        default:
//            return DefWindowProc(hWnd, message, wParam, lParam);
//    }   
//}
//
//bool initDirect3D(void)
//{
//    pD3D = NULL;
//    pd3dDevice = NULL;
//
//    // create the DirectX object
//    if(NULL == (pD3D = Direct3DCreate9(D3D_SDK_VERSION))) return false;
//
//    char *wsPath = "Resource\\Images\\item_22.png"; // path to the image
//    D3DXIMAGE_INFO Info;
//
//    if (FAILED(D3DXGetImageInfoFromFile("Resource\\Images\\item_22.png", &Info)))
//    {
//        MessageBox(NULL, "You're a terrible programmer!", "ERROR", MB_OK);
//        stopEverything = true;
//    } else {
//        pd3dDevice -> CreateOffscreenPlainSurface(Info.Width, Info.Height, Info.Format, D3DPOOL_SYSTEMMEM, &Surface, NULL);
//        D3DXLoadSurfaceFromFile(Surface, NULL, NULL, "Resource\\Images\\item_22.png", NULL, D3DX_FILTER_NONE, 0, NULL);
//        pd3dDevice -> GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &BackBuffer);
//    }
//
//    // fill the presentation parameters structure
//    D3DPRESENT_PARAMETERS d3dpp;
//    ZeroMemory(&d3dpp, sizeof(d3dpp));
//
//    d3dpp.Windowed          = TRUE;
//    d3dpp.SwapEffect        = D3DSWAPEFFECT_DISCARD;
//    d3dpp.BackBufferFormat  = D3DFMT_X8R8G8B8;
//    d3dpp.BackBufferCount   = 1;
//    d3dpp.BackBufferHeight  = 480;
//    d3dpp.BackBufferWidth   = 640;
//    d3dpp.hDeviceWindow     = wndHandle;
//
//    // create a default DirectX device
//    if (FAILED(pD3D -> CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, wndHandle, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &pd3dDevice))) return false;
//
//    return true;
//}
//
//void render(void)
//{
//    // check to make sure you have a valid Direct3D device
//    if (NULL == pd3dDevice) return;
//
//    pd3dDevice -> Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);   // clear the back buffer to a blue color
//
//    if (SUCCEEDED(pd3dDevice -> BeginScene()))
//    {
//        if (stopEverything == false)
//        {
//            pd3dDevice -> UpdateSurface(Surface, NULL, BackBuffer, NULL);
//        }
//
//        // end the scene
//        pd3dDevice -> EndScene();
//    }
//
//    // present the back buffer contents to the display
//    pd3dDevice -> Present(NULL, NULL, NULL, NULL);
//}
//
//void cleanUp (void)
//{
//    // release the device and the Direct3D object
//    if (pd3dDevice != NULL) pd3dDevice -> Release();
//    if (pD3D != NULL) pD3D -> Release();
//}