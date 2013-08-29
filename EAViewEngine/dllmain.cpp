// dllmain.cpp : Implementation of DllMain.

#include "stdafx.h"
#include "resource.h"
#include "EAViewEngine_i.h"
#include "dllmain.h"
#include "compreg.h"
#include "xdlldata.h"

CEAViewEngineModule _AtlModule;

class CEAViewEngineApp : public CWinApp
{
public:

// Overrides
	virtual BOOL InitInstance();
	virtual int ExitInstance();

	DECLARE_MESSAGE_MAP()
};

BEGIN_MESSAGE_MAP(CEAViewEngineApp, CWinApp)
END_MESSAGE_MAP()

CEAViewEngineApp theApp;

BOOL CEAViewEngineApp::InitInstance()
{
#ifdef _MERGE_PROXYSTUB
	if (!PrxDllMain(m_hInstance, DLL_PROCESS_ATTACH, NULL))
		return FALSE;
#endif
	return CWinApp::InitInstance();
}

int CEAViewEngineApp::ExitInstance()
{
	return CWinApp::ExitInstance();
}
