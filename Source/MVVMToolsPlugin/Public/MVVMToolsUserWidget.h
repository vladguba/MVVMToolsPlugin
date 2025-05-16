#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MVVMToolsUserWidget.generated.h"

class UMVVMToolsViewModel;
class UEditableTextBox;
class UButton;

UCLASS()
class MVVMTOOLSPLUGIN_API UMVVMToolsUserWidget : public UUserWidget
{
    GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MVVM")
    UMVVMToolsViewModel* ViewModel;

    UPROPERTY(meta = (BindWidget))
    UEditableTextBox* NameTextBox;

    UPROPERTY(meta = (BindWidget))
    UButton* SaveButton;

    UPROPERTY(meta = (BindWidget))
    UButton* LoadButton;

    virtual void NativeConstruct() override;

private:
    UFUNCTION()
    void OnNameTextChanged(const FText& Text);

    UFUNCTION()
    void OnSaveClicked();

    UFUNCTION()
    void OnLoadClicked();
};