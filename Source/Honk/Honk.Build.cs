// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Honk : ModuleRules
{
	public Honk(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "PhysXVehicles", "HeadMountedDisplay" });
		PublicDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		PublicDefinitions.Add("HMD_MODULE_INCLUDED=1");
	}
}
