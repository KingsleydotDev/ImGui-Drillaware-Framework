#pragma once
#define WINDOW_WIDTH  620
#define WINDOW_HEIGHT 470

extern bool loader_active;

namespace fonts {
    extern ImFont* font;
    extern ImFont* font2;
    extern ImFont* Main_Font;
    extern ImFont* Regylar;
    extern ImFont* icons;
    extern ImFont* ico_list;
    extern ImFont* ico;
}

namespace settings {
    extern int tab;
    extern bool check1, check2, check3, check4, check5, check6, check7;
    extern float sliderfloat;
    extern int sliderint;
    extern bool multi_items_count[5];
    extern const char* multi_items[5];
    extern int select;
    extern const char* items[3];
}

extern ImColor color_edit4;
extern ImVec4 accentcolor;
extern ImVec4 buttonhovercolor;
