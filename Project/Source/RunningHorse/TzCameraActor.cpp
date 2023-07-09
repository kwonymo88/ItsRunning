// Fill out your copyright notice in the Description page of Project Settings.


#include "TzCameraActor.h"
#include "RunningHorseGameModeBase.h"

ATzCameraActor::ATzCameraActor(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	
}

void ATzCameraActor::BeginPlay()
{
	GameModeBase = GetWorld()->GetAuthGameMode<ARunningHorseGameModeBase>();

	/*FHitResult HitResult;
	if (GetCameraHitResult(HitResult))
	{
		BaseViewLocation = HitResult.ImpactPoint;
	}
	else
	{
		check(false);
	}
	BaseLocation = GetActorLocation();*/
}

void ATzCameraActor::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (GameModeBase.IsValid() && GameModeBase->ShouldUpdateCamera())
	{
		UpdateLocationByRunnerLoc(DeltaSeconds, GameModeBase->LeadRunnerLocation);
	}
}

void ATzCameraActor::UpdateLocationByRunnerLoc(float DeltaSeconds, const FVector& RunnerLoc)
{
	FVector CurrentActorLoc = GetActorLocation();
	if (RunnerLoc.X > CurrentActorLoc.X)
	{
		double TargetX = FMath::FInterpTo(CurrentActorLoc.X, RunnerLoc.X, DeltaSeconds, fInterpSpeed);
		SetActorLocation(FVector(TargetX, CurrentActorLoc.Y, CurrentActorLoc.Z));
	}
}

bool ATzCameraActor::GetCameraHitResult(FHitResult& OutHit)
{
	FVector StartLoc = GetActorLocation();
	FVector EndLoc = GetActorLocation() + (GetActorForwardVector() * 2000.f);

	FCollisionQueryParams Params;
	if (GetWorld()->LineTraceSingleByChannel(OutHit, StartLoc, EndLoc, ECollisionChannel::ECC_Visibility, Params))
	{
		return true;
		
	}
	return false;
}
