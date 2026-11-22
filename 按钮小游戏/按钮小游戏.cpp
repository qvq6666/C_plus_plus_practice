#include "raylib.h"
#include <fstream>
using namespace std;
int game_scene = 0;

// 全部用到的汉字Unicode码点
int cnCodePoints[] = {
    0x9000,0x51FA,0x6E38,0x620F, // 退 出 游 戏
    25353,38062,23567,28216,25103, 
    28857,25105,65281,
    20998,25968,
    26368,39640,20998,25968,
    37325,32622,26368,39640,20998
};
int cnCodeCount = sizeof(cnCodePoints)/sizeof(int);
Font cnFontSmall; // 按钮小字
Font cnFontBig;   // 标题大字
Vector2 MeasureTextCodepointsCompat(Font font, const int* codepoints, int count, float fontSize, float spacing){
    float width = 0.0f;
    float maxHeight = 0.0f;
    for(int i = 0; i < count; i++){
        GlyphInfo g = GetGlyphInfo(font, codepoints[i]);
        float gw = (float)g.advanceX * fontSize / (float)font.baseSize;
        float gh = (float)g.image.height * fontSize / (float)font.baseSize;
        width += gw;
        if(i != count - 1) width += spacing;
        if(gh > maxHeight) maxHeight = gh;
    }
    return {width, maxHeight};
}

struct Button{
    Rectangle rect;//位置大小
    int* codeArr;//文字
    int codeLen;//文字字数
    int fontSize;//字体大小
    int thickness;//黑框大小
    Color normalColor;//普通状态颜色
    Color hoverColor;//碰到颜色
    Color pressColor;//点击颜色
    bool isHover;//是否碰到？
    bool isClick;//是否点击？
};

void ButtonUpdate(Button& btn){
    Vector2 mouse = GetMousePosition();//获取鼠标位置
    btn.isHover = CheckCollisionPointRec(mouse,btn.rect);//是否碰到了按钮？
    btn.isClick = btn.isHover && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);//是否点击了按钮？
}

void ButtonDraw(Button& btn, Font font){
    Color drawColor = btn.normalColor;
    if(btn.isHover) drawColor = btn.hoverColor;
    if(btn.isHover && IsMouseButtonDown(MOUSE_LEFT_BUTTON)) drawColor = btn.pressColor;

    DrawRectangleRec(btn.rect, drawColor);
    DrawRectangleLinesEx(btn.rect,btn.thickness,BLACK);
    int fontsize = btn.fontSize;
    float space = 2.0f;
    Vector2 textSize = MeasureTextCodepointsCompat(font, btn.codeArr, btn.codeLen, fontsize, space);
    DrawTextCodepoints(
        font, btn.codeArr, btn.codeLen,{
            btn.rect.x + (btn.rect.width - textSize.x)/2,
            btn.rect.y + (btn.rect.height - textSize.y)/2
        },
        fontsize, space, BLACK
    );
}
int high_score(){
    //获取Fraction_high.txt的数据
    int high = 0;
    std::ifstream fin("Fraction_high.txt");
    if (fin.is_open()){
        fin>>high;
    }
    fin.close();
    return high;
}
int new_high_score(int new_high){
    //new_high参数用来跟Fraction_high.txt的数据比较，如果大替换
    int high = high_score();
    if (high < new_high){
        std::ofstream fin("Fraction_high.txt");
        if (fin.is_open()){
            fin<<new_high;
        }
        fin.close();
    }
    return 0;
}
int main(){
    int W = 1920;
    int H = 1080;
    InitWindow(W,H,"按钮小游戏");
    SetExitKey(KEY_NULL);
    SetTargetFPS(60);
    SetTraceLogLevel(LOG_NONE);
    // 两套字体：按钮用64基础，标题用256基础
    cnFontSmall = LoadFontEx("SourceHanSansSC-Heavy.otf",64,cnCodePoints, cnCodeCount);
    cnFontBig   = LoadFontEx("SourceHanSansSC-Heavy.otf",256,cnCodePoints, cnCodeCount);

    int score_plus_Btn_TextCode[] = {28857,25105,65281};
    Button score_plus_Btn = {
        {800,450,300,80},
        score_plus_Btn_TextCode,
        sizeof(score_plus_Btn_TextCode)/sizeof(int),
        60,
        6,
        Color{30,144,255,255},
        Color{100,180,255,255},
        Color{0,40,110,255},
        false, false
    };
    int exit_TextCode[] = {0x9000,0x51FA,0x6E38,0x620F}; 
    Button game_exit = {
        {800,600,300,80},
        exit_TextCode,
        sizeof(exit_TextCode)/sizeof(int),
        60,
        6,
        Color{30,144,255,255},
        Color{100,180,255,255},
        Color{0,40,110,255},
        false, false
    };
    int High_score_btn_text[] = {37325,32622,26368,39640,20998};
    Button High_score_0_btn = {
        {0,120,300,80},
        High_score_btn_text,
        sizeof(High_score_btn_text)/sizeof(int),
        60,
        6,
        Color{30,144,255,255},
        Color{100,180,255,255},
        Color{0,40,110,255},
        false, false
    };
    int score_0_btn_text[] = {37325,32622,20998,25968};
    Button score_0_btn = {
        {0,20,300,80},
        score_0_btn_text,
        sizeof(score_0_btn_text)/sizeof(int),
        60,
        6,
        Color{30,144,255,255},
        Color{100,180,255,255},
        Color{0,40,110,255},
        false, false
    };
    int titleCode[] = {25353,38062,23567,28216,25103};
    int titleCnt = sizeof(titleCode)/sizeof(int);
    float Wait_time = 0.0f;
    float wait_y = 500;
    bool Yes_no_Wait = false;
    int score = 0;
    int High_score = high_score();
    while(!WindowShouldClose()){
        float gt = GetFrameTime();
        ButtonUpdate(score_plus_Btn);
        ButtonUpdate(game_exit);
        ButtonUpdate(High_score_0_btn);
        ButtonUpdate(score_0_btn);
        if(score_plus_Btn.isClick){
            score += 1;
            Yes_no_Wait = true;
        }
        if (game_exit.isClick){
            break;
        }
        if (High_score_0_btn.isClick){
            std::ofstream fin("Fraction_high.txt");
            if (fin.is_open()){
                fin<<0;
            }
            fin.close();
            High_score = 0;
        }
        if (score_0_btn.isClick){
            score = 0;
        }
        if (score >= 9999){
            score = 9999;
        }
        if (High_score >= 9999){
            High_score = 9999;
        }
        if (Yes_no_Wait){
            Wait_time = 0.3f;
            wait_y = 450;
            Yes_no_Wait = false;
        }
        BeginDrawing();
        ClearBackground(WHITE);
        if (Wait_time > 0.0f){
            wait_y -= 300.0f * gt;
            DrawText("+1",300,wait_y,100,RED);
            Wait_time -= gt;
        }

        
        DrawTextCodepoints(cnFontBig,titleCode,titleCnt,{625,200},200,2,GREEN);
        int titleCode2[] = {20998,25968};
        int titleCnt2 = sizeof(titleCode2)/sizeof(int);
        
        if (score>High_score){
            DrawTextCodepoints(cnFontBig,titleCode2,titleCnt2,{250,500},100,2,GOLD);
            DrawText(TextFormat(":%d",score),400,518,85,GOLD);
        }
        else{
            DrawTextCodepoints(cnFontBig,titleCode2,titleCnt2,{250,500},100,2,BLACK);
            DrawText(TextFormat(":%d",score),400,518,85,BLACK);
        }
        
        int titleCode3[] = {26368,39640,20998,25968};
        int titleCnt3 = sizeof(titleCode3)/sizeof(int);
        DrawTextCodepoints(cnFontBig,titleCode3,titleCnt3,{250,600},100,2,BLACK);
        DrawText(TextFormat(":%d",High_score),550,618,85,BLACK);
        ButtonDraw(score_plus_Btn,cnFontSmall);
        ButtonDraw(game_exit,cnFontSmall);
        ButtonDraw(High_score_0_btn,cnFontSmall);
        ButtonDraw(score_0_btn,cnFontSmall);
        EndDrawing();
    }
    
    new_high_score(score);
    UnloadFont(cnFontSmall);
    UnloadFont(cnFontBig);
    CloseWindow();
    return 0;
}