/*************************************************************************************************
 * GRAPHICS.CPP                                                Copyright (c) 2003 Eamonn Doherty *
 *                                                                                               *
 * Direct3D code                                                                                 *
 *************************************************************************************************/

/*
 *	The code presented here is composed of a series of functions and global variables rather than
 *  as a class. This is to keep the project simple. I highly recommend creating a class to store
 *  the graphics code in for your own project.
 *
 *  Note that for brevity's sake, I removed most of my error-checking code from the functions
 *  here.
 */

#include "Graphics.h"

//********************************
//* Global Variables             *
//********************************

//Direct3D 9 interface
IDirect3D9* d3d;

//Graphics adapter interface
IDirect3DDevice9* d3dDevice;

//Capabilities of graphics adapter
D3DCAPS9 d3dCaps;

//Direct3D present parameters
D3DPRESENT_PARAMETERS d3dPresent;

//Vertex buffer for drawing quads
IDirect3DVertexBuffer9* vertexBuffer;


//********************************
//* Functions                    *
//********************************

//Initialize Direct3D
int InitD3D (int resWidth, int resHeight, D3DFORMAT resFormat, HWND hWnd, BOOL bWindowedMode)
{
    HRESULT hr;

    //Make Direct3D object
    d3d = Direct3DCreate9(D3D_SDK_VERSION);

    //Make sure NULL pointer was not returned
    if (!d3d)
        return FALSE;

    //Get device capabilities
    ZeroMemory (&d3dCaps, sizeof(d3dCaps));
    if (FAILED(d3d->GetDeviceCaps (D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &d3dCaps)))
        return FALSE;

    //Setup present parameters
    ZeroMemory(&d3dPresent,sizeof(d3dPresent));
    d3dPresent.SwapEffect = D3DSWAPEFFECT_FLIP;
    d3dPresent.hDeviceWindow = hWnd;
    d3dPresent.BackBufferCount = 1;

    //Check if windowed
    if (bWindowedMode)
    {
        D3DDISPLAYMODE d3ddm;
        RECT rWindow;

        //Get display mode
        d3d->GetAdapterDisplayMode (D3DADAPTER_DEFAULT, &d3ddm);

        //Get window bounds
        GetClientRect (hWnd, &rWindow);

        //Setup screen dimensions
        resWidth = rWindow.right - rWindow.left;
        resHeight = rWindow.bottom - rWindow.top;

        //Setup backbuffer
        d3dPresent.Windowed = true;
        d3dPresent.BackBufferFormat = d3ddm.Format;
        d3dPresent.BackBufferWidth = rWindow.right - rWindow.left;
        d3dPresent.BackBufferHeight = rWindow.bottom - rWindow.top;
    }
    else
    {        
        d3dPresent.Windowed = false;
        d3dPresent.BackBufferWidth = resWidth;
        d3dPresent.BackBufferHeight = resHeight;
        d3dPresent.BackBufferFormat = resFormat;
    }

    //Check if hardware vertex processing is available
    if (d3dCaps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
    {    
        //Create device with hardware vertex processing
        hr = d3d->CreateDevice(D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL, hWnd,
            D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dPresent, &d3dDevice);        
    }
    else
    {
        //Create device with software vertex processing
        hr = d3d->CreateDevice(D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL, hWnd,
            D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dPresent, &d3dDevice);
    }

    //Make sure device was created
    if (FAILED(hr))
        return FALSE;

    //Set vertex shader
    d3dDevice->SetVertexShader(NULL);
    d3dDevice->SetFVF (D3DFVF_TLVERTEX);

    //Create vertex buffer and set as stream source
    d3dDevice->CreateVertexBuffer(sizeof(TLVERTEX) * 4, NULL, D3DFVF_TLVERTEX, D3DPOOL_MANAGED,
                                  &vertexBuffer, NULL);
    d3dDevice->SetStreamSource (0, vertexBuffer, 0, sizeof(TLVERTEX));

    //Setup rendering states
    d3dDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
    d3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
    d3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
    d3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
    d3dDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);

    //Successfully initalized Direct3D
    return TRUE;
}


//Close Direct3D
int CloseD3D()
{
    //Release vertex buffer
    if (vertexBuffer)
        vertexBuffer->Release ();

    //Release device
    if (d3dDevice)
        d3dDevice->Release();

    //Release d3d object
    if (d3d)
        d3d->Release();

    //Successfully closed Direct3D
    return TRUE;
}


//Clear backbuffer
int ClearBuffer () { return d3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, 255, 0.0f, 0); }

//Present
int Present () { return d3dDevice->Present (NULL, NULL, NULL, NULL); }
   
//Begin drawing
int BeginDrawing () { return d3dDevice->BeginScene (); }

//End drawing
int EndDrawing () { return d3dDevice->EndScene (); }


//Load a texture
//Supported formats: BMP, PPM, DDS, JPG, PNG, TGA, DIB
IDirect3DTexture9 *LoadTexture(char *fileName)
{
    IDirect3DTexture9 *d3dTexture;
    D3DXIMAGE_INFO SrcInfo;			//Optional

    //Use a magenta colourkey
    D3DCOLOR colorkey = 0xFFFF00FF;

    // Load image from file
    if (FAILED(D3DXCreateTextureFromFileEx (d3dDevice, fileName, 0, 0, 1, 0, 
          D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, D3DX_FILTER_NONE, D3DX_DEFAULT, 
          colorkey, &SrcInfo, NULL, &d3dTexture)))
    {
        return NULL;
    }

	//Return the newly made texture
    return d3dTexture;
}


//Draw a textured quad on the back-buffer
void BlitD3D (IDirect3DTexture9 *texture, RECT *rDest, D3DCOLOR vertexColour, float rotate)
{
	TLVERTEX* vertices;

	//Lock the vertex buffer
	vertexBuffer->Lock(0, 0, (void **)&vertices, NULL);

	//Setup vertices
	//A -0.5f modifier is applied to vertex coordinates to match texture and screen coords
	//Some drivers may compensate for this automatically, but on others texture alignment errors are introduced
	//More information on this can be found in the Direct3D 9 documentation
	vertices[0].colour = vertexColour;
	vertices[0].x = (float) rDest->left - 0.5f;
	vertices[0].y = (float) rDest->top - 0.5f;
	vertices[0].z = 0.0f;
	vertices[0].rhw = 1.0f;
	vertices[0].u = 0.0f;
	vertices[0].v = 0.0f;

	vertices[1].colour = vertexColour;
	vertices[1].x = (float) rDest->right - 0.5f;
	vertices[1].y = (float) rDest->top - 0.5f;
	vertices[1].z = 0.0f;
	vertices[1].rhw = 1.0f;
	vertices[1].u = 1.0f;
	vertices[1].v = 0.0f;

	vertices[2].colour = vertexColour;
	vertices[2].x = (float) rDest->right - 0.5f;
	vertices[2].y = (float) rDest->bottom - 0.5f;
	vertices[2].z = 0.0f;
	vertices[2].rhw = 1.0f;
	vertices[2].u = 1.0f;
	vertices[2].v = 1.0f;

	vertices[3].colour = vertexColour;
	vertices[3].x = (float) rDest->left - 0.5f;
	vertices[3].y = (float) rDest->bottom - 0.5f;
	vertices[3].z = 0.0f;
	vertices[3].rhw = 1.0f;
	vertices[3].u = 0.0f;
	vertices[3].v = 1.0f;

  ////Handle rotation
  //if (rotate != 0)
  //{
  //    RECT rOrigin;
  //    float centerX, centerY;

  //    //Find center of destination rectangle
  //    centerX = (float)(rDest->left + rDest->right) / 2;
  //    centerY = (float)(rDest->top + rDest->bottom) / 2;

  //    //Translate destination rect to be centered on the origin
  //    rOrigin.top = rDest->top - (int)(centerY);
  //    rOrigin.bottom = rDest->bottom - (int)(centerY);
  //    rOrigin.left = rDest->left - (int)(centerX);
  //    rOrigin.right = rDest->right - (int)(centerX);

  //    //Rotate vertices about the origin
  //    bufferVertices[index].x = rOrigin.left * cosf(rotate) -
  //                              rOrigin.top * sinf(rotate);
  //    bufferVertices[index].y = rOrigin.left * sinf(rotate) +
  //                              rOrigin.top * cosf(rotate);

  //    bufferVertices[index + 1].x = rOrigin.right * cosf(rotate) -
  //                                  rOrigin.top * sinf(rotate);
  //    bufferVertices[index + 1].y = rOrigin.right * sinf(rotate) +
  //                                  rOrigin.top * cosf(rotate);

  //    bufferVertices[index + 2].x = rOrigin.right * cosf(rotate) -
  //                                  rOrigin.bottom * sinf(rotate);
  //    bufferVertices[index + 2].y = rOrigin.right * sinf(rotate) +
  //                                  rOrigin.bottom * cosf(rotate);

  //    bufferVertices[index + 3].x = rOrigin.left * cosf(rotate) -
  //                                  rOrigin.bottom * sinf(rotate);
  //    bufferVertices[index + 3].y = rOrigin.left * sinf(rotate) +
  //                                  rOrigin.bottom * cosf(rotate);

  //    //Translate vertices to proper position
  //    bufferVertices[index].x += centerX;
  //    bufferVertices[index].y += centerY;
  //    bufferVertices[index + 1].x += centerX;
  //    bufferVertices[index + 1].y += centerY;
  //    bufferVertices[index + 2].x += centerX;
  //    bufferVertices[index + 2].y += centerY;
  //    bufferVertices[index + 3].x += centerX;
  //    bufferVertices[index + 3].y += centerY;
  //}

	//Unlock the vertex buffer
	vertexBuffer->Unlock();

	//Set texture
	d3dDevice->SetTexture (0, texture);

	//Draw image
	d3dDevice->DrawPrimitive (D3DPT_TRIANGLEFAN, 0, 2);
}


//Draw a textured quad on the back-buffer
void BlitExD3D (IDirect3DTexture9 *texture, RECT *rDest, D3DCOLOR *vertexColours /* -> D3DCOLOR[4] */,
             float rotate)
{
	TLVERTEX* vertices;

	//Lock the vertex buffer
	vertexBuffer->Lock(0, 0, (void **)&vertices, NULL);

	//Setup vertices
	//A -0.5f modifier is applied to vertex coordinates to match texture and screen coords
	//Some drivers may compensate for this automatically, but on others texture alignment errors are introduced
	//More information on this can be found in the Direct3D 9 documentation
	vertices[0].colour = vertexColours[0];
	vertices[0].x = (float) rDest->left - 0.5f;
	vertices[0].y = (float) rDest->top - 0.5f;
	vertices[0].z = 0.0f;
	vertices[0].rhw = 1.0f;
	vertices[0].u = 0.0f;
	vertices[0].v = 0.0f;

	vertices[1].colour = vertexColours[1];
	vertices[1].x = (float) rDest->right - 0.5f;
	vertices[1].y = (float) rDest->top - 0.5f;
	vertices[1].z = 0.0f;
	vertices[1].rhw = 1.0f;
	vertices[1].u = 1.0f;
	vertices[1].v = 0.0f;

	vertices[2].colour = vertexColours[2];
	vertices[2].x = (float) rDest->right - 0.5f;
	vertices[2].y = (float) rDest->bottom - 0.5f;
	vertices[2].z = 0.0f;
	vertices[2].rhw = 1.0f;
	vertices[2].u = 1.0f;
	vertices[2].v = 1.0f;

	vertices[3].colour = vertexColours[3];
	vertices[3].x = (float) rDest->left - 0.5f;
	vertices[3].y = (float) rDest->bottom - 0.5f;
	vertices[3].z = 0.0f;
	vertices[3].rhw = 1.0f;
	vertices[3].u = 0.0f;
	vertices[3].v = 1.0f;

  //Handle rotation
  //if (rotate != 0)
  //{
  //    RECT rOrigin;
  //    float centerX, centerY;

  //    //Find center of destination rectangle
  //    centerX = (float)(rDest->left + rDest->right) / 2;
  //    centerY = (float)(rDest->top + rDest->bottom) / 2;

  //    //Translate destination rect to be centered on the origin
  //    rOrigin.top = rDest->top - (int)(centerY);
  //    rOrigin.bottom = rDest->bottom - (int)(centerY);
  //    rOrigin.left = rDest->left - (int)(centerX);
  //    rOrigin.right = rDest->right - (int)(centerX);

  //    //Rotate vertices about the origin
  //    bufferVertices[index].x = rOrigin.left * cosf(rotate) -
  //                              rOrigin.top * sinf(rotate);
  //    bufferVertices[index].y = rOrigin.left * sinf(rotate) +
  //                              rOrigin.top * cosf(rotate);

  //    bufferVertices[index + 1].x = rOrigin.right * cosf(rotate) -
  //                                  rOrigin.top * sinf(rotate);
  //    bufferVertices[index + 1].y = rOrigin.right * sinf(rotate) +
  //                                  rOrigin.top * cosf(rotate);

  //    bufferVertices[index + 2].x = rOrigin.right * cosf(rotate) -
  //                                  rOrigin.bottom * sinf(rotate);
  //    bufferVertices[index + 2].y = rOrigin.right * sinf(rotate) +
  //                                  rOrigin.bottom * cosf(rotate);

  //    bufferVertices[index + 3].x = rOrigin.left * cosf(rotate) -
  //                                  rOrigin.bottom * sinf(rotate);
  //    bufferVertices[index + 3].y = rOrigin.left * sinf(rotate) +
  //                                  rOrigin.bottom * cosf(rotate);

  //    //Translate vertices to proper position
  //    bufferVertices[index].x += centerX;
  //    bufferVertices[index].y += centerY;
  //    bufferVertices[index + 1].x += centerX;
  //    bufferVertices[index + 1].y += centerY;
  //    bufferVertices[index + 2].x += centerX;
  //    bufferVertices[index + 2].y += centerY;
  //    bufferVertices[index + 3].x += centerX;
  //    bufferVertices[index + 3].y += centerY;
  //}

	//Unlock the vertex buffer
	vertexBuffer->Unlock();

	//Set texture
	d3dDevice->SetTexture (0, texture);

	//Draw image
	d3dDevice->DrawPrimitive (D3DPT_TRIANGLEFAN, 0, 2);
}