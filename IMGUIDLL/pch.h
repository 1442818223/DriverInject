
#include <windows.h>
#include <vector>
#include<d3d9.h>//////////必加
#include <d3dx9.h>//////////必加
#include <fstream>


#include"IM/imconfig.h"
#include"IM/imgui.h"
#include"IM/imgui_impl_dx9.h"
#include"IM/imgui_impl_win32.h"
#include"IM/imgui_internal.h"
#include"IM/imstb_rectpack.h"
#include"IM/imstb_textedit.h"
#include"IM/imstb_truetype.h"

#include"IM/detours.h" //必须找到detour里面的include文件拉进来 
#include"IM/detver.h"

#include "读写.h"
#include "Helpers.hpp"

#pragma comment(lib,"d3d9.lib")//////////必加
#pragma comment(lib,"d3dx9.lib")//////////必加
#pragma comment(lib,"detours.lib")


typedef HRESULT(WINAPI* Reset_t)(LPDIRECT3DDEVICE9, D3DPRESENT_PARAMETERS*); //19
typedef long(__stdcall* EndScene_t)(LPDIRECT3DDEVICE9);                      //42


#define FILENAME "c:\\Windows\\Fonts\\msyh.ttc"

void 初始化();

extern ULONG64 MouDle1;