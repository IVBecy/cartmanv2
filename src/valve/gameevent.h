#pragma once

#include "../helpers/vmt.h"
 
class GameEvent {
public:
    const char* GetName() 
    {
        return vmt::callFunction<const char*>(this, 1);
    }

    int GetInt(const char* name, int defValue = 0)
    {
        return vmt::callFunction<int>(this, 6, name, defValue);
    }
       //// VIRTUAL_METHOD(int, getInt, 6, (const char* keyName, int defaultValue = 0), (this, keyName, defaultValue))
       // VIRTUAL_METHOD(float, getFloat, 8, (const char* keyName, float defaultValue = 0.0f), (this, keyName, defaultValue))
       // VIRTUAL_METHOD(const char*, getString, 9, (const char* keyName, const char* defaultValue = ""), (this, keyName, defaultValue))
       // VIRTUAL_METHOD(void, setString, 16, (const char* keyName, const char* value), (this, keyName, value))
};

class GameEventListener {
public:
    virtual ~GameEventListener() {}
    virtual void fireGameEvent(GameEvent* event) = 0;
    virtual int getEventDebugId() { return 42; }
};

class GameEventManager {
public:
    bool AddListener(GameEventListener* listener, const char* name)
    {
        return vmt::callFunction<bool>(this, 3, listener, name, false);
    }
};
