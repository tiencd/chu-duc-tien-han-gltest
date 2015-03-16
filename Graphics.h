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
const DWORD D3DFVF_TLVERTEX = D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1;

//Custom vertex
struct TLVERTEX
{
    float x;
    float y;
    float z;
    D3DCOLOR colour;
    float u;
    float v;
};

//********************************
//* Function Prototypes          *
//********************************

//Initialize Direct3D
int InitD3D (int resWidth, int resHeight, D3DFORMAT resFormat, HWND hWnd, BOOL bWindowedMode = false);

//Setup Direct3D for rendering
void InitRendering (int resWidth, int resHeight);

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

//Draw Retangle
void DrawRetangle(int x, int y, int w, int h, D3DCOLOR color);

//Draw text
void DrawString(char *text, int x, int y, D3DCOLOR fontColor);

//Draw a textured quad on the back-buffer
void BlitD3D (IDirect3DTexture9* texture, RECT* rDest, float rotate = 0);

//Setup the quad in the vertex buffer
void SetupQuad ();

//Begin batched drawing
void BeginBatchDrawing (IDirect3DTexture9* texture);

//Add a quad to the batching buffer
void AddQuad (RECT* rSource, RECT* rDest, D3DCOLOR colour);

//End batched drawing (put all quads in the buffer on screen)
void EndBatchDrawing ();

//Fill the index buffer
void FillIndexBuffer();