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
<<<<<<< Updated upstream
	//CSVInit("°ÔÀÓºÏ CSV - ½ÃÆ®1.csv", scenedata);
	
 	CreateCsvFile(&csvFile,"°ÔÀÓºÏ CSV0 (1).csv");
=======
	//CSVInit("ï¿½ï¿½ï¿½Óºï¿½ CSV - ï¿½ï¿½Æ®1.csv", scenedata);
	
 	CreateCsvFile(&csvFile,"ï¿½ï¿½ï¿½Óºï¿½ CSV.csv");
>>>>>>> Stashed changes

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
	Text_CreateMoveText(&data->Text1, "d2coding.ttf", data->FontSize, L"T A K E N", 9,0.8f);

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
		titleElapsedTime = 0.0f;

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


<<<<<<< Updated upstream
int32		Count;//Ä«¿îÆ® °ª
#define TEXT_COUNT 3//¹®ÀÚ¿­ Ä«¿îÆ®
=======
int32		Count;//Ä«ï¿½ï¿½Æ® ï¿½ï¿½
#define TEXT_COUNT 3//ï¿½ï¿½ï¿½Ú¿ï¿½ Ä«ï¿½ï¿½Æ®
>>>>>>> Stashed changes


const wchar_t* ruleStr[] = {
	L"°Ô ÀÓ ¹æ ¹ý",
	L"- ¼±ÅÃÁö°¡ ¾ø´Â Àå¸éÀº ½ºÆäÀÌ½º¹Ù¸¦ ´©¸£¸é Àå¸éÀÌ ³Ñ¾î°©´Ï´Ù.",
	L"- ¼±ÅÃÁö°¡ ÀÖ´Â Àå¸éÀº ¹æÇâÅ°¿Í ½ºÆäÀÌ½º¹Ù¸¦ ÀÌ¿ëÇÏ¿© ¼±ÅÃÇÒ ¼ö ÀÖ½À´Ï´Ù."
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
	
<<<<<<< Updated upstream
	data->Alpha = Clamp(1, data->Alpha + 1, 255);// ÆäÀÌµå ÀÎ
	Renderer_DrawTextFade(&data->Text[0], 10, 30, data->Alpha);
	Renderer_DrawTextFade(&data->Text[1], 10, 600, data->Alpha);
	Renderer_DrawTextFade(&data->Text[2], 10, 630, data->Alpha);
=======

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
	L"ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½Ù¸ï¿½ï¿½ï¿½ ï¿½Î»ï¿½ï¿½ï¿½ ï¿½Ô°ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½Ï°ï¿½ ï¿½ï¿½Æ°ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½Ìºï¿½",
};


int32		Count;//Ä«ï¿½ï¿½Æ® ï¿½ï¿½
#define TEXT_COUNT 3//ï¿½ï¿½ï¿½Ú¿ï¿½ Ä«ï¿½ï¿½Æ®

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
>>>>>>> Stashed changes



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

<<<<<<< Updated upstream
=======
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



>>>>>>> Stashed changes
void logOnFinished(void)
{
	LogInfo("You can show this log on stopped the music");
}

void log2OnFinished(int32 channel)
{
	LogInfo("You can show this log on stopped the effect");
}
typedef struct MainSceneData

	Text		select1;
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
<<<<<<< Updated upstream
	Text		text2;	
=======

>>>>>>> Stashed changes

	Text		select1;
	int32		text3RedValue;
	int32		text3GreenValue;
	int32		text3BlueValue;
	int32		text3FontSize;
	bool		text3isITALIC;
	Text		text3;
	int32		text3Len;
	int32		text3LoadLen;
	float		text3speed;

	int32		select1X;
	int32		select1Y;
<<<<<<< Updated upstream
	Text		select1;
=======

	Image		select1;
>>>>>>> Stashed changes
	int32		select2X;
	int32		select2Y;
	Image		select2;
	int32		select3X;
	int32		select3Y;
	Image		select3;
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
	//1. ï¿½ï¿½ï¿½, 26p
	//2. ï¿½ï¿½ï¿½, 27p
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
	wchar_t* chr = ParseToUnicode(csvFile.Items[sceneNum][text1]);
	wchar_t* chr2 = ParseToUnicode(csvFile.Items[sceneNum][text2]);

	//if (chr != L"0")
		Text_CreateText(&data->text1, TEXT1_FONT, data->text1FontSize, ParseToUnicode(csvFile.Items[sceneNum][text1]), wcslen(ParseToUnicode(csvFile.Items[sceneNum][text1])));
	//if (chr2 != L"0")
		Text_CreateText(&data->text2, TEXT2_FONT, TEXT2_FONT_SIZE, ParseToUnicode(csvFile.Items[sceneNum][text2]), wcslen(ParseToUnicode(csvFile.Items[sceneNum][text2])));
	
	//Text_CreateText(&data->text3, "aL.ttf", data->text3FontSize, ParseToUnicode(csvFile.Items[sceneNum][text3]), wcslen(ParseToUnicode(csvFile.Items[sceneNum][text3])));


	//Text_LoadText(&data->text1, ParseToAscii(csvFile.Items[sceneNum][textFileName1]));
	//Text_LoadText(&data->text2, ParseToAscii(csvFile.Items[sceneNum][textFileName2]));
	//Text_LoadText(&data->text3, ParseToAscii(csvFile.Items[sceneNum][textFileName3]));

	if (data->text3isITALIC)
		Text_SetFontStyle(&data->text3, FS_ITALIC);


	data->Volume = 1.0f;
	

	Text_CreateMoveText(&data->text1, "d2coding.ttf", 16, str2[0], wcslen(str2[0]), 2.0f);
	Text_CreateMoveText(&data->text2, "d2coding.ttf", 16, str2[1], wcslen(str2[1]), 2.0f);
	
	
	
	data->playerSelectValue = 1;

	
	textElapsedtime = 0;
	
}

void update_main(void)
{
	MainSceneData* data = (MainSceneData*)g_Scene.Data;

<<<<<<< Updated upstream
=======
	
	
>>>>>>> Stashed changes
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
		if (data->playerSelectValue < data->selectCount)
			++data->playerSelectValue;
	}

	if (Input_GetKeyDown(VK_BACK))
	{
		sceneNum = prevSceneNum;
		
		Scene_SetNextScene(SCENE_MAIN);
	}
	textElapsedtime += Timer_GetDeltaTime();
	if (data->text3LoadLen != data->text3Len)
	{
		if (textElapsedtime >= data->text3speed)
		{
			textElapsedtime = 0;

			Text_CreateText(&data->text3, "aL.ttf", data->text3FontSize, ParseToUnicode(csvFile.Items[sceneNum][text3]), data->text3LoadLen);
		}

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