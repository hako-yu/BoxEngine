
#pragma once

template<typename InFuncType>
class FQueueWorkExecutor
{
public:
	void Exec(const InFuncType& InFunc)
	{
		bIsBusy = true;
		ExecInternal(InFunc);
		bIsBusy = false;
	}

	bool CanExec()
	{
		return !bIsBusy;
	}

protected:
	virtual void ExecInternal(const InFuncType& InFunc) = 0;

private:
	bool bIsBusy = false;
};
