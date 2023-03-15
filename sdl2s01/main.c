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

#define SDL_WINDOW_TITLE "�ҵ� SDL �մ���01"

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

	// ����һ������, �ɹ����ش���ָ��, ʧ�ܷ���NULL
	SDL_Window* l_window = SDL_CreateWindow(
		SDL_WINDOW_TITLE,			// ���ڱ���
		SDL_WINDOWPOS_UNDEFINED,	// ����λ�� x
		SDL_WINDOWPOS_UNDEFINED,	// ����λ�� y
		640, 480,		 			// ���ڴ�С �� w, �� h
		0);							// ���ڱ�־λ����ʱ���ԣ�
	if (l_window == NULL)
	{
		SDL_Log("Could not create window: %s", SDL_GetError());
		return 1;
	}

	// ��Ϣѭ��
	SDL_Event l_event;	//����һ��SDL��Ϣ
	bool l_quit = false;	//��Ϣѭ�����ڱ�����
	while(!l_quit)
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

	// �ͷŴ�����Դ
	SDL_Quit();

	return 0;

}
