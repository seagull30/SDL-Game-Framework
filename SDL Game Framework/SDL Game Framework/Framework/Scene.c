#include "stdafx.h"
#include "Scene.h"

#include "Framework.h"

Scene g_Scene;

int32		Count;//ī��Ʈ ��
#define TEXT_COUNT 3//���ڿ� ī��Ʈ

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


void init_title(void)
{
	g_Scene.Data = malloc(sizeof(TitleSceneData));
	memset(g_Scene.Data, 0, sizeof(TitleSceneData));
	memset(&csvFile, 0, sizeof(CsvFile));
	//CSVInit("���Ӻ� CSV - ��Ʈ1.csv", scenedata);
	CreateCsvFile(&csvFile, "csv�ֽ�_18��_1539.xlsx - ��Ʈ1.csv");
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
	L"�� �� �� ��",
	L"- �������� ���� ����� �����̽��ٸ� ������ ����� �Ѿ�ϴ�.",
	L"- �������� �ִ� ����� ����Ű�� �����̽��ٸ� �̿��Ͽ� ������ �� �ֽ��ϴ�.",
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
	
	data->Alpha = Clamp(1, data->Alpha + 1, 255);// ���̵� ��
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
const wchar_t* str2[] = {
	L"���⼭�� ����� �̹��� ������ ���ؼ� �˾ƺ��ô�.",
	L"ȭ��ǥŰ�� �̹����� �̵���ų �� �ֽ��ϴ�.",
	L"EŰ�� ������ ����Ʈ�� �����ų �� �ֽ��ϴ�. ����Ʈ �Ҹ��� ������ ������ ���� �� �����ϼ���.",
	L"MŰ�� ������ ���ų� �� �� �ֽ��ϴ�.",
	L"PŰ�� ������ ���߰ų� �簳�� �� �ֽ��ϴ�.",
	L"1���� 2������ ������ ������ �� �ֽ��ϴ�.",
	L"WASD�� �̹����� �������� ������ �� �ֽ��ϴ�.",
	L"KLŰ�� �̹����� ������ ������ �� �ֽ��ϴ�."
};

#define GUIDELINE_COUNT 8

//typedef struct MainSceneData
//{
//	Text		GuideLine[GUIDELINE_COUNT];
//	Music		BGM;
//	float		Volume;
//	SoundEffect Effect;
//	Image		BackGround;
//	float		Speed;
//	int32		X;
//	int32		Y;
//	int32		Alpha;
//} MainSceneData;




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
	float		Volume;
	Image		BackGround;
	int32		BackGroundX;
	int32		BackGroundY;
	int32		imageEffect;
	int32		textTime;
	int32		temp;
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
	int32		select1Value;
	Text		select2;
	int32		select2Value;
	Text		select3;
	int32		select3Value;
	int32		playerSelectValue;
} MainSceneData;

static int32 sceneNum = 3;
static int32 prevSceneNum = 1;

void init_main(void)
{
	g_Scene.Data = malloc(sizeof(MainSceneData));
	memset(g_Scene.Data, 0, (sizeof(MainSceneData)));
	MainSceneData* data = (MainSceneData*)g_Scene.Data;



	data->index = ParseToInt(csvFile.Items[sceneNum][0]);
	Audio_LoadMusic(&data->BGM, ParseToAscii(csvFile.Items[sceneNum][1]));
	Audio_HookMusicFinished(logOnFinished);
	Audio_PlayFadeIn(&data->BGM, INFINITY_LOOP, 3000);
	Image_LoadImage(&data->BackGround, ParseToAscii(csvFile.Items[sceneNum][2]));
	data->select1Value = ParseToInt(csvFile.Items[sceneNum][13]);
	data->select2Value = ParseToInt(csvFile.Items[sceneNum][15]);
	data->select3Value = ParseToInt(csvFile.Items[sceneNum][17]);
	Text_LoadText(&data->text1, ParseToAscii(csvFile.Items[sceneNum][9]));
	Text_LoadText(&data->text2, ParseToAscii(csvFile.Items[sceneNum][10]));
	Text_LoadText(&data->text3, ParseToAscii(csvFile.Items[sceneNum][11]));

	data->Volume = 1.0f;
	
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
	
	if (Input_GetKeyDown('1'))
	{
		prevSceneNum = sceneNum;
		sceneNum = data->select1Value;
		Scene_SetNextScene(SCENE_MAIN);
	}

	if (Input_GetKey('W'))
	{
		--data->playerSelectValue;
	}
	
	if (Input_GetKey('S'))
	{
		++data->playerSelectValue;
	}
	if (Input_GetKeyDown(VK_SPACE))
	{
		Scene_SetNextScene(SCENE_CREDIT);
	}
}

void render_main(void)
{
	MainSceneData* data = (MainSceneData*)g_Scene.Data;

	Renderer_DrawImage(&data->BackGround, data->BackGroundX, data->BackGroundY);

	SDL_Color color = { .r = 255, .g = 255, .b = 255, .a = 255 };
	Renderer_DrawTextSolid(&data->text1, 0, 0, color);
	for (int i = 0; i < 5; ++i)
	{
		Renderer_DrawTextSolid(&data->text2[i], 0, 30 * (i + 1), color);

	}
	for (int i = 0; i < 5; ++i)
	{
		Renderer_DrawTextSolid(&data->text3[i], 0, 50 + (15 * (i + 1)), color);

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

#pragma region creditscene
const wchar_t* str4[] = {
	L"��Ÿ���� ��ȹ��",
	L"    ������",
	L"    ������",
	L"    ������",
	L"��Ÿ���� ���߹�",
	L"    ���λ�",
	L"    ������",
	L"    �ּ���"
};
#define GUIDELINE_COUNT 8
typedef struct creditscene
{
	Text		GuideLine[GUIDELINE_COUNT];
	Music		BGM;
	float		Volume;
	SoundEffect Effect;
	Image		BackGround1;
	Image		BackGround2;
	float		Speed;
	int32		X;
	int32		Y;
	int32		Alpha;
} creditscene;

void init_credit(void)
{

	g_Scene.Data = malloc(sizeof(creditscene));
	memset(g_Scene.Data, 0, sizeof(creditscene));

	creditscene* data = (creditscene*)g_Scene.Data;
	Image_LoadImage(&data->BackGround1, "credit1.png");
	Image_LoadImage(&data->BackGround2, "credit2.png");

	for (int32 i = 0; i < GUIDELINE_COUNT; ++i)
	{
		Text_CreateText(&data->GuideLine[i], "d2coding.ttf", 20, str4[i], wcslen(str4[i]));
	}

	/*Audio_LoadMusic(&data->BGM, "index1.mp3");
	Audio_HookMusicFinished(logOnFinished);
	Audio_LoadSoundEffect(&data->Effect, "effect2.wav");
	Audio_HookSoundEffectFinished(log2OnFinished);
	Audio_PlayFadeIn(&data->BGM, INFINITY_LOOP, 3000);*/

	/*data->Volume = 1.0f;
	data->Speed = 400.0f;*/
	data->X = 0;
	data->Y = 0;
	data->Alpha = 255; // ���� 
}

void update_credit(void)
{
	creditscene* data = (creditscene*)g_Scene.Data;
	if (Input_GetKeyDown(VK_SPACE))
	{
		Scene_SetNextScene(SCENE_MAX);
	}
}

static float elaspedtime = 0.0f;
void render_credit(void)
{
	creditscene* data = (creditscene*)g_Scene.Data;
	//(&data->BackGround1, data->X, data->Y);
	//(&data->BackGround2, data->X, data->Y);
	elaspedtime += Timer_GetDeltaTime();

	if (elaspedtime < 1.0f)
	{

		Renderer_DrawImage(&data->BackGround1, data->X, data->Y);
		data->Alpha = Clamp(0, data->Alpha - 1, 220);
		Image_SetAlphaValue(&data->BackGround1, data->Alpha);
		//SDL_Color color = { .r = 255, .g = 255, .b = 255, .a = 255 };
		//Renderer_DrawTextBlended(&data->BackGround1, 400, 400, color);

	}

	if (elaspedtime > 1.0f)
	{
		data->Alpha = Clamp(10, data->Alpha, 190);
		Image_SetAlphaValue(&data->BackGround2, data->Alpha);
		Renderer_DrawImage(&data->BackGround2, data->X, data->Y);

		for (int32 i = 0; i < GUIDELINE_COUNT; ++i)
		{
			SDL_Color color = { .r = 255, .g = 255, .b = 255, .a = 255 };
			Renderer_DrawTextSolid(&data->GuideLine[i], 900, 40 * i, color);
		}

	}
}

void release_credit(void)
{
	creditscene* data = (creditscene*)g_Scene.Data;

	for (int32 i = 0; i < GUIDELINE_COUNT; ++i)
	{
		Text_FreeText(&data->GuideLine[i]);
	}

	Image_FreeImage(&data->BackGround1);
	Image_FreeImage(&data->BackGround2);
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
	case SCENE_CREDIT:
		g_Scene.Init = init_credit;
		g_Scene.Update = update_credit;
		g_Scene.Render = render_credit;
		g_Scene.Release = release_credit;
	}

	g_Scene.Init();

	s_nextScene = SCENE_NULL;
}