﻿// ThumbnailHandler.h : 缩略图处理程序的声明

#pragma once
#include "resource.h"       // 主符号

#include <atlhandler.h>
#include <atlhandlerimpl.h>
#include "..\Drawing\DrawingDoc.h"
#include "DrawingHandlers_i.h"

using namespace ATL;

// CThumbnailHandler

class ATL_NO_VTABLE CThumbnailHandler :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CThumbnailHandler, &CLSID_Thumbnail>,
	public CThumbnailProviderImpl
{
public:
	CThumbnailHandler()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_THUMBNAIL_HANDLER)
DECLARE_NOT_AGGREGATABLE(CThumbnailHandler)

BEGIN_COM_MAP(CThumbnailHandler)
	COM_INTERFACE_ENTRY(IInitializeWithStream)
	COM_INTERFACE_ENTRY(IThumbnailProvider)
END_COM_MAP()

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
		CThumbnailProviderImpl::FinalRelease();
	}

protected:
	virtual HRESULT GetBitmap(UINT cx, HBITMAP *phbmp, WTS_ALPHATYPE *pdwAlpha)
	{
		if (m_pDocument == nullptr)
		{
			return E_NOTIMPL;
		}

		// 实现 IDocument 派生类中的 OnDrawThumbnail
		static int const nDocDimensions = 256;
		if (!m_pDocument->GetThumbnail(nDocDimensions, phbmp, pdwAlpha))
		{
			return E_FAIL;
		}

		return S_OK;
	}

	DECLARE_DOCUMENT(CDrawingDoc)
};

OBJECT_ENTRY_AUTO(__uuidof(Thumbnail), CThumbnailHandler)
