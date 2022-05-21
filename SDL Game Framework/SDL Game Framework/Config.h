// Config.h : 각종 설정 매크로
#pragma once

// 창의 크기
#define WINDOW_WIDTH	1920
#define WINDOW_HEIGHT	1080

// 애셋 경로
#define IMAGE_DIRECTORY	"Asset/Image"
#define SOUND_DIRECTORY	"Asset/Sound"
#define FONT_DIRECTORY "Asset/Font"
#define TEXT_DIRECTORY "Asset/Txt"
#define DATA_DIRECTORY "Asset/Data"

// FPS
#define FPS				60

// Back Buffer 클리어할 때 색깔
#define CLEAR_COLOR_R	255
#define CLEAR_COLOR_G	255
#define CLEAR_COLOR_B	255
#define CLEAR_COLOR_A	255

#define SELECT_POS_Y 365

#define TEXT1_FONT "aB.ttf"
#define TEXT1_FONT_SIZE 23 * ONE_POINT_FIVE
#define TEXT1_POS_X 11
#define TEXT1_POS_Y 50

#define TEXT2_FONT TEXT1_FONT
#define TEXT2_FONT_SIZE 26* ONE_POINT_FIVE
#define TEXT2_POS_X 960
#define TEXT2_POS_Y 850

#define TEXT3_FONT "aL.ttf"
#define TEXT3_POS_X TEXT2_POS_X
#define TEXT3_POS_Y 930

#define ONE_POINT_FIVE	1.5