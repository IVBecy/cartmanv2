#include "../valve/cbaseentity.h"
#include "../valve/imaterialsystem.h"
#include "../valve/istudiorender.h"
#include "../valve/modelrender.h"
#include "../valve/cmatrix.h"
#include "../valve/gameevent.h"


namespace visual {
	void chams(void* results, const ModelRenderInfo& info, CMatrix3x4* bones, float* flexWeight, float* flexDelayedWeight, const CVector& modelOrigin, const int32_t flags);
	void skyColour();
	void skyBox();
	void hitMarker();
	void setMaterial(IMaterial* mat,bool state, float colours[3]);
}