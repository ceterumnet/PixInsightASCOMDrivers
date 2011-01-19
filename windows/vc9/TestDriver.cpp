#include "TestDriver.h"


namespace pcl
{

	TestDriver::TestDriver()
	{
		//Console().WriteLn("CTOR?");
	}

	//TestDriver * TestDriver::Initialize()
	//{
	//	Console().WriteLn("initializing at least...");
	//	return new TestDriver();
	//}
	
	pcl::String TestDriver::DoSomething()
	{
		//Console().WriteLn("doin somethin");
		return String("Data from the TestDriver");
	}

}
