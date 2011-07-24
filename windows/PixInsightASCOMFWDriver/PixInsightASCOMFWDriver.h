#include <IPixInsightFilterWheel.h>
#include "stdafx.h"
#include <atlsafe.h>
#pragma once

#import "c:\Program Files (x86)\Common Files\ASCOM\Interface\AscomMasterInterfaces.tlb"
#import "C:\\Windows\\System32\\ScrRun.dll" \
	rename_namespace("SystemOld") \
	rename("DeleteFile","DeleteFileItem") \
	rename("MoveFile","MoveFileItem") \
	rename("CopyFile","CopyFileItem") \
	rename("FreeSpace","FreeDriveSpace") \
	rename("Unknown","UnknownDiskType") \
	rename("Folder","DiskFolder")

#import "progid:DriverHelper.Chooser" \
	rename("Yield","ASCOMYield") \
	rename("MessageBox","ASCOMMessageBox")

//#using <mscorlib.dll>
using namespace AscomInterfacesLib;
using namespace DriverHelper;

namespace pcl
{

	class PixInsightASCOMFWDriver : public IPixInsightFilterWheel
	{
	public:
		PixInsightASCOMFWDriver ();
		virtual void SetLogger(void(*)(String));
		virtual void Dispose();
	    virtual String Description();
		virtual bool Connected();
	    virtual int SetConnected(bool);
		virtual void SetupDialog();
		virtual short Position();
		virtual int SetPosition(uint8);
		virtual uint8 MaxPosition();
		virtual uint8 MinPosition();
		virtual bool IsMoving();
	private:
		void (*theLogger)(String);
		int ConnectFW();
		int DisconnectFW();
		IFilterWheelPtr theFWPtr;
		uint16 ASCOMDataToPi( long );
		
	};

}
