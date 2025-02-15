#pragma once

#include "Type.h"

typedef struct Image
{
	struct SDL_Texture* Texture;
	int32				Width;
	int32				Height;
	float				ScaleX;
	float				ScaleY;
} Image;

/// <summary>
/// 이미지 관련 라이브러리를 초기화한다.
/// </summary>
/// <returns>성공했다면 true, 아니면 false</returns>
bool Image_Init(void);

/// <summary>
/// 이미지 관련 라이브러리를 정리한다.
/// </summary>
void Image_Cleanup(void);

/// <summary>
/// 이미지를 불러온다.
/// </summary>
/// <param name="image">이미지 객체</param>
/// <param name="filename">파일 이름</param>
void Image_LoadImage(Image* image, const char* filename);

/// <summary>
/// 이미지 관련 자원을 반환한다. Release시 반드시 출력하자.
/// </summary>
/// <param name="image">Image 객체</param>
void Image_FreeImage(Image* image);

/// <summary>
/// 이미지의 알파값을 변경한다.
/// </summary>
/// <param name="image">이미지 객체</param>
/// <param name="alpha">파일 이름</param>
void Image_SetAlphaValue(Image* image, uint8 alpha);


/// <summary>
/// 이미지를 페이드인 한다
/// </summary>
/// <param name="image">이미지 객체</param>
/// <param name="Alpha">알파값</param>
/// <param name="Min">알파 최소값</param>
/// <param name="Max">알파 최댓값</param>
void Image_FadedIn(Image* image, int32 Alpha);

/// <summary>
/// 이미지를 페이드아웃 한다
/// </summary>
/// <param name="image">이미지 객체</param>
/// <param name="Alpha">알파값</param>
/// <param name="Min">알파 최소값</param>
/// <param name="Max">알파 최댓값</param>
void Image_FadeOut(Image* image, int32 Alpha, int32 Min, int32 Max);

