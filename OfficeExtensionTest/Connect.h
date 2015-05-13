#pragma once

// class ID: {903518C9-04DF-4527-9844-E34585C53307}
extern const CLSID CLSID_Connect = { 0x903518c9, 0x4df, 0x4527, { 0x98, 0x44, 0xe3, 0x45, 0x85, 0xc5, 0x33, 0x7 } };


class ATL_NO_VTABLE Connect :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<Connect, &CLSID_Connect>,
	public IDispatchImpl < _IDTExtensibility2,
	&IID__IDTExtensibility2,
	&LIBID_AddInDesignerObjects, 1, 0 >
{
public:
	Connect();

	BEGIN_COM_MAP(Connect)
		COM_INTERFACE_ENTRY(IDTExtensibility2)
	END_COM_MAP()


public:
	//IDTExtensibility2.
	STDMETHOD(OnConnection)(
		IDispatch * Application, ext_ConnectMode ConnectMode,
		IDispatch *AddInInst, SAFEARRAY **custom);

	STDMETHOD(OnAddInsUpdate)(SAFEARRAY **custom);

	STDMETHOD(OnStartupComplete)(SAFEARRAY **custom);

	STDMETHOD(OnBeginShutdown)(SAFEARRAY **custom);

	STDMETHOD(OnDisconnection)(
		ext_DisconnectMode RemoveMode, SAFEARRAY **custom);
};
