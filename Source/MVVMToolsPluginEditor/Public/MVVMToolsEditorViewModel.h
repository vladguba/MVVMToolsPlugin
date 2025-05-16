#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MVVMToolsEditorViewModel.generated.h"

class UMVVMToolsEditorDataModel;
class FAssetDragDropOp;

UCLASS()
class MVVMTOOLSPLUGINEDITOR_API UMVVMToolsEditorViewModel : public UObject
{
    GENERATED_BODY()

public:
    UFUNCTION()
    void Initialize();

    UFUNCTION()
    void AddFavoriteAsset(const FSoftObjectPath& AssetPath);

    UFUNCTION()
    void RemoveFavoriteAsset(const FSoftObjectPath& AssetPath);

    const TArray<TSoftObjectPtr<UObject>>& GetFavoriteAssets() const;

    TSharedRef<FAssetDragDropOp> CreateAssetDragDropOp(const FSoftObjectPath& AssetPath) const;

    FORCEINLINE UMVVMToolsEditorDataModel* GetModel() const { return Model; }

private:
    UMVVMToolsEditorDataModel* Model = nullptr;
};