#include "MVVMToolsSlateWidget.h"
#include "MVVMToolsEditorViewModel.h"
#include "MVVMToolsEditorDataModel.h"
#include "PropertyCustomizationHelpers.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "DragAndDrop/AssetDragDropOp.h"

// Constructs the Slate widget, creates its ViewModel, and builds the UI layout
void SMVVMToolsSlateWidget::Construct(const FArguments& InArgs)
{
    ViewModel = NewObject<UMVVMToolsEditorViewModel>(
        GetTransientPackage(),
        NAME_None,
        RF_Standalone
    );
    ViewModel->AddToRoot();
    ViewModel->Initialize();

    RefreshList();

    ChildSlot
        [
            SNew(SBorder).Padding(8)
                [
                    SNew(SVerticalBox)

                        + SVerticalBox::Slot().AutoHeight().Padding(0, 0, 0, 6)
                        [
                            SNew(STextBlock)
                                .Font(FAppStyle::GetFontStyle("ItalicFont"))
                                .Text(FText::FromString(
                                    "Add your favorite assets below,\n"
                                    "then drag-and-drop them onto the level viewport to place."
                                ))
                        ]

                    + SVerticalBox::Slot().AutoHeight().Padding(0, 0, 0, 8)
                        [
                            SNew(STextBlock)
                                .Font(FAppStyle::GetFontStyle("BoldFont"))
                                .Text(InArgs._Title)
                        ]

                        + SVerticalBox::Slot().AutoHeight().Padding(0, 0, 0, 8)
                        [
                            SNew(SObjectPropertyEntryBox)
                                .AllowedClass(UStaticMesh::StaticClass())
                                .AllowClear(true)
                                .OnObjectChanged(FOnSetObject::CreateSP(
                                    this, &SMVVMToolsSlateWidget::OnAssetPicked))
                        ]

                        + SVerticalBox::Slot().FillHeight(1)
                        [
                            SAssignNew(ListView, SListView<TSharedPtr<FAssetData>>)
                                .ListItemsSource(&ItemsSource)
                                .OnGenerateRow(this, &SMVVMToolsSlateWidget::OnGenerateRow)
                        ]
                ]
        ];
}

// Handler invoked when the user picks an asset: adds it via the ViewModel and refreshes the list
void SMVVMToolsSlateWidget::OnAssetPicked(const FAssetData& AssetData)
{
    ViewModel->AddFavoriteAsset(AssetData.ToSoftObjectPath());
    RefreshList();
}

// Rebuilds the list of shared pointers to FAssetData from the ViewModel’s soft pointers
void SMVVMToolsSlateWidget::RefreshList()
{
    ItemsSource.Empty();
    FAssetRegistryModule& AR = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");

    for (const TSoftObjectPtr<UObject>& SoftPtr : ViewModel->GetModel()->FavoriteAssets)
    {
        const FSoftObjectPath& Path = SoftPtr.ToSoftObjectPath();
        FAssetData Data = AR.Get().GetAssetByObjectPath(Path);
        if (Data.IsValid())
        {
            ItemsSource.Add(MakeShared<FAssetData>(Data));
        }
    }

    if (ListView.IsValid())
    {
        ListView->RequestListRefresh();
    }
}

// Generates a list row: configures drag-and-drop and remove-button functionality
TSharedRef<ITableRow> SMVVMToolsSlateWidget::OnGenerateRow(
    TSharedPtr<FAssetData> Item,
    const TSharedRef<STableViewBase>& OwnerTable)
{
    return SNew(STableRow<TSharedPtr<FAssetData>>, OwnerTable)
        .OnDragDetected(FOnDragDetected::CreateLambda([this, Item](const FGeometry&, const FPointerEvent&)
            {
                TSharedRef<FAssetDragDropOp> DragOp = ViewModel->CreateAssetDragDropOp(
                    Item->ToSoftObjectPath());
                return FReply::Handled().BeginDragDrop(DragOp);
            }))
        .Content()
        [
            SNew(SHorizontalBox)

                + SHorizontalBox::Slot().FillWidth(1).VAlign(VAlign_Center)
                [
                    SNew(STextBlock)
                        .Text(FText::FromName(Item->AssetName))
                ]

                + SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center).Padding(4, 0, 0, 0)
                [
                    SNew(SButton)
                        .Text(FText::FromString("X"))
                        .OnClicked_Lambda([this, Item]()
                            {
                                return OnRemoveClicked(Item);
                            })
                ]
        ];
}

// Called when the user clicks the "X": asks ViewModel to remove and then refreshes the list
FReply SMVVMToolsSlateWidget::OnRemoveClicked(TSharedPtr<FAssetData> Item)
{
    ViewModel->RemoveFavoriteAsset(Item->ToSoftObjectPath());
    RefreshList();
    return FReply::Handled();
}