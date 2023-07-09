// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RunnerActorComponent.generated.h"

class ATzRunner;

UCLASS( ClassGroup=(Custom) , Blueprintable)
class RUNNINGHORSE_API URunnerActorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URunnerActorComponent();

protected:
	UPROPERTY(Transient)
	TWeakObjectPtr<ATzRunner> OwnerRunner;

protected:
	virtual void OnRegister() override;
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	virtual void ActivateBuff();
	virtual void DeactivateBuff();

protected:
	UPROPERTY(EditAnywhere, Category = "RunningHorse | SlowComponent")
	float AddSpeedMin;

	UPROPERTY(EditAnywhere, Category = "RunningHorse | SlowComponent")
	float AddSpeedMax;

	UPROPERTY(EditAnywhere, Category = "RunningHorse | SlowComponent")
	float InterpSpeed;

	UPROPERTY(EditAnywhere, Category = "RunningHorse | SlowComponent")
	float ActiveTimeMax;
	
	UPROPERTY(EditAnywhere, Category = "RunningHorse | SlowComponent")
	float ActiveTimeMin;

	UPROPERTY(Transient)
	float TargetActiveTime;

	UPROPERTY(Transient)
	float TargetAddSpeed;

	UPROPERTY(Transient)
	float ActivationTime;

	UPROPERTY(Transient)
	bool bActivate;

	UPROPERTY(Transient)
	float RunnerRankAdventage;
};
