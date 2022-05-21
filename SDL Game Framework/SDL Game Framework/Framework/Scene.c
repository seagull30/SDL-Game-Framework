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

char* playMusicName;

void init_title(void)
{
	g_Scene.Data = malloc(sizeof(TitleSceneData));
	memset(g_Scene.Data, 0, sizeof(TitleSceneData));
	memset(&csvFile, 0, sizeof(CsvFile));
	
 	CreateCsvFile(&csvFile,"게임북 CSV.csv");

	Audio_LoadMusic(&backmusic, "index1.mp3");
	Audio_Play(&backmusic, INFINITY_LOOP);
	playMusicName = "index1.mp3";
	

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

	static float imageElapsedTime;
	imageElapsedTime += Timer_GetDeltaTime();
	Renderer_DrawImage(&data->image1, 0, 0);
	Renderer_DrawImage(&data->image2, 0, 95);
	Image_SetAlphaValue(&data->image2, 0);
	if (imageElapsedTime >= 0.6f)
	{

		canShow = !canShow;
		imageElapsedTime = 0.0f;

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
	float elapsedTime;
	int32 textLen;
	int32 textLoadLen;



} PrologueSceneData;



void init_prologue(void)
{
	g_Scene.Data = malloc(sizeof(PrologueSceneData));
	memset(g_Scene.Data, 0, sizeof(PrologueSceneData));

	PrologueSceneData* data = (PrologueSceneData*)g_Scene.Data;
	
	Image_LoadImage(&data->image, "index3.jpg");


	data->elapsedTime = 0;
	data->textLen = wcslen(str[0]);
	data->textLoadLen = 0;


}
void update_prologue(void)
{
	PrologueSceneData* data = (PrologueSceneData*)g_Scene.Data;

	
	

	if (Input_GetKeyDown(VK_SPACE))
	{
		Scene_SetNextScene(SCENE_MAIN);
	}

	data->elapsedTime += Timer_GetDeltaTime();
	if (data->textLoadLen != data->textLen)
	{
		if (data->elapsedTime >= 0.03f)
		{
			data->elapsedTime = 0;
			++data->textLoadLen;
			Text_CreateText(&data->text, "aM.ttf", 45, str[0], data->textLoadLen);
		}

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
	SoundEffect Effect;

	Image		BackGround;
	int32		BackGroundX;
	int32		BackGroundY;
	bool		BackGroundEffectisActive;
	int32		BackGroundEffectCount;
	int32		BackGroundEffectElasedTime;

	int32		imageEffect;

	int32		textEffect;

	Text		text1;
	int32		text1FontSize;

	Text		text2;	

	int32		text3RedValue;
	int32		text3GreenValue;
	int32		text3BlueValue;
	int32		text3FontSize;
	bool		text3isITALIC;
	Text		text3;
	int32		text3Delay;
	float		text3DelayElapsedtime;
	int32		text3Len;
	int32		text3LoadLen;
	float		text3Speed;
	float		text3Elapsedtime;

	bool		textIsShow;

	Image		select1;
	int32		select1X;
	int32		select1Y;
	Image		select2;
	int32		select2X;
	int32		select2Y;
	Image		select3;
	int32		select3X;
	int32		select3Y;

	int32		selectCount;
	int32		selectValue[3];
	int32		playerSelectValue;
} MainSceneData;

typedef enum mainSceneDataNumber
{
index,
BGMFileName,
EffectSound,
BackGroundFileName,
imageTime,
imageEffect,
textTime,
textSpeed,
text1,
text1Effect,
text2,
//text2Effect,
text3,
text3Effect,
select1,
select1Value,
select2,
select2Value,
select3,
select3Value
} mainSceneDataNumber;

static int32 sceneNum = 1;
static int32 prevSceneNum = 1;
Music backmusic;



void init_main(void)
{
	g_Scene.Data = malloc(sizeof(MainSceneData));
	memset(g_Scene.Data, 0, (sizeof(MainSceneData)));
	MainSceneData* data = (MainSceneData*)g_Scene.Data;

	data->index = ParseToInt(csvFile.Items[sceneNum][index]);
	char* nextBGMName = ParseToAscii(csvFile.Items[sceneNum][BGMFileName]);
	if (strcmp(nextBGMName, playMusicName) != 0)
	{
		Audio_FreeMusic(&backmusic);
		playMusicName = nextBGMName;
		Audio_LoadMusic(&backmusic, nextBGMName);
		Audio_HookMusicFinished(logOnFinished);
		Audio_Play(&backmusic, INFINITY_LOOP);
	}

	Image_LoadImage(&data->BackGround, ParseToAscii(csvFile.Items[sceneNum][BackGroundFileName]));

	data->selectCount = 0;
	for (int i = 0; i < 3; ++i)
	{
		int32 check = ParseToInt(csvFile.Items[sceneNum][select1Value + i * 2]);
		if (check != 0)
		{
			data->selectValue[i] = check;
			++data->selectCount;
		}
	}
	
	switch (data->selectCount)
	{
	case 2:
		Image_LoadImage(&data->select1, ParseToAscii(csvFile.Items[sceneNum][select1]));
		data->select1X = 580;
		data->select1Y = SELECT_POS_Y;
		Image_LoadImage(&data->select2, ParseToAscii(csvFile.Items[sceneNum][select2]));
		data->select2X = 985;
		data->select2Y = SELECT_POS_Y;
		break;
	case 3:
		Image_LoadImage(&data->select1, ParseToAscii(csvFile.Items[sceneNum][select1]));
		data->select1X = 380;
		data->select1Y = SELECT_POS_Y;
		Image_LoadImage(&data->select2, ParseToAscii(csvFile.Items[sceneNum][select2]));
		data->select2X = 785;
		data->select2Y = SELECT_POS_Y;
		Image_LoadImage(&data->select3, ParseToAscii(csvFile.Items[sceneNum][select3]));
		data->select3X = 1190;
		data->select3Y = SELECT_POS_Y;
		break;
	default:
		Image_LoadImage(&data->select1, ParseToAscii(csvFile.Items[sceneNum][select1]));
		data->select1X = 70;
		data->select1Y = 990;
		break;
	}
	data->text3RedValue = 255;
	data->text3GreenValue = 255;
	data->text3BlueValue = 255;

	switch (ParseToInt(csvFile.Items[sceneNum][text1Effect]))
	{

	case 2:
		data->text1FontSize = 27;
		break;
	default:
		data->text1FontSize = 26;
		break;
	}



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
	
		Text_CreateText(&data->text1, TEXT1_FONT, TEXT1_FONT_SIZE, ParseToUnicode(csvFile.Items[sceneNum][text1]), wcslen(ParseToUnicode(csvFile.Items[sceneNum][text1])));
	
		Text_CreateText(&data->text2, TEXT2_FONT, TEXT2_FONT_SIZE, ParseToUnicode(csvFile.Items[sceneNum][text2]), wcslen(ParseToUnicode(csvFile.Items[sceneNum][text2])));
		//Text_CreateText(&data->text3, "aL.ttf", data->text3FontSize, ParseToUnicode(csvFile.Items[sceneNum][text3]), wcslen(ParseToUnicode(csvFile.Items[sceneNum][text3])));

	
	if (data->text3isITALIC)
		Text_SetFontStyle(&data->text3, FS_ITALIC);

	data->imageEffect = ParseToInt(csvFile.Items[sceneNum][imageEffect]);
	
	switch (data->imageEffect)
	{
	case 1:
		data->BackGroundEffectCount = 6;
		data->BackGroundEffectElasedTime = 0;
		break;
	case 2:
		data->BackGroundEffectCount = 6;
		data->BackGroundEffectElasedTime = 0;
		break;
	default:
		break;
	}
	if (ParseToAscii(csvFile.Items[sceneNum][EffectSound])[0] != '0')
	{
		Audio_LoadSoundEffect(&data->Effect, ParseToAscii(csvFile.Items[sceneNum][EffectSound]));
		Audio_PlaySoundEffect(&data->Effect, 0);
	}

	data->Volume = 1.0f;
	
	
	data->BackGroundX = 0;
	data->BackGroundY = 0;
	data->playerSelectValue = 1;

	data->text3Len = wcslen(ParseToUnicode(csvFile.Items[sceneNum][text3]));
	data->text3LoadLen = 0;

	if (data->text3LoadLen == data->text3Len)
		data->textIsShow = true;
	else
		data->textIsShow = false;
	data->text3Delay = ParseToInt(csvFile.Items[sceneNum][textTime]);
	data->text3DelayElapsedtime = 0;
	data->text3Speed = ParseToFloat(csvFile.Items[sceneNum][textSpeed]);
	data-> text3Elapsedtime = 0;

}

void update_main(void)
{
	MainSceneData* data = (MainSceneData*)g_Scene.Data;

	if (Input_GetKeyDown('E'))
	{
		Audio_PlaySoundEffect(&data->Effect, 1);
	}

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

	//다음씬 및 출력속도 바꿔주기
	if (Input_GetKeyDown(VK_SPACE))
	{
		if (data->textIsShow)
		{
			prevSceneNum = sceneNum;
			sceneNum = data->selectValue[data->playerSelectValue - 1];
			Scene_SetNextScene(SCENE_MAIN);
		}
	}

	if (Input_GetKey(VK_SPACE))
	{

		data->text3Speed = 0.00f;
		//data->text3LoadLen = data->text3Len;
		//data->textIsShow = !data->textIsShow;
		//Text_CreateText(&data->text3, "aL.ttf", data->text3FontSize, ParseToUnicode(csvFile.Items[sceneNum][text3]), data->text3LoadLen);
	}

	if (Input_GetKeyUp(VK_SPACE))
	{
		data->text3Speed = ParseToFloat(csvFile.Items[sceneNum][textSpeed]);
	}

	//선택지 선택
	if (Input_GetKeyDown(VK_LEFT))
	{
		if (data->playerSelectValue > 1)
			--data->playerSelectValue;
	}

	if (Input_GetKeyDown(VK_RIGHT))
	{
		if (data->playerSelectValue < data->selectCount)
			++data->playerSelectValue;
	}

	//이전씬으로 돌아가기
	if (Input_GetKeyDown(VK_BACK))
	{
		sceneNum = prevSceneNum;

		Scene_SetNextScene(SCENE_MAIN);
	}

	// 1글자씩 출력
	data->text3DelayElapsedtime += Timer_GetDeltaTime();
	if (data->text3DelayElapsedtime >= data->text3Delay)
	{
		if (data->text3LoadLen != data->text3Len)
		{
			data->text3Elapsedtime += Timer_GetDeltaTime();
			if (data->text3Elapsedtime >= data->text3Speed)
			{
				data->text3Elapsedtime = 0;
				++data->text3LoadLen;
				Text_CreateText(&data->text3, "aL.ttf", data->text3FontSize, ParseToUnicode(csvFile.Items[sceneNum][text3]), data->text3LoadLen);
				if (data->text3LoadLen == data->text3Len)
					data->textIsShow = !data->textIsShow;
			}

		}
	}

	switch (data->playerSelectValue)
	{
	case 1:
		Image_SetAlphaValue(&data->select1, 255);
		Image_SetAlphaValue(&data->select2, 100);
		Image_SetAlphaValue(&data->select3, 100);
		break;
	case 2:
		Image_SetAlphaValue(&data->select1, 100);
		Image_SetAlphaValue(&data->select2, 255);
		Image_SetAlphaValue(&data->select3, 100);
		break;
	case 3:
		Image_SetAlphaValue(&data->select1, 100);
		Image_SetAlphaValue(&data->select2, 100);
		Image_SetAlphaValue(&data->select3, 255);
		break;
	default:
		break;
	}



}


void render_main(void)
{
	MainSceneData* data = (MainSceneData*)g_Scene.Data;

	Renderer_DrawImage(&data->BackGround, data->BackGroundX, data->BackGroundY);

	if (data->textIsShow)
	{

		Renderer_DrawImage(&data->select1, data->select1X, data->select1Y);
		Renderer_DrawImage(&data->select2, data->select2X, data->select2Y);
		Renderer_DrawImage(&data->select3, data->select3X, data->select3Y);

	}


	SDL_Color color = { .r = 255, .g = 255, .b = 255, .a = 255 };
	SDL_Color color3 = { .r = data->text3RedValue, .g = data->text3GreenValue, .b = data->text3BlueValue, .a = 255 };
	if (data->text3DelayElapsedtime >= data->text3Delay)
	{
		Renderer_DrawTextBlended(&data->text1, TEXT1_POS_X, TEXT1_POS_Y, color);

		Renderer_DrawTextBlended(&data->text2, TEXT2_POS_X - (data->text2.Length / 2 * (TEXT2_FONT_SIZE / 1.5)), TEXT2_POS_Y, color);

		Renderer_DrawTextBlended(&data->text3, TEXT3_POS_X - (data->text3.Length / 2 * (data->text3FontSize / 1.5)), TEXT3_POS_Y, color3);

	}



}

void release_main(void)
{
	MainSceneData* data = (MainSceneData*)g_Scene.Data;
	
	Text_FreeText(&data->text1); 
	Text_FreeText(&data->text2);
	Text_FreeText(&data->text3);
	Image_FreeImage(&data->BackGround);
	Audio_FreeSoundEffect(&data->Effect);
	Audio_FreeMusic(&data->BGM);
	//if (ParseToAscii(csvFile.Items[sceneNum][BGMFileName]) != "index1.mp3")
	//	Audio_Play(&backmusic, INFINITY_LOOP);
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