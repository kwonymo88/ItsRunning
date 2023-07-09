// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TzRunner.generated.h"

class URunnerActorComponent;
class UActorComponent;
class ATzLane;

UENUM()
enum class ESTATE_TYPE : uint8
{
	NONE,
	READY,
	RUN,
	FINISH
};

UCLASS()
class RUNNINGHORSE_API ATzRunner : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATzRunner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void PostInitializeComponents() override;

protected:
	UPROPERTY(Transient)
	FVector GoalLocation;

	UPROPERTY(Transient)
	ESTATE_TYPE State;

	UPROPERTY(Transient, BlueprintReadOnly, Category = "ATzRunner | Move")
	float Speed = 0.f;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "ATzRunner | Move")
	float MinStartSpeed;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "ATzRunner | Move")
	float MaxStartSpeed;

	UPROPERTY(Transient, BlueprintReadOnly, Category = "ATzRunner | Move")
	float AddSpeed = 0.f;

	UPROPERTY(Transient, BlueprintReadOnly, Category = "ATzRunner | Move")
	FVector vDir; 

	UPROPERTY(EditAnyWhere, Category = "ATzRunner | Move")
	float fBreakSpeed;

	UPROPERTY(EditDefaultsOnly, Category = "ATzRunner | Move")
	TSubclassOf<URunnerActorComponent> StartRunnerActorCompClass;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	URunnerActorComponent* AttachRunnerActorComp;

protected:
	UPROPERTY(Transient)
	float SpeedScale = 0.f;

	UPROPERTY(Transient, BlueprintReadOnly, Category = "ATzRunner | Move")
	FVector PrevMoveVector;

	UPROPERTY(Transient, BlueprintReadOnly,Category = "ATzRunner | Move")
	float Velocity;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "ATzRunner | Move")
	TSet<UActorComponent*> ActivatedRunnerComps;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "ATzRunner | Character")
	TArray<FLinearColor> ColorVariation;

	UPROPERTY(Transient, BlueprintReadOnly)
	TWeakObjectPtr<ATzLane>	CachedLaneActor;

public:
	UFUNCTION(BlueprintCallable)
	int GetLaneIndex();

public:
	float GetAddSpeed() const { return AddSpeed; }
	float CalculateTotalSpeed() const;
	float GetSpeed() const;
	FORCEINLINE FVector GetDir() const { return vDir; }
	FORCEINLINE bool IsRunning() const { return State == ESTATE_TYPE::RUN; }
	FORCEINLINE bool IsActivateRunnerComp() const { return !ActivatedRunnerComps.IsEmpty(); }


	FVector GetRunnerDir() const;
	void SetSpeed(const float InSpeed);
	void IncreaseAddSpeed(const float InSpeed);
	void ReadyCharacter(ATzLane* InLaneActor, FVector InGoalLocation);
	void FinishCharacter();
	void Start();
	void AddRunnerComponent(TSubclassOf<URunnerActorComponent> RunnerCompClass);
	void RemoveRunnerComponent();
	void RemoveRunnerComponent(const URunnerActorComponent* TargetActorComp);
	void UpdateLaneIndex();

	UFUNCTION(BlueprintImplementableEvent)
	void BP_OnSetupCharacterDate();
};
