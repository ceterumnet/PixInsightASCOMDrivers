#ifndef DLLEXPORTS_H
#define DLLEXPORTS_H

#ifdef __dll__
#define IMPEXP __declspec(dllexport) 
#else
#define IMPEXP __declspec(dllimport)
#endif 	// __dll__

#include "PixInsightASCOMDriver.h"
#include <IPixInsightCamera.h>

//typedef IPixInsightCamera* IPixInsightCameraPtr;

extern "C"

IMPEXP pcl::PixInsightASCOMDriver* InitializeCamera(void);


#endif	// DLLEXPORTS_H
