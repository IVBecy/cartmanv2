#pragma once
// SDK
#include "../valve/clientclass.h"
#include "../valve/ivengineclient.h"
#include "../valve/icliententitylist.h"
#include "../valve/iclientmodeshared.h"
#include "../valve/ibaseclientdll.h"
#include "../valve/istudiorender.h"
#include "../valve/imaterialsystem.h"
#include "../valve/iglobalvars.h"
#include "../valve/ienginetrace.h"
#include "../valve/icvar.h"
#include "../valve/ivpanel.h"
#include "../valve/ienginevgui.h"
#include "../valve/ivdebugoverlay.h"
#include "../valve/isurface.h"
#include "../valve/iglowmanager.h"
#include "../valve/modelrender.h"
#include "../valve/modelinfo.h"
#include "../valve/ivrenderview.h"
#include "../valve//gameevent.h"
#include "../valve/input.h"

#include "../helpers/pattern.h"

// Interface getter
typedef void* (__cdecl* tCreateInterface)(const char* name, int* retCode);
void* GetInterface(const char* interfaceName, const char* dll);

// Interface list
namespace interfaces
{
    inline IBaseClientDLL* baseClient = (IBaseClientDLL*)GetInterface("VClient018", "client.dll");
    inline IClientModeShared* clientMode = **(IClientModeShared***)((*(uintptr_t**)baseClient)[10] + 0x5);
    inline IVEngineClient* baseEngine = (IVEngineClient*)GetInterface("VEngineClient014", "engine.dll");
    inline IClientEntityList* entityList = (IClientEntityList*)GetInterface("VClientEntityList003", "client.dll");
    inline ClientClass* clientClass = baseClient->GetAllClasses();
    inline IStudioRender* studioRender = (IStudioRender*)GetInterface("VStudioRender026", "studiorender.dll");
    inline IMaterialSystem* materialSystem = (IMaterialSystem*)GetInterface("VMaterialSystem080", "materialsystem.dll");
    inline IGlobalVars* globals = **(IGlobalVars***)((*(uintptr_t**)(baseClient))[11] + 10);;
    inline IEngineTrace* engineTrace = (IEngineTrace*)GetInterface("EngineTraceClient004", "engine.dll");
    inline ICvar* cVar = (ICvar*)GetInterface("VEngineCvar007","vstdlib.dll");
    inline IVPanel* panel = (IVPanel*)GetInterface("VGUI_Panel009", "vgui2.dll");
    inline IEngineVGui* engineGui = (IEngineVGui*)GetInterface("VEngineVGui001", "engine.dll");
    inline IVDebugOverlay* debugOverlay = (IVDebugOverlay*)GetInterface("VDebugOverlay004", "engine.dll");
    inline ISurface* surface = (ISurface*)GetInterface("VGUI_Surface031", "vguimatsurface.dll");
    inline ModelRender* modelRender = (ModelRender*)GetInterface("VEngineModel016", "engine.dll");
    inline ModelInfo* modelInfo = (ModelInfo*)GetInterface("VModelInfoClient004", "engine.dll");
    inline IVRenderView* renderView = (IVRenderView*)GetInterface("VEngineRenderView014", "engine.dll");
    inline GameEvent* gameEvent = (GameEvent*)GetInterface("GAMEEVENTSMANAGER002", "engine.dll");
    inline CInput* input = *(CInput**)((*(uintptr_t**)baseClient)[16] + 0x1);
}
