// Dear ImGui: standalone example application for DirectX 9
// If you are new to Dear ImGui, read documentation from the docs/ folder + read the top of imgui.cpp.
// Read online: https://github.com/ocornut/imgui/tree/master/docs

#include "imgui.h"
#include "imgui_impl_dx9.h"
#include "imgui_impl_win32.h"
#include <d3d9.h>
#include <tchar.h>
#include "main.h"
#include "Font.h"
#include <string>
#include "images.h"
#include <d3dx9.h>
#include "imgui_custom.h"
#pragma comment(lib, "d3dx9.lib")

#include "variables.h"

// Data
static LPDIRECT3D9              g_pD3D = NULL;
static LPDIRECT3DDEVICE9        g_pd3dDevice = NULL;
static D3DPRESENT_PARAMETERS    g_d3dpp = {};

// Forward declarations of helper functions
bool CreateDeviceD3D(HWND hWnd);
void CleanupDeviceD3D();
void ResetDevice();
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);


// Main code
int main(int, char**)
{
    // Create application window
    //ImGui_ImplWin32_EnableDpiAwareness();
    WNDCLASSEXW wc = { sizeof(wc), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, L"ImGui Example", NULL };
    ::RegisterClassExW(&wc);
    HWND hwnd = ::CreateWindowW(wc.lpszClassName, L"Dear ImGui DirectX9 Example", WS_OVERLAPPEDWINDOW, 100, 100, 1280, 800, NULL, NULL, wc.hInstance, NULL);

    // Initialize Direct3D
    if (!CreateDeviceD3D(hwnd))
    {
        CleanupDeviceD3D();
        ::UnregisterClassW(wc.lpszClassName, wc.hInstance);
        return 1;
    }

    // Show the window
    ::ShowWindow(hwnd, SW_SHOWDEFAULT);
    ::UpdateWindow(hwnd);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io; 
    ImGuiStyle& style = ImGui::GetStyle();
  
    
    style.Colors[ImGuiCol_WindowBg] = ImColor(12,12,12);
    style.Colors[ImGuiCol_ChildBg] = ImColor(9,9,9);
    style.Colors[ImGuiCol_Border] = ImColor(12, 12, 12, 0);
    style.Colors[ImGuiCol_FrameBg] = ImColor(18, 18, 18);
    style.Colors[ImGuiCol_TextSelectedBg] = ImColor(accentcolor);

    style.ChildRounding = 5.f;
    style.ItemSpacing = ImVec2(0, 0);
    ImGui::GetStyle().WindowPadding = ImVec2(0, 0);
    style.WindowRounding = 5.f;
    ImGui_ImplWin32_Init(hwnd);
    ImGui_ImplDX9_Init(g_pd3dDevice);
    
    fonts::font = io.Fonts->AddFontFromMemoryTTF(&Font, sizeof Font, 24.f, NULL, io.Fonts->GetGlyphRangesCyrillic());
    //fonts::font2 = io.Fonts->AddFontFromMemoryTTF(&Font, sizeof Font, 18.f, NULL, io.Fonts->GetGlyphRangesCyrillic());
    //fonts::Main_Font = io.Fonts->AddFontFromMemoryTTF(&Font, sizeof Font, 18.f, NULL, io.Fonts->GetGlyphRangesCyrillic());
    fonts::Regylar = io.Fonts->AddFontFromMemoryTTF(&Font1, sizeof Font1, 18.f, NULL, io.Fonts->GetGlyphRangesCyrillic());
    //fonts::icons = io.Fonts->AddFontFromMemoryTTF(&icon, sizeof icon, 28, NULL, io.Fonts->GetGlyphRangesCyrillic());
    //fonts::ico_list = io.Fonts->AddFontFromMemoryTTF(&icon2, sizeof(icon2), 18, NULL, io.Fonts->GetGlyphRangesCyrillic());
    //fonts::ico = io.Fonts->AddFontFromMemoryTTF(&iconc, sizeof(iconc), 26, NULL, io.Fonts->GetGlyphRangesCyrillic());
    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImColor(0,0,0);
    DWORD window_flags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBringToFrontOnFocus;
    RECT screen_rect;
    GetWindowRect(GetDesktopWindow(), &screen_rect);
    auto x = float(screen_rect.right - WINDOW_WIDTH) / 2.f;
    auto y = float(screen_rect.bottom - WINDOW_HEIGHT) / 2.f;

    // Main loop
    bool done = false;
    while (!done)
    {
        // Poll and handle messages (inputs, window resize, etc.)
        // See the WndProc() function below for our to dispatch events to the Win32 backend.
        MSG msg;
        while (::PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
        {
            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);
            if (msg.message == WM_QUIT)
                done = true;
        }
        if (done)
            break;

        // Start the Dear ImGui frame
        ImGui_ImplDX9_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();            
        {
            //ImGui::SetNextWindowPos(ImVec2(0, 400), ImGuiCond_Once);
            ImGui::SetNextWindowSize(ImVec2(WINDOW_WIDTH, WINDOW_HEIGHT));

            ImGui::Begin("DRILLAWARE", &loader_active, window_flags);
            {
                ImDrawList* draw = ImGui::GetWindowDrawList();
                const auto& p = ImGui::GetWindowPos();

                draw->AddRectFilled(ImVec2(p.x,p.y),ImVec2(p.x + 620, p.y + 50), ImColor(9,9,9), 5,ImDrawCornerFlags_Top);
                draw->AddRectFilled(ImVec2(p.x, p.y + 50), ImVec2(p.x + 620, p.y + 51), ImColor(18,18,18), 5);
                draw->AddRectFilled(ImVec2(p.x, p.y + 51), ImVec2(p.x + 140, p.y + 470), ImColor(9,9,9), 5, ImDrawCornerFlags_BotLeft);
                draw->AddText(fonts::font, 24, ImVec2(p.x + 14, p.y + 12), ImColor(255, 255, 255), ".");
                draw->AddText(fonts::font, 24, ImVec2(p.x + 18, p.y + 12), ImColor(accentcolor), "DRILLAWARE");

                ImGui::SetCursorPos(ImVec2(1, 55));
                ImGui::BeginGroup(); {

                    ImGui::TextLine("Main");
                    if (custom::tab("Host", 0 == settings::tab))
                        settings::tab = 0;             
                    if (custom::tab("Friends", 1 == settings::tab))
                        settings::tab = 1;
                    if (custom::tab("Players", 2 == settings::tab))
                        settings::tab = 2;
                    if (custom::tab("Trickshotting",  3 == settings::tab))
                        settings::tab = 3;
                    if (custom::tab("Tweaks", 4 == settings::tab))
                        settings::tab = 4;
                    ImGui::TextLine("Misc");
                    if (custom::tab("Profile", 5 == settings::tab))
                        settings::tab = 5;
                    if (custom::tab("About", 6 == settings::tab))
                        settings::tab = 6;

                }ImGui::EndGroup();

                if (settings::tab == 0) {
                    ImGui::SetCursorPos(ImVec2(150, 25));
                    custom::begin_child("Host", ImVec2(224, 435));
                    ImGui::SetCursorPos(ImVec2(10,40));
                    ImGui::BeginGroup(); {
                        ImGui::Checkbox("Enable DLC", &settings::check1);
                        ImGui::Checkbox("Anti Leave", &settings::check2);
                        ImGui::Checkbox("FFA Team Fix", &settings::check3);
                        ImGui::Checkbox("Disable Equipment", &settings::check4);                     

                    }ImGui::EndGroup();
                    custom::end_child();
                    ImGui::SetCursorPos(ImVec2(384, 25));
                    custom::begin_child("Lobby Settings", ImVec2(224, 435));
                    ImGui::SetCursorPos(ImVec2(10, 40));
                    ImGui::BeginGroup(); {
                        ImGui::PushFont(fonts::Regylar);
                        custom::combo("Select Map", &variables::map_list_number, variables::map_list, IM_ARRAYSIZE(variables::map_list), 5);
                        custom::button("Change Map", ImVec2(95, 25)); ImGui::SameLine(); custom::button("Fast Restart", ImVec2(95, 25));
                        custom::button("Match Settings", ImVec2(200, 25));
                        custom::button("Start Match", ImVec2(200, 25));
                        ImGui::PopFont();

                    }ImGui::EndGroup();
                    custom::end_child();
                }
                if (settings::tab == 1) {
                    ImGui::SetCursorPos(ImVec2(150, 25));
                    custom::begin_child("Friends", ImVec2(224, 435));
                    ImGui::SetCursorPos(ImVec2(10, 40));
                    ImGui::BeginGroup(); {
                        ImGui::PushFont(fonts::Regylar);
                        ImGui::InputText("Friend 1", variables::friend1, IM_ARRAYSIZE(variables::friend1));
                        ImGui::InputText("Friend 2", variables::friend2, IM_ARRAYSIZE(variables::friend2));
                        ImGui::InputText("Friend 3", variables::friend3, IM_ARRAYSIZE(variables::friend3));
                        ImGui::InputText("Friend 4", variables::friend4, IM_ARRAYSIZE(variables::friend4));
                        ImGui::PopFont();
                    }ImGui::EndGroup();
                    custom::end_child();
                }
                if (settings::tab == 2) {
                    ImGui::SetCursorPos(ImVec2(150, 25));
                    custom::begin_child("Kick Players", ImVec2(224, 435));
                    ImGui::SetCursorPos(ImVec2(10, 40));
                    ImGui::BeginGroup(); {
                        ImGui::PushFont(fonts::Regylar);
                        custom::button("Player1", ImVec2(95, 25)); ImGui::SameLine();custom::button("Player2", ImVec2(95, 25));
                        custom::button("Player3", ImVec2(95, 25)); ImGui::SameLine();custom::button("Player4", ImVec2(95, 25));
                        custom::button("Player5", ImVec2(95, 25)); ImGui::SameLine();custom::button("Player6", ImVec2(95, 25));
                        custom::button("Player7", ImVec2(95, 25)); ImGui::SameLine();custom::button("Player8", ImVec2(95, 25));
                        custom::button("Player9", ImVec2(95, 25)); ImGui::SameLine();custom::button("Player10", ImVec2(95, 25));
                        custom::button("Player11", ImVec2(95, 25)); ImGui::SameLine();custom::button("Player12", ImVec2(95, 25));
                        custom::button("Player13", ImVec2(95, 25)); ImGui::SameLine();custom::button("Player14", ImVec2(95, 25));
                        custom::button("Player15", ImVec2(95, 25)); ImGui::SameLine();custom::button("Player16", ImVec2(95, 25));
                        custom::button("Player17", ImVec2(95, 25)); ImGui::SameLine();custom::button("Player18", ImVec2(95, 25));
                        ImGui::PopFont();

                    }ImGui::EndGroup();
                    custom::end_child();
                }
                if (settings::tab == 3) {
                    ImGui::SetCursorPos(ImVec2(150, 25));
                    custom::begin_child("Trickshotting", ImVec2(224, 435));
                    ImGui::SetCursorPos(ImVec2(10, 40));
                    ImGui::BeginGroup(); {
                        ImGui::PushFont(fonts::Regylar);
                        ImGui::SliderFloat("Ladder Cap", &variables::fLadderCap, 100.0f, 360.0f, "% .1f");
                        ImGui::SliderFloat("Prone Cap", &variables::fProneCap, 85.0f, 360.0f, "% .1f");

                        ImGui::PopFont();
                    }ImGui::EndGroup();
                    custom::end_child();
                    ImGui::SetCursorPos(ImVec2(384, 25));
                    custom::begin_child("Trickshotting 2", ImVec2(224, 435));
                    ImGui::SetCursorPos(ImVec2(10, 40));
                    ImGui::BeginGroup(); {
                        ImGui::PushFont(fonts::Regylar);
                        ImGui::PopFont();

                    }ImGui::EndGroup();
                    custom::end_child();
                }
                if (settings::tab == 4) {
                    ImGui::SetCursorPos(ImVec2(150, 25));
                    custom::begin_child("Tweaks", ImVec2(224, 435));
                    ImGui::SetCursorPos(ImVec2(10, 40));
                    ImGui::BeginGroup(); {
                        ImGui::SliderInt("Frames Per Second", &variables::iFPS, 125, 333);
                        ImGui::SliderFloat("Field Of View", &variables::fFieldOfView, 65.0f, 120.0f, "%.1f");
                        ImGui::Checkbox("Third Person", &variables::bThirdPerson);
                    }ImGui::EndGroup();
                    custom::end_child();
                    ImGui::SetCursorPos(ImVec2(384, 25));
                    custom::begin_child("Tweaks 2", ImVec2(224, 435));
                    
                    ImGui::SetCursorPos(ImVec2(10, 40));
                    ImGui::BeginGroup(); {
                        ImGui::PushFont(fonts::Regylar);
                        ImGui::PopFont();

                    }ImGui::EndGroup();
                    custom::end_child();
                }
                if (settings::tab == 5) {
                    ImGui::SetCursorPos(ImVec2(150, 25));
                    custom::begin_child("Account", ImVec2(224, 435));
                    ImGui::SetCursorPos(ImVec2(10, 40));
                    ImGui::BeginGroup(); {
                        ImGui::PushFont(fonts::Regylar);
                        ImGui::SliderInt("Prestige", &variables::iPrestige, 0, 11);
                        custom::button("Send Prestige", ImVec2(200, 25));
                        custom::button("Level 70", ImVec2(200, 25));
                        ImGui::PopFont();
                    }ImGui::EndGroup();
                    custom::end_child();
                }
                if (settings::tab == 6) {
                    ImGui::SetCursorPos(ImVec2(150, 25));
                    custom::begin_child("About", ImVec2(224, 435));
                    ImGui::SetCursorPos(ImVec2(10, 40));
                    ImGui::BeginGroup(); {
                        ImGui::PushFont(fonts::Regylar);
                        ImGui::Text("Thank you to Josh/@GRIIMtB");
                        ImGui::Text("More features to be added");
                        ImGui::Text("soon. ");
                        ImGui::PopFont();
                    }ImGui::EndGroup();
                    custom::end_child();
                    ImGui::SetCursorPos(ImVec2(384, 25));
                    custom::begin_child("Misc", ImVec2(224, 435));
                    ImGui::SetCursorPos(ImVec2(10, 40));
                    ImGui::BeginGroup(); {
                        ImGui::PushFont(fonts::Regylar);
                        //ImGui::Text("Accent Color");
                        //ImGui::ColorEdit4("##Accent color", (float*)&accentcolor, ImGuiColorEditFlags_AlphaPreview | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoTooltip);
                        ImGui::PopFont();

                    }ImGui::EndGroup();
                    custom::end_child();
                }
            }ImGui::End();
        }

     
        ImGui::EndFrame();
        g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
        g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
        g_pd3dDevice->SetRenderState(D3DRS_SCISSORTESTENABLE, FALSE);
        D3DCOLOR clear_col_dx = D3DCOLOR_RGBA((int)(clear_color.x*clear_color.w*255.0f), (int)(clear_color.y*clear_color.w*255.0f), (int)(clear_color.z*clear_color.w*255.0f), (int)(clear_color.w*255.0f));
        g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, clear_col_dx, 1.0f, 0);
        if (g_pd3dDevice->BeginScene() >= 0)
        {
            ImGui::Render();
            ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
            g_pd3dDevice->EndScene();
        }
        HRESULT result = g_pd3dDevice->Present(NULL, NULL, NULL, NULL);

        // Handle loss of D3D9 device
        if (result == D3DERR_DEVICELOST && g_pd3dDevice->TestCooperativeLevel() == D3DERR_DEVICENOTRESET)
            ResetDevice();
    }

    ImGui_ImplDX9_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    CleanupDeviceD3D();
    ::DestroyWindow(hwnd);
    ::UnregisterClassW(wc.lpszClassName, wc.hInstance);

    return 0;
}

// Helper functions

bool CreateDeviceD3D(HWND hWnd)
{
    if ((g_pD3D = Direct3DCreate9(D3D_SDK_VERSION)) == NULL)
        return false;

    // Create the D3DDevice
    ZeroMemory(&g_d3dpp, sizeof(g_d3dpp));
    g_d3dpp.Windowed = TRUE;
    g_d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    g_d3dpp.BackBufferFormat = D3DFMT_UNKNOWN; // Need to use an explicit format with alpha if needing per-pixel alpha composition.
    g_d3dpp.EnableAutoDepthStencil = TRUE;
    g_d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
    g_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;           // Present with vsync
    //g_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;   // Present without vsync, maximum unthrottled framerate
    if (g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &g_d3dpp, &g_pd3dDevice) < 0)
        return false;

    return true;
}

void CleanupDeviceD3D()
{
    if (g_pd3dDevice) { g_pd3dDevice->Release(); g_pd3dDevice = NULL; }
    if (g_pD3D) { g_pD3D->Release(); g_pD3D = NULL; }
}

void ResetDevice()
{
    ImGui_ImplDX9_InvalidateDeviceObjects();
    HRESULT hr = g_pd3dDevice->Reset(&g_d3dpp);
    if (hr == D3DERR_INVALIDCALL)
        IM_ASSERT(0);
    ImGui_ImplDX9_CreateDeviceObjects();
}

// Forward declare message handler from imgui_impl_win32.cpp
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// Win32 message handler
// You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
// - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
// - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
// Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
        return true;

    switch (msg)
    {
    case WM_SIZE:
        if (g_pd3dDevice != NULL && wParam != SIZE_MINIMIZED)
        {
            g_d3dpp.BackBufferWidth = LOWORD(lParam);
            g_d3dpp.BackBufferHeight = HIWORD(lParam);
            ResetDevice();
        }
        return 0;
    case WM_SYSCOMMAND:
        if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
            return 0;
        break;
    case WM_DESTROY:
        ::PostQuitMessage(0);
        return 0;
    }
    return ::DefWindowProc(hWnd, msg, wParam, lParam);
}
