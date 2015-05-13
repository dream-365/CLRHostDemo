// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the OFFICEEXTENSIONTEST_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// OFFICEEXTENSIONTEST_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef OFFICEEXTENSIONTEST_EXPORTS
#define OFFICEEXTENSIONTEST_API __declspec(dllexport)
#else
#define OFFICEEXTENSIONTEST_API __declspec(dllimport)
#endif

// This class is exported from the OfficeExtensionTest.dll
class OFFICEEXTENSIONTEST_API COfficeExtensionTest {
public:
	COfficeExtensionTest(void);
	// TODO: add your methods here.
};

extern OFFICEEXTENSIONTEST_API int nOfficeExtensionTest;

OFFICEEXTENSIONTEST_API int fnOfficeExtensionTest(void);
