#include "PixInsightASCOMDriver.h"

#define ASCOM_WRAP(PROPERTY) if(theCameraPtr->Connected)\
								return theCameraPtr->PROPERTY;\
							 return -1;

#define ASCOM_WRAP_BOOL(PROPERTY) if(theCameraPtr->Connected)\
								  {\
									if(theCameraPtr->PROPERTY == VARIANT_TRUE)\
										return true;\
									}\
								  return false;

namespace pcl
{

	PixInsightASCOMDriver::PixInsightASCOMDriver()
	{
		theCameraPtr = NULL;
		CoInitialize(NULL);
		C = NULL;
		
		C.CreateInstance("DriverHelper.Chooser");
		C->DeviceTypeV = "Camera";
		
		drvrId = C->Choose("");
		
		if(C != NULL)
		{
			C.Release();			
			theCameraPtr.CreateInstance((LPCSTR)drvrId);
		}
	}

	void PixInsightASCOMDriver::Dispose()
	{
		if( theCameraPtr )
			theCameraPtr.Release();
	}

	void PixInsightASCOMDriver::SetLogger(void(*_theLogger)(String))
	{
		theLogger = _theLogger;
		theLogger(String("The Logger has been successfully set."));
	}
	short PixInsightASCOMDriver::BinX()
	{
		ASCOM_WRAP(BinX);
	}
	short PixInsightASCOMDriver::BinY()
	{
		ASCOM_WRAP(BinY);
	}
	int PixInsightASCOMDriver::SetBinX(short binX)
	{
		if(theCameraPtr->Connected)
		{
			theCameraPtr->BinX = binX;
			return 1;
		}
		return -1;
	}
	int PixInsightASCOMDriver::SetBinY(short binY)
	{
		if(theCameraPtr->Connected)
		{
			theCameraPtr->BinY = binY;
			return 1;
		}
		return -1;
	}
	IPixInsightCamera::CameraStateEnum PixInsightASCOMDriver::CameraState()
	{
		if(theCameraPtr->Connected)
		{
			switch (theCameraPtr->CameraState) {
				case cameraDownload :
					return CameraDownload;
				case cameraError :
					return CameraError;
				case cameraExposing :
					return CameraExposing;
				case cameraIdle :
					return CameraIdle;
				case cameraReading :
					return CameraReading;
				case cameraWaiting :
					return CameraWaiting;
				default:
					return CameraIdle; // This is kinda lame...maybe we should add an enum for this case?
			}
		}
		return CameraError;
	}
	long PixInsightASCOMDriver::CameraXSize()
	{
		ASCOM_WRAP(CameraXSize);
	}
	long PixInsightASCOMDriver::CameraYSize()
	{
		ASCOM_WRAP(CameraYSize);
	}
	bool PixInsightASCOMDriver::CanAbortExposure()
	{
		ASCOM_WRAP_BOOL(CanAbortExposure);
	}
	bool PixInsightASCOMDriver::CanAsymmetricBin()
	{
		ASCOM_WRAP_BOOL(CanAsymmetricBin);
	}
	bool PixInsightASCOMDriver::CanGetCoolerPower()
	{
		ASCOM_WRAP_BOOL(CanGetCoolerPower);
	}
	bool PixInsightASCOMDriver::CanPulseGuide()
	{
		ASCOM_WRAP_BOOL(CanPulseGuide);
	}
	bool PixInsightASCOMDriver::CanSetCCDTemperature()
	{
		ASCOM_WRAP_BOOL(CanSetCCDTemperature);
	}
	bool PixInsightASCOMDriver::CanStopExposure()
	{
		ASCOM_WRAP_BOOL(CanStopExposure);
	}
	double PixInsightASCOMDriver::CCDTemperature()
	{
		ASCOM_WRAP(CCDTemperature);
	}
	bool PixInsightASCOMDriver::Connected()
	{
		ASCOM_WRAP_BOOL(Connected);
	}

	int PixInsightASCOMDriver::ConnectCamera()
	{
		if(theCameraPtr != NULL)
		{
			theCameraPtr->Connected = 1;
			return 1;
		}
		return 0;
	}

	int PixInsightASCOMDriver::DisconnectCamera()
	{
		if(theCameraPtr->Connected) {
			theCameraPtr->Connected = false;
			return 1;
		}			
		return 0;
	}

	int PixInsightASCOMDriver::SetConnected(bool connectCamera)
	{
		if(connectCamera == true && theCameraPtr == NULL)
			return PixInsightASCOMDriver::ConnectCamera();
		if(connectCamera == true && theCameraPtr->Connected == false)
			return PixInsightASCOMDriver::ConnectCamera();
		else if(connectCamera == true && theCameraPtr->Connected == VARIANT_TRUE)
			return 1;
		else if(connectCamera == false && theCameraPtr->Connected == VARIANT_TRUE)
			return PixInsightASCOMDriver::DisconnectCamera();
		else
			return 0;
	}

	bool PixInsightASCOMDriver::CoolerOn()
	{
		ASCOM_WRAP_BOOL(CoolerOn);
	}
	int PixInsightASCOMDriver::SetCoolerOn(bool coolerOn)
	{
		if(theCameraPtr->Connected && coolerOn)
		{
			theCameraPtr->CoolerOn = VARIANT_TRUE;
			return 1;
		}
		else if(theCameraPtr->Connected && !coolerOn)
		{
			theCameraPtr->CoolerOn = VARIANT_FALSE;
			return 1;
		}
		return 0;
	}
	double PixInsightASCOMDriver::CoolerPower()
	{
		ASCOM_WRAP(CoolerPower);
	}
	String PixInsightASCOMDriver::Description()
	{
		return String("ASCOM Driver");
	}

	double PixInsightASCOMDriver::ElectronsPerADU()
	{
		ASCOM_WRAP(ElectronsPerADU);
	}

	double PixInsightASCOMDriver::FullWellCapacity()
	{
		ASCOM_WRAP(FullWellCapacity);
	}

	bool PixInsightASCOMDriver::HasShutter()
	{
		ASCOM_WRAP_BOOL(HasShutter);
	}

	double PixInsightASCOMDriver::HeatSinkTemperature()
	{
		ASCOM_WRAP(HeatSinkTemperature);
	}
	uint16 PixInsightASCOMDriver::ASCOMDataToPi( long _i )
	{
		return _i + 32768;
	}

	//Application needs to own this memory...
	//This may need to be a pointer instead...
	void PixInsightASCOMDriver::ImageArray(UInt16Image *theImage)
	{
		
		uint32 *imageData;
		SafeArrayAccessData(theCameraPtr->ImageArray.parray, (void **)&imageData);
		int dims = SafeArrayGetDim(theCameraPtr->ImageArray.parray);
		long ubound1, ubound2, lbound1, lbound2;
		SafeArrayGetUBound(theCameraPtr->ImageArray.parray,1,&ubound1);
		SafeArrayGetUBound(theCameraPtr->ImageArray.parray,2,&ubound2);
		SafeArrayGetLBound(theCameraPtr->ImageArray.parray,1,&lbound1);
		SafeArrayGetLBound(theCameraPtr->ImageArray.parray,2,&lbound2);

		int sizeX = ubound1 - lbound1;
		int sizeY = ubound2 - lbound2;	
		
		uint16 *piImageData = **theImage;

		for( size_type i = 0, N = theImage->NumberOfPixels(); i < N; ++i)
			*piImageData++ = *imageData++;

		SafeArrayUnaccessData( theCameraPtr->ImageArray.parray );
	}
	
	bool PixInsightASCOMDriver::ImageReady()
	{
		ASCOM_WRAP_BOOL(ImageReady);
	}

	bool PixInsightASCOMDriver::IsPulseGuiding()
	{
		ASCOM_WRAP_BOOL(IsPulseGuiding);
	}

	String PixInsightASCOMDriver::LastError()
	{
		if(theCameraPtr->Connected)
		{
			return String((wchar_t *)theCameraPtr->LastError);
		}
		return String("");
	}
	double PixInsightASCOMDriver::LastExposureDuration()
	{
		ASCOM_WRAP(LastExposureDuration);
	}
	// Reports the actual exposure start in the FITS-standard CCYY-MM-DDThh:mm:ss[.sss...] format.
	String PixInsightASCOMDriver::LastExposureStartTime()
	{
		if(theCameraPtr->Connected)
		{
			return String((wchar_t *)theCameraPtr->LastExposureStartTime);
		}
		return String("");
	}
	long PixInsightASCOMDriver::MaxADU()
	{
		ASCOM_WRAP(MaxADU);
	}
	short PixInsightASCOMDriver::MaxBinX()
	{
		ASCOM_WRAP(MaxBinX);
	}
	short PixInsightASCOMDriver::MaxBinY()
	{
		ASCOM_WRAP(MaxBinY);
	}
	long PixInsightASCOMDriver::NumX()
	{
		ASCOM_WRAP(NumX);
	}
	long PixInsightASCOMDriver::NumY()
	{
		ASCOM_WRAP(NumY);
	}
	int PixInsightASCOMDriver::SetNumX(long numX)
	{
		if(theCameraPtr->Connected)
		{
			theCameraPtr->NumX = numX;
			return 1;
		}
		return 0;
	}
	int PixInsightASCOMDriver::SetNumY(long numY)
	{
		if(theCameraPtr->Connected)
		{
			theCameraPtr->NumY = numY;
			return 1;
		}
		return 0;	
	}
	double PixInsightASCOMDriver::PixelSizeX()
	{
		ASCOM_WRAP(PixelSizeX);
	}
	double PixInsightASCOMDriver::PixelSizeY()
	{
		ASCOM_WRAP(PixelSizeY);
	}

	int PixInsightASCOMDriver::SetCCDTemperature(double ccdTemp)
	{
		if(theCameraPtr->Connected)
		{
			theCameraPtr->SetCCDTemperature = ccdTemp;
			return 1;
		}
		return 0;	
	}

	double PixInsightASCOMDriver::GetSetCCDTemperature()
	{
		ASCOM_WRAP(SetCCDTemperature);
	}

	double PixInsightASCOMDriver::StartX()
	{
		ASCOM_WRAP(StartX);
	}
	int PixInsightASCOMDriver::SetStartX(double setX)
	{
		if(theCameraPtr->Connected)
		{
			theCameraPtr->StartX = setX;
			return 1;
		}
		return 0;	
	}
	double PixInsightASCOMDriver::StartY()
	{
		ASCOM_WRAP(StartY);
	}
	int PixInsightASCOMDriver::SetStartY(double setY)
	{
		if(theCameraPtr->Connected)
		{
			theCameraPtr->StartY = setY;
			return 1;
		}
		return 0;	
	}
	int PixInsightASCOMDriver::AbortExposure()
	{
		if(theCameraPtr->Connected)
		{
			theCameraPtr->AbortExposure();
			return 1;
		}
		return 0;
	}
	int PixInsightASCOMDriver::PulseGuide(IPixInsightCamera::GuideDirection direction, long duration)
	{
		if(theCameraPtr->Connected)
		{
			switch(direction) {
				case GuideNorth:
					return theCameraPtr->PulseGuide(guideNorth, duration);
				case GuideSouth:
					return theCameraPtr->PulseGuide(guideSouth, duration);
				case GuideEast:
					return theCameraPtr->PulseGuide(guideEast, duration);
				case GuideWest:
					return theCameraPtr->PulseGuide(guideWest, duration);
			}
		}
		return 0;	
	}
	void PixInsightASCOMDriver::SetupDialog()
	{
		if(theCameraPtr->Connected)
			theCameraPtr->SetupDialog();
	}
	void PixInsightASCOMDriver::StartExposure(double duration)
	{
		if(theCameraPtr->Connected)
			theCameraPtr->StartExposure(duration, VARIANT_TRUE);
	}
	void PixInsightASCOMDriver::StopExposure()
	{
		if(theCameraPtr->Connected)
			theCameraPtr->StopExposure();
	}


}
	