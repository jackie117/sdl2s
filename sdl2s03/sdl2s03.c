/// sdl2s02.c
/// Ŀ�꣺�޸�ָ������
/// 1. ��ȡ���ؾ���
/// 2. �޸�ָ������
/// l_surface->pixels ��һ��ָ�����ؾ����ָ�루�����ϵ���˳������У�
/// ���ؾ��� = ÿ�����ص���ɫֵ��RGB��������
/// 
#include <stdio.h>
#include <stdbool.h>

// Ҳ������������Ӱ���Ŀ¼ �� D:\SDK\SDL2-2.26.4\include ��#include <SDL.h>
#include "D:\SDK\SDL2-2.26.4\include\SDL.h"

// ��������ӿ�Ŀ¼ �� D:\SDK\SDL2-2.26.4\lib\x64
#pragma comment(lib, "SDL2.lib")
#pragma comment(lib, "SDL2main.lib")

// ���� utf-8 �ַ���
// ��ʾ���ı����ǲ�����ͳ�GB����
#pragma execution_character_set("utf-8")

#define SDL_WINDOW_TITLE "�ҵ� SDL �մ���02"
#define SDL_WINDOW_WIDTH 640
#define SDL_WINDOW_HEIGHT 480

SDL_Window* g_window = NULL;

/// ��ʼ������
int InitWindow()
{
	// ����һ������, �ɹ����ش���ָ��, ʧ�ܷ���NULL
	g_window = SDL_CreateWindow(
		SDL_WINDOW_TITLE,			// ���ڱ���
		SDL_WINDOWPOS_UNDEFINED,	// ����λ�� x
		SDL_WINDOWPOS_UNDEFINED,	// ����λ�� y
		SDL_WINDOW_WIDTH, SDL_WINDOW_HEIGHT,// ���ڴ�С �� w, �� h
		0);							// ���ڱ�־λ����ʱ���ԣ�
	if (g_window == NULL)
	{
		SDL_Log("Could not create window: %s", SDL_GetError());
		return 1;
	}
	return 0;
}

/// ��Ϣѭ�� EventLoop
int EventLoop()
{
	SDL_Event l_event;		//����һ��SDL��Ϣ
	bool l_quit = false;	//��Ϣѭ�����ڱ�����
	while (!l_quit)
	{
		SDL_WaitEvent(&l_event);
		// �ж���Ϣ/�¼� ������
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
	// ��ʼ��SDL VIDEO, �ɹ�����0, ʧ�ܷ�������������루������
	int l_iv = SDL_Init(SDL_INIT_VIDEO);
	if (l_iv)
	{
		// ��ӡ������Ϣ, �� SDL_GetError ���ؾ��������Ϣ
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return 1;
	}

	// ��ʼ������
	InitWindow();

	// ��ȡ���ڵı��棨surface����һ����άͼ������������ʾ���������ݡ�
	SDL_Surface* l_surface = SDL_GetWindowSurface(g_window);
	// ����һ�����Σ��������ڱ����� ������x y w h��λ��+��С
	SDL_Rect l_rect1 = { 0, 0, SDL_WINDOW_WIDTH, SDL_WINDOW_HEIGHT };
	// �����ɫ ���������棬���Σ���ɫ�� ��ɫΪrgbģʽ
	SDL_FillRect(l_surface, &l_rect1, 0xffffff);
	// �ٴ���һ������ 100*100λ�����Ͻ�
	SDL_Rect l_rect2 = { 0, 0, 100, 100 };
	// �����ɫ ����ɫ���� SDL_MapRGB
	/// SDL_MapRGB��һ�� RGB��Ԫ�� ӳ�䵽 �������ظ�ʽ �Ĳ�͸������ֵ
	SDL_FillRect(l_surface, &l_rect2, SDL_MapRGB(l_surface->format, 255, 255, 0));
	
////////////////////////////////////////////////////////////////////////
	// �޸�ָ������
	// ��ȡ���ؾ���
	uint32_t* l_pixels = (uint32_t*)l_surface->pixels;
	// �޸�ָ������
	uint32_t x = 50;	// ��50��
	uint32_t y = 50;	// ��50��
	for (uint32_t i = 0; i < 100; i++)
	{
		// l_surface->w �Ǵ��ڿ��
		// y * l_surface->w �ǵ�y�еĵ�һ������
		// (y * l_surface->w) + x �ǵ�y�еĵ�x������
		// 0xff00ff ����ɫ
		l_pixels[ ((y * l_surface->w) + x) + i] = 0xff00ff;
	}

////////////////////////////////////////////////////////////////////////
	// ���´���
	SDL_UpdateWindowSurface(g_window);

	// ��Ϣѭ��
	EventLoop();

	// �ͷŴ�����Դ ��������SDL�ѳ�ʼ������Դ���˳���ȷ��û���ڴ�й©
	SDL_Quit();

	return 0;

}
