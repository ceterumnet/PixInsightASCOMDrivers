#define __dll__
#include "DllExports.h"

int WINAPI DllEntryPoint(HINSTANCE hinst, unsigned long reason, void*)
{
        return 1;
}

IMPEXP pcl::PixInsightASCOMFWDriver* InitializeDevice()
{
	return new pcl::PixInsightASCOMFWDriver;
}
