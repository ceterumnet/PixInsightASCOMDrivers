#define __dll__
#include "DllExports.h"

int WINAPI DllEntryPoint(HINSTANCE hinst, unsigned long reason, void*)
{
        return 1;
}

pcl::PixInsightASCOMCameraDriver *driverRef = 0;
IMPEXP pcl::PixInsightASCOMCameraDriver* InitializeDevice()
{
	driverRef = new pcl::PixInsightASCOMCameraDriver;
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