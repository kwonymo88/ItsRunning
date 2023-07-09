// Fill out your copyright notice in the Description page of Project Settings.


#include "RunningHorseGameModeBase.h"
#include "TzLane.h"
#include "TzRunner.h"
#include "LanePlace.h"
#include "Kismet/GameplayStatics.h"
#include "RunnerActorComponent.h"
#include "Engine/DataTable.h"
#include "RunnerCompDataTable.h"

ARunningHorseGameModeBase::ARunningHorseGameModeBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickGroup = TG_PrePhysics;
}

void ARunningHorseGameModeBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (RunningState == ERunningState::Running)
	{
		TickRunner();
		//EvaluateRunnerComp();
		if (RemainEvaluateRunnerCompTime < 0.f)
		{
			EvaluateRunnerComp();
			RemainEvaluateRunnerCompTime = EvaluateRunnerCompTime;
		}
		else
		{
			RemainEvaluateRunnerCompTime -= DeltaSeconds;
		}
	}
	else if (RunningState == ERunningState::Ready)
	{
		SetCurrentModeTime(CurrentModeTime - DeltaSeconds);
		if (CurrentModeTime <= 0.f)
		{
			SetRunningState(ERunningState::Running);
			for (auto Lane : LaneActors)
			{
				Lane->HorseGameStart();
			}
		}
	}
}

void ARunningHorseGameModeBase::TickRunner()
{
	if (Runners.IsEmpty())
	{
		return;
	}

	bool bUpdateRank = false;
	Runners.Sort([&bUpdateRank](const auto& A, const auto& B)
		{
			if (!A.IsRunning())
			{
				return true;
			}

			if (A.GetActorLocation().X > B.GetActorLocation().X)
			{
				return true;
			}
			else
			{
				bUpdateRank = true;
				return false;
			}
		});
	if (bUpdateRank)
	{
		if (UpdatedRunnerRank.IsBound())
		{
			UpdatedRunnerRank.Broadcast(Runners);
		}
	}
	LeadRunnerLocation.X = Runners[0]->GetActorLocation().X;
	/*for (auto& Runner : Runners)
	{
		EvaluateLeadRunnerLocation(Runner.Get(), LeadRunnerLocation);
		
	}*/
}

//void ARunningHorseGameModeBase::EvaluateLeadRunnerLocation(const ATzRunner* pRunner, FVector& outLeadRunnerLocation)
//{
//	if (pRunner && pRunner->GetActorLocation().X > LeadRunnerLocation.X)
//	{
//		LeadRunnerLocation.X = pRunner->GetActorLocation().X;
//	}
//}

void ARunningHorseGameModeBase::HorseGameStart()
{
	InitHorseGame();
	SetRunningState(ERunningState::Ready);	
	//GetWorld()->GetTimerManager().SetTimer(ReadyToStartTimerHandle, this, &ARunningHorseGameModeBase::OnReadyToStartTimerHandle, 1, false);
}

void ARunningHorseGameModeBase::OnReadyToStartTimerHandle()
{
	
}

void ARunningHorseGameModeBase::InitHorseGame()
{
	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ALanePlace::StaticClass(), Actors);
	for (auto TargetActor : Actors)
	{
		ALanePlace* LanePlace = Cast<ALanePlace>(TargetActor);
		if (LanePlace && LanePlace->GetIndex() < PlayerCount)
		{
			ATzLane* pTzLaneActor = GetWorld()->SpawnActor<ATzLane>(LaneClass, LanePlace->GetTransform());
			if (pTzLaneActor)
			{
				LaneActors.Emplace(pTzLaneActor);
				pTzLaneActor->OnDelegateFinishedRunner().BindUObject(this, &ARunningHorseGameModeBase::OnFinishedRunner);
				
				
			}
		}
	}

	LaneActors.Sort([](auto& lhs, auto& rhs)
		{
			if (lhs.GetActorLocation().Y > rhs.GetActorLocation().Y) return true;
			return false;
		});

	int LaneIndex = 1;
	for (auto& LaneActor : LaneActors)
	{
		LaneActor->LaneIndex = LaneIndex++;
		ATzRunner* pTzRunner = LaneActor->ReadyToPlay();
		if (pTzRunner)
		{
			Runners.Emplace(pTzRunner);
		}
	}
}

int ARunningHorseGameModeBase::GetRunnerRank(ATzRunner* pRunner) const
{
	for (int RunnerIdx = Runners.Num() - 1; RunnerIdx >= 0; --RunnerIdx)
	{
		if (Runners[RunnerIdx] == pRunner)
		{
			return RunnerIdx;
		}
	}
	return INDEX_NONE;
}

void ARunningHorseGameModeBase::OnFinishedRunner(const ATzLane* FinisheLane, const ATzRunner* FinishRunner)
{
	if (FinisheLane && FinishRunner)
	{
		UE_LOG(LogTemp, Log,TEXT("%s"), *FString::Format(TEXT("OnFinishedRunner Lane : [{0}], Runner[{1}]"), {FinisheLane->GetName(), FinishRunner->GetName()}));

		Runners.Remove(const_cast<ATzRunner*>(FinishRunner));
		FinishedRunners.Add(FinishRunner);
		if (Runners.IsEmpty())
		{
			SetRunningState(ERunningState::Finished);
		}
		FinishedRunnerDelegate.Broadcast(FinisheLane->GetLaneIndex());
	}
}

void ARunningHorseGameModeBase::StartPlay()
{
	Super::StartPlay();
	RemainEvaluateRunnerCompTime = EvaluateRunnerCompTime;

	if (RunnerCompDataTable)
	{
		TArray<FRunnerCompData*> RunnerComps;
		RunnerCompDataTable->GetAllRows<FRunnerCompData>(TEXT("RuunerCompDataTable"), RunnerComps);
		int StartProb = 0.f;
		for (auto RunnerCompData : RunnerComps)
		{
			URunnerActorComponent* RunnerActorComp = Cast<URunnerActorComponent>(RunnerCompData->RunnerComp->GetDefaultObject());
			if (RunnerActorComp)
			{
				StartProb += RunnerCompData->ActivateProb;
				CandidateRunnerActorProbInfos.Emplace(FRunnerActorCompProb(RunnerCompData->RunnerComp, StartProb));
			}
		}
	}
}

bool ARunningHorseGameModeBase::ShouldUpdateCamera()
{
	if (RunningState == ERunningState::Running)
	{
		return true;
	}
	return false;
}

void ARunningHorseGameModeBase::EvaluateRunnerComp()
{
	for (auto Runner : Runners)
	{
		
		if (Runner&& !Runner->IsActivateRunnerComp())
		{
			float Prob = FMath::RandRange(0.f, 100.f);
			for (auto CandidateRunnerActorProb : CandidateRunnerActorProbInfos)
			{
				if (CandidateRunnerActorProb.Prob > Prob)
				{
					Runner->AddRunnerComponent(CandidateRunnerActorProb.RunnerActorCompClass);
					break;
				}
			}
		}
	}
}

void ARunningHorseGameModeBase::ModifyLaneCount(int LaneCount)
{
	for (auto LaneActor : LaneActors)
	{
		if (LaneActor->LaneIndex <= LaneCount)
		{
			LaneActor->SetEnableLane();
		}
		else
		{
			LaneActor->SetDisableLane();
		}
	}
}

void ARunningHorseGameModeBase::SetPlayerCount(const int InPlayerCount)
{
	PlayerCount = FMath::Clamp(InPlayerCount, MinPlayerCount, MaxPlayerCount);
	if (PlayerCount != InPlayerCount)
	{
		//PlayerCount = InPlayerCount;

		//ModifyLaneCount(PlayerCount);
	}
}

void ARunningHorseGameModeBase::SetRunningState(const ERunningState NewRunningState)
{
	RunningState = NewRunningState;
	
	_ChangedRunningStateDelegate.Broadcast(RunningState);

	switch (RunningState)
	{
	case ERunningState::Ready:
		SetCurrentModeTime(ReadyToStartTime);
		break;
	}
}

void ARunningHorseGameModeBase::SetCurrentModeTime(float Time)
{
	int PrevSec = CurrentModeTime;
	CurrentModeTime = Time;
	int UpdatedSec = CurrentModeTime;
	if (UpdatedSec != PrevSec
		&& UpdatedModeSecDelegate.IsBound())
	{
		UpdatedModeSecDelegate.Broadcast(UpdatedSec);
	}
}