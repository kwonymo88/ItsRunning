// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraModifier.h"
#include "TzCameraModifier.generated.h"

/**
 * 
 */
UCLASS()
class RUNNINGHORSE_API UTzCameraModifier : public UCameraModifier
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TWeakObjectPtr<class ARunningHorseGameModeBase>	RunningGameMode;

protected:
	virtual void ModifyCamera(float DeltaTime, FVector ViewLocation, FRotator ViewRotation, float FOV, FVector& NewViewLocation, FRotator& NewViewRotation, float& NewFOV) override;

	virtual void EnableModifier() override;
	virtual void DisableModifier(bool bImmediate = false) override;
};
