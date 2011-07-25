#define __dll__
#include "DllExports.h"

pcl::PixInsightASCOMFWDriver *driverRef = 0;
int WINAPI DllEntryPoint(HINSTANCE hinst, unsigned long reason, void*)
{
        return 1;
}

IMPEXP pcl::PixInsightASCOMFWDriver* InitializeDevice()
{
	driverRef = new pcl::PixInsightASCOMFWDriver;
	return driverRef;
}

BOOL WINAPI DllMain(
  __in  HINSTANCE hinstDLL,
  __in  DWORD fdwReason,
  __in  LPVOID lpvReserved
)
{
	if(fdwReason == DLL_PROCESS_DETACH )
		driverRef->Dispose();
	return true;
}
