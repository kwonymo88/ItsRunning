// Fill out your copyright notice in the Description page of Project Settings.


#include "TzLane.h"
#include "TzRunner.h"

// Sets default values
ATzLane::ATzLane()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	if (RootComponent)
	{
		StartPoint = CreateDefaultSubobject<USceneComponent>(TEXT("StartPoint"));
		if (StartPoint)
		{
			StartPoint->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
		}

		GoalPoint = CreateDefaultSubobject<USceneComponent>(TEXT("GoalPoint"));
		if (GoalPoint)
		{
			GoalPoint->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
		}
	}
	LaneState = ESTATE_LANE::ESTATE_NONE;
}

// Called when the game starts or when spawned
void ATzLane::BeginPlay()
{
	Super::BeginPlay();

	
}

// Called every frame
void ATzLane::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (LaneRunner && LaneRunner->IsRunning())
	{
		if (FVector::DotProduct(LaneRunner->GetActorForwardVector(), LaneRunner->GetRunnerDir()) <= 0.f)
		{
			LaneRunner->FinishCharacter();
			UE_LOG(LogTemp, Log, TEXT("Finished Runner"));
			LaneState = ESTATE_LANE::ESTATE_FINISHED;
			if (DelegateFinishedRunner.IsBound())
			{
				DelegateFinishedRunner.Execute(this, LaneRunner);
			}
		}
	}
}

void ATzLane::HorseGameStart()
{
	if (LaneRunner)
	{
		LaneRunner->Start();
	}

	LaneState = ESTATE_LANE::ESTATE_RUN;
}

void ATzLane::SetEnableLane()
{
	bEnableLane = true;
	GetRootComponent()->SetVisibility(true, true);
}

void ATzLane::SetDisableLane()
{
	bEnableLane = false;
	GetRootComponent()->SetVisibility(false, true);
}

ATzRunner* ATzLane::ReadyToPlay()
{
	if (RunnerClass && StartPoint)
	{
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.Owner = this;
		SpawnInfo.bNoFail = true;

		FTransform SpawnTransform;
		SpawnTransform.SetLocation(StartPoint->GetComponentLocation());

		LaneRunner = GetWorld()->SpawnActor<ATzRunner>(RunnerClass, SpawnTransform, SpawnInfo);
		if (LaneRunner)
		{
			LaneRunner->ReadyCharacter(this, GoalPoint->GetComponentLocation());
		}

		LaneState = ESTATE_LANE::ESTATE_READY;
		return LaneRunner;
	}
	return nullptr;
}