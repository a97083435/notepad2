/******************************************************************************
*
*
* matepath - The universal Explorer-like Plugin
*
* matepath.h
*   Global definitions and declarations
*
* See Readme.txt for more information about this source code.
* Please send me your comments to this work.
*
* See License.txt for details about distribution and modification.
*
*                                              (c) Florian Balmer 1996-2011
*                                                  florian.balmer@gmail.com
*                                              https://www.flos-freeware.ch
*
*
******************************************************************************/
#pragma once

//==== Main Window ============================================================
#define WC_MATEPATH L"matepath"
#define WC_NOTEPAD4 L"Notepad4"
#define MY_APPUSERMODELID	L"matepath File Browser"

#define WS_MATEPATH ((WS_OVERLAPPEDWINDOW ^ \
					  (WS_MINIMIZEBOX | WS_MAXIMIZEBOX)) | \
					 (WS_CLIPCHILDREN | WS_POPUP))

//==== Data Type for WM_COPYDATA ==============================================
#define DATA_MATEPATH_PATHARG 0xFB30

//==== ComboBox Control =======================================================
//#define WC_COMBOBOX L"ComboBox"
#define WS_DRIVEBOX (WS_CHILD | \
					 /*WS_VISIBLE |*/ \
					 WS_CLIPSIBLINGS | \
					 WS_VSCROLL | \
					 CBS_DROPDOWNLIST)

//==== Listview Control =======================================================
#define WS_DIRLIST (WS_CHILD | \
					WS_VISIBLE | \
					WS_CLIPSIBLINGS | \
					WS_CLIPCHILDREN | \
					LVS_REPORT | \
					LVS_NOCOLUMNHEADER | \
					LVS_SHAREIMAGELISTS | \
					LVS_AUTOARRANGE | \
					LVS_SINGLESEL | \
					LVS_SHOWSELALWAYS)

//==== Toolbar Style ==========================================================
#define WS_TOOLBAR (WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | \
					TBSTYLE_TOOLTIPS | TBSTYLE_ALTDRAG | TBSTYLE_LIST | \
					CCS_NODIVIDER | CCS_NOPARENTALIGN)

//==== ReBar Style ============================================================
#define WS_REBAR (WS_CHILD | /*WS_VISIBLE |*/ WS_CLIPCHILDREN | WS_BORDER | \
				  RBS_VARHEIGHT | RBS_BANDBORDERS /*| RBS_FIXEDORDER */ | \
				  CCS_NODIVIDER |/*CCS_NORESIZE | */CCS_NOPARENTALIGN)

//==== Ids ====================================================================
#define IDC_STATUSBAR 0x00A0
#define IDC_TOOLBAR   0x00A1
#define IDC_REBAR     0x00A2
#define IDC_DRIVEBOX  0xA000
#define IDC_DIRLIST   0xA001

// submenu in popup menu, IDR_MAINWND
#define IDP_POPUP_SUBMENU_PATH	0
#define IDP_POPUP_SUBMENU_LIST	1
#define IDP_POPUP_SUBMENU_DRIVE	2
#define IDP_POPUP_SUBMENU_BAR	3
#define IDP_POPUP_SUBMENU_TRAY	4

//==== Statusbar ==============================================================
#define ID_FILEINFO		0
#define ID_MENUHELP		(255 | SBT_NOBORDERS)

//==== Timer for Change Notifications =========================================
#define ID_TIMER		0xA000

/**
 * App message used to center MessageBox to the window of the program.
 */
#define APPM_CENTER_MESSAGE_BOX		(WM_APP + 1)
#define APPM_TRAYMESSAGE			(WM_APP + 4) // Callback Message from System Tray

enum EscFunction {
	EscFunction_None = 0,
	EscFunction_Minimize,
	EscFunction_Exit,
};

enum StartupDirectory {
	StartupDirectory_None = 0,
	StartupDirectory_MRU,
	StartupDirectory_Favorite,
};

enum UseTargetApplication {
	UseTargetApplication_None = 0,
	UseTargetApplication_Use,
	UseTargetApplication_NotSet,
};

enum TargetApplicationMode {
	TargetApplicationMode_None = 0,
	TargetApplicationMode_SendMsg,
	TargetApplicationMode_UseDDE,
};

#define INI_SECTION_NAME_MATEPATH			L"matepath"
#define INI_SECTION_NAME_SETTINGS			L"Settings"
#define INI_SECTION_NAME_FLAGS				L"Settings2"
#define INI_SECTION_NAME_WINDOW_POSITION	L"Window Position"
#define INI_SECTION_NAME_TOOLBAR_LABELS		L"Toolbar Labels"
#define INI_SECTION_NAME_FILTERS			L"Filters"
#define INI_SECTION_NAME_TARGET_APPLICATION	L"Target Application"

#define MRU_KEY_COPY_MOVE_HISTORY			L"Copy/Move MRU"

#define MAX_INI_SECTION_SIZE_SETTINGS			(4 * 1024)
#define MAX_INI_SECTION_SIZE_FLAGS				(4 * 1024)
#define MAX_INI_SECTION_SIZE_TOOLBAR_LABELS		(2 * 1024)
#define MAX_INI_SECTION_SIZE_FILTERS			(4 * 1024)
#define MAX_INI_SECTION_SIZE_TARGET_APPLICATION	(4 * 1024)

//==== Function Declarations ==================================================
BOOL InitApplication(HINSTANCE hInstance) noexcept;
void InitInstance(HINSTANCE hInstance, int nCmdShow);
bool ActivatePrevInst() noexcept;
void GetRelaunchParameters(LPWSTR szParameters) noexcept;
void ShowNotifyIcon(HWND hwnd, bool bAdd) noexcept;

bool ChangeDirectory(HWND hwnd, LPCWSTR lpszNewDir, bool bUpdateHistory);
void SetUILanguage(int resID) noexcept;
void LoadSettings() noexcept;
void SaveSettingsNow() noexcept;
void SaveSettings(bool bSaveSettingsNow) noexcept;
void SaveWindowPosition(WCHAR *pIniSectionBuf) noexcept;
void ClearWindowPositionHistory() noexcept;
void ParseCommandLine() noexcept;
void LoadFlags() noexcept;
void LoadLaunchSetings() noexcept;

bool CheckIniFile(LPWSTR lpszFile, LPCWSTR lpszModule) noexcept;
bool CheckIniFileRedirect(LPWSTR lpszFile, LPCWSTR lpszModule) noexcept;
bool FindIniFile() noexcept;
bool TestIniFile() noexcept;
bool CreateIniFile(LPCWSTR lpszIniFile) noexcept;

bool DisplayPath(LPCWSTR lpPath, UINT uIdError);
bool DisplayLnkFile(LPCWSTR pszLnkFile, LPCWSTR pszResPath);

void LaunchTarget(LPCWSTR lpFileName, bool bOpenNew);
void SnapToTarget(HWND hwnd) noexcept;
void SnapToDefaultPos(HWND hwnd) noexcept;

LRESULT CALLBACK MainWndProc(HWND hwnd, UINT umsg, WPARAM wParam, LPARAM lParam);
LRESULT MsgCreate(HWND hwnd, WPARAM wParam, LPARAM lParam) noexcept;
void CreateBars(HWND hwnd, HINSTANCE hInstance) noexcept;
void MsgDPIChanged(HWND hwnd, WPARAM wParam, LPARAM lParam) noexcept;
void MsgThemeChanged(HWND hwnd, WPARAM wParam, LPARAM lParam) noexcept;
void MsgSize(HWND hwnd, WPARAM wParam, LPARAM lParam) noexcept;
void MsgInitMenu(HWND hwnd, WPARAM wParam, LPARAM lParam);
LRESULT MsgCommand(HWND hwnd, WPARAM wParam, LPARAM lParam);
LRESULT MsgNotify(HWND hwnd, WPARAM wParam, LPARAM lParam);
