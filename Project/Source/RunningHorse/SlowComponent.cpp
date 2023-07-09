// Fill out your copyright notice in the Description page of Project Settings.


#include "SlowComponent.h"
#include "TzRunner.h"

// Sets default values for this component's properties
USlowComponent::USlowComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USlowComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void USlowComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	/*if (OwnerRunner.IsValid())
	{
		OwnerRunner->SetAddSpeed(FMath::FInterpTo(OwnerRunner->GetSpeed(), TargetSpeed, DeltaTime, InterpSpeed));
	}*/
}

void USlowComponent::ActivateBuff()
{
	Super::ActivateBuff();

	if (OwnerRunner.IsValid())
	{
		ATzRunner* RunnerActor = Cast<ATzRunner>(OwnerRunner->GetClass()->GetDefaultObject());
		if (RunnerActor)
		{
			TargetAddSpeed = FMath::RandRange(AddSpeedMin, AddSpeedMax);
			OwnerRunner->IncreaseAddSpeed(TargetAddSpeed);
			bActivate = true;
		}
	}
}

void USlowComponent::DeactivateBuff()
{
	if (OwnerRunner.IsValid())
	{
		ATzRunner* RunnerActor = Cast<ATzRunner>(OwnerRunner->GetClass()->GetDefaultObject());
		if (RunnerActor)
		{
			OwnerRunner->IncreaseAddSpeed(-TargetAddSpeed);
		}
	}
	Super::DeactivateBuff();
}

