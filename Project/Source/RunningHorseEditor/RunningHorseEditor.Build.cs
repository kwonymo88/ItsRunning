// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class RunningHorseEditor : ModuleRules
{
	public RunningHorseEditor(ReadOnlyTargetRules Target) : base(Target)
	{
        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "CoreUObject",
                "ApplicationCore",
                "Engine",
                "Slate",
                "UMG",
            }
        );

        PrivateDependencyModuleNames.AddRange(
        new string[]
            {
                "SlateCore",
            }
        );

        if (Target.Type == TargetType.Editor)
        {
            PublicDependencyModuleNames.AddRange(
                new string[] {
                    "EditorFramework",
                    "UnrealEd",
                }
            );
        }

        DynamicallyLoadedModuleNames.AddRange(
            new string[] {
                
            }
        );

        // Circular references that need to be cleaned up
        CircularlyReferencedDependentModules.AddRange(
           new string[] {
                
           }
       );
    }
}
