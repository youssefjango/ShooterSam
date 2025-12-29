// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ShooterSam : ModuleRules
{
	public ShooterSam(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate",
			"Niagara"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"ShooterSam",
			"ShooterSam/Variant_Platforming",
			"ShooterSam/Variant_Platforming/Animation",
			"ShooterSam/Variant_Combat",
			"ShooterSam/Variant_Combat/AI",
			"ShooterSam/Variant_Combat/Animation",
			"ShooterSam/Variant_Combat/Gameplay",
			"ShooterSam/Variant_Combat/Interfaces",
			"ShooterSam/Variant_Combat/UI",
			"ShooterSam/Variant_SideScrolling",
			"ShooterSam/Variant_SideScrolling/AI",
			"ShooterSam/Variant_SideScrolling/Gameplay",
			"ShooterSam/Variant_SideScrolling/Interfaces",
			"ShooterSam/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
