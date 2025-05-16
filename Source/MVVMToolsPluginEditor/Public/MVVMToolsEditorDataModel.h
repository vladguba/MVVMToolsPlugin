#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MVVMToolsEditorDataModel.generated.h"

UCLASS(config = EditorPerProjectUserSettings, defaultconfig)
class MVVMTOOLSPLUGINEDITOR_API UMVVMToolsEditorDataModel : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UPROPERTY(config, EditAnywhere, Category = "Quick Access")
	TArray<TSoftObjectPtr<UObject>> FavoriteAssets;
};