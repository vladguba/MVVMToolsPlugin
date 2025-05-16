#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

class UMVVMToolsEditorViewModel;

class SMVVMToolsSlateWidget : public SCompoundWidget
{
public:
    SLATE_BEGIN_ARGS(SMVVMToolsSlateWidget) {}
        SLATE_ARGUMENT(FText, Title)
    SLATE_END_ARGS()

    void Construct(const FArguments& InArgs);

private:
    UMVVMToolsEditorViewModel* ViewModel = nullptr;

    TArray<TSharedPtr<FAssetData>> ItemsSource;
    TSharedPtr<SListView<TSharedPtr<FAssetData>>> ListView;

    void OnAssetPicked(const FAssetData& AssetData);

    void RefreshList();

    TSharedRef<ITableRow> OnGenerateRow(
        TSharedPtr<FAssetData> Item,
        const TSharedRef<STableViewBase>& OwnerTable);

    FReply OnRemoveClicked(TSharedPtr<FAssetData> Item);
};