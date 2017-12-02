

#include "ActivityCode.h"



QString Activity_toString(ActivityCode id)
{
	if(id == code_onInitialize)
	{
		return "onInitialize";
	}
	else if(id == code_onFinalize)
	{
		return "onFinalize";
	}
	else if(id == code_onStartup)
	{
		return "onStartup";
	}
	else if(id == code_onShutdown)
	{
		return "onShutdown";
	}
	else if(id == code_onActivated)
	{
		return "onActivated";
	}
	else if(id == code_onDeactivated)
	{
		return "onDeactivated";
	}
	else if(id == code_onExecute)
	{
		return "onExecute";
	}
	else if (id == code_onAborting)
	{
		return "onAborting";
	}
	else if(id == code_onError)
	{
		return "onError";
	}
	else if(id == code_onReset)
	{
		return "onReset";
	}
	else if(id == code_onStateUpdate)
	{
		return "onStateUpdate";
	}
	else if(id == code_onRateChanged)
	{
		return "onRateChanged";
	}
	else if (id == code_inputFromSimulator)
	{
		return "inputFromSimulator";
	}
	else if (id == code_outputToSimulator)
	{
		return "outputToSimulator";
	}
	else if (id == code_setBody)
	{
		return "setBody";
	}

	return "";
}

