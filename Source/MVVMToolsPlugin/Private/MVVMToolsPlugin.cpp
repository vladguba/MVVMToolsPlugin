#include "MVVMToolsPlugin.h"
#include "Blueprint/UserWidget.h"

IMPLEMENT_MODULE(FMVVMToolsPluginModule, MVVMToolsPlugin)

// Called when the runtime module starts: binds to world initialization events
void FMVVMToolsPluginModule::StartupModule()
{
    FWorldDelegates::OnPostWorldInitialization.AddRaw(this, &FMVVMToolsPluginModule::OnWorldInit);
}

// Called when the runtime module shuts down: unbinds from world initialization events
void FMVVMToolsPluginModule::ShutdownModule()
{
    FWorldDelegates::OnPostWorldInitialization.RemoveAll(this);
}

/// Called after the world is initialized, this is where we can create our widget and add it to the viewport.
void FMVVMToolsPluginModule::OnWorldInit(UWorld* World, const UWorld::InitializationValues)
{
    if (!World->IsGameWorld()) return;

    static const FString Path = TEXT("/MVVMToolsPlugin/Widgets/WBP_MVVMTools.WBP_MVVMTools_C");
    UClass* WidgetBP = LoadClass<UUserWidget>(nullptr, *Path);
    if (!WidgetBP) return;

    World->GetTimerManager().SetTimerForNextTick([World, WidgetBP]()
        {
            if (APlayerController* PC = World->GetFirstPlayerController())
            {
                CreateWidget<UUserWidget>(PC, WidgetBP)->AddToViewport();
            }
        });
}