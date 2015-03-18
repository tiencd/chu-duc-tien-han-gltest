/*************************************************************************************************
 * TEXTURE.CPP                                                 Copyright (c) 2003 Eamonn Doherty *
 *                                                                                               *
 * CTexture class implementation                                                                 *
 *************************************************************************************************/

#include "Texture.h"

//********************************
//* Static Member Initialization *
//********************************

list <CTexture::LOADEDTEXTURE*> CTexture::loadedTextures;

//********************************
//* Class Member Functions       *
//********************************

//Load texture from file
int CTexture::Init (char sFilename[], int width, int height)
{
    D3DSURFACE_DESC surfaceDesc;
    LOADEDTEXTURE* newTexture;
    list<LOADEDTEXTURE*>::iterator itTextures;

    //Make sure texture is not already loaded
    if (bLoaded)
        return TRUE;

    //Convert filename to lowercase letters
    //sFilename = strlwr(sFilename);
	//string strTmp = sFilename + to_string(width) + "-" + to_string(height);
	//char *str =(char *)strTmp.c_str();
    //Check if texture is in the loaded list
    for (itTextures = loadedTextures.begin (); itTextures != loadedTextures.end (); itTextures++)
        if ((*itTextures)->sFilename == sFilename)
        {   
            //Get LOADEDTEXTURE object
            texture = *itTextures;  

            //Increment reference counter
            (*itTextures)->referenceCount++;

            //Set loaded flag
            bLoaded = TRUE;

            //Successfully found texture
            return TRUE;
        }

        //Texture was not in the list, make a new texture
        newTexture = new LOADEDTEXTURE;

        //Load texture from file
        newTexture->texture = LoadTexture (sFilename);

        //Make sure texture was loaded
        if (!newTexture->texture)
            return FALSE;

        //Get texture dimensions
        newTexture->texture->GetLevelDesc(0, &surfaceDesc);

        //Set new texture parameters
        newTexture->referenceCount = 1;
        newTexture->sFilename = sFilename;
		if(width == 0 && height == 0) {
			newTexture->width = surfaceDesc.Width;
			newTexture->height = surfaceDesc.Height;
		} else {
			newTexture->width = width;
			newTexture->height = height;
		}

        //Push new texture onto list
        loadedTextures.push_back (newTexture);

        //Setup current texture instance
        texture = loadedTextures.back();
        bLoaded = TRUE;

        //Successfully loaded texture
        return TRUE;
}


//Unload a texture
int CTexture::Close()
{
    //Make sure texture is loaded
    if (!bLoaded)
        return FALSE;
    
    //Decrement reference counter and nullify pointer
    texture->referenceCount--;
    texture = NULL;

    //Clear loaded flag
    bLoaded = FALSE;

    //Successfully unloaded texture
    return TRUE;
}


//Release all unreferenced textures
//Release all unreferenced textures
int CTexture::GarbageCollect()
{
    list<LOADEDTEXTURE*>::iterator it;
    list<LOADEDTEXTURE*>::iterator itNext;

    //Go through loaded texture list
    for (it = loadedTextures.begin(); it != loadedTextures.end ();)   
        if ((*it)->referenceCount <= 0)
        {
            //Get next iterator
            itNext = it;
            itNext++;

            //Release texture
            if ((*it)->texture)
                (*it)->texture->Release();
            (*it)->texture = NULL;

            //Delete LOADEDTEXTURE object
            delete (*it);
            loadedTextures.erase (it);

            //Move to next element
            it = itNext;
        } else it++; //Increment iterator

    //Successfully released unreferenced textures
    return TRUE;
}


//Release all textures
int CTexture::CleanupTextures()
{
    list<LOADEDTEXTURE*>::iterator it;
 
     //Go through loaded texture list
    for (it = loadedTextures.begin(); it != loadedTextures.end (); it++)
    {
        //Release texture
        if ((*it)->texture)
            (*it)->texture->Release();
        (*it)->texture = NULL;
        
         //Delete LOADEDTEXTURE object
        delete (*it);
    }

    //Clear list
    loadedTextures.clear ();

    //Successfully released all textures
    return TRUE;
}


//Draw texture with limited colour modulation
void CTexture::Blit (int X, int Y, float rotate)
{
    RECT rDest;

    //Setup destination rectangle
    rDest.left = X;
    rDest.right = X + texture->width;
    rDest.top = Y;
    rDest.bottom = Y + texture->height;

    //Draw texture
    BlitD3D (texture->texture, &rDest, rotate);
}


////Draw texture with full colour modulation
//void CTexture::BlitEx (int X, int Y, D3DCOLOR* vertexColours, float rotate)
//{
//    RECT rDest;
//
//    //Setup destination rectangle
//    rDest.left = X;
//    rDest.right = X + texture->width;
//    rDest.top = Y;
//    rDest.bottom = Y + texture->height;
//
//    //Draw texture
//    BlitExD3D (texture->texture, &rDest, vertexColours, rotate);
//}
