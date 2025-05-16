#include "MVVMToolsPluginEditor.h"
#include "WorkspaceMenuStructureModule.h"
#include "WorkspaceMenuStructure.h"
#include "MVVMToolsSlateWidget.h" 

#define LOCTEXT_NAMESPACE "MVVMDemo"

const FName FMVVMToolsPluginEditorModule::MVVMDemoTabName("MVVMDemo");

// Called when the plugin editor starts up: registers our custom tab in the global tab manager
void FMVVMToolsPluginEditorModule::StartupModule()
{
    FGlobalTabmanager::Get()
        ->RegisterNomadTabSpawner(MVVMDemoTabName,
            FOnSpawnTab::CreateRaw(this, &FMVVMToolsPluginEditorModule::OnSpawnPluginTab))
        .SetDisplayName(LOCTEXT("DemoTabTitle", "MVVM Demo"))
        .SetMenuType(ETabSpawnerMenuType::Enabled)
        .SetGroup(WorkspaceMenu::GetMenuStructure().GetDeveloperToolsMiscCategory());
}

// Called when the plugin editor shuts down: unregisters our custom tab
void FMVVMToolsPluginEditorModule::ShutdownModule()
{
    FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(MVVMDemoTabName);
}

// Spawns the actual dock tab containing our Slate widget
TSharedRef<SDockTab> FMVVMToolsPluginEditorModule::OnSpawnPluginTab(const FSpawnTabArgs&)
{
    return SNew(SDockTab)
        .TabRole(ETabRole::NomadTab)
        [
            SNew(SMVVMToolsSlateWidget)
                .Title(LOCTEXT("SlateWidgetTitle", "MVVM Tools Slate"))
        ];
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FMVVMToolsPluginEditorModule, MVVMToolsPluginEditor)