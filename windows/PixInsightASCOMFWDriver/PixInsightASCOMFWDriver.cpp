#include "PixInsightASCOMFWDriver.h"


#define ASCOM_WRAP_BOOL(PROPERTY) 		if( this->Connected() )\
										{\
											if( theFWPtr2.GetProperty(PROPERTY)->boolVal == VARIANT_TRUE)\
												return true;\
										}\
										return false;\

namespace pcl
{

	PixInsightASCOMFWDriver::PixInsightASCOMFWDriver()
	{
		CoInitialize(NULL);
		_ChooserPtr C = NULL;
		
		C.CreateInstance("DriverHelper.Chooser");
		C->DeviceTypeV = "FilterWheel";
		
		drvrId = C->Choose("");
		
		if(C != NULL)
		{
			C.Release();			
			theFWPtr2.CreateObject(drvrId);
		}
	}

	void PixInsightASCOMFWDriver::Dispose()
	{
		theFWPtr2.Clear();
	}

	void PixInsightASCOMFWDriver::SetLogger(void(*_theLogger)(String))
	{
		theLogger = _theLogger;
		theLogger(String("The Logger has been successfully set."));
	}
	
	bool PixInsightASCOMFWDriver::Connected()
	{
		ASCOM_WRAP_BOOL("Connected");
	}

	int PixInsightASCOMFWDriver::ConnectFW()
	{
		return theFWPtr2.SetProperty( "Connected", true );
	}

	int PixInsightASCOMFWDriver::DisconnectFW()
	{
		return theFWPtr2.SetProperty( "Connected", false );
	}

	int PixInsightASCOMFWDriver::SetConnected(bool connectFW)
	{
		if( connectFW == true)
		{
			if( this->Connected() )
				return 1;
			return this->ConnectFW();
		}
		else
		{
			if( this->Connected() )
				return this->DisconnectFW();
			return 1;
		}
	}

	String PixInsightASCOMFWDriver::Description()
	{
		return String("ASCOM FW Driver");
	}

	void PixInsightASCOMFWDriver::SetupDialog()
	{
		if(this->Connected())
			theFWPtr2.InvokeMethod("SetupDialog");
	}
	
	short PixInsightASCOMFWDriver::Position()
	{
		if( this->Connected() )
			return theFWPtr2.GetProperty("Position")->iVal;
	    return -2;
	}

	int PixInsightASCOMFWDriver::SetPosition(uint8 p)
	{
		return theFWPtr2.SetProperty("Position", p);
	}

	uint8 PixInsightASCOMFWDriver::MaxPosition()
	{
		uint8 i = SafeArrayGetElemsize(theFWPtr2.GetProperty("Names")->parray);
		return i;
	}

	uint8 PixInsightASCOMFWDriver::MinPosition()
	{
		return 1;
	}

	bool PixInsightASCOMFWDriver::IsMoving()
	{
		if( this->Position() == -1 )
			return true;
		return false;
	}
}
