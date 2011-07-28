#include "PixInsightASCOMCameraDriver.h"

#define ASCOM_WRAP_BOOL(PROPERTY) 		if( theCameraPtr2.GetProperty("Connected")->boolVal == VARIANT_TRUE)\
										{\
											if( theCameraPtr2.GetProperty("PROPERTY")->boolVal == VARIANT_TRUE)\
											return true;\
										}\
										return false;

		
namespace pcl
{

	PixInsightASCOMCameraDriver::PixInsightASCOMCameraDriver()
	{
		
		CoInitialize(NULL);
		_ChooserPtr C = NULL;
		
		C.CreateInstance("DriverHelper.Chooser");
		C->DeviceTypeV = "Camera";
		
		drvrId = C->Choose("");
		
		if(C != NULL)
		{
			C.Release();			
			theCameraPtr2.CreateObject(drvrId);
		}
	}

	void PixInsightASCOMCameraDriver::Dispose()
	{
		theCameraPtr2.Clear();
	}

	void PixInsightASCOMCameraDriver::SetLogger(void(*_theLogger)(String))
	{
		theLogger = _theLogger;
		theLogger(String("The Logger has been successfully set."));
	}
	short PixInsightASCOMCameraDriver::BinX()
	{
		VARIANT *res = theCameraPtr2.GetProperty("BinX");
		return res->iVal;
		
	}
	short PixInsightASCOMCameraDriver::BinY()
	{
		VARIANT *res = theCameraPtr2.GetProperty("BinY");
		return res->iVal;
	}
	int PixInsightASCOMCameraDriver::SetBinX(short binX)
	{
		if(this->Connected())
		{
			theCameraPtr2.SetProperty("BinX",  binX);
			return 1;
		}
		return -1;
	}
	int PixInsightASCOMCameraDriver::SetBinY(short binY)
	{
		if(this->Connected())
		{
			theCameraPtr2.SetProperty("BinY",  binY);
			return 1;
		}
		return -1;
	}

	IPixInsightCamera::CameraStateEnum PixInsightASCOMCameraDriver::CameraState()
	{
		if( this->Connected() )
		{
			switch ( theCameraPtr2.GetProperty("CameraState")->intVal ) {
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
		VARIANT *res = theCameraPtr2.GetProperty("CameraXSize");
		return res->iVal;
	}
	long PixInsightASCOMCameraDriver::CameraYSize()
	{
		VARIANT *res = theCameraPtr2.GetProperty("CameraYSize");
		return res->iVal;
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
		if( theCameraPtr2.GetProperty("Connected")->boolVal == VARIANT_TRUE)
		{
			if( theCameraPtr2.GetProperty("CanSetCCDTemperature")->boolVal == VARIANT_TRUE)
				return true;
		}
		return false;
	}
	bool PixInsightASCOMCameraDriver::CanStopExposure()
	{
		ASCOM_WRAP_BOOL(CanStopExposure);
	}
	double PixInsightASCOMCameraDriver::CCDTemperature()
	{
		VARIANT *res = theCameraPtr2.GetProperty("CCDTemperature");
		return res->dblVal;
	}

	bool PixInsightASCOMCameraDriver::Connected()
	{
		VARIANT *res = theCameraPtr2.GetProperty("Connected");
		if( res->boolVal == VARIANT_TRUE )
			return true;
		return false;
	}

	int PixInsightASCOMCameraDriver::ConnectCamera(  )
	{
		return theCameraPtr2.SetProperty( "Connected", true );
	}

	int PixInsightASCOMCameraDriver::DisconnectCamera()
	{
		return theCameraPtr2.SetProperty( "Connected", false );
	}

	int PixInsightASCOMCameraDriver::SetConnected(bool connectCamera)
	{
		if( connectCamera == true )
		{
			if( this->Connected() )
				return 1;
			else
				return this->ConnectCamera();
		}
		else
		{
			if( this->Connected() )
				return this->DisconnectCamera( );
			else 
				return 1;
		}
	}

	bool PixInsightASCOMCameraDriver::CoolerOn()
	{
		ASCOM_WRAP_BOOL(CoolerOn);		
	}

	int PixInsightASCOMCameraDriver::SetCoolerOn(bool coolerOn)
	{
		if(this->Connected())
		{
			theCameraPtr2.SetProperty( "CoolerOn", coolerOn );
			return 1;
		}
		
		return 0;
	}
	double PixInsightASCOMCameraDriver::CoolerPower()
	{
		//ASCOM_WRAP(CoolerPower);
		return 1;
	}
	String PixInsightASCOMCameraDriver::Description()
	{
		return String("ASCOM Driver");
	}

	double PixInsightASCOMCameraDriver::ElectronsPerADU()
	{
		//ASCOM_WRAP(ElectronsPerADU);
		return 1;
	}

	double PixInsightASCOMCameraDriver::FullWellCapacity()
	{
		//ASCOM_WRAP(FullWellCapacity);
		return 1;
	}

	bool PixInsightASCOMCameraDriver::HasShutter()
	{
		ASCOM_WRAP_BOOL(HasShutter);
	}

	double PixInsightASCOMCameraDriver::HeatSinkTemperature()
	{
		//ASCOM_WRAP(HeatSinkTemperature);
		return 1;
	}
	uint16 PixInsightASCOMCameraDriver::ASCOMDataToPi( long _i )
	{
		return _i + 32768;
	}

	//Application needs to own this memory...
	//This may need to be a pointer instead...
	void PixInsightASCOMCameraDriver::ImageArray(UInt16Image *theImage)
	{
		
		//uint32 *imageData;
		//SafeArrayAccessData(theCameraPtr->ImageArray.parray, (void **)&imageData);
		//int dims = SafeArrayGetDim(theCameraPtr->ImageArray.parray);
		//long ubound1, ubound2, lbound1, lbound2;
		//SafeArrayGetUBound(theCameraPtr->ImageArray.parray,1,&ubound1);
		//SafeArrayGetUBound(theCameraPtr->ImageArray.parray,2,&ubound2);
		//SafeArrayGetLBound(theCameraPtr->ImageArray.parray,1,&lbound1);
		//SafeArrayGetLBound(theCameraPtr->ImageArray.parray,2,&lbound2);

		//int sizeX = ubound1 - lbound1;
		//int sizeY = ubound2 - lbound2;	
		//
		//uint16 *piImageData = **theImage;

		//for( size_type i = 0, N = theImage->NumberOfPixels(); i < N; ++i)
		//	*piImageData++ = *imageData++;

		//SafeArrayUnaccessData( theCameraPtr->ImageArray.parray );
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
		if(this->Connected() )
		{
			return String((wchar_t *)theCameraPtr2.GetProperty("LastError"));
		}
		return String("");
	}
	double PixInsightASCOMCameraDriver::LastExposureDuration()
	{
		//ASCOM_WRAP(LastExposureDuration);
		return 1;
	}
	// Reports the actual exposure start in the FITS-standard CCYY-MM-DDThh:mm:ss[.sss...] format.
	String PixInsightASCOMCameraDriver::LastExposureStartTime()
	{
		if(this->Connected())
		{
			return String((wchar_t *)theCameraPtr2.GetProperty("LastExposureStartTime"));
		}
		return String("");
	}
	long PixInsightASCOMCameraDriver::MaxADU()
	{
		//ASCOM_WRAP(MaxADU);
		return 1;
	}
	short PixInsightASCOMCameraDriver::MaxBinX()
	{
		VARIANT *res = theCameraPtr2.GetProperty("MaxBinX");
		return res->iVal;
	}
	short PixInsightASCOMCameraDriver::MaxBinY()
	{
		VARIANT *res = theCameraPtr2.GetProperty("MaxBinY");
		return res->iVal;
	}
	long PixInsightASCOMCameraDriver::NumX()
	{
		VARIANT *res = theCameraPtr2.GetProperty("NumX");
		return res->iVal;
	}
	long PixInsightASCOMCameraDriver::NumY()
	{
		VARIANT *res = theCameraPtr2.GetProperty("NumY");
		return res->iVal;
	}
	int PixInsightASCOMCameraDriver::SetNumX(long numX)
	{
		if(this->Connected())
		{
			theCameraPtr2.SetProperty("NumX",  numX);
			return 1;
		}
		return -1;
	}
	int PixInsightASCOMCameraDriver::SetNumY(long numY)
	{
		if(this->Connected())
		{
			theCameraPtr2.SetProperty("NumY",  numY);
			return 1;
		}
		return -1;
	}
	double PixInsightASCOMCameraDriver::PixelSizeX()
	{
		VARIANT *res = theCameraPtr2.GetProperty("PixelSizeX");
		return res->dblVal;
	}
	double PixInsightASCOMCameraDriver::PixelSizeY()
	{
		VARIANT *res = theCameraPtr2.GetProperty("PixelSizeY");
		return res->dblVal;
	}

	int PixInsightASCOMCameraDriver::SetCCDTemperature(double ccdTemp)
	{
		if(this->Connected())
		{
			theCameraPtr2.SetProperty("SetCCDTemperature", ccdTemp);
			return 1;
		}
		return 0;	
	}

	double PixInsightASCOMCameraDriver::GetSetCCDTemperature()
	{
		VARIANT *res = theCameraPtr2.GetProperty("SetCCDTemperature");
		return res->dblVal;
	}

	double PixInsightASCOMCameraDriver::StartX()
	{
		VARIANT *res = theCameraPtr2.GetProperty("StartX");
		return res->dblVal;
	}
	int PixInsightASCOMCameraDriver::SetStartX(double setX)
	{
		if(this->Connected())
		{
			theCameraPtr2.SetProperty("StartX", setX);
			return 1;
		}
		return 0;	
	}
	double PixInsightASCOMCameraDriver::StartY()
	{
		VARIANT *res = theCameraPtr2.GetProperty("StartY");
		return res->dblVal;
	}
	int PixInsightASCOMCameraDriver::SetStartY(double setY)
	{
		if(this->Connected())
		{
			theCameraPtr2.SetProperty("StartY", setY);
			return 1;
		}
		return 0;
	}
	int PixInsightASCOMCameraDriver::AbortExposure()
	{
		if(this->Connected())
		{
			theCameraPtr2.InvokeMethod("AbortExposure");
			return 1;
		}
		return 0;
	}
	int PixInsightASCOMCameraDriver::PulseGuide(IPixInsightCamera::GuideDirection direction, long duration)
	{
		//if(theCameraPtr->Connected)
		//{
		//	switch(direction) {
		//		case GuideNorth:
		//			return theCameraPtr->PulseGuide(guideNorth, duration);
		//		case GuideSouth:
		//			return theCameraPtr->PulseGuide(guideSouth, duration);
		//		case GuideEast:
		//			return theCameraPtr->PulseGuide(guideEast, duration);
		//		case GuideWest:
		//			return theCameraPtr->PulseGuide(guideWest, duration);
		//	}
		//}
		return 0;	
	}
	void PixInsightASCOMCameraDriver::SetupDialog()
	{
		//if(theCameraPtr->Connected)
		//	theCameraPtr->SetupDialog();
	}
	void PixInsightASCOMCameraDriver::StartExposure(double duration)
	{
		////if(theCameraPtr->Connected)
		////	theCameraPtr->StartExposure(duration, VARIANT_TRUE);
		//HRESULT hr;
		////CComPtr<ICamera> dispatch;
		//DISPID dispid;
		//WCHAR *member = L"StartExposure";
		//DISPPARAMS* dispparams;
		//VARIANT varResult;
		//// Get your pointer to the IDispatch interface on the object here.  Also setup your params in dispparams.

		//hr = theCameraPtr->GetIDsOfNames(IID_NULL, &member, 1, LOCALE_SYSTEM_DEFAULT, &dispid);
		//if (SUCCEEDED(hr)) {
		//  hr = theCameraPtr->Invoke(1, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, dispparams, &varResult, NULL, NULL);
		//}

		
	}
	void PixInsightASCOMCameraDriver::StopExposure()
	{
		//if(theCameraPtr->Connected)
		//	theCameraPtr->StopExposure();
	}


}
	