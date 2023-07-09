// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraActor.h"
#include "TzCameraActor.generated.h"

/**
 * 
 */
class ARunningHorseGameModeBase;

UCLASS()
class RUNNINGHORSE_API ATzCameraActor : public ACameraActor
{
	GENERATED_BODY()

	ATzCameraActor(const FObjectInitializer& ObjectInitializer);

private:
	TWeakObjectPtr<ARunningHorseGameModeBase> GameModeBase;

	UPROPERTY(EditAnywhere, Category = "TzCameraActor | Data")
	FVector BaseLocation;

	UPROPERTY(EditAnywhere, Category = "TzCameraActor | Data")
	FVector BaseViewLocation;

	UPROPERTY(EditAnywhere, Category = "TzCameraActor | Data")
	float fInterpSpeed;

public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void UpdateLocationByRunnerLoc(float DeltaSeconds, const FVector& RunnerLoc);
	bool GetCameraHitResult(FHitResult& OutHit);
};
