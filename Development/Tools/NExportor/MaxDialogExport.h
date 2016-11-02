#pragma once

class MaxDialogExport
{
public:
	MaxDialogExport();

	virtual ~MaxDialogExport();

	
public:
	// ��Ҫȥ��CALLBACK ������û����
	static INT_PTR CALLBACK MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );

	static void OnSkinChecked();

	static void OnMeshChecked();

	static INT_PTR CALLBACK QueryDialogMessage( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );
private:
	void BrowserOutputFolder( );
	void Export( );
	void QueryResourceName( );
	void SaveConfig( );
	void LoadConfig();
	bool CanSaveFile( NekoEngine::eResourceType Type, NekoEngine::WString& FinalFileName );
	void SerializeConfig( NekoEngine::PropertySerializer& Ser );
private:
	HWND mWindow;
};