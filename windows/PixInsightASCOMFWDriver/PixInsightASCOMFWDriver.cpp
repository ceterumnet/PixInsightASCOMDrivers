#include "PixInsightASCOMFWDriver.h"

#define ASCOM_WRAP(PROPERTY) if(theFWPtr->Connected)\
								return theFWPtr->PROPERTY;\
							 return -1;

#define ASCOM_WRAP_BOOL(PROPERTY) if(theFWPtr->Connected)\
								  {\
									if(theFWPtr->PROPERTY == VARIANT_TRUE)\
										return true;\
									}\
								  return false;

namespace pcl
{

	PixInsightASCOMFWDriver::PixInsightASCOMFWDriver()
	{
		theFWPtr = NULL;
		CoInitialize(NULL);
		_ChooserPtr C = NULL;
		
		C.CreateInstance("DriverHelper.Chooser");
		C->DeviceTypeV = "FilterWheel";
		_bstr_t  drvrId = C->Choose("");
		
		if(C != NULL)
		{
			C.Release();			
			theFWPtr.CreateInstance((LPCSTR)drvrId);
		}
	}

	void PixInsightASCOMFWDriver::SetLogger(void(*_theLogger)(String))
	{
		theLogger = _theLogger;
		theLogger(String("The Logger has been successfully set."));
	}
	
	bool PixInsightASCOMFWDriver::Connected()
	{
		ASCOM_WRAP_BOOL(Connected);
	}

	int PixInsightASCOMFWDriver::ConnectFW()
	{
		if(theFWPtr != NULL)
		{
			theFWPtr->Connected = 1;
			return 1;
		}
		return 0;
	}

	int PixInsightASCOMFWDriver::DisconnectFW()
	{
		if(theFWPtr->Connected) {
			theFWPtr->Connected = false;
			return 1;
		}			
		return 0;
	}

	int PixInsightASCOMFWDriver::SetConnected(bool connectFW)
	{
		if(connectFW == true && theFWPtr == NULL)
			return PixInsightASCOMFWDriver::ConnectFW();
		if(connectFW == true && theFWPtr->Connected == false)
			return PixInsightASCOMFWDriver::ConnectFW();
		else if(connectFW == true && theFWPtr->Connected == VARIANT_TRUE)
			return 1;
		else if(connectFW == false && theFWPtr->Connected == VARIANT_TRUE)
			return PixInsightASCOMFWDriver::DisconnectFW();
		else
			return 0;
	}

	
	String PixInsightASCOMFWDriver::Description()
	{
		return String("ASCOM FW Driver");
	}

	void PixInsightASCOMFWDriver::SetupDialog()
	{
		if(theFWPtr->Connected)
			theFWPtr->SetupDialog();
	}
	
	short PixInsightASCOMFWDriver::Position()
	{
		ASCOM_WRAP(Position);
	}

	int PixInsightASCOMFWDriver::SetPosition(uint8 p)
	{
		theFWPtr->Position = p;
		return p;
	}

	uint8 PixInsightASCOMFWDriver::MaxPosition()
	{
		uint8 i = SafeArrayGetElemsize(theFWPtr->Names);
		return i;
	}

	uint8 PixInsightASCOMFWDriver::MinPosition()
	{
		return 1;
	}

	bool PixInsightASCOMFWDriver::IsMoving()
	{
		if( theFWPtr->Position == -1 )
			return true;
		return false;
	}
}
