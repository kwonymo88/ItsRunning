// Fill out your copyright notice in the Description page of Project Settings.


#include "TZAccelComponent.h"
#include "TzRunner.h"

// Sets default values for this component's properties
UTZAccelComponent::UTZAccelComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTZAccelComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTZAccelComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UTZAccelComponent::ActivateBuff()
{
	Super::ActivateBuff();

	if (OwnerRunner.IsValid())
	{
		ATzRunner* RunnerActor = Cast<ATzRunner>(OwnerRunner->GetClass()->GetDefaultObject());
		if (RunnerActor)
		{
			TargetAddSpeed = FMath::RandRange(AddSpeedMin, AddSpeedMax);
			//OwnerRunner->Set(FMath::FInterpTo(OwnerRunner->GetSpeed(), TargetSpeed, DeltaTime, InterpSpeed));
			bActivate = true;
		}
	}
}

void UTZAccelComponent::DeactivateBuff()
{
	if (OwnerRunner.IsValid())
	{
		ATzRunner* RunnerActor = Cast<ATzRunner>(OwnerRunner->GetClass()->GetDefaultObject());
		if (RunnerActor)
		{
			//OwnerRunner->SetSpeed(RunnerActor->GetSpeed());
		}
	}
	Super::DeactivateBuff();
}

