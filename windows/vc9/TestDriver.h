#include <IPixInsightCamera.h>

namespace pcl
{

	class TestDriver : public IPixInsightCamera
	{
	public:
		TestDriver();
		pcl::String  DoSomething();
		
	};

}
