// Fill out your copyright notice in the Description page of Project Settings.


#include "TzRunner.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "TzAIController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "RunnerActorComponent.h"
#include "TzLane.h"
#include "Components/SkeletalMeshComponent.h"

// Sets default values
ATzRunner::ATzRunner()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;

	State = ESTATE_TYPE::NONE;
}

// Called when the game starts or when spawned
void ATzRunner::BeginPlay()
{
	Super::BeginPlay();
	SpeedScale = 1.f;
}

// Called every frame
void ATzRunner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	/*if (State == ESTATE_TYPE::RUN)
	{
		FVector AddVector = vDir * GetSpeed();
		Velocity = AddVector.Size();
		SetActorLocation(GetActorLocation() + (AddVector * DeltaTime));
	}
	else if (State == ESTATE_TYPE::FINISH)
	{
		Velocity = FMath::FInterpTo(Velocity, 0.f, DeltaTime, fBreakSpeed);
		FVector AddVector = vDir * Velocity;
		SetActorLocation(GetActorLocation() + (AddVector * DeltaTime));

		if (Velocity < 30.f)
		{
			Velocity = 0.f;
			State = ESTATE_TYPE::NONE;
		}
	}*/

	if (State == ESTATE_TYPE::RUN
		|| State == ESTATE_TYPE::FINISH)
	{
		if (State == ESTATE_TYPE::FINISH)
		{
			SpeedScale -= DeltaTime;
			SpeedScale = FMath::Clamp(SpeedScale, 0.f, 1.f);
			if (FMath::IsNearlyZero(SpeedScale))
			{
				State = ESTATE_TYPE::NONE;
			}
		}
	}
	FVector TargetVector = vDir * CalculateTotalSpeed() * SpeedScale;
	FVector ResultVector = FMath::VInterpTo(PrevMoveVector, TargetVector, DeltaTime, 10.f);
	Velocity = ResultVector.Size();
	SetActorLocation(GetActorLocation() + ResultVector * DeltaTime);
	PrevMoveVector = ResultVector;
}

// Called to bind functionality to input
void ATzRunner::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATzRunner::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
}


int ATzRunner::GetLaneIndex()
{
	if (CachedLaneActor.IsValid())
	{
		return CachedLaneActor->GetLaneIndex();
	}
	return 0;
}

float ATzRunner::CalculateTotalSpeed() const
{
	return GetSpeed() + GetAddSpeed();
}

float ATzRunner::GetSpeed() const
{
	return Speed;
}

FVector ATzRunner::GetRunnerDir() const
{
	return FVector(GoalLocation - GetActorLocation()).GetSafeNormal();
}

void ATzRunner::SetSpeed(const float InSpeed)
{
	Speed = InSpeed;
}

void ATzRunner::IncreaseAddSpeed(const float InSpeed)
{
	AddSpeed += InSpeed;
}

void ATzRunner::ReadyCharacter(ATzLane* InLaneActor, FVector InGoalLocation)
{
	CachedLaneActor = InLaneActor;
	State = ESTATE_TYPE::READY;
	GoalLocation = InGoalLocation;
	vDir = FVector(GoalLocation - GetActorLocation()).GetSafeNormal();
	vDir.Z = vDir.Y = 0.f;
	BP_OnSetupCharacterDate();
}

void ATzRunner::FinishCharacter()
{
	State = ESTATE_TYPE::FINISH;
}

void ATzRunner::Start()
{
	State = ESTATE_TYPE::RUN;
	Speed = FMath::RandRange(MinStartSpeed, MaxStartSpeed);
	SpeedScale = 1.f;
	if (StartRunnerActorCompClass)
	{
		AddRunnerComponent(StartRunnerActorCompClass);
	}
	SetActorTickEnabled(true);
}

void ATzRunner::AddRunnerComponent(TSubclassOf<URunnerActorComponent> RunnerCompClass)
{
	URunnerActorComponent* NewRunnerComp = NewObject<URunnerActorComponent>(this, RunnerCompClass);
	if (NewRunnerComp)
	{
		NewRunnerComp->RegisterComponent();
		ActivatedRunnerComps.Add(NewRunnerComp);
	}
}

void ATzRunner::RemoveRunnerComponent()
{
	TArray<UActorComponent*> RunnerActorComps;
	GetComponents(RunnerActorComps);
	for (auto RunnerActorComp : RunnerActorComps)
	{
		RunnerActorComp->DestroyComponent();
	}
	ActivatedRunnerComps.Empty();
}

void ATzRunner::RemoveRunnerComponent(const URunnerActorComponent* TargetActorComp)
{
	TArray<UActorComponent*> RunnerActorComps;
	GetComponents(RunnerActorComps);
	for (auto RunnerActorComp : RunnerActorComps)
	{
		if (RunnerActorComp == TargetActorComp)
		{
			RunnerActorComp->DestroyComponent();
			break;
		}
	}

	ActivatedRunnerComps.Remove(TargetActorComp);
}

void ATzRunner::UpdateLaneIndex()
{
	if (HasAnyFlags(RF_Transactional))
	{
		int32 LaneIndex = CachedLaneActor->GetLaneIndex() - 1;
		if (CachedLaneActor.IsValid() && ColorVariation.IsValidIndex(LaneIndex))
		{
			USkeletalMeshComponent* SkeletalMesh = GetMesh();
			int32 MaterialNum = GetMesh()->GetNumMaterials();
			for (int32 i = 0; i < MaterialNum; ++i)
			{
				UMaterialInterface* MaterialInterface = GetMesh()->GetMaterial(i);
				if (MaterialInterface)
				{
					UMaterialInstanceDynamic* DynamicMaterial = Cast<UMaterialInstanceDynamic>(MaterialInterface);
					if (!DynamicMaterial)
					{
						DynamicMaterial = GetMesh()->CreateAndSetMaterialInstanceDynamic(i);
					}
					DynamicMaterial->SetVectorParameterValue(TEXT("MainColor"), ColorVariation[LaneIndex]);
				}
			}
		}
	}
}
