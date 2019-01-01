// dllmain.cpp: DllMain 的实现。

#include "stdafx.h"
#include "resource.h"
#include "DrawingHandlers_i.h"
#include "dllmain.h"
#include "xdlldata.h"

CDrawingHandlersModule _AtlModule;

class CDrawingHandlersApp : public CWinApp
{
public:

// 重写
	virtual BOOL InitInstance();
	virtual int ExitInstance();

	DECLARE_MESSAGE_MAP()
};

BEGIN_MESSAGE_MAP(CDrawingHandlersApp, CWinApp)
END_MESSAGE_MAP()

CDrawingHandlersApp theApp;

BOOL CDrawingHandlersApp::InitInstance()
{
	if (!PrxDllMain(m_hInstance, DLL_PROCESS_ATTACH, nullptr))
		return FALSE;
	return CWinApp::InitInstance();
}

int CDrawingHandlersApp::ExitInstance()
{
	return CWinApp::ExitInstance();
}
