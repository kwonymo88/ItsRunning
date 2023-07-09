// Fill out your copyright notice in the Description page of Project Settings.


#include "TzCameraModifier.h"
#include "RunningHorseGameModeBase.h"

void UTzCameraModifier::ModifyCamera(float DeltaTime, FVector ViewLocation, FRotator ViewRotation, float FOV, FVector& NewViewLocation, FRotator& NewViewRotation, float& NewFOV)
{
	if (RunningGameMode.IsValid())
	{
		if (RunningGameMode->ShouldUpdateCamera())
		{
			//RunningGameMode->LeadRunnerLocation.X;
		}
	}
}

void UTzCameraModifier::EnableModifier()
{
	if (CameraOwner)
	{
		//Cast<TzPlayerController>(CameraOwner->GetOwningPlayerController());
		RunningGameMode = Cast<ARunningHorseGameModeBase>(GetWorld()->GetAuthGameMode());
	}
}

void UTzCameraModifier::DisableModifier(bool bImmediate)
{
}
