// Fill out your copyright notice in the Description page of Project Settings.


#include "RHCheatManager.h"
#include "RunningHorseGameModeBase.h"

void URHCheatManager::StartHorse()
{
	ARunningHorseGameModeBase* GameModeBase = GetWorld()->GetAuthGameMode<ARunningHorseGameModeBase>();
	if (GameModeBase)
	{
		GameModeBase->HorseGameStart();
	}
}
