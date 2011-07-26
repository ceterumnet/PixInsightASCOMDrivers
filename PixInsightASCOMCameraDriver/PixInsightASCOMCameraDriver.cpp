#include "PixInsightASCOMCameraDriver.h"

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

	PixInsightASCOMCameraDriver::PixInsightASCOMCameraDriver()
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

	void PixInsightASCOMCameraDriver::Dispose()
	{
		if( theCameraPtr )
			theCameraPtr.Release();
	}

	void PixInsightASCOMCameraDriver::SetLogger(void(*_theLogger)(String))
	{
		theLogger = _theLogger;
		theLogger(String("The Logger has been successfully set."));
	}
	short PixInsightASCOMCameraDriver::BinX()
	{
		ASCOM_WRAP(BinX);
	}
	short PixInsightASCOMCameraDriver::BinY()
	{
		ASCOM_WRAP(BinY);
	}
	int PixInsightASCOMCameraDriver::SetBinX(short binX)
	{
		if(theCameraPtr->Connected)
		{
			theCameraPtr->BinX = binX;
			return 1;
		}
		return -1;
	}
	int PixInsightASCOMCameraDriver::SetBinY(short binY)
	{
		if(theCameraPtr->Connected)
		{
			theCameraPtr->BinY = binY;
			return 1;
		}
		return -1;
	}
	IPixInsightCamera::CameraStateEnum PixInsightASCOMCameraDriver::CameraState()
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
	long PixInsightASCOMCameraDriver::CameraXSize()
	{
		ASCOM_WRAP(CameraXSize);
	}
	long PixInsightASCOMCameraDriver::CameraYSize()
	{
		ASCOM_WRAP(CameraYSize);
	}
	bool PixInsightASCOMCameraDriver::CanAbortExposure()
	{
		ASCOM_WRAP_BOOL(CanAbortExposure);
	}
	bool PixInsightASCOMCameraDriver::CanAsymmetricBin()
	{
		ASCOM_WRAP_BOOL(CanAsymmetricBin);
	}
	bool PixInsightASCOMCameraDriver::CanGetCoolerPower()
	{
		ASCOM_WRAP_BOOL(CanGetCoolerPower);
	}
	bool PixInsightASCOMCameraDriver::CanPulseGuide()
	{
		ASCOM_WRAP_BOOL(CanPulseGuide);
	}
	bool PixInsightASCOMCameraDriver::CanSetCCDTemperature()
	{
		ASCOM_WRAP_BOOL(CanSetCCDTemperature);
	}
	bool PixInsightASCOMCameraDriver::CanStopExposure()
	{
		ASCOM_WRAP_BOOL(CanStopExposure);
	}
	double PixInsightASCOMCameraDriver::CCDTemperature()
	{
		ASCOM_WRAP(CCDTemperature);
	}
	bool PixInsightASCOMCameraDriver::Connected()
	{
		ASCOM_WRAP_BOOL(Connected);
	}

	int PixInsightASCOMCameraDriver::ConnectCamera()
	{
		if(theCameraPtr != NULL)
		{
			theCameraPtr->Connected = 1;
			return 1;
		}
		return 0;
	}

	int PixInsightASCOMCameraDriver::DisconnectCamera()
	{
		if(theCameraPtr->Connected) {
			theCameraPtr->Connected = false;
			return 1;
		}			
		return 0;
	}

	int PixInsightASCOMCameraDriver::SetConnected(bool connectCamera)
	{
		HRESULT hr;
		//CComPtr<ICamera> dispatch;
		DISPID dispid;
		WCHAR *member = L"Connected";
		DISPPARAMS dispparams;
		dispparams.cArgs = 1;
		dispparams.cNamedArgs = 0;
		dispparams.rgvarg = new VARIANTARG[dispparams.cArgs];
		dispparams.rgvarg[0].vt =  VT_BOOL;
        dispparams.rgvarg[0].iVal =  VARIANT_TRUE;
		VARIANT varResult;
		// Get your pointer to the IDispatch interface on the object here.  Also setup your params in dispparams.

		hr = theCameraPtr->GetIDsOfNames(IID_NULL, &member, 1, LOCALE_SYSTEM_DEFAULT, &dispid);
		if (SUCCEEDED(hr)) {
			//We may need to deal with initialization here...
			if(connectCamera == true && theCameraPtr == NULL)
			{
				return 0;
			}
			if( connectCamera == true && theCameraPtr )
			{
				hr = theCameraPtr->Invoke(1, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &dispparams, &varResult, NULL, NULL);
				return hr;
			}
			else if(connectCamera == true && theCameraPtr->Connected == VARIANT_TRUE)
			{
				return 1;
			}
			else if(connectCamera == false && theCameraPtr->Connected == VARIANT_TRUE)
			{
				return PixInsightASCOMCameraDriver::DisconnectCamera();
			}
		}

		
		
		return 0;
	}

	bool PixInsightASCOMCameraDriver::CoolerOn()
	{
		ASCOM_WRAP_BOOL(CoolerOn);
	}
	int PixInsightASCOMCameraDriver::SetCoolerOn(bool coolerOn)
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
	double PixInsightASCOMCameraDriver::CoolerPower()
	{
		ASCOM_WRAP(CoolerPower);
	}
	String PixInsightASCOMCameraDriver::Description()
	{
		return String("ASCOM Driver");
	}

	double PixInsightASCOMCameraDriver::ElectronsPerADU()
	{
		ASCOM_WRAP(ElectronsPerADU);
	}

	double PixInsightASCOMCameraDriver::FullWellCapacity()
	{
		ASCOM_WRAP(FullWellCapacity);
	}

	bool PixInsightASCOMCameraDriver::HasShutter()
	{
		ASCOM_WRAP_BOOL(HasShutter);
	}

	double PixInsightASCOMCameraDriver::HeatSinkTemperature()
	{
		ASCOM_WRAP(HeatSinkTemperature);
	}
	uint16 PixInsightASCOMCameraDriver::ASCOMDataToPi( long _i )
	{
		return _i + 32768;
	}

	//Application needs to own this memory...
	//This may need to be a pointer instead...
	void PixInsightASCOMCameraDriver::ImageArray(UInt16Image *theImage)
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
	
	bool PixInsightASCOMCameraDriver::ImageReady()
	{
		ASCOM_WRAP_BOOL(ImageReady);
	}

	bool PixInsightASCOMCameraDriver::IsPulseGuiding()
	{
		ASCOM_WRAP_BOOL(IsPulseGuiding);
	}

	String PixInsightASCOMCameraDriver::LastError()
	{
		if(theCameraPtr->Connected)
		{
			return String((wchar_t *)theCameraPtr->LastError);
		}
		return String("");
	}
	double PixInsightASCOMCameraDriver::LastExposureDuration()
	{
		ASCOM_WRAP(LastExposureDuration);
	}
	// Reports the actual exposure start in the FITS-standard CCYY-MM-DDThh:mm:ss[.sss...] format.
	String PixInsightASCOMCameraDriver::LastExposureStartTime()
	{
		if(theCameraPtr->Connected)
		{
			return String((wchar_t *)theCameraPtr->LastExposureStartTime);
		}
		return String("");
	}
	long PixInsightASCOMCameraDriver::MaxADU()
	{
		ASCOM_WRAP(MaxADU);
	}
	short PixInsightASCOMCameraDriver::MaxBinX()
	{
		ASCOM_WRAP(MaxBinX);
	}
	short PixInsightASCOMCameraDriver::MaxBinY()
	{
		ASCOM_WRAP(MaxBinY);
	}
	long PixInsightASCOMCameraDriver::NumX()
	{
		ASCOM_WRAP(NumX);
	}
	long PixInsightASCOMCameraDriver::NumY()
	{
		ASCOM_WRAP(NumY);
	}
	int PixInsightASCOMCameraDriver::SetNumX(long numX)
	{
		if(theCameraPtr->Connected)
		{
			theCameraPtr->NumX = numX;
			return 1;
		}
		return 0;
	}
	int PixInsightASCOMCameraDriver::SetNumY(long numY)
	{
		if(theCameraPtr->Connected)
		{
			theCameraPtr->NumY = numY;
			return 1;
		}
		return 0;	
	}
	double PixInsightASCOMCameraDriver::PixelSizeX()
	{
		ASCOM_WRAP(PixelSizeX);
	}
	double PixInsightASCOMCameraDriver::PixelSizeY()
	{
		ASCOM_WRAP(PixelSizeY);
	}

	int PixInsightASCOMCameraDriver::SetCCDTemperature(double ccdTemp)
	{
		if(theCameraPtr->Connected)
		{
			theCameraPtr->SetCCDTemperature = ccdTemp;
			return 1;
		}
		return 0;	
	}

	double PixInsightASCOMCameraDriver::GetSetCCDTemperature()
	{
		ASCOM_WRAP(SetCCDTemperature);
	}

	double PixInsightASCOMCameraDriver::StartX()
	{
		ASCOM_WRAP(StartX);
	}
	int PixInsightASCOMCameraDriver::SetStartX(double setX)
	{
		if(theCameraPtr->Connected)
		{
			theCameraPtr->StartX = setX;
			return 1;
		}
		return 0;	
	}
	double PixInsightASCOMCameraDriver::StartY()
	{
		ASCOM_WRAP(StartY);
	}
	int PixInsightASCOMCameraDriver::SetStartY(double setY)
	{
		if(theCameraPtr->Connected)
		{
			theCameraPtr->StartY = setY;
			return 1;
		}
		return 0;	
	}
	int PixInsightASCOMCameraDriver::AbortExposure()
	{
		if(theCameraPtr->Connected)
		{
			theCameraPtr->AbortExposure();
			return 1;
		}
		return 0;
	}
	int PixInsightASCOMCameraDriver::PulseGuide(IPixInsightCamera::GuideDirection direction, long duration)
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
	void PixInsightASCOMCameraDriver::SetupDialog()
	{
		if(theCameraPtr->Connected)
			theCameraPtr->SetupDialog();
	}
	void PixInsightASCOMCameraDriver::StartExposure(double duration)
	{
		//if(theCameraPtr->Connected)
		//	theCameraPtr->StartExposure(duration, VARIANT_TRUE);
		HRESULT hr;
		//CComPtr<ICamera> dispatch;
		DISPID dispid;
		WCHAR *member = L"StartExposure";
		DISPPARAMS* dispparams;
		VARIANT varResult;
		// Get your pointer to the IDispatch interface on the object here.  Also setup your params in dispparams.

		hr = theCameraPtr->GetIDsOfNames(IID_NULL, &member, 1, LOCALE_SYSTEM_DEFAULT, &dispid);
		if (SUCCEEDED(hr)) {
		  hr = theCameraPtr->Invoke(1, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, dispparams, &varResult, NULL, NULL);
		}

		
	}
	void PixInsightASCOMCameraDriver::StopExposure()
	{
		if(theCameraPtr->Connected)
			theCameraPtr->StopExposure();
	}


}
	