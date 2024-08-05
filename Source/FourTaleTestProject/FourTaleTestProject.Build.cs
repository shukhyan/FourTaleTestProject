// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class FourTaleTestProject : ModuleRules
{
	public FourTaleTestProject(ReadOnlyTargetRules Target) : base(Target)
	{
		PrivateDependencyModuleNames.AddRange(new string[] { "GameplayTasks", "Niagara", "GameplayTags", "AIModule" });
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "GameplayAbilities" });
	}
}
