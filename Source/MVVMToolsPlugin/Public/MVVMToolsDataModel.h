#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MVVMToolsDataModel.generated.h"

UCLASS(BlueprintType)
class MVVMTOOLSPLUGIN_API UMVVMToolsDataModel : public UObject
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Data")
    FString PlayerName;
};