// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class NexusDefense : ModuleRules
{
	public NexusDefense(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicIncludePaths.AddRange(new string[] { "NexusDefense" });

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "UMG", "AssetRegistry" });
	}
}
