// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class SpaceCatRTS : ModuleRules
{
	public SpaceCatRTS(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "NavigationSystem", "AIModule" });

        PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore", "UMG" });
    }
}
