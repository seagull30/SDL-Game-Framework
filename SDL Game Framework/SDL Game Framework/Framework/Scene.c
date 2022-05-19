#include "stdafx.h"
#include "Scene.h"

#include "Framework.h"

Scene g_Scene;

static ESceneType s_nextScene = SCENE_NULL;
#define _MAX_SINEN_NUM 100
#include "LoadCSV.h"
#include "Csv.h"

#pragma region TitleScene

#define SOLID 0
#define SHADED 1
#define BLENDED 2

const wchar_t* str[] = {
	L"여기는 타이틀씬입니다. 텍스트와 관련된 여러가지를 테스트해봅시다.",
	L"B키를 누르면 폰트가 굵게 변합니다.",
	L"I키를 누르면 폰트가 이탤릭체로 변합니다.",
	L"U키를 누르면 텍스트에 밑줄이 생깁니다.",
	L"S키를 누르면 텍스트에 취소선이 생깁니다.",
	L"N키를 누르면 다시 원래대로 돌아옵니다.",
	L"C키를 누르면 렌더 모드가 바뀝니다. (Solid -> Shaded -> Blended)",
	L"1키를 누르면 텍스트가 작아집니다.",
	L"2키를 누르면 텍스트가 커집니다.",
	L"스페이스 키를 누르면 다음 씬으로 넘어갑니다."
};

typedef struct TitleSceneData
{
	Text	GuideLine[10];
	Text	TestText;
	int32	FontSize;
	int32	RenderMode;
	Image	TestImage;
} TitleSceneData;

static SceneData scenedata[_MAX_SINEN_NUM];
const CsvFile csvFile;

Music backmusic;
char* prevPlayMusic;
char* playMusic;

void init_title(void)
{
	g_Scene.Data = malloc(sizeof(TitleSceneData));
	memset(g_Scene.Data, 0, sizeof(TitleSceneData));
	memset(&csvFile, 0, sizeof(CsvFile));
	//CSVInit("게임북 CSV - 시트1.csv", scenedata);
	CreateCsvFile(&csvFile,"csv최신_18일_1539.xlsx - 시트1.csv");

	Audio_LoadMusic(&backmusic, "index1.mp3");
	//Audio_HookMusicFinished(logOnFinished);
	Audio_PlayFadeIn(&backmusic, INFINITY_LOOP, 3000);
	playMusic = "index.mp3";
	prevPlayMusic = "index.mp3";


	TitleSceneData* data = (TitleSceneData*)g_Scene.Data;
	for (int32 i = 0; i < 10; ++i)
	{
		Text_CreateText(&data->GuideLine[i], "d2coding.ttf", 16, str[i], wcslen(str[i]));
	}

	data->FontSize = 24;
	Text_CreateText(&data->TestText, "d2coding.ttf", data->FontSize, L"이 텍스트가 변합니다.", 13);

	data->RenderMode = SOLID;

	Image_LoadImage(&data->TestImage, "Background.jfif");
}

void update_title(void)
{
	TitleSceneData* data = (TitleSceneData*)g_Scene.Data;

	if (Input_GetKeyDown('B'))
	{
		Text_SetFontStyle(&data->TestText, FS_BOLD);
	}

	if (Input_GetKeyDown('I'))
	{
		Text_SetFontStyle(&data->TestText, FS_ITALIC);
	}

	if (Input_GetKeyDown('U'))
	{
		Text_SetFontStyle(&data->TestText, FS_UNDERLINE);
	}

	if (Input_GetKeyDown('S'))
	{
		Text_SetFontStyle(&data->TestText, FS_STRIKETHROUGH);
	}

	if (Input_GetKeyDown('N'))
	{
		Text_SetFontStyle(&data->TestText, FS_NORMAL);
	}

	if (Input_GetKeyDown('C'))
	{
		data->RenderMode = (data->RenderMode + 1) % 3;
	}

	if (Input_GetKey('1'))
	{
		--data->FontSize;
		Text_SetFont(&data->TestText, "d2coding.ttf", data->FontSize);
	}

	if (Input_GetKey('2'))
	{
		++data->FontSize;
		Text_SetFont(&data->TestText, "d2coding.ttf", data->FontSize);
	}

	if (Input_GetKeyDown(VK_SPACE))
	{
		Scene_SetNextScene(SCENE_MAIN);
	}
}

void render_title(void)
{
	TitleSceneData* data = (TitleSceneData*)g_Scene.Data;
	for (int32 i = 0; i < 10; ++i)
	{
		SDL_Color color = { .a = 255 };
		Renderer_DrawTextSolid(&data->GuideLine[i], 10, 20 * i, color);
	}

	switch (data->RenderMode)
	{
	case SOLID:
	{
		SDL_Color color = { .a = 255 };
		Renderer_DrawTextSolid(&data->TestText, 400, 400, color);
	}
	break;
	case SHADED:
	{
		SDL_Color bg = { .a = 255 };
		SDL_Color fg = { .r = 255, .g = 255, .a = 255 };
		Renderer_DrawTextShaded(&data->TestText, 400, 400, fg, bg);
	}
	break;
	case BLENDED:
	{
		Renderer_DrawImage(&data->TestImage, 400, 400);
		SDL_Color color = { .r = 255, .g = 255, .b = 255, .a = 255 };
		Renderer_DrawTextBlended(&data->TestText, 400, 400, color);
	}
	break;
	}
}

void release_title(void)
{
	TitleSceneData* data = (TitleSceneData*)g_Scene.Data;

	for (int32 i = 0; i < 10; ++i)
	{
		Text_FreeText(&data->GuideLine[i]);
	}
	Text_FreeText(&data->TestText);

	Image_FreeImage(&data->TestImage);

	SafeFree(g_Scene.Data);
}
#pragma endregion

#pragma region MainScene

void logOnFinished(void)
{
	LogInfo("You can show this log on stopped the music");
}

void log2OnFinished(int32 channel)
{
	LogInfo("You can show this log on stopped the effect");
}
typedef struct MainSceneData
{
	int32		index;
	Music		BGM;
	char*		playMusic;
	float		Volume;
	Image		BackGround;
	int32		BackGroundX;
	int32		BackGroundY;
	int32		imageEffect;
	int32		textTime;
	int32		textSpeed;
	int32		text1X;
	int32		text1Y;
	Text		text1;
	int32		text2X;
	int32		text2Y;
	Text		text2[5];
	int32		text3X;
	int32		text3Y;
	Text		text3[5];
	Text		select1;
	Text		select2;
	Text		select3;
	int32		selectCount;
	int32		selectValue[3];
	int32		playerSelectValue;
} MainSceneData;

typedef enum mainSceneDataNumber
{
index,
BGMFileName,
BackGroundFileName,
imageTime,
imageEffect,
textTime,
textSpeed,
textEffect,
textFileName1,
//text1x,
//text1y,
textFileName2,
//text2x,
//text2y,
textFileName3,
//text3x,
//text3y,
select1,
select1Value,
select2,
select2Value,
select3,
select3Value
} mainSceneDataNumber;

static int32 sceneNum = 3;
static int32 prevSceneNum = 1;
Music backmusic;
char* prevPlayMusic = "index.mp3";
char* playMusic = "index.mp3";
void init_main(void)
{
	g_Scene.Data = malloc(sizeof(MainSceneData));
	memset(g_Scene.Data, 0, (sizeof(MainSceneData)));
	MainSceneData* data = (MainSceneData*)g_Scene.Data;

	

	data->index = ParseToInt(csvFile.Items[sceneNum][index]);
	//if (playMusic != ParseToAscii(csvFile.Items[sceneNum][BackGroundFileName]))
	//{
	//	Audio_LoadMusic(&backmusic, ParseToAscii(csvFile.Items[sceneNum][BGMFileName]));
	//	playMusic =
	//}
	//Audio_HookMusicFinished(logOnFinished);
	//Audio_PlayFadeIn(&data->BGM, INFINITY_LOOP, 3000);
	Image_LoadImage(&data->BackGround, ParseToAscii(csvFile.Items[sceneNum][BackGroundFileName]));
	data->selectCount = 0;
	for (int i = 0; i < 3; ++i)
	{
		int32 check = ParseToInt(csvFile.Items[sceneNum][select1Value]);
		if (check != 0)
		{
			data->selectValue[i] = check;
			++data->selectCount;
		}
	}
	
	Text_LoadText(&data->text1, ParseToAscii(csvFile.Items[sceneNum][textFileName1]));
	Text_LoadText(&data->text2, ParseToAscii(csvFile.Items[sceneNum][textFileName2]));
	Text_LoadText(&data->text3, ParseToAscii(csvFile.Items[sceneNum][textFileName3]));

	data->Volume = 1.0f;
	//data->text1X = ParseToInt(csvFile.Items[sceneNum][text1x]);
	//data->text1Y = ParseToInt(csvFile.Items[sceneNum][text1y]);
	//data->text2X = ParseToInt(csvFile.Items[sceneNum][text2x]);
	//data->text2Y = ParseToInt(csvFile.Items[sceneNum][text2y]);
	//data->text3X = ParseToInt(csvFile.Items[sceneNum][text3x]);
	//data->text3Y = ParseToInt(csvFile.Items[sceneNum][text3y]);
	
	data->BackGroundX = 0;
	data->BackGroundY = 0;
	data->playerSelectValue = 1;
	
}

void update_main(void)
{
	MainSceneData* data = (MainSceneData*)g_Scene.Data;

	if (Input_GetKeyDown('M'))
	{
		if (Audio_IsMusicPlaying())
		{
			Audio_Stop();
		}
		else
		{
			Audio_Play(&data->BGM, INFINITY_LOOP);
		}
	}

	if (Input_GetKeyDown('P'))
	{
		if (Audio_IsMusicPaused())
		{
			Audio_Resume();
		}
		else
		{
			Audio_Pause();
		}
	}
	
	if (Input_GetKeyDown(VK_SPACE))
	{
	
		prevSceneNum = sceneNum;
		sceneNum = data->selectValue[data->playerSelectValue];
		Scene_SetNextScene(SCENE_MAIN);
	}

	if (Input_GetKeyDown('W'))
	{
		if (data->playerSelectValue > 1)
			--data->playerSelectValue;
	}
	
	if (Input_GetKeyDown('S'))
	{
		if (data->playerSelectValue < data->selectCount)
			++data->playerSelectValue;
	}

	if (Input_GetKeyDown(VK_BACK))
	{
		sceneNum = prevSceneNum;
		
		Scene_SetNextScene(SCENE_MAIN);
	}
}

void render_main(void)
{
	MainSceneData* data = (MainSceneData*)g_Scene.Data;

	Renderer_DrawImage(&data->BackGround, data->BackGroundX, data->BackGroundY);

	SDL_Color color = { .r = 255, .g = 255, .b = 255, .a = 255 };
	Renderer_DrawTextSolid(&data->text1, 11,12, color);
	for (int i = 0; i < 5; ++i)
	{
		Renderer_DrawTextSolid(&data->text2[i], data->text2X, data->text2Y * (i + 1), color);

	}
	for (int i = 0; i < 5; ++i)
	{
		Renderer_DrawTextSolid(&data->text3[i], 291, 600 + (20 * (i + 1)), color);

	}

}

void release_main(void)
{
	MainSceneData* data = (MainSceneData*)g_Scene.Data;
	
	Text_FreeText(&data->text1); 
	Text_FreeText(&data->text2);
	Text_FreeText(&data->text3);
	Image_FreeImage(&data->BackGround);
	Audio_FreeMusic(&data->BGM);
	
	SafeFree(g_Scene.Data);
}
#pragma endregion

bool Scene_IsSetNextScene(void)
{
	if (SCENE_NULL == s_nextScene)
	{
		return false;
	}
	else
	{
		return true;
	}
}

void Scene_SetNextScene(ESceneType scene)
{
	assert(s_nextScene == SCENE_NULL);
	assert(SCENE_NULL < scene&& scene < SCENE_MAX);

	s_nextScene = scene;
}

void Scene_Change(void)
{
	assert(s_nextScene != SCENE_NULL);

	if (g_Scene.Release)
	{
		g_Scene.Release();
	}

	switch (s_nextScene)
	{
	case SCENE_TITLE:
		g_Scene.Init = init_title;
		g_Scene.Update = update_title;
		g_Scene.Render = render_title;
		g_Scene.Release = release_title;
		break;
	case SCENE_MAIN:
		g_Scene.Init = init_main;
		g_Scene.Update = update_main;
		g_Scene.Render = render_main;
		g_Scene.Release = release_main;
		break;
	}

	g_Scene.Init();

	s_nextScene = SCENE_NULL;
}