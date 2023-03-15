/// sdl2s02.c
/// 目标：修改指定像素
/// 1. 获取像素矩阵
/// 2. 修改指定像素
/// l_surface->pixels 是一个指向像素矩阵的指针（左到右上到下顺序的数列）
/// 像素矩阵 = 每个像素的颜色值（RGB）的数列
/// 
#include <stdio.h>
#include <stdbool.h>

// 也可以设置中添加包含目录 如 D:\SDK\SDL2-2.26.4\include 、#include <SDL.h>
#include "D:\SDK\SDL2-2.26.4\include\SDL.h"

// 设置中添加库目录 如 D:\SDK\SDL2-2.26.4\lib\x64
#pragma comment(lib, "SDL2.lib")
#pragma comment(lib, "SDL2main.lib")

// 设置 utf-8 字符集
// 显示中文标题是不会解释成GB编码
#pragma execution_character_set("utf-8")

#define SDL_WINDOW_TITLE "我的 SDL 空窗口02"
#define SDL_WINDOW_WIDTH 640
#define SDL_WINDOW_HEIGHT 480

SDL_Window* g_window = NULL;

/// 初始化窗口
int InitWindow()
{
	// 创建一个窗口, 成功返回窗口指针, 失败返回NULL
	g_window = SDL_CreateWindow(
		SDL_WINDOW_TITLE,			// 窗口标题
		SDL_WINDOWPOS_UNDEFINED,	// 窗口位置 x
		SDL_WINDOWPOS_UNDEFINED,	// 窗口位置 y
		SDL_WINDOW_WIDTH, SDL_WINDOW_HEIGHT,// 窗口大小 宽 w, 高 h
		0);							// 窗口标志位（暂时忽略）
	if (g_window == NULL)
	{
		SDL_Log("Could not create window: %s", SDL_GetError());
		return 1;
	}
	return 0;
}

/// 消息循环 EventLoop
int EventLoop()
{
	SDL_Event l_event;		//定义一个SDL消息
	bool l_quit = false;	//消息循环的哨兵变量
	while (!l_quit)
	{
		SDL_WaitEvent(&l_event);
		// 判断消息/事件 的类型
		switch (l_event.type)
		{
		case SDL_QUIT:
		{
			l_quit = true;
			break;
		}
		default:
		{
			break;
		}
		}
	}
	return l_event.type;
}


int main()
{
	// 初始化SDL VIDEO, 成功返回0, 失败返回其他错误编码（负数）
	int l_iv = SDL_Init(SDL_INIT_VIDEO);
	if (l_iv)
	{
		// 打印错误信息, 用 SDL_GetError 返回具体错误信息
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return 1;
	}

	// 初始化窗口
	InitWindow();

	// 获取窗口的表面（surface），一个二维图像，这里用来显示创建的内容。
	SDL_Surface* l_surface = SDL_GetWindowSurface(g_window);
	// 创建一个矩形（用作窗口背景） 参数（x y w h）位置+大小
	SDL_Rect l_rect1 = { 0, 0, SDL_WINDOW_WIDTH, SDL_WINDOW_HEIGHT };
	// 填充颜色 参数（表面，矩形，颜色） 颜色为rgb模式
	SDL_FillRect(l_surface, &l_rect1, 0xffffff);
	// 再创建一个矩形 100*100位于左上角
	SDL_Rect l_rect2 = { 0, 0, 100, 100 };
	// 填充颜色 （红色）让 SDL_MapRGB
	/// SDL_MapRGB将一个 RGB三元组 映射到 给定像素格式 的不透明像素值
	SDL_FillRect(l_surface, &l_rect2, SDL_MapRGB(l_surface->format, 255, 255, 0));
	
////////////////////////////////////////////////////////////////////////
	// 修改指定像素
	// 获取像素矩阵
	uint32_t* l_pixels = (uint32_t*)l_surface->pixels;
	// 修改指定像素
	uint32_t x = 50;	// 第50行
	uint32_t y = 50;	// 第50列
	for (uint32_t i = 0; i < 100; i++)
	{
		// l_surface->w 是窗口宽度
		// y * l_surface->w 是第y行的第一个像素
		// (y * l_surface->w) + x 是第y行的第x个像素
		// 0xff00ff 是紫色
		l_pixels[ ((y * l_surface->w) + x) + i] = 0xff00ff;
	}

////////////////////////////////////////////////////////////////////////
	// 更新窗口
	SDL_UpdateWindowSurface(g_window);

	// 消息循环
	EventLoop();

	// 释放窗口资源 清理所有SDL已初始化的资源并退出，确保没有内存泄漏
	SDL_Quit();

	return 0;

}
