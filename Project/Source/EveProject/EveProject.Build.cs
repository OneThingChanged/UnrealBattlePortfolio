// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class EveProject : ModuleRules
{
	public EveProject(ReadOnlyTargetRules Target) : base(Target)
	{
		PrivateDependencyModuleNames.AddRange(new string[] { "MovieSceneTools" });
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { 
			"Core", 
			"GameplayTags", 
			"CoreUObject", 
			"Engine", 
			"InputCore", 
			"EnhancedInput", 
			"Niagara", 
			"Slate", 
			"SlateCore", 
			"UMG",
			"AIModule",
			"GameplayTasks",
			"NavigationSystem",
			"OnlineSubsystem",
			"OnlineSubsystemUtils",
			"AkAudio"
		});
		
		DynamicallyLoadedModuleNames.Add("OnlineSubsystemNull");

		PrivateIncludePaths.Add("EveProject/Public");
	}
}
