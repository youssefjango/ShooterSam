// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ShooterSamFinal : ModuleRules
{
	public ShooterSamFinal(ReadOnlyTargetRules Target) : base(Target)
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
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"ShooterSamFinal",
			"ShooterSamFinal/Variant_Platforming",
			"ShooterSamFinal/Variant_Platforming/Animation",
			"ShooterSamFinal/Variant_Combat",
			"ShooterSamFinal/Variant_Combat/AI",
			"ShooterSamFinal/Variant_Combat/Animation",
			"ShooterSamFinal/Variant_Combat/Gameplay",
			"ShooterSamFinal/Variant_Combat/Interfaces",
			"ShooterSamFinal/Variant_Combat/UI",
			"ShooterSamFinal/Variant_SideScrolling",
			"ShooterSamFinal/Variant_SideScrolling/AI",
			"ShooterSamFinal/Variant_SideScrolling/Gameplay",
			"ShooterSamFinal/Variant_SideScrolling/Interfaces",
			"ShooterSamFinal/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
