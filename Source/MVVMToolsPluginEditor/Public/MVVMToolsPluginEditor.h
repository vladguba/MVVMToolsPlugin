#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FMVVMToolsPluginEditorModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:
	TSharedRef<class SDockTab> OnSpawnPluginTab(const class FSpawnTabArgs& Args);

	static const FName MVVMDemoTabName;
};
