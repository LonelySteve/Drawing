// dllmain.h: 模块类的声明。

class CDrawingHandlersModule : public ATL::CAtlDllModuleT<CDrawingHandlersModule>
{
public :
	DECLARE_LIBID(LIBID_DrawingHandlersLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_DRAWINGHANDLERS, "{57c995f1-7cd6-4d2e-bcae-03a2ec9e8285}")
};

extern class CDrawingHandlersModule _AtlModule;
