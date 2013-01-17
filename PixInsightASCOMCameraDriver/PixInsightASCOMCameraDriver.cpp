#include "PixInsightASCOMCameraDriver.h"

#define ASCOM_WRAP_BOOL(PROPERTY) 		if( this->Connected() )\
										{\
											if( theCameraPtr2.GetProperty(PROPERTY)->boolVal == VARIANT_TRUE)\
												return true;\
										}\
										return false;\


		
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
		// I'm thinking that this is getting "double disposed because we have a stack initialized variable
		// with theCameraPtr2.
		// theCameraPtr2.Clear();
	}

	void PixInsightASCOMCameraDriver::SetLogger(void(*_theLogger)(String))
	{
		theLogger = _theLogger;
		theLogger(String("The Logger has been successfully set."));
	}

	short PixInsightASCOMCameraDriver::BinX()
	{
		if(this->Connected())
		{
			return theCameraPtr2.GetProperty("BinX")->iVal;
		}
		return -1;
	}

	short PixInsightASCOMCameraDriver::BinY()
	{
		if(this->Connected())
		{
			return theCameraPtr2.GetProperty("BinY")->iVal;
		}
		return -1;
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
		if(this->Connected())
			return theCameraPtr2.GetProperty("CameraXSize")->lVal;
		return -1;
		
	}

	long PixInsightASCOMCameraDriver::CameraYSize()
	{
		if(this->Connected())
			return theCameraPtr2.GetProperty("CameraYSize")->lVal;
		return -1;
	}

	bool PixInsightASCOMCameraDriver::CanAbortExposure()
	{
		ASCOM_WRAP_BOOL("CanAbortExposure");
	}

	bool PixInsightASCOMCameraDriver::CanAsymmetricBin()
	{
		ASCOM_WRAP_BOOL("CanAsymmetricBin");
	}

	bool PixInsightASCOMCameraDriver::CanGetCoolerPower()
	{
		ASCOM_WRAP_BOOL("CanGetCoolerPower");
	}

	bool PixInsightASCOMCameraDriver::CanPulseGuide()
	{
		ASCOM_WRAP_BOOL("CanPulseGuide");
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
		ASCOM_WRAP_BOOL("CanStopExposure");
	}

	double PixInsightASCOMCameraDriver::CCDTemperature()
	{
		if(this->Connected())
			return theCameraPtr2.GetProperty("CCDTemperature")->dblVal;
		return -1;
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
		ASCOM_WRAP_BOOL("CoolerOn");		
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
		if(this->Connected())
			return theCameraPtr2.GetProperty("CoolerPower")->dblVal;
		return 0;
	}

	String PixInsightASCOMCameraDriver::Description()
	{
		return String("ASCOM Driver");
	}

	double PixInsightASCOMCameraDriver::ElectronsPerADU()
	{
		if(this->Connected())
		{
			return theCameraPtr2.GetProperty( "ElectronsPerADU" )->dblVal;
		}
		return 1;
	}

	double PixInsightASCOMCameraDriver::FullWellCapacity()
	{
		if(this->Connected())
		{
			return theCameraPtr2.GetProperty( "FullWellCapacity" )->dblVal;
		}
		return 1;
	}

	bool PixInsightASCOMCameraDriver::HasShutter()
	{
		ASCOM_WRAP_BOOL("HasShutter");
	}

	double PixInsightASCOMCameraDriver::HeatSinkTemperature()
	{
		if(this->Connected())
		{
			return theCameraPtr2.GetProperty( "HeatSinkTemperature" )->dblVal;
		}
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
		
		uint32 *imageData;
		SafeArrayAccessData(theCameraPtr2.GetProperty("ImageArray")->parray, (void **)&imageData);
		int dims = SafeArrayGetDim(theCameraPtr2.GetProperty("ImageArray")->parray);
		long ubound1, ubound2, lbound1, lbound2;
		SafeArrayGetUBound(theCameraPtr2.GetProperty("ImageArray")->parray,1,&ubound1);
		SafeArrayGetUBound(theCameraPtr2.GetProperty("ImageArray")->parray,2,&ubound2);
		SafeArrayGetLBound(theCameraPtr2.GetProperty("ImageArray")->parray,1,&lbound1);
		SafeArrayGetLBound(theCameraPtr2.GetProperty("ImageArray")->parray,2,&lbound2);

		int sizeX = ubound1 - lbound1;
		int sizeY = ubound2 - lbound2;	
		
		uint16 *piImageData = **theImage;

		for( size_type i = 0, N = theImage->NumberOfPixels(); i < N; ++i)
			*piImageData++ = *imageData++;

		SafeArrayUnaccessData( theCameraPtr2.GetProperty("ImageArray")->parray );
	}
	
	bool PixInsightASCOMCameraDriver::ImageReady()
	{
		ASCOM_WRAP_BOOL("ImageReady");
	}

	bool PixInsightASCOMCameraDriver::IsPulseGuiding()
	{
		ASCOM_WRAP_BOOL("IsPulseGuiding");
	}

	String PixInsightASCOMCameraDriver::LastError()
	{
		if(this->Connected() )
			return String(theCameraPtr2.GetProperty("LastError")->bstrVal);
		return String("");
	}
	double PixInsightASCOMCameraDriver::LastExposureDuration()
	{
		if(this->Connected())
			return theCameraPtr2.GetProperty( "LastExposureDuration" )->dblVal;
		return 1;
	}
	// Reports the actual exposure start in the FITS-standard CCYY-MM-DDThh:mm:ss[.sss...] format.
	String PixInsightASCOMCameraDriver::LastExposureStartTime()
	{
		if(this->Connected())
			return String(theCameraPtr2.GetProperty("LastExposureStartTime")->bstrVal);
		return String("");
	}

	long PixInsightASCOMCameraDriver::MaxADU()
	{
		if(this->Connected())
			return theCameraPtr2.GetProperty( "MaxADU" )->lVal;
		return 1;
	}

	short PixInsightASCOMCameraDriver::MaxBinX()
	{
		if(this->Connected())
			return theCameraPtr2.GetProperty("MaxBinX")->iVal;
		return -1;
	}

	short PixInsightASCOMCameraDriver::MaxBinY()
	{
		if(this->Connected())
			return theCameraPtr2.GetProperty("MaxBinY")->iVal;
		return -1;
	}

	long PixInsightASCOMCameraDriver::NumX()
	{
		if(this->Connected())
			return theCameraPtr2.GetProperty("NumX")->lVal;
		return -1;
	}

	long PixInsightASCOMCameraDriver::NumY()
	{
		if(this->Connected())
			return theCameraPtr2.GetProperty("NumY")->iVal;
		return -1;
	}

	int PixInsightASCOMCameraDriver::SetNumX(long numX)
	{
		if(this->Connected())
			return theCameraPtr2.SetProperty("NumX",  numX);
		return -1;
	}

	int PixInsightASCOMCameraDriver::SetNumY(long numY)
	{
		if(this->Connected())
			return theCameraPtr2.SetProperty("NumY",  numY);
		return -1;
	}

	double PixInsightASCOMCameraDriver::PixelSizeX()
	{
		
		if(this->Connected())
			return theCameraPtr2.GetProperty("PixelSizeX")->dblVal;
		return -1;
	}

	double PixInsightASCOMCameraDriver::PixelSizeY()
	{
		if(this->Connected())
			return theCameraPtr2.GetProperty("PixelSizeY")->dblVal;
		return -1;
	}

	int PixInsightASCOMCameraDriver::SetCCDTemperature(double ccdTemp)
	{
		if(this->Connected())
			return theCameraPtr2.SetProperty("SetCCDTemperature", ccdTemp);
		return -1;	
	}

	double PixInsightASCOMCameraDriver::GetSetCCDTemperature()
	{
		if(this->Connected())
			return theCameraPtr2.GetProperty("SetCCDTemperature")->dblVal;
		return -1;
	}

	double PixInsightASCOMCameraDriver::StartX()
	{
		if(this->Connected())
			return theCameraPtr2.GetProperty("StartX")->dblVal;
		return -1;
	}

	int PixInsightASCOMCameraDriver::SetStartX(double setX)
	{
		if(this->Connected())
			return theCameraPtr2.SetProperty("StartX", setX);
		return -1;	
	}
	
	double PixInsightASCOMCameraDriver::StartY()
	{
		if(this->Connected())
			return theCameraPtr2.GetProperty("StartY")->dblVal;
		return -1;
	}

	int PixInsightASCOMCameraDriver::SetStartY(double setY)
	{
		if(this->Connected())
			return theCameraPtr2.SetProperty("StartY", setY);
		return -1;
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
		if(this->Connected())
		{
			switch(direction) {
				case GuideNorth:
					return theCameraPtr2.InvokeMethod("PulseGuide", guideNorth, duration)->iVal;
				case GuideSouth:
					return theCameraPtr2.InvokeMethod("PulseGuide", guideSouth, duration)->iVal;
				case GuideEast:
					return theCameraPtr2.InvokeMethod("PulseGuide", guideEast, duration)->iVal;
				case GuideWest:
					return theCameraPtr2.InvokeMethod("PulseGuide", guideWest, duration)->iVal;
			}
		}
		return -1;	
	}
	
	void PixInsightASCOMCameraDriver::SetupDialog()
	{
		theCameraPtr2.InvokeMethod("SetupDialog");
	}

	void PixInsightASCOMCameraDriver::StartExposure(double duration)
	{
		if(this->Connected())
			theCameraPtr2.InvokeMethod("StartExposure", duration, VARIANT_TRUE);
	}

	void PixInsightASCOMCameraDriver::StopExposure()
	{
		if(this->Connected())
			theCameraPtr2.InvokeMethod("StopExposure");
	}
}
	