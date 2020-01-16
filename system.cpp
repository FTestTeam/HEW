#include"grid.h"
#include"texture.h"
#include"model.h"
#include"sound.h"
#include"light.h"
#include"cube.h"
#include"background.h"

void System_Init()
{
	
	Texture_Init();
	Model_Init();
	Grid_Init();
	Cube_Init();
}

void System_UnInit()
{
	
	Grid_UnInit();
	Texture_Release();
	Model_UnInit();
	Cube_UnInit();
}

void System_Update()
{

}

void System_Draw()
{
	Grid_Draw();
}