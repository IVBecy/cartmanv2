#include "../helpers/vmt.h"

class IVRenderView
{
public:

	void SetBlend(float blend) 
	{
		vmt::callFunction<float>(this, 4);
	}

	void SetColorModulation(float blend[3]) 
	{
		vmt::callFunction<float>(this, 6,blend[0], blend[1], blend[2]);
	}

};