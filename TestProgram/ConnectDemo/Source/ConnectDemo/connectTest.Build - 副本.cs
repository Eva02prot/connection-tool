// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.IO;

public class connectTest : ModuleRules
{
    //get the module path to location ThirdPartyPath
    private string ModulePath
    {
        get
        {
            return ModuleDirectory;
        }
    }

    //get the ThirdPartyPath path
    private string ThirdPartyPath
    {
        get
        {
            return Path.GetFullPath(Path.Combine(ModulePath, "../../ThirdParty"));
        }
    }

    public connectTest(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });

        PublicIncludePaths.Add(Path.Combine(ThirdPartyPath, "include"));
        PublicAdditionalLibraries.Add(Path.Combine(ThirdPartyPath, "lib", "ConnectionPlatformSDK.lib"));

        // Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
    }
}
