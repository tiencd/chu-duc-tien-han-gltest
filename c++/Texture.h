/*************************************************************************************************
 * TEXTURE.H                                                   Copyright (c) 2003 Eamonn Doherty *
 *                                                                                               *
 * CTexture class definition                                                                     *
 *************************************************************************************************/

#pragma once

#include <windows.h>
#include <assert.h>
#include <d3d9.h>
#include <string>
#include <sstream>
#include <list>
#include "Graphics.h"
using namespace std;


//********************************
//* Class Prototype              *
//********************************

class CTexture
{
public:

    //Set default member values
    CTexture()
    {
        bLoaded = FALSE;
        texture = NULL;
    }

    //Load texture from file
    int CTexture::Init (char sFilename[], int width = 0, int height = 0);

    //Unload a texture
    int CTexture::Close();

    //Draw texture with limited colour modulation
    void CTexture::Blit (int X, int Y, float rotate = 0);

    //Draw texture with full colour modulation
    //void CTexture::BlitEx (int X, int Y, D3DCOLOR* vertexColours, float rotate);

    //Release all unreferenced textures
    static int GarbageCollect();

    //Release all unreferenced textures
    static int CleanupTextures();

//private:

    //Loaded texture struct
    struct LOADEDTEXTURE
    {
        int referenceCount;             //Amount of CTexture instances containing this texture
        IDirect3DTexture9* texture;     //The texture
        string sFilename;               //The filename of the texture
        int width;                      //Width of the texture
        int height;                     //Height of the texture
    };

    //Linked list of all loaded textures
    static list <LOADEDTEXTURE*> loadedTextures;

    BOOL bLoaded;           //Texture loaded flag
    LOADEDTEXTURE* texture; //The texture



};