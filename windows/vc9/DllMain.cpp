#define __dll__
#include "DllExports.h"

int WINAPI DllEntryPoint(HINSTANCE hinst, unsigned long reason, void*)
{
        return 1;
}

IMPEXP pcl::PixInsightASCOMDriver* InitializeDevice()
{
	return new pcl::PixInsightASCOMDriver;
}
