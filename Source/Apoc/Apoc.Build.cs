// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Apoc : ModuleRules
{
	public Apoc(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[]
        {
	        "Core", 
	        "CoreUObject", 
	        "Engine", 
	        "InputCore", 
	        "HeadMountedDisplay", 
	        "NavigationSystem", 
	        "AIModule"
        });
        
        PublicIncludePaths.AddRange(new string[]
        {
	        "Apoc/Character",
	        "Apoc/FuncLibrary",
	        "Apoc/Game",
	        "Apoc/Weapon"
        });
    }
	
}