#include "MVVMToolsViewModel.h"
#include "JsonObjectConverter.h"

UMVVMToolsViewModel::UMVVMToolsViewModel(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    Model = ObjectInitializer.CreateDefaultSubobject<UMVVMToolsDataModel>(this, TEXT("DataModel"), false);
    Model->PlayerName = TEXT("Player");
}

// Sets the player's name in the data model.
void UMVVMToolsViewModel::SetPlayerName(const FString& NewName)
{
    if (Model) Model->PlayerName = NewName;
}

// Gets the player's name from the data model.
FString UMVVMToolsViewModel::GetPlayerName() const
{
    return Model ? Model->PlayerName : TEXT("");
}

// Serializes the data model to a JSON file at the specified path.
void UMVVMToolsViewModel::SaveToJson(const FString& FilePath)
{
    FString Json;
    FJsonObjectConverter::UStructToJsonObjectString(
        Model->GetClass(),
        Model,
        Json,
        0, 0
    );
    FFileHelper::SaveStringToFile(Json, *FilePath);
}

// Loads the data model from a JSON file at the specified path.
void UMVVMToolsViewModel::LoadFromJson(const FString& FilePath)
{
    FString Json;
    if (FFileHelper::LoadFileToString(Json, *FilePath))
    {
        FJsonObjectConverter::JsonObjectStringToUStruct<UMVVMToolsDataModel>(
            Json,
            Model,
            0, 0,
            false,
            nullptr
        );
    }
}