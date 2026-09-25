using UnrealBuildTool;

public class DesignBenchEditor : ModuleRules
{
    public DesignBenchEditor(ReadOnlyTargetRules Target) : base(Target)
    {
        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core"
            }
        );

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "CoreUObject",
                "Engine",
                "DesignBench",
                "DataValidation",
		"GameplayTags",
		"AssetRegistry",
		"UnrealEd"
            }
        );
    }
}