/*************************************************************************************************
 * GRAPHICS.H                                                  Copyright (c) 2003 Eamonn Doherty *
 *                                                                                               *
 * Direct3D code                                                                                 *
 *************************************************************************************************/

/*
 *	The code presented here is composed of a series of functions and global variables rather than
 *  as a class. This is to keep the project simple. I highly recommend creating a class to store
 *  the graphics code in for your own project
 */

#pragma once

#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>

//Custom vertex format
const DWORD D3DFVF_TLVERTEX = D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1;

/* Vertices:

    v0               v1
    |---------------|
    |\              |
    |  \            |
    |    \          |
    |      \        |
    |        \      |
    |          \    |
    |            \  |
    |              \|
    |---------------|
    v3               v2

    z = 0
    rhw = 1
*/

//Custom vertex
struct TLVERTEX
{
    float x;
    float y;
    float z;
    float rhw;
    D3DCOLOR colour;
    float u;
    float v;
};


//********************************
//* Function Prototypes          *
//********************************

//Initialize Direct3D
int InitD3D (int resWidth, int resHeight, D3DFORMAT resFormat, HWND hWnd, BOOL bWindowedMode = false);

//Close Direct3D
int CloseD3D ();

//Clear buffer
int ClearBuffer();

//Present
int Present();

//Begin drawing
int BeginDrawing ();

//End drawing
int EndDrawing ();

//Load a texture
IDirect3DTexture9 *LoadTexture(char *fileName);

//Draw a textured quad on the back-buffer
void BlitD3D (IDirect3DTexture9 *texture, RECT *rDest, D3DCOLOR vertexColour = 0xFFFFFFFF,
           float fRotate = 0);

//Draw a textured quad on the back-buffer with full colour modulation
void BlitExD3D (IDirect3DTexture9 *texture, RECT *rDest, D3DCOLOR *vertexColours /* -> D3DCOLOR[4] */,
             float rotate = 0);