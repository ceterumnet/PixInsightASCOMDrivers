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
		CoInitialize(NULL);

		_ChooserPtr C = NULL;
		C.CreateInstance("DriverHelper.Chooser");
		C->DeviceTypeV = "Camera";
		_bstr_t  drvrId = C->Choose("");

		if(C != NULL)
		{
			C.Release();
			
			theCameraPtr.CreateInstance((LPCSTR)drvrId);
			if(theCameraPtr != NULL)
			{
				theCameraPtr->Connected = 1;
				return 1;
			}
		}
		return 0;
	}

	int PixInsightASCOMDriver::DisconnectCamera()
	{
		return 0;
	}

	int PixInsightASCOMDriver::SetConnected(bool connectCamera)
	{
		if(connectCamera == true && isConnected == false)
		{
			return PixInsightASCOMDriver::ConnectCamera();
		}
		else if(connectCamera == true && isConnected == true)
		{
			return 1;
		}
		else if(connectCamera == false && isConnected == true)
		{
			return PixInsightASCOMDriver::DisconnectCamera();
		}
		else
		{
			return 1;
		}
	}

	bool PixInsightASCOMDriver::CoolerOn()
	{
		return false;
	}
	int PixInsightASCOMDriver::SetCoolerOn(bool coolerOn)
	{
		return 0;
	}
	double PixInsightASCOMDriver::CoolerPower()
	{
		return 0;
	}
	String PixInsightASCOMDriver::Description()
	{
		return String("ASCOM Driver");
	}
	double PixInsightASCOMDriver::ElectronsPerADU()
	{
		return 0;
	}
	double PixInsightASCOMDriver::FullWellCapacity()
	{
		return 0;
	}
	bool PixInsightASCOMDriver::HasShutter()
	{
		return false;
	}
	double PixInsightASCOMDriver::HeatSinkTemperature()
	{
		return 0;
	}
	
	Array< Array<long> > PixInsightASCOMDriver::ImageArray()
	{
		return Array< Array<long> >();
	}
	//Array< Array<long> > PixInsightASCOMDriver::ImageArrayVariant() = 0;
	bool PixInsightASCOMDriver::ImageReady()
	{
		return false;
	}
	bool PixInsightASCOMDriver::IsPulseGuiding()
	{
		return false;
	}
	String PixInsightASCOMDriver::LastError()
	{
		return String("");
	}
	double PixInsightASCOMDriver::LastExposureDuration()
	{
		return 0;
	}
	// Reports the actual exposure start in the FITS-standard CCYY-MM-DDThh:mm:ss[.sss...] format.
	String PixInsightASCOMDriver::LastExposureStartTime()
	{
		return String("");
	}
	long PixInsightASCOMDriver::MaxADU()
	{
		return 0;
	}
	short PixInsightASCOMDriver::MaxBinX()
	{
		return 0;
	}
	short PixInsightASCOMDriver::MaxBinY()
	{
		return 0;
	}
	long PixInsightASCOMDriver::NumX()
	{
		return 0;
	}
	long PixInsightASCOMDriver::NumY()
	{
		return 0;
	}
	int PixInsightASCOMDriver::SetNumX(long)
	{
		return 0;
	}
	int PixInsightASCOMDriver::SetNumY(long)
	{
		return 0;
	}
	double PixInsightASCOMDriver::PixelSizeX()
	{
		return 0;
	}
	double PixInsightASCOMDriver::PixelSizeY()
	{
		return 0;
	}
	double PixInsightASCOMDriver::SetCCDTemperature()
	{
		return 0;
	}
	double PixInsightASCOMDriver::StartX()
	{
		return 0;
	}
	int PixInsightASCOMDriver::SetStartX(double setX)
	{
		return 0;
	}
	double PixInsightASCOMDriver::StartY()
	{
		return 0;
	}
	int PixInsightASCOMDriver::SetStartY(double setY)
	{
		return 0;
	}
	int PixInsightASCOMDriver::AbortExposure()
	{
		return 0;
	}
	int PixInsightASCOMDriver::PulseGuide(IPixInsightCamera::GuideDirection direction)
	{
		return 0;
	}
	void PixInsightASCOMDriver::SetupDialog()
	{
	}
	void PixInsightASCOMDriver::StartExposure()
	{
	}
	void PixInsightASCOMDriver::StopExposure()
	{
	}


}
