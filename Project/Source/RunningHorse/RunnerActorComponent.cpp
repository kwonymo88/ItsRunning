// Fill out your copyright notice in the Description page of Project Settings.


#include "RunnerActorComponent.h"
#include "RunningHorse/RunningHorseGameModeBase.h"
#include "TzRunner.h"

// Sets default values for this component's properties
URunnerActorComponent::URunnerActorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void URunnerActorComponent::OnRegister()
{
	Super::OnRegister();

	OwnerRunner = Cast<ATzRunner>(GetOwner());
}

// Called when the game starts
void URunnerActorComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	ActivateBuff();
}


// Called every frame
void URunnerActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	if (ActivationTime + TargetActiveTime < GetWorld()->GetTimeSeconds())
	{
		DeactivateBuff();
	}
}

#pragma optimize("", off)
void URunnerActorComponent::ActivateBuff()
{
	ActivationTime = GetWorld()->GetTimeSeconds();
	TargetActiveTime = FMath::RandRange(ActiveTimeMin, ActiveTimeMax);

	if (!OwnerRunner.IsValid())
	{
		return;
	}

	if (ARunningHorseGameModeBase* pHorseGameMode = GetWorld()->GetAuthGameMode<ARunningHorseGameModeBase>())
	{
		RunnerRankAdventage = (pHorseGameMode->GetRunnerNum() - pHorseGameMode->GetRunnerRank(OwnerRunner.Get())) * 0.03f;
		if (OwnerRunner.IsValid())
		{
			TargetAddSpeed = FMath::RandRange(AddSpeedMin, AddSpeedMax);
			float DecreaseSpeed = TargetAddSpeed * RunnerRankAdventage;
			TargetAddSpeed -= DecreaseSpeed;
			OwnerRunner->IncreaseAddSpeed(TargetAddSpeed);
			bActivate = true;
		}

		UE_LOG(LogTemp, Log, TEXT("%s"), *FString::Format(TEXT("ActivateBuff [{0}]"), { OwnerRunner->GetName() }));
	}
}
#pragma optimize("", on)

void URunnerActorComponent::DeactivateBuff()
{
	if (OwnerRunner.IsValid())
	{
		OwnerRunner->IncreaseAddSpeed(-TargetAddSpeed);
		UE_LOG(LogTemp, Log, TEXT("%s"), *FString::Format(TEXT("DeactivateBuff [{0}]"), { OwnerRunner->GetName() }));
		OwnerRunner->RemoveRunnerComponent(this);
		OwnerRunner.Reset();
	}

	OwnerRunner.Reset();
	bActivate = false;
}

