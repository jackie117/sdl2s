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

#define SDL_WINDOW_TITLE "我的 SDL 空窗口01"

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

	// 创建一个窗口, 成功返回窗口指针, 失败返回NULL
	SDL_Window* l_window = SDL_CreateWindow(
		SDL_WINDOW_TITLE,			// 窗口标题
		SDL_WINDOWPOS_UNDEFINED,	// 窗口位置 x
		SDL_WINDOWPOS_UNDEFINED,	// 窗口位置 y
		640, 480,		 			// 窗口大小 宽 w, 高 h
		0);							// 窗口标志位（暂时忽略）
	if (l_window == NULL)
	{
		SDL_Log("Could not create window: %s", SDL_GetError());
		return 1;
	}

	// 消息循环
	SDL_Event l_event;	//定义一个SDL消息
	bool l_quit = false;	//消息循环的哨兵变量
	while(!l_quit)
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

	// 释放窗口资源
	SDL_Quit();

	return 0;

}
