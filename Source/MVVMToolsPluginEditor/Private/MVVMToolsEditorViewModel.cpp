#include "MVVMToolsEditorViewModel.h"
#include "MVVMToolsEditorDataModel.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "DragAndDrop/AssetDragDropOp.h"

// Initializes the view model by assigning the data model
void UMVVMToolsEditorViewModel::Initialize()
{
    Model = GetMutableDefault<UMVVMToolsEditorDataModel>();
}

// Adds the specified asset to the list of favorite assets
void UMVVMToolsEditorViewModel::AddFavoriteAsset(const FSoftObjectPath& AssetPath)
{
    TSoftObjectPtr<UObject> SoftPtr(AssetPath);
    if (!Model->FavoriteAssets.Contains(SoftPtr))
    {
        Model->FavoriteAssets.Add(SoftPtr);
        Model->SaveConfig();
    }
}

// Removes the specified asset from the list of favorite assets
void UMVVMToolsEditorViewModel::RemoveFavoriteAsset(const FSoftObjectPath& AssetPath)
{
    TSoftObjectPtr<UObject> SoftPtr(AssetPath);
    Model->FavoriteAssets.Remove(SoftPtr);
    Model->SaveConfig();
}

const TArray<TSoftObjectPtr<UObject>>& UMVVMToolsEditorViewModel::GetFavoriteAssets() const
{
    return Model->FavoriteAssets;
}

// Creates and returns a drag-and-drop operation for the given asset path
TSharedRef<FAssetDragDropOp> UMVVMToolsEditorViewModel::CreateAssetDragDropOp(const FSoftObjectPath& AssetPath) const
{
    FAssetRegistryModule& ARModule =
        FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
    FAssetData Data = ARModule.Get().GetAssetByObjectPath(AssetPath);

    TArray<FAssetData> Assets;
    Assets.Add(MoveTemp(Data));
    return FAssetDragDropOp::New(Assets);
}