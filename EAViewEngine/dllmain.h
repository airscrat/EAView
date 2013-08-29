// dllmain.h : Declaration of module class.

class CEAViewEngineModule : public ATL::CAtlDllModuleT< CEAViewEngineModule >
{
public :
	DECLARE_LIBID(LIBID_EAViewEngineLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_EAVIEWENGINE, "{1BF79665-F923-4074-9057-FE4E78238552}")
};

extern class CEAViewEngineModule _AtlModule;
