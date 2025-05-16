#include "MVVMToolsUserWidget.h"
#include "MVVMToolsViewModel.h"
#include "Components/EditableTextBox.h"
#include "Components/Button.h"

// Sets default values
void UMVVMToolsUserWidget::NativeConstruct()
{
    Super::NativeConstruct();

    if (!ViewModel)
    {
        ViewModel = NewObject<UMVVMToolsViewModel>(this);
    }

    if (UEditableTextBox* NameBox = Cast<UEditableTextBox>(GetWidgetFromName("NameTextBox")))
    {
        NameBox->OnTextChanged.AddDynamic(this, &UMVVMToolsUserWidget::OnNameTextChanged);
        NameBox->SetText(FText::FromString(ViewModel->GetPlayerName()));
    }

    if (SaveButton)
        SaveButton->OnClicked.AddDynamic(this, &UMVVMToolsUserWidget::OnSaveClicked);

    if (LoadButton)
        LoadButton->OnClicked.AddDynamic(this, &UMVVMToolsUserWidget::OnLoadClicked);
}

// This function is called when the text in the name box changes
void UMVVMToolsUserWidget::OnNameTextChanged(const FText& Text)
{
    ViewModel->SetPlayerName(Text.ToString());
}

// This function is called when the Save button is clicked
void UMVVMToolsUserWidget::OnSaveClicked()
{
    const FString Path = FPaths::ProjectSavedDir() / TEXT("data.json");
    ViewModel->SaveToJson(Path);
}

// This function is called when the Load button is clicked
void UMVVMToolsUserWidget::OnLoadClicked()
{
    const FString Path = FPaths::ProjectSavedDir() / TEXT("data.json");
    ViewModel->LoadFromJson(Path);
    if (NameTextBox)
        NameTextBox->SetText(FText::FromString(ViewModel->GetPlayerName()));
}