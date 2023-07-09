// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RunningHorseGameModeBase.generated.h"

/**
 * 
 */
UENUM()
enum class ERunningState : uint8
{
	None,
	Ready,
	Running,
	Finished,
};

class ATzRunner;
class UDataTable;
class URunnerActorComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FChangedRunningStateDelegate, ERunningState, RunningState);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFinishedRunnerDelegate, int, LaneIndex);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUpdatedRunnerRank, const TArray<ATzRunner*>&, Runners );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUpdatedModeSecDelegate, int, CurrentModeSec);

UCLASS()
class RUNNINGHORSE_API ARunningHorseGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	ARunningHorseGameModeBase(const FObjectInitializer& ObjectInitializer);

public:
	virtual void Tick(float DeltaSeconds) override;
	void TickRunner();

	//void EvaluateLeadRunnerLocation(const ATzRunner* pRunner, FVector& outLeadRunnerLocation);

public:
	UFUNCTION(BlueprintCallable)
	virtual void HorseGameStart();

	UFUNCTION(BlueprintCallable)
	virtual void InitHorseGame();

public:
	UPROPERTY(EditDefaultsOnly, Category = "RunningHorseGameModeBase | Game")
	TSubclassOf<class ATzLane>	LaneClass;

	UPROPERTY(EditAnywhere, Category = "RunningHorseGameModeBase | Game")
	TArray<class ATzLane*> LaneActors;

	UPROPERTY(EditAnywhere, Category = "RunningHorseGameModeBase | Game")
	float EvaluateRunnerCompTime = 1.f;

	UPROPERTY(Transient)
	float RemainEvaluateRunnerCompTime = 0.f;

	UPROPERTY(Transient, BlueprintReadOnly)
	int PlayerCount = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int MaxPlayerCount = 10;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int MinPlayerCount = 2;

	UPROPERTY(VisibleAnywhere, Category = "RunningHorseGameModeBase | Game")
	FVector LeadRunnerLocation;

	UPROPERTY(VisibleAnywhere, Category = "RunningHorseGameModeBase | Game")
	ERunningState RunningState = ERunningState::None;

	UPROPERTY(transient, BlueprintReadOnly)
	TArray<const ATzRunner*> FinishedRunners;

	TArray<ATzRunner*> Runners;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float ReadyToStartTime = 3.9f;

	float CurrentModeTime;

public:
	UFUNCTION(BlueprintCallable)
	void SetPlayerCount(const int InPlayerCount);

	UFUNCTION(BlueprintCallable)
	const TArray<ATzRunner*>& GetRunners() const { return Runners; }

	int GetRunnerRank(ATzRunner* pRunner) const;
	int GetRunnerNum() const { return Runners.Num(); }

public:
	void OnFinishedRunner(const class ATzLane* FinisheLane, const ATzRunner* FinishRunner);
	bool ShouldUpdateCamera();


	virtual void StartPlay() override;

protected:
	void ModifyLaneCount(int LaneCount);
	void OnReadyToStartTimerHandle();
	void SetRunningState(const ERunningState NewRunningState);
	void SetCurrentModeTime(float Time);

private:
	void EvaluateRunnerComp();

	UPROPERTY(EditDefaultsOnly)
	UDataTable* RunnerCompDataTable;

	struct FRunnerActorCompProb
	{
		TSubclassOf<URunnerActorComponent> RunnerActorCompClass;
		float Prob;
		FRunnerActorCompProb(TSubclassOf<URunnerActorComponent> InActorComp, float InProb)
			: RunnerActorCompClass(InActorComp), Prob(InProb)
		{
		}
	};

	TArray<FRunnerActorCompProb> CandidateRunnerActorProbInfos;

protected:
	UPROPERTY(BlueprintAssignable)
	FChangedRunningStateDelegate _ChangedRunningStateDelegate;

	UPROPERTY(BlueprintAssignable)
	FFinishedRunnerDelegate	FinishedRunnerDelegate;

	UPROPERTY(BlueprintAssignable)
	FUpdatedRunnerRank	UpdatedRunnerRank;

	UPROPERTY(BlueprintAssignable)
	FUpdatedModeSecDelegate	UpdatedModeSecDelegate;
	
	
public:
	FChangedRunningStateDelegate& GetChangedRunningStateDelegate() { return _ChangedRunningStateDelegate; }
	FFinishedRunnerDelegate& GetFinishedRunnerDelegate() { return FinishedRunnerDelegate; }
	FUpdatedRunnerRank GetUpdatedRunnerRank() { return UpdatedRunnerRank; }
	FUpdatedModeSecDelegate	GetUpdatedModeSecDelegate() { return UpdatedModeSecDelegate; }
};
