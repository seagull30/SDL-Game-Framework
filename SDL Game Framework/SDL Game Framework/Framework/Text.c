#include "stdafx.h"
#include "Text.h"
#include "Input.h"
#include "Scene.h"
static char s_path[MAX_PATH];

bool Text_Init(void)
{
	if (0 != TTF_Init())
	{
		return false;
	}

	return true;
}

void Text_Cleanup(void)
{
	TTF_Quit();
}

void Text_CreateText(Text* text, const char* fontFile, int32 fontSize, const wchar_t* str, int32 length)
{
	Text_SetFont(text, fontFile, fontSize);
	
	text->String = malloc(sizeof(wchar_t) * (length + 1));
	for (int32 i = 0; i < length; ++i)
	{
		(text->String)[i] = str[i];
	}
	(text->String)[length] = L'\0';
	
	text->Length = length;
}

void Text_FreeText(Text* text)
{
	TTF_CloseFont(text->Font);
	text->Font = NULL;

	SafeFree(text->String);
	
	text->Length = 0;
}

void Text_SetFont(Text* text, const char* fontFile, int32 fontSize)
{
	if (text->Font)
	{
		TTF_CloseFont(text->Font);
	}

	LogInfo("Loading Font : %s", fontFile);
	sprintf_s(s_path, sizeof(s_path), "%s/%s", FONT_DIRECTORY, fontFile);
	text->Font = TTF_OpenFont(s_path, fontSize);
}

void Text_SetFontStyle(Text* text, EFontStyle style)
{
	TTF_SetFontStyle(text->Font, style);
}

EFontStyle Text_GetFontStyle(const Text* text)
{
	return (EFontStyle)TTF_GetFontStyle(text->Font);
}

bool Text_MoveOn(void)
{
	static float elapsedTime;
	elapsedTime += Timer_GetDeltaTime();
	if (elapsedTime > 100.0f)
	{
		
		if (Input_GetKeyDown(VK_ESCAPE))
			elapsedTime = 0.0f;
			return false;
			
	}
	else
		return true;

}

void Text_CreateMoveText(Text* text, const char* fontFile, int32 fontSize, const wchar_t* str, int32 length, static float timer)
{
	if (Text_MoveOn() == true)
	{
		static int32 i = 1;
		static float elapsedTime;
		elapsedTime += Timer_GetDeltaTime();
		if (elapsedTime >= timer)
		{

			if (i < length + 1)
				i++;
			Text_CreateText(text, fontFile, fontSize, str, i);
			elapsedTime = 0.0f;

			if (i > length + 1)
				i = 0;
		}

	}

}

void Text_LoadText(Text* text, const char* filename)
{
	
	LogInfo("Text Loading... %s", filename);

	static char path[MAX_PATH];

	sprintf_s(path, sizeof(path), "%s/%s", TEXT_DIRECTORY, filename);
	
	FILE* p_file = NULL;
	wchar_t str[256];
	int32 strlen = wcslen(str);
		if (0 == fopen_s(&p_file, path, "r,ccs=UTF-8"))
		{

			while (NULL != fgetws(str, 256, p_file))
			{
				
				if (str[strlen - 1] == '\n')
					Text_CreateText(text, "d2coding.ttf", 16, str, strlen - 1);//Text_CreateMoveText �� ����.
				else
					Text_CreateText(text, "d2coding.ttf", 16, str, strlen);
				++text;
			}

		}
	
}




#define TEXT_COUNT 3

void Text_TextChoice(const Text* text, int32 Count)
{
	for (int32 i = 0; i < TEXT_COUNT; ++i)
	{

		if (i == Count)
		{
			SDL_Color foreColor = { .r = 255, .g = 255, .b = 255 };
			SDL_Color backColor = { .r = 255, .a = 125 };
			Renderer_DrawTextShaded(text[i], 10, 30 * i, foreColor, backColor);
		}
		else
		{
			SDL_Color foreColor = { .r = 255, .g = 255, .b = 255 };
			SDL_Color backColor = { .a = 125 };
			Renderer_DrawTextShaded(text[i], 10, 30 * i, foreColor, backColor);
		}

	}
}
