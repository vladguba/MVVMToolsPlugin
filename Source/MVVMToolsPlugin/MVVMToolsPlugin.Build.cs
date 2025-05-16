using UnrealBuildTool;

public class MVVMToolsPlugin : ModuleRules
{
	public MVVMToolsPlugin(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new[]
       {
            "Core",
            "CoreUObject",
            "Engine",
            "UMG"
        });
        PrivateDependencyModuleNames.AddRange(new[]
        {
            "Json",
            "JsonUtilities"
        });
    }
}
