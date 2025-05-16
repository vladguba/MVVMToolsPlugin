#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MVVMToolsDataModel.h"
#include "MVVMToolsViewModel.generated.h"

UCLASS(Blueprintable)
class MVVMTOOLSPLUGIN_API UMVVMToolsViewModel : public UObject
{
    GENERATED_BODY()

public:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MVVM")
    UMVVMToolsDataModel* Model;

    UMVVMToolsViewModel(const FObjectInitializer& ObjectInitializer);

    UFUNCTION(BlueprintCallable, Category = "MVVM")
    void SetPlayerName(const FString& NewName);

    UFUNCTION(BlueprintCallable, Category = "MVVM")
    FString GetPlayerName() const;

    UFUNCTION(BlueprintCallable, Category = "Persistence")
    void SaveToJson(const FString& FilePath);

    UFUNCTION(BlueprintCallable, Category = "Persistence")
    void LoadFromJson(const FString& FilePath);
};