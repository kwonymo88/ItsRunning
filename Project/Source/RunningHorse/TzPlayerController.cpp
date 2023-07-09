// Fill out your copyright notice in the Description page of Project Settings.


#include "TzPlayerController.h"
#include "RHCheatManager.h"
#include "RunningHorseGameModeBase.h"
#include "Kismet/GameplayStatics.h"

ATzPlayerController::ATzPlayerController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	CheatClass = URHCheatManager::StaticClass();
}

void ATzPlayerController::BeginPlay()
{
	Super::BeginPlay();

	ARunningHorseGameModeBase* pGameModeBase = GetWorld()->GetAuthGameMode<ARunningHorseGameModeBase>();
	if (pGameModeBase)
	{
		//if (pGameModeBase->GetChangedRunningStateDelegate().IsBoundToObject(this) == false)
		{
			pGameModeBase->GetChangedRunningStateDelegate().AddDynamic(this, &ATzPlayerController::OnChanged_RunningState);
		}
	}
}

void ATzPlayerController::OnChanged_RunningState(ERunningState InRunningState)
{
	BP_OnChanged_RunningState(InRunningState);
}