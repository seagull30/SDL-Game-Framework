#include "stdafx.h"
#include "Scene.h"

#include "Framework.h"

Scene g_Scene;

int32		Count;//카운트 값
#define TEXT_COUNT 3//문자열 카운트

static ESceneType s_nextScene = SCENE_NULL;
#define _MAX_SINEN_NUM 100
#include "LoadCSV.h"
#include "Csv.h"

#pragma region TitleScene

#define SOLID 0
#define SHADED 1
#define BLENDED 2

const CsvFile csvFile;

typedef struct TitleSceneData
{
	Text	Text1;
	Text	Text2;
	Text	Text3;
	int32	FontSize;
	int32	RenderMode;
	Image	index1;

} TitleSceneData;


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


	data->FontSize = 50;
	Text_CreateText(&data->Text2, "d2coding.ttf", data->FontSize, L"- G A M E S T A R T -", 21);
	data->FontSize = 30;
	Text_CreateText(&data->Text3, "d2coding.ttf", data->FontSize, L"PRESS - SPACE - BUTTON", 22);

	data->RenderMode = SOLID;

	Image_LoadImage(&data->index1, "index0.png");
}

void update_title(void)
{
	TitleSceneData* data = (TitleSceneData*)g_Scene.Data;


	data->FontSize = 50;
	Text_CreateMoveText(&data->Text1, "d2coding.ttf", data->FontSize, L"T A K E N", 8, 0.5f);



	Text_SetFontStyle(&data->Text1, FS_BOLD);
	Text_SetFontStyle(&data->Text2, FS_BOLD);
	Text_SetFontStyle(&data->Text3, FS_BOLD);


	if (Input_GetKeyDown(VK_SPACE))
	{
		Scene_SetNextScene(SCENE_RULE);
	}
}
bool canShow = 0;

void render_title(void)
{

	TitleSceneData* data = (TitleSceneData*)g_Scene.Data;
	static float elapsedTime;
	elapsedTime += Timer_GetDeltaTime();
	Renderer_DrawImage(&data->index1, 0, 0);


	SDL_Color foreColor = { .r = 255, .g = 255, .b = 255 };
	SDL_Color backColor = { .a = 125 };
	Renderer_DrawTextShaded(&data->Text1, 400, 100, foreColor, backColor);

	if (elapsedTime >= 0.7f)
	{

		canShow = !canShow;
		elapsedTime = 0.0f;

	}

	if (canShow == true)
	{
		SDL_Color foreColor = { .r = 255 };
		SDL_Color backColor = { .a = 0 };
		Renderer_DrawTextShaded(&data->Text2, 275, 500, foreColor, backColor);
		Renderer_DrawTextShaded(&data->Text3, 375, 600, foreColor, backColor);

	}



}

void release_title(void)
{
	TitleSceneData* data = (TitleSceneData*)g_Scene.Data;


	Text_FreeText(&data->Text1);
	Text_FreeText(&data->Text2);
	Text_FreeText(&data->Text3);

	SafeFree(g_Scene.Data);
}
#pragma endregion

#pragma region ruleScene

const wchar_t* ruleStr[] =
{
	L"게 임 방 법",
	L"- 선택지가 없는 장면은 스페이스바를 누르면 장면이 넘어갑니다.",
	L"- 선택지가 있는 장면은 방향키와 스페이스바를 이용하여 선택할 수 있습니다.",
};



typedef struct RuleSceneData
{
	Text Text[TEXT_COUNT];
	Image image;
	int32 Alpha;
	int32 ImageAlpha;

} RuleSceneData;



void init_rule(void)
{
	g_Scene.Data = malloc(sizeof(RuleSceneData));
	memset(g_Scene.Data, 0, sizeof(RuleSceneData));

	RuleSceneData* data = (RuleSceneData*)g_Scene.Data;

	Image_LoadImage(&data->image, "index0.png");
	for (int32 i = 0; i < TEXT_COUNT; ++i)
	{

		Text_CreateText(&data->Text[i], "d2coding.ttf", 25, ruleStr[i], wcslen(ruleStr[i]));

	}
	data->Alpha = 0;
	
}
void update_rule(void)
{
	RuleSceneData* data = (RuleSceneData*)g_Scene.Data;
	
	
	
	if (Input_GetKeyDown(VK_SPACE))
	{
		Scene_SetNextScene(SCENE_MAIN);
	}

}

void render_rule(void)
{

	RuleSceneData* data = (RuleSceneData*)g_Scene.Data;
	Image_FadeIn(&data->image, data->Alpha, 0, 255);
	Renderer_DrawImage(&data->image, 0, 0);
	
	data->Alpha = Clamp(1, data->Alpha + 1, 255);// 페이드 인
	Renderer_DrawTextFade(&data->Text[0], 10, 30, data->Alpha);
	Renderer_DrawTextFade(&data->Text[1], 10, 600, data->Alpha);
	Renderer_DrawTextFade(&data->Text[2], 10, 630, data->Alpha);



}

void release_rule(void)
{

	RuleSceneData* data = (RuleSceneData*)g_Scene.Data;

	Text_FreeText(&data->Text[0]);
	Text_FreeText(&data->Text[1]);
	Text_FreeText(&data->Text[2]);


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
	case SCENE_RULE:
		g_Scene.Init = init_rule;
		g_Scene.Update = update_rule;
		g_Scene.Render = render_rule;
		g_Scene.Release = release_rule;
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