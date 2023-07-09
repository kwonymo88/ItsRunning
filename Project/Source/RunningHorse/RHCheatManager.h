// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CheatManager.h"
#include "RHCheatManager.generated.h"

/**
 * 
 */
UCLASS()
class RUNNINGHORSE_API URHCheatManager : public UCheatManager
{
	GENERATED_BODY()

	UFUNCTION(exec)
	void StartHorse();
};
