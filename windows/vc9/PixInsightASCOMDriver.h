#include <IPixInsightCamera.h>
#include "stdafx.h"
#include <atlsafe.h>
#pragma once

#import "c:\Program Files (x86)\Common Files\ASCOM\Interface\AscomMasterInterfaces.tlb"
#import "C:\\Windows\\System32\\ScrRun.dll" \
	no_namespace \
	rename("DeleteFile","DeleteFileItem") \
	rename("MoveFile","MoveFileItem") \
	rename("CopyFile","CopyFileItem") \
	rename("FreeSpace","FreeDriveSpace") \
	rename("Unknown","UnknownDiskType") \
	rename("Folder","DiskFolder")

#import "progid:DriverHelper.Chooser" \
	rename("Yield","ASCOMYield") \
	rename("MessageBox","ASCOMMessageBox")

using namespace AscomInterfacesLib;
using namespace DriverHelper;

namespace pcl
{

	class PixInsightASCOMDriver : public IPixInsightCamera
	{
	public:
		PixInsightASCOMDriver();
		virtual void SetLogger(void(*)(String));
		virtual short BinX();
	    virtual short BinY();
	    virtual int SetBinX(short);
	    virtual int SetBinY(short);
	    virtual CameraStateEnum CameraState();
	    virtual long CameraXSize();
	    virtual long CameraYSize();
	    virtual bool CanAbortExposure();
	    virtual bool CanAsymmetricBin();
	    virtual bool CanGetCoolerPower();
	    virtual bool CanPulseGuide();
	    virtual bool CanSetCCDTemperature();
	    virtual bool CanStopExposure();
	    virtual double CCDTemperature();
	    virtual bool Connected();
	    virtual int SetConnected(bool);
	    virtual bool CoolerOn();
	    virtual int SetCoolerOn(bool);
	    virtual double CoolerPower();
	    virtual String Description();
	    virtual double ElectronsPerADU();
	    virtual double FullWellCapacity();
	    virtual bool HasShutter();
	    virtual double HeatSinkTemperature();
		
		virtual void ImageArray(UInt16Image *theImage);
	    //virtual Array< Array<long> > ImageArrayVariant();
	    virtual bool ImageReady();
	    virtual bool IsPulseGuiding();
	    virtual String LastError();
	    virtual double LastExposureDuration();
	    // Reports the actual exposure start in the FITS-standard CCYY-MM-DDThh:mm:ss[.sss...] format.
	    virtual String LastExposureStartTime();
	    virtual long MaxADU();
	    virtual short MaxBinX();
        virtual short MaxBinY();
        virtual long NumX();
        virtual long NumY();
        virtual int SetNumX(long);
        virtual int SetNumY(long);
        virtual double PixelSizeX();
        virtual double PixelSizeY();
        virtual int SetCCDTemperature(double);
        virtual double StartX();
        virtual int SetStartX(double);
        virtual double StartY();
        virtual int SetStartY(double);
        virtual int AbortExposure();
        virtual int PulseGuide(GuideDirection, long);
        virtual void SetupDialog();
        virtual void StartExposure(double);
        virtual void StopExposure();
		virtual double GetSetCCDTemperature();
	private:
		void (*theLogger)(String);
		int ConnectCamera();
		int DisconnectCamera();
		ICameraPtr theCameraPtr;
		uint16 ASCOMDataToPi( long );
		
	};

}
