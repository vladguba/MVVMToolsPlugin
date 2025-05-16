#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FMVVMToolsPluginModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:
	void OnWorldInit(UWorld* World, const UWorld::InitializationValues);
};
