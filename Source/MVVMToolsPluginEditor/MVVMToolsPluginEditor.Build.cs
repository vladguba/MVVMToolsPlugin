using UnrealBuildTool;

public class MVVMToolsPluginEditor : ModuleRules
{
	public MVVMToolsPluginEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PrivateDependencyModuleNames.AddRange(new[]
       {
            "Core",
            "CoreUObject",
            "Engine",
            "Slate",
            "SlateCore",
            "WorkspaceMenuStructure",
            "InputCore",
            "DeveloperSettings",
            "UnrealEd",
            "PropertyEditor"
        });
    }
}
