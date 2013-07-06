#ifndef DLLEXPORTS_H
#define DLLEXPORTS_H

#ifdef __dll__
#define IMPEXP __declspec(dllexport) 
#else
#define IMPEXP __declspec(dllimport)
#endif 	// __dll__

#include "PixInsightASCOMCameraDriver.h"
#include <IPixInsightCamera.h>


extern "C"

IMPEXP pcl::PixInsightASCOMCameraDriver* InitializeDevice(void);


#endif	// DLLEXPORTS_H
