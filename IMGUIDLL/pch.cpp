
#include "pch.h"


IDirect3DDevice9* g_pd3dDevice = nullptr;			//创建一个全局唯一D3D设备******

HWND 游戏窗口句柄 = NULL;                      //**********
ULONG64 MouDle1 = NULL;                        //********



Reset_t oReset;
EndScene_t oEndScene;




//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//[1](IMGUI配置)
ID3DXFont* g_FontSmall = nullptr;						//创建一个D3D绘制文本对象
IDirect3DStateBlock9* stateBlock = nullptr;
int FontSize = 17; // 字体大小
void CreatFont(IDirect3DDevice9* direct3ddevice9)
{
	if (FAILED(D3DXCreateFont(direct3ddevice9, FontSize, 0, FW_NORMAL, 1, FALSE, DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, DEFAULT_QUALITY, DEFAULT_PALETTE | FF_DONTCARE, L"微软雅黑", &g_FontSmall)))
	{
		MessageBox(NULL, L"字体创建失败，请重试", L"温馨提示", 0);
		exit(0);
	}
	direct3ddevice9->CreateStateBlock(D3DSBT_ALL, &stateBlock); // 保存当前渲染状态
	direct3ddevice9->SetRenderState(D3DRS_ALPHABLENDENABLE, 1);// 开启透明混合
	direct3ddevice9->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);// 设置目标混合
	direct3ddevice9->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);// 禁用深度测试
	direct3ddevice9->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);// 设置顶点格式
}

std::fstream _file;
void initialize_imgui(IDirect3DDevice9* direct3ddevice9)
{
	//IMGUI_CHECKVERSION();
	//ImGui::CreateContext();
	//ImGuiIO& io = ImGui::GetIO(); (void)io;
	////io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	//io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
	////io.IniFilename = nullptr;
	////io.WantSaveIniSettings = false;
	//io.IniFilename = NULL;
	//io.LogFilename = nullptr;

	//ImGui::StyleColorsLight();

	//ImFontConfig f_cfg;
	//f_cfg.FontDataOwnedByAtlas = false;
	//ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\msyh.ttc", 25.0f, nullptr, io.Fonts->GetGlyphRangesChineseFull());
	////IM_ASSERT(font != nullptr);                     //字体                                                //能显示中文

	//ImGui_ImplWin32_Init(游戏窗口句柄);
	//ImGui_ImplDX9_Init(direct3ddevice9);
	
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.IniFilename = nullptr;
	io.LogFilename = nullptr;

	ImGui::StyleColorsLight();
	ImGui_ImplWin32_Init(游戏窗口句柄);
	ImGui_ImplDX9_Init(direct3ddevice9);
	_file.open(FILENAME, std::ios::in);
	if (!_file)
	{
		ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\simsun.ttc", 10.0f, NULL, io.Fonts->GetGlyphRangesChineseFull());
	}
	else
	{
		ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\msyh.ttc", 14.0f, NULL, io.Fonts->GetGlyphRangesChineseFull());
	}
}

//[2](业务逻辑)
bool 内透开关, 隐藏菜单;//逻辑型
void 功能绘制()
{
	if (内透开关)
	{
		Show();
	}
	else {
		NoShow();
	}
}
void 菜单绘制()
{
	if (GetAsyncKeyState(VK_INSERT) != 0)
	{
		隐藏菜单 = !隐藏菜单;
	}
	if (隐藏菜单 == false)
	{
		ImGui::Begin(u8"   人机和谐");
		ImGui::StyleColorsClassic();
		ImGui::SameLine(305.0f);
		ImGui::Separator();
		if (ImGui::CollapsingHeader(u8"显示"))
		{
			ImGui::Checkbox(u8"内透开关", &内透开关);
			ImGui::SameLine();

		}

		ImGui::End();
	}

}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////





//二,
void BegingDraw()
{
	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
}
void EndDraw()
{
	ImGui::EndFrame();
	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
}
WNDPROC g_original_proc = nullptr;
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT __stdcall self_proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
		return true;

	return CallWindowProc(g_original_proc, hWnd, uMsg, wParam, lParam);
}
bool first_call = FALSE;
IDirect3DDevice9* g_Gamedirect3ddevice9;
HRESULT __stdcall hkEndScene(IDirect3DDevice9* direct3ddevice9)
{
	if (first_call == FALSE)
	{
		first_call = TRUE;
		g_Gamedirect3ddevice9 = direct3ddevice9;
		CreatFont(direct3ddevice9);
		initialize_imgui(direct3ddevice9);
		g_original_proc = (WNDPROC)SetWindowLongPtr(游戏窗口句柄, GWLP_WNDPROC, (LONG_PTR)self_proc);
	}
	Helpers::UnHookFunction((PVOID*)(&oEndScene), hkEndScene);

	BegingDraw();
	菜单绘制();//选择功能  
	功能绘制();//执行功能
	EndDraw();

	HRESULT result = direct3ddevice9->EndScene();
	Helpers::HookFunction((PVOID*)(&oEndScene), hkEndScene);
	return result;
}
//一,
HRESULT __stdcall hkReset(IDirect3DDevice9* direct3ddevice9, D3DPRESENT_PARAMETERS* pPresentationParameters)
{
	Helpers::UnHookFunction((PVOID*)(&oReset), hkReset);

	ImGui_ImplDX9_InvalidateDeviceObjects();
	HRESULT result = direct3ddevice9->Reset(pPresentationParameters);
	ImGui_ImplDX9_CreateDeviceObjects();

	Helpers::HookFunction((PVOID*)(&oReset), hkReset);
	return result;
}
//总,
void HookD3D()
{
	ULONG64* dDeviceVT = (ULONG64*)*(ULONG64*)g_pd3dDevice;
	oReset = (Reset_t)dDeviceVT[16]; //拿到第16个函数地址,保存起来以便于恢复
	oEndScene = (EndScene_t)dDeviceVT[42];//拿到第42个函数地址

	Helpers::HookFunction((PVOID*)(&oReset), hkReset);
	Helpers::HookFunction((PVOID*)(&oEndScene), hkEndScene);
}













void 地址初始化()
{
	MouDle1 = (unsigned __int64)GetModuleHandle(L"crossfire.exe");
}

IDirect3D9* g_Object = nullptr;					//创建一个D3D对象  
D3DPRESENT_PARAMETERS g_Params;					//创建一个D3D后台处理的类型
unsigned int __stdcall initialize_d3d9(HWND hwnd)
{
	g_Object = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_Object == FALSE)
	{
		MessageBox(NULL, L"Direct3D9创建失败", L"温馨提示", 0);
		exit(-1);
	}
	memset(&g_Params, 0, sizeof(g_Params));
	g_Params.Windowed = TRUE;
	g_Params.SwapEffect = D3DSWAPEFFECT_DISCARD;
	g_Params.BackBufferFormat = D3DFMT_UNKNOWN;
	g_Params.EnableAutoDepthStencil = TRUE;
	g_Params.AutoDepthStencilFormat = D3DFMT_D16;

	HRESULT result = g_Object->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hwnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING, &g_Params, &g_pd3dDevice);////
	printf("D3D创建返回值：%d\n", result);
	if (result != 0)
	{
		MessageBox(NULL, L"CreateDevice失败！", L"温馨提示", 0);
		exit(-1);
	}
	return 1;
}

void 初始化()
{
	while (游戏窗口句柄 == NULL)
	{
		游戏窗口句柄 = FindWindowA("CrossFire", "穿越火线");
		//游戏窗口句柄 = FindWindowA("Direct3DwindowClass", NULL);
	}

	if (initialize_d3d9(游戏窗口句柄) != 1) //先把设备D3D设备创建好
	{
		MessageBox(NULL, L"初始化D3D失败！", L"温馨提示", 0);
		exit(-1);
	}

	地址初始化();

	HookD3D();///////////

}