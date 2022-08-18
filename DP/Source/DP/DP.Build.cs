// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class DP : ModuleRules
{
	public DP(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}
