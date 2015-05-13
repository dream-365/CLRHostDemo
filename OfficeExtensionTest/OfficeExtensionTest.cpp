// OfficeExtensionTest.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "OfficeExtensionTest.h"


// This is an example of an exported variable
OFFICEEXTENSIONTEST_API int nOfficeExtensionTest=0;

// This is an example of an exported function.
OFFICEEXTENSIONTEST_API int fnOfficeExtensionTest(void)
{
	return 42;
}

// This is the constructor of a class that has been exported.
// see OfficeExtensionTest.h for the class definition
COfficeExtensionTest::COfficeExtensionTest()
{
	return;
}
