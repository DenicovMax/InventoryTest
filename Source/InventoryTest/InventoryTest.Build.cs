// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class InventoryTest : ModuleRules
{
	public InventoryTest(ReadOnlyTargetRules Target) : base(Target)
	{
		PrivateDependencyModuleNames.AddRange(new string[] { "MediaAssets", });
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject",
			"Engine", "InputCore", "HeadMountedDisplay", 
			"UMG" , "SlateCore", "InventoryCore", "MediaAssets", "DesktopPlatform", "Slate", "QuestSystem" });
	}
}
