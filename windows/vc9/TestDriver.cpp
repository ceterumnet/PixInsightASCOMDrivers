#include "TestDriver.h"


namespace pcl
{

	TestDriver::TestDriver()
	{

	}

	short TestDriver::BinX()
	{
		return 0;
	}
	short TestDriver::BinY()
	{
		return 0;
	}
	int TestDriver::SetBinX(short binX)
	{
		return 0;
	}
	int SetBinY(short binY)
	{
		return 0;
	}
	IPixInsightCamera::CameraStateEnum TestDriver::CameraState()
	{
		return IPixInsightCamera::CameraStateEnum::CameraIdle;

	}
	long TestDriver::CameraXSize()
	{
		return 0;
	}
	long TestDriver::CameraYSize()
	{
		return 0;
	}
	bool TestDriver::CanAbortExposure()
	{
		return true;
	}
	bool TestDriver::CanAsymetricBin()
	{
		return true;
	}
	bool TestDriver::CanGetCoolerPower()
	{
		return true;
	}
	bool TestDriver::CanPulseGuide()
	{
		return true;
	}
	bool TestDriver::CanSetCCDTemperature()
	{
		return true;
	}
	bool TestDriver::CanStopExposure()
	{
		return true;
	}
	double TestDriver::CCDTemperature()
	{
		return 10;
	}
	bool TestDriver::Connected()
	{
		return false;
	}
	int TestDriver::SetConnected(bool cameraConnected)
	{
		return 0;
	}
	bool TestDriver::CoolerOn()
	{
		return false;
	}
	int TestDriver::SetCoolerOn(bool coolerOn)
	{
		return 0;
	}
	double TestDriver::CoolerPower()
	{
		return 0;
	}
	String TestDriver::Description()
	{
		return String("Data from the TestDriver");
	}
	double TestDriver::ElectronsPerADU()
	{
		return 0;
	}
	double TestDriver::FullWellCapacity()
	{
		return 0;
	}
	bool TestDriver::HasShutter()
	{
		return false;
	}
	double TestDriver::HeatSinkTemperature()
	{
		return 0;
	}
	Array< Array<long> > TestDriver::ImageArray()
	{
		return NULL;
	}
	//Array< Array<long> > TestDriver::ImageArrayVariant() = 0;
	bool TestDriver::ImageReady()
	{
		return false;
	}
	bool TestDriver::IsPulseGuiding()
	{
		return false;
	}
	String TestDriver::LastError()
	{
		return NULL;
	}
	double TestDriver::LastExposureDuration()
	{
		return 0;
	}
	// Reports the actual exposure start in the FITS-standard CCYY-MM-DDThh:mm:ss[.sss...] format.
	String TestDriver::LastExposureStartTime()
	{
		return NULL;
	}
	long TestDriver::MaxADU()
	{
		return 0;
	}
	short TestDriver::MaxBinX()
	{
		return 0;
	}
	short TestDriver::MaxBinY()
	{
		return 0;
	}
	long TestDriver::NumX()
	{
		return 0;
	}
	long TestDriver::NumY()
	{
		return 0;
	}
	int TestDriver::SetNumX(long)
	{
		return 0;
	}
	int TestDriver::SetNumY(long)
	{
		return 0;
	}
	double TestDriver::PixelSizeX()
	{
		return 0;
	}
	double TestDriver::PixelSizeY()
	{
		return 0;
	}
	double TestDriver::SetCCDTemperature()
	{
		return 0;
	}
	double TestDriver::StartX()
	{
		return 0;
	}
	int TestDriver::SetStartX(double setX)
	{
		return 0;
	}
	double TestDriver::StartY()
	{
		return 0;
	}
	int TestDriver::SetStartY(double setY)
	{
		return 0;
	}
	int AbortExposure()
	{
		return 0;
	}
	int TestDriver::PulseGuide(IPixInsightCamera::GuideDirection direction)
	{
		return 0;
	}
	void TestDriver::SetupDialog()
	{
	}
	void TestDriver::StartExposure()
	{
	}
	void TestDriver::StopExposure()
	{
	}s
}
