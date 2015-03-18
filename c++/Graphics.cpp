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
 *  here. Also, initialization takes place over three functions: InitD3D(), InitRendering(), and
 *  SetupQuad() in order to avoid having a single massive function.
 */

#include "Graphics.h"
#include <assert.h>
#include <fstream>
#include <sstream>
using namespace std;

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

//Vertex buffer and index buffer for batched drawing
IDirect3DVertexBuffer9* vertexBatchBuffer;
IDirect3DIndexBuffer9* indexBatchBuffer;

//Max amount of vertices that can be put in the batching buffer
const int BATCH_BUFFER_SIZE = 1000;

//Vertices currently in the batching buffer
int numBatchVertices;
TLVERTEX* batchVertices;

//Info on texture used for batched drawing
float batchTexWidth;
float batchTexHeight;

// font image

 ID3DXFont *m_font;

//********************************
//* Functions                    *
//********************************

//Initialize Direct3D
int InitD3D (int resWidth, int resHeight, D3DFORMAT resFormat, HWND hWnd, BOOL bWindowedMode)
{
    HRESULT hr;
    //Create the D3D object
    d3d = Direct3DCreate9(D3D_SDK_VERSION);
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

    //Setup Direct3D for rendering
    InitRendering (resWidth, resHeight);
	D3DXCreateFont(d3dDevice, 26, 0, FW_BOLD, 0, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, TEXT("Arial"), &m_font );
    //Success
    return TRUE;
}


//Setup Direct3D for rendering
void InitRendering (int resWidth, int resHeight)
{
    D3DXMATRIX matOrtho;
    D3DXMATRIX matIdentity;

    //Setup an orthographic perspective
    D3DXMatrixOrthoLH (&matOrtho, (float) resWidth, (float) resHeight, 1.0f, 10.0f);
    D3DXMatrixIdentity (&matIdentity);
    d3dDevice->SetTransform (D3DTS_PROJECTION, &matOrtho);
    d3dDevice->SetTransform (D3DTS_VIEW, &matIdentity);
    d3dDevice->SetTransform (D3DTS_WORLD, &matIdentity);
    
    //Create a vertex buffer and set stream source
    d3dDevice->CreateVertexBuffer(4 * sizeof(TLVERTEX), D3DUSAGE_WRITEONLY,
                                  D3DFVF_TLVERTEX, D3DPOOL_MANAGED, &vertexBuffer, NULL);
    d3dDevice->SetStreamSource(0, vertexBuffer, 0, sizeof(TLVERTEX));

    //Create batching vertex and index buffers
    d3dDevice->CreateVertexBuffer(BATCH_BUFFER_SIZE * sizeof(TLVERTEX), D3DUSAGE_WRITEONLY,
                                  D3DFVF_TLVERTEX, D3DPOOL_MANAGED, &vertexBatchBuffer, NULL);
    d3dDevice->CreateIndexBuffer (BATCH_BUFFER_SIZE * 3, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16,
                                  D3DPOOL_MANAGED, &indexBatchBuffer, NULL);
    d3dDevice->SetIndices(indexBatchBuffer);
    numBatchVertices = 0;

    //Fill the index buffer
    FillIndexBuffer ();

    //Setup vertex format
    d3dDevice->SetVertexShader(NULL);
    d3dDevice->SetFVF (D3DFVF_TLVERTEX);

    //Setup the quad
    SetupQuad ();

    //Set render states
    d3dDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
    d3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
    d3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
    d3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
    d3dDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
}


//Setup the quad
void SetupQuad ()
{
    TLVERTEX* vertices = NULL;
    vertexBuffer->Lock(0, 4 * sizeof(TLVERTEX), (VOID**)&vertices, 0);

    //Setup vertices
    vertices[0].colour = 0xffffffff;
    vertices[0].x = 0.0f;
    vertices[0].y = 0.0f;
    vertices[0].z = 1.0f;
    vertices[0].u = 0.0f;
    vertices[0].v = 0.0f;

    vertices[1].colour = 0xffffffff;
    vertices[1].x = 1.0f;
    vertices[1].y = 0.0f;
    vertices[1].z = 1.0f;
    vertices[1].u = 1.0f;
    vertices[1].v = 0.0f;

    vertices[2].colour = 0xffffffff;
    vertices[2].x = 1.0f;
    vertices[2].y = -1.0f;
    vertices[2].z = 1.0f;
    vertices[2].u = 1.0f;
    vertices[2].v = 1.0f;

    vertices[3].colour = 0xffffffff;
    vertices[3].x = 0.0f;
    vertices[3].y = -1.0f;
    vertices[3].z = 1.0f;
    vertices[3].u = 0.0f;
    vertices[3].v = 1.0f;

    vertexBuffer->Unlock();
}


//Close Direct3D
int CloseD3D()
{
    //Clear stream source
    d3dDevice->SetStreamSource (0, NULL, 0, 0);
    
    //Release vertex buffer
    if (vertexBuffer)
        vertexBuffer->Release ();

    //Release batching buffers
    if (vertexBatchBuffer)
        vertexBatchBuffer->Release ();
    if (indexBatchBuffer)
        indexBatchBuffer->Release ();

    //Release device
    if (d3dDevice)
        d3dDevice->Release();

    //Release d3d object
    if (d3d)
        d3d->Release();
	if(m_font)
		m_font->Release();
    //Successfully closed Direct3D
    return TRUE;
}


//Clear backbuffer
int ClearBuffer () { return d3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_ARGB(255,245,245,245), 0.0f, 0); }

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

// Draw rectangle (dang bi sai)
void DrawRetangle(int x, int y, int w, int h, D3DCOLOR color) {
	D3DRECT rect = {x, y, x + w, y + h};
	d3dDevice->Clear(0, &rect, D3DCLEAR_TARGET, color, 1.0f, 0);
}

void DrawString(char * text, int x, int y, int w, int h, D3DCOLOR fontColor)
{

	// Create a colour for the text - in this case blue
	//D3DCOLOR fontColor = D3DCOLOR_ARGB(255,0,0,255);    

	// Create a rectangle to indicate where on the screen it should be drawn
	RECT rct;
	rct.left=x;
	rct.top=y;
	rct.right= SCREEN_WIDTH ;
	rct.bottom= SCREEN_HEIGHT;

	// Draw some text 
	//m_font->s
	m_font->DrawText(NULL, text, -1, &rct, 0, fontColor );
	//m_font->
}

//Draw a textured quad on the backbuffer
void BlitD3D(IDirect3DTexture9* texture, RECT* rDest, float rotate)
{
    float X;
    float Y;
    D3DXMATRIX matTranslation;
    D3DXMATRIX matScaling;
    D3DXMATRIX matTransform;
    
    //Get coordinates
    X = rDest->left - (float)(d3dPresent.BackBufferWidth) / 2;
    Y = -rDest->top + (float)(d3dPresent.BackBufferHeight) / 2; 

    //Setup translation and scaling matrices
    D3DXMatrixScaling (&matScaling, (float)(rDest->right - rDest->left),
        (float)(rDest->bottom - rDest->top), 1.0f);
    D3DXMatrixTranslation (&matTranslation, X, Y, 0.0f);
    matTransform = matScaling * matTranslation;

    //Check if quad is rotated
    if (rotate)
    {
        D3DXMATRIX matRotate;

        //Create rotation matrix about the z-axis
        D3DXMatrixRotationZ (&matRotate, rotate);

        //Multiply matrices together
        matTransform *= matRotate;
    }

    //Draw the quad
    d3dDevice->SetTransform (D3DTS_WORLD, &matTransform);
    d3dDevice->SetTexture (0, texture);
    d3dDevice->DrawPrimitive(D3DPT_TRIANGLEFAN, 0, 2);
}


//Fill the index buffer
void FillIndexBuffer ()
{
    int index = 0;
    short* indices = NULL;

    //Lock index buffer
    indexBatchBuffer->Lock (0, BATCH_BUFFER_SIZE  * 3, (void**) &indices, 0);

    for (int vertex = 0; vertex < BATCH_BUFFER_SIZE; vertex += 4)
    {
        indices[index] = vertex;
        indices[index + 1] = vertex + 2;
        indices[index + 2] = vertex + 3;
        indices[index + 3] = vertex;
        indices[index + 4] = vertex + 1;
        indices[index + 5] = vertex + 2;
        index += 6;
    }

    //Unlock index buffer
    indexBatchBuffer->Unlock ();
}


//Get ready for batch drawing
void BeginBatchDrawing (IDirect3DTexture9* texture)
{
    D3DXMATRIX matIdentity;
    D3DSURFACE_DESC surfDesc;

    //Lock the batching vertex buffer
    numBatchVertices = 0;
    vertexBatchBuffer->Lock (0, BATCH_BUFFER_SIZE * sizeof(TLVERTEX), (void **) &batchVertices, 0);

    //Get texture dimensions
    texture->GetLevelDesc (0, &surfDesc);
    batchTexWidth = (float) surfDesc.Width;
    batchTexHeight = (float) surfDesc.Height;

    //Set texture
    d3dDevice->SetTexture (0, texture);

    //Set world matrix to an identity matrix
    D3DXMatrixIdentity (&matIdentity);
    d3dDevice->SetTransform (D3DTS_WORLD, &matIdentity);

    //Set stream source to batch buffer
    d3dDevice->SetStreamSource (0, vertexBatchBuffer, 0, sizeof(TLVERTEX));
}


//Add a quad to the batching buffer
void AddQuad (RECT* rSource, RECT* rDest, D3DCOLOR colour)
{
    float X;
    float Y;
    float destWidth;
    float destHeight;

    //Calculate coordinates
    X = rDest->left - (float)(d3dPresent.BackBufferWidth) / 2;
    Y = -rDest->top + (float)(d3dPresent.BackBufferHeight) / 2; 
    destWidth = (float)(rDest->right - rDest->left);
    destHeight = (float)(rDest->bottom - rDest->top);

    //Setup vertices in buffer
    batchVertices[numBatchVertices].colour = colour;
    batchVertices[numBatchVertices].x = X;
    batchVertices[numBatchVertices].y = Y;
    batchVertices[numBatchVertices].z = 1.0f;
    batchVertices[numBatchVertices].u = rSource->left / batchTexWidth;
    batchVertices[numBatchVertices].v = rSource->top / batchTexHeight;
    
    batchVertices[numBatchVertices + 1].colour = colour;
    batchVertices[numBatchVertices + 1].x = X + destWidth;
    batchVertices[numBatchVertices + 1].y = Y;
    batchVertices[numBatchVertices + 1].z = 1.0f;
    batchVertices[numBatchVertices + 1].u = rSource->right / batchTexWidth;
    batchVertices[numBatchVertices + 1].v = rSource->top / batchTexHeight;

    batchVertices[numBatchVertices + 2].colour = colour;
    batchVertices[numBatchVertices + 2].x = X + destWidth;
    batchVertices[numBatchVertices + 2].y = Y - destHeight;
    batchVertices[numBatchVertices + 2].z = 1.0f;
    batchVertices[numBatchVertices + 2].u = rSource->right / batchTexWidth;
    batchVertices[numBatchVertices + 2].v = rSource->bottom / batchTexHeight;

    batchVertices[numBatchVertices + 3].colour = colour;
    batchVertices[numBatchVertices + 3].x = X;
    batchVertices[numBatchVertices + 3].y = Y - destHeight;
    batchVertices[numBatchVertices + 3].z = 1.0f;
    batchVertices[numBatchVertices + 3].u = rSource->left / batchTexWidth;
    batchVertices[numBatchVertices + 3].v = rSource->bottom / batchTexHeight;

    //Increase vertex count
    numBatchVertices += 4;

    //Flush buffer if it's full
    if (numBatchVertices == BATCH_BUFFER_SIZE)
    {
        //Unlock vertex buffer
        vertexBatchBuffer->Unlock();
        
        //Draw quads in the buffer
        d3dDevice->DrawIndexedPrimitive (D3DPT_TRIANGLELIST, 0, 0, numBatchVertices, 0,
                                        numBatchVertices / 2);        

        //Reset vertex count        
        numBatchVertices = 0;        

        //Lock vertex buffer
        vertexBatchBuffer->Lock (0, BATCH_BUFFER_SIZE * sizeof(TLVERTEX), (void **)
                                 &batchVertices, 0);
    }

}


//Finish batch drawing
void EndBatchDrawing()
{
    //Unlock vertex buffer
    vertexBatchBuffer->Unlock();

    //Draw the quads in the buffer if it wasn't just flushed
    if (numBatchVertices)
        d3dDevice->DrawIndexedPrimitive (D3DPT_TRIANGLELIST, 0, 0, numBatchVertices, 0,
                                         numBatchVertices / 2);

    //Set stream source to regular buffer
    d3dDevice->SetStreamSource (0, vertexBuffer, 0, sizeof(TLVERTEX));

    //Reset vertex count        
    numBatchVertices = 0;        
}
