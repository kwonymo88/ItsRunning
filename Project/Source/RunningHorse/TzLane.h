// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TzLane.generated.h"

UENUM()
enum class ESTATE_LANE : uint8
{
	ESTATE_NONE,
	ESTATE_READY,
	ESTATE_RUN,
	ESTATE_FINISHED
};

DECLARE_DELEGATE_TwoParams(FDelegateFinishedRunner, const class ATzLane*, const class ATzRunner*);

UCLASS()
class RUNNINGHORSE_API ATzLane : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATzLane();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	void HorseGameStart();

public:
	UPROPERTY(EditDefaultsOnly, Category = "Runner")
	TSubclassOf<class ATzRunner>	RunnerClass;

	UPROPERTY(Category = "ATzLane | Point", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* StartPoint;

	UPROPERTY(Category = "ATzLane | Point", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* GoalPoint;

	UPROPERTY(EditAnywhere, Category = "RunningHorseGameModeBase | Game")
	class ATzRunner* LaneRunner;

	UPROPERTY(EditInstanceOnly)
	int LaneIndex;

	UPROPERTY(VisibleAnywhere, Category = "RunningHorseGameModeBase | Game")
	ESTATE_LANE LaneState;

	UPROPERTY(Transient)
	bool bEnableLane;

	FDelegateFinishedRunner	DelegateFinishedRunner;

public:
	FORCEINLINE FDelegateFinishedRunner& OnDelegateFinishedRunner() { return DelegateFinishedRunner; }

	UFUNCTION(BlueprintCallable)
	int GetLaneIndex() const { return LaneIndex; }

	void SetDisableLane();
	void SetEnableLane();
	ATzRunner* ReadyToPlay();
};
