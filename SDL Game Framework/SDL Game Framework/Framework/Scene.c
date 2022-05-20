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

const CsvFile csvFile;

typedef struct TitleSceneData
{
	Text	Text1;
	Text	Text2;
	Text	Text3;
	int32	FontSize;
	int32	RenderMode;
	Image	image1;
	Image	image2;

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
	
 	CreateCsvFile(&csvFile,"게임북 CSV0 (1).csv");

	Audio_LoadMusic(&backmusic, "index1.mp3");
	//Audio_HookMusicFinished(logOnFinished);
	Audio_PlayFadeIn(&backmusic, INFINITY_LOOP, 3000);
	playMusic = "index.mp3";
	prevPlayMusic = "index.mp3";

	TitleSceneData* data = (TitleSceneData*)g_Scene.Data;

	data->RenderMode = SOLID;

	Image_LoadImage(&data->image1, "index0.jpg");
	Image_LoadImage(&data->image2, "index0-2.png");
}

void update_title(void)
{
	TitleSceneData* data = (TitleSceneData*)g_Scene.Data;

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
	Renderer_DrawImage(&data->image1, 0, 0);
	Renderer_DrawImage(&data->image2, 0, 95);
	Image_SetAlphaValue(&data->image2, 0);
	if (elapsedTime >= 0.6f)
	{

		canShow = !canShow;
		elapsedTime = 0.0f;

	}

	if (canShow == true)
	{
		Image_SetAlphaValue(&data->image2, 255);

	}



}

void release_title(void)
{
	TitleSceneData* data = (TitleSceneData*)g_Scene.Data;
	Image_FreeImage(&data->image1);
	Image_FreeImage(&data->image2);


	SafeFree(g_Scene.Data);
}
#pragma endregion
	
#pragma region ruleScene


int32		Count;//카운트 값
#define TEXT_COUNT 3//문자열 카운트


typedef struct RuleSceneData
{
	Text Text[TEXT_COUNT];
	Image image;
	int32 Alpha;

} RuleSceneData;



void init_rule(void)
{
	g_Scene.Data = malloc(sizeof(RuleSceneData));
	memset(g_Scene.Data, 0, sizeof(RuleSceneData));

	RuleSceneData* data = (RuleSceneData*)g_Scene.Data;

	Image_LoadImage(&data->image, "index1.jpg");
	
	
}
void update_rule(void)
{
	RuleSceneData* data = (RuleSceneData*)g_Scene.Data;
	
	
	
	if (Input_GetKeyDown(VK_SPACE))
	{
		Scene_SetNextScene(SCENE_PROLOGUE);
	}

}

void render_rule(void)
{

	RuleSceneData* data = (RuleSceneData*)g_Scene.Data;
	data->Alpha = Clamp(0, data->Alpha++, 255);
	
	Image_FadedIn(&data->image, data->Alpha);
	
	Renderer_DrawImage(&data->image, 0, 0);
	

}

void release_rule(void)
{

	RuleSceneData* data = (RuleSceneData*)g_Scene.Data;
	Image_FreeImage(&data->image);

}
#pragma endregion

#pragma region PrologueScene

const wchar_t* str[] =
{
	L"전직 경찰로 다리에 부상을 입고 은퇴 후 보조금을 받으며 평범하게 살아가던 데이빗",
};


int32		Count;//카운트 값
#define TEXT_COUNT 3//문자열 카운트

typedef struct PrologueSceneData
{
	Text text[TEXT_COUNT];
	Image image;
	int32 Alpha;

} PrologueSceneData;



void init_prologue(void)
{
	g_Scene.Data = malloc(sizeof(PrologueSceneData));
	memset(g_Scene.Data, 0, sizeof(PrologueSceneData));

	PrologueSceneData* data = (PrologueSceneData*)g_Scene.Data;
	
	Image_LoadImage(&data->image, "index3.jpg");


}
void update_prologue(void)
{
	PrologueSceneData* data = (PrologueSceneData*)g_Scene.Data;

	Text_CreateMoveText(&data->text, "aM.ttf", 45, str[0], wcslen(str[0]), 2.0f);
	

	if (Input_GetKeyDown(VK_SPACE))
	{
		Scene_SetNextScene(SCENE_MAIN);
	}

}

void render_prologue(void)
{

	PrologueSceneData* data = (PrologueSceneData*)g_Scene.Data;

	data->Alpha = Clamp(0, data->Alpha++, 255);
	Image_FadedIn(&data->image, data->Alpha);
	Renderer_DrawImage(&data->image, 0, 0);
	SDL_Color color = { .r = 255, .g = 255, .b = 255 };
	Renderer_DrawTextBlended(&data->text, 200, 950, color);



}

void release_prologue(void)
{

	PrologueSceneData* data = (PrologueSceneData*)g_Scene.Data;
	Image_FreeImage(&data->image);
	Text_FreeText(&data->text);

}
#pragma endregion

#pragma region MainScene

const wchar_t* str2[] = 
{
	L"여기서는 사운드와 이미지 블렌딩에 대해서 알아봅시다.",
	L"화살표키로 이미지를 이동시킬 수 있습니다.",
	L"E키를 누르면 이펙트를 재생시킬 수 있습니다. 이펙트 소리가 작으니 볼륨을 낮춘 후 진행하세요.",
	L"M키로 음악을 끄거나 켤 수 있습니다.",
	L"P키로 음악을 멈추거나 재개할 수 있습니다.",
	L"1번과 2번으로 볼륨을 조절할 수 있습니다.",
	L"WASD로 이미지의 스케일을 조정할 수 있습니다.",
	L"KL키로 이미지의 투명도를 조절할 수 있습니다."
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
	char*		playMusic;
	float		Volume;
	Image		BackGround;
	int32		BackGroundX;
	int32		BackGroundY;
	int32		imageEffect;
	int32		textTime;
	int32		textSpeed;
	int32		textEffect;

	
	
	Text		text1;

	Text		text2;	

	int32		text3RedValue;
	int32		text3GreenValue;
	int32		text3BlueValue;
	int32		text3FontSize;
	bool		text3isITALIC;
	Text		text3;

	int32		select1X;
	int32		select1Y;

	Text		select1;
	int32		select2X;
	int32		select2Y;
	Text		select2;
	int32		select3X;
	int32		select3Y;
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
text1,
text1Effect,
text2,
text2Effect,
text3,
text3Effect,
select1,
select1Value,
select2,
select2Value,
select3,
select3Value
} mainSceneDataNumber;

static int32 sceneNum = 4;
static int32 prevSceneNum = 1;
Music backmusic;

void init_main(void)
{
	g_Scene.Data = malloc(sizeof(MainSceneData));
	memset(g_Scene.Data, 0, (sizeof(MainSceneData)));
	MainSceneData* data = (MainSceneData*)g_Scene.Data;

	data->index = ParseToInt(csvFile.Items[sceneNum][index]);

	if (ParseToAscii(csvFile.Items[sceneNum][BGMFileName])!="index1.mp3")
	{
		Audio_Stop();
		Audio_LoadMusic(&data->BGM, ParseToAscii(csvFile.Items[sceneNum][BGMFileName]));
		Audio_HookMusicFinished(logOnFinished);
		Audio_PlayFadeIn(&data->BGM, INFINITY_LOOP, 3000);	
	}

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
	
	//switch (data->selectCount)
	//{
	//case 2:
	//	Text_CreateText(&data->select1, FONT, TEXT_SIZE, ParseToUnicode(csvFile.Items[sceneNum][select1]), wcslen(ParseToUnicode(csvFile.Items[sceneNum][select1])));
	//	data->select1X = 100;
	//	data->select1Y = 100;
	//	Text_CreateText(&data->select2, FONT, TEXT_SIZE, ParseToUnicode(csvFile.Items[sceneNum][select2]), wcslen(ParseToUnicode(csvFile.Items[sceneNum][select2])));
	//	data->select2X = 100;
	//	data->select2Y = 100;
	//	break;
	//case 3:
	//	Text_CreateText(&data->select1, FONT, TEXT_SIZE, ParseToUnicode(csvFile.Items[sceneNum][select1]), wcslen(ParseToUnicode(csvFile.Items[sceneNum][select1])));
	//	data->select1X = 100;
	//	data->select1Y = 100;
	//	Text_CreateText(&data->select2, FONT, TEXT_SIZE, ParseToUnicode(csvFile.Items[sceneNum][select2]), wcslen(ParseToUnicode(csvFile.Items[sceneNum][select2])));
	//	data->select2X = 100;
	//	data->select2Y = 100;
	//	Text_CreateText(&data->select3, FONT, TEXT_SIZE, ParseToUnicode(csvFile.Items[sceneNum][select3]), wcslen(ParseToUnicode(csvFile.Items[sceneNum][select2])));
	//	data->select3X = 100;
	//	data->select3Y = 100;
	//	break;
	//default:
	//	break;
	//}


	data->text3RedValue = 255;
	data->text3GreenValue = 255;
	data->text3BlueValue = 255;

	switch (ParseToInt(csvFile.Items[sceneNum][text3Effect]))
	{
	case 1:
		data->text3RedValue = 213;
		data->text3GreenValue = 213;
		data->text3BlueValue = 213;
		data->text3FontSize = 23 * ONE_POINT_FIVE;
		data->text3isITALIC = false;
		break;
	case 2:
		data->text3FontSize = 27 * ONE_POINT_FIVE;
		data->text3isITALIC = false;
		break;
	case 3:
		data->text3FontSize = 36 * ONE_POINT_FIVE;
		data->text3isITALIC = true;
		break;
	case 4:
		data->text3FontSize = 27 * ONE_POINT_FIVE;
		data->text3isITALIC = true;
		break;
	case 5:
		data->text3RedValue = 166;
		data->text3GreenValue = 207;
		data->text3BlueValue = 244;
		data->text3FontSize = 27 * ONE_POINT_FIVE;
		data->text3isITALIC = false;
		break;
	case 6:
		data->text3GreenValue = 192;
		data->text3BlueValue = 0;
		data->text3FontSize = 27 * ONE_POINT_FIVE;
		data->text3isITALIC = false;
		break;
	case 7:
		data->text3GreenValue = 192;
		data->text3BlueValue = 0;
		data->text3FontSize = 27 * ONE_POINT_FIVE;
		data->text3isITALIC = true;
		break;
	case 8:
		data->text3GreenValue = 0;
		data->text3BlueValue = 0;
		data->text3FontSize = 27 * ONE_POINT_FIVE;
		data->text3isITALIC = false;
		break;
	case 9:
		data->text3GreenValue = 0;
		data->text3BlueValue = 0;
		data->text3FontSize = 27 * ONE_POINT_FIVE;
		data->text3isITALIC = true;
		break;
	case 10:
		data->text3GreenValue = 0;
		data->text3BlueValue = 0;
		data->text3FontSize = 36 * ONE_POINT_FIVE;
		data->text3isITALIC = true;
		break;
	default:
		
		data->text3FontSize = 27 * ONE_POINT_FIVE;
		data->text3isITALIC = false;
		break;
	}
	wchar_t* chr = ParseToUnicode(csvFile.Items[sceneNum][text1]);
	wchar_t* chr2 = ParseToUnicode(csvFile.Items[sceneNum][text2]);

	//if (chr != L"0")
		Text_CreateText(&data->text1, TEXT1_FONT, TEXT1_FONT_SIZE, ParseToUnicode(csvFile.Items[sceneNum][text1]), wcslen(ParseToUnicode(csvFile.Items[sceneNum][text1])));
	//if (chr2 != L"0")
		Text_CreateText(&data->text2, TEXT2_FONT, TEXT2_FONT_SIZE, ParseToUnicode(csvFile.Items[sceneNum][text2]), wcslen(ParseToUnicode(csvFile.Items[sceneNum][text2])));
	//if (ParseToUnicode(csvFile.Items[sceneNum][text3]) != 0)
		Text_CreateText(&data->text3, "aL.ttf", data->text3FontSize, ParseToUnicode(csvFile.Items[sceneNum][text3]), wcslen(ParseToUnicode(csvFile.Items[sceneNum][text3])));

	//Text_LoadText(&data->text1, ParseToAscii(csvFile.Items[sceneNum][textFileName1]));
	//Text_LoadText(&data->text2, ParseToAscii(csvFile.Items[sceneNum][textFileName2]));
	//Text_LoadText(&data->text3, ParseToAscii(csvFile.Items[sceneNum][textFileName3]));

	if (data->text3isITALIC)
		Text_SetFontStyle(&data->text3, FS_ITALIC);



	data->Volume = 1.0f;
	
	
	data->BackGroundX = 0;
	data->BackGroundY = 0;
	data->playerSelectValue = 1;
	
}

void update_main(void)
{
	MainSceneData* data = (MainSceneData*)g_Scene.Data;
	

	Text_CreateMoveText(&data->text1, "d2coding.ttf", 16, str2[0], wcslen(str2[0]), 2.0f);
	Text_CreateMoveText(&data->text2, "d2coding.ttf", 16, str2[1], wcslen(str2[1]), 2.0f);
	
	
	
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

	if (Input_GetKeyDown(VK_UP))
	{
		if (data->playerSelectValue > 1)
			--data->playerSelectValue;
	}
	
	if (Input_GetKeyDown(VK_DOWN))
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
	SDL_Color color3 = { .r = data->text3RedValue, .g = data->text3GreenValue, .b = data->text3BlueValue, .a = 255 };
	
	Renderer_DrawTextBlended(& data->text1, TEXT1_POS_X, TEXT1_POS_Y, color);

	Renderer_DrawTextBlended(&data->text2, TEXT2_POS_X - (data->text2.Length / 2 * (TEXT2_FONT_SIZE/1.5)), TEXT2_POS_Y, color);

	Renderer_DrawTextBlended(&data->text3, TEXT3_POS_X - (data->text3.Length / 2 * (data->text3FontSize/1.5)), TEXT3_POS_Y, color3);



}

void release_main(void)
{
	MainSceneData* data = (MainSceneData*)g_Scene.Data;
	
	Text_FreeText(&data->text1); 
	Text_FreeText(&data->text2);
	Text_FreeText(&data->text3);
	Image_FreeImage(&data->BackGround);
	Audio_FreeMusic(&data->BGM);
	if (ParseToAscii(csvFile.Items[sceneNum][BGMFileName]) != "index1.mp3")
		Audio_Play(&backmusic, INFINITY_LOOP);
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
	case SCENE_PROLOGUE:
		g_Scene.Init = init_prologue;
		g_Scene.Update = update_prologue;
		g_Scene.Render = render_prologue;
		g_Scene.Release = release_prologue;
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