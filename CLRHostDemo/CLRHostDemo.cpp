#pragma region Includes and Imports

#include "stdafx.h"
#include <windows.h>

#include <metahost.h>
#pragma comment(lib, "mscoree.lib")

// Import mscorlib.tlb (Microsoft Common Language Runtime Class Library).
#import "mscorlib.tlb" raw_interfaces_only				\
    high_property_prefixes("_get","_put","_putref")		\
    rename("ReportEvent", "InteropServices_ReportEvent")
using namespace mscorlib;
#pragma endregion

void CleanUp(ICLRMetaHost *pMetaHost, ICLRRuntimeInfo *pRuntimeInfo, ICLRRuntimeHost *pClrRuntimeHost);

int _tmain(int argc, _TCHAR* argv[])
{

	PCWSTR pszVersion = L"v4.0.30319";

	PCWSTR pszAssemblyPath = L"ManangedLib.dll";

	PCWSTR pszClassName = L"ManangedLib.TestClass";

	HRESULT hr;

	ICLRMetaHost *pMetaHost = NULL;
	ICLRRuntimeInfo *pRuntimeInfo = NULL;

	// ICorRuntimeHost and ICLRRuntimeHost are the two CLR hosting interfaces
	// supported by CLR 4.0. Here we demo the ICLRRuntimeHost interface that 
	// was provided in .NET v2.0 to support CLR 2.0 new features. 
	// ICLRRuntimeHost does not support loading the .NET v1.x runtimes.
	ICLRRuntimeHost *pClrRuntimeHost = NULL;

	// The static method in the .NET class to invoke.
	PCWSTR pszStaticMethodName = L"OnStart";
	PCWSTR pszStringArg = L"Hello World";
	DWORD dwLengthRet;

	// 
	// Load and start the .NET runtime.
	// 

	wprintf(L"Load and start the .NET runtime %s \n", pszVersion);

	hr = CLRCreateInstance(CLSID_CLRMetaHost, IID_PPV_ARGS(&pMetaHost));

	if (FAILED(hr))
	{
		wprintf(L"CLRCreateInstance failed w/hr 0x%08lx\n", hr);

		CleanUp(pMetaHost, pRuntimeInfo, pClrRuntimeHost);

		return -1;
	}

	// Get the ICLRRuntimeInfo corresponding to a particular CLR version. It 
	// supersedes CorBindToRuntimeEx with STARTUP_LOADER_SAFEMODE.
	hr = pMetaHost->GetRuntime(pszVersion, IID_PPV_ARGS(&pRuntimeInfo));

	if (FAILED(hr))
	{
		wprintf(L"ICLRMetaHost::GetRuntime failed w/hr 0x%08lx\n", hr);

		CleanUp(pMetaHost, pRuntimeInfo, pClrRuntimeHost);

		return -1;
	}

	// Check if the specified runtime can be loaded into the process. This 
	// method will take into account other runtimes that may already be 
	// loaded into the process and set pbLoadable to TRUE if this runtime can 
	// be loaded in an in-process side-by-side fashion. 
	BOOL fLoadable;

	hr = pRuntimeInfo->IsLoadable(&fLoadable);

	if (FAILED(hr))
	{
		wprintf(L"ICLRRuntimeInfo::IsLoadable failed w/hr 0x%08lx\n", hr);

		CleanUp(pMetaHost, pRuntimeInfo, pClrRuntimeHost);

		return -1;
	}

	if (!fLoadable)
	{
		wprintf(L".NET runtime %s cannot be loaded\n", pszVersion);

		CleanUp(pMetaHost, pRuntimeInfo, pClrRuntimeHost);

		return -1;
	}

	// Load the CLR into the current process and return a runtime interface 
	// pointer. ICorRuntimeHost and ICLRRuntimeHost are the two CLR hosting  
	// interfaces supported by CLR 4.0. Here we demo the ICLRRuntimeHost 
	// interface that was provided in .NET v2.0 to support CLR 2.0 new 
	// features. ICLRRuntimeHost does not support loading the .NET v1.x 
	// runtimes.
	hr = pRuntimeInfo->GetInterface(
		CLSID_CLRRuntimeHost,
		IID_PPV_ARGS(&pClrRuntimeHost));

	if (FAILED(hr))
	{
		wprintf(L"ICLRRuntimeInfo::GetInterface failed w/hr 0x%08lx\n", hr);

		CleanUp(pMetaHost, pRuntimeInfo, pClrRuntimeHost);

		return -1;
	}

	// Start the CLR.
	hr = pClrRuntimeHost->Start();
	if (FAILED(hr))
	{
		wprintf(L"CLR failed to start w/hr 0x%08lx\n", hr);

		CleanUp(pMetaHost, pRuntimeInfo, pClrRuntimeHost);

		return -1;
	}

	// 
	// Load the NET assembly and call the static method GetStringLength of 
	// the type CSSimpleObject in the assembly.
	// 

	wprintf(L"Load the assembly %s\n", pszAssemblyPath);

	// The invoked method of ExecuteInDefaultAppDomain must have the 
	// following signature: static int pwzMethodName (String pwzArgument)
	// where pwzMethodName represents the name of the invoked method, and 
	// pwzArgument represents the string value passed as a parameter to that 
	// method. If the HRESULT return value of ExecuteInDefaultAppDomain is 
	// set to S_OK, pReturnValue is set to the integer value returned by the 
	// invoked method. Otherwise, pReturnValue is not set.

	hr = pClrRuntimeHost->ExecuteInDefaultAppDomain(
		pszAssemblyPath,
		pszClassName, 
		pszStaticMethodName, 
		pszStringArg, 
		&dwLengthRet);


	if (FAILED(hr))
	{
		wprintf(L"Failed to call GetStringLength w/hr 0x%08lx\n", hr);

		CleanUp(pMetaHost, pRuntimeInfo, pClrRuntimeHost);

		return -1;
	}

	// Print the call result of the static method.
	wprintf(L"Call %s.%s(\"%s\") => %d\n", pszClassName, pszStaticMethodName,
		pszStringArg, dwLengthRet);

	CleanUp(pMetaHost, pRuntimeInfo, pClrRuntimeHost);

	return 0;
}

void CleanUp(ICLRMetaHost *pMetaHost, ICLRRuntimeInfo *pRuntimeInfo, ICLRRuntimeHost *pClrRuntimeHost)
{
	if (pMetaHost)
	{
		pMetaHost->Release();
		pMetaHost = NULL;
	}
	if (pRuntimeInfo)
	{
		pRuntimeInfo->Release();
		pRuntimeInfo = NULL;
	}
	if (pClrRuntimeHost)
	{
		// Please note that after a call to Stop, the CLR cannot be 
		// reinitialized into the same process. This step is usually not 
		// necessary. You can leave the .NET runtime loaded in your process.
		//wprintf(L"Stop the .NET runtime\n");
		//pClrRuntimeHost->Stop();

		pClrRuntimeHost->Release();
		pClrRuntimeHost = NULL;
	}
}

