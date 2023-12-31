
#pragma once

class FRunnable
{
public:
    virtual void Init() = 0;
    virtual void Run() = 0;
    virtual void Stop() = 0;
	virtual void Exit() = 0;
};
