#include <IPixInsightCamera.h>

namespace pcl
{

	class TestDriver : public IPixInsightCamera
	{
	public:
		TestDriver();
		virtual short BinX();
	    virtual short BinY();
	    virtual int SetBinX(short);
	    virtual int SetBinY(short);
	    virtual CameraStateEnum CameraState();
	    virtual long CameraXSize();
	    virtual long CameraYSize();
	    virtual bool CanAbortExposure();
	    virtual bool CanAsymetricBin();
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
	    virtual Array< Array<long> > ImageArray();
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
        virtual double SetCCDTemperature();
        virtual double StartX();
        virtual int SetStartX(double);
        virtual double StartY();
        virtual int SetStartY(double);
        virtual int AbortExposure();
        virtual int PulseGuide(GuideDirection);
        virtual void SetupDialog();
        virtual void StartExposure();
        virtual void StopExposure();
	};

}
