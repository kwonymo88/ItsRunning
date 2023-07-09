// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "RunnerCompDataTable.generated.h"

/**
 * 
 */
class URunnerActorComponent;

USTRUCT(BlueprintType)
struct RUNNINGHORSE_API FRunnerCompData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FRunnerCompData")
	float ActivateProb;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FRunnerCompData")
	TSubclassOf<URunnerActorComponent> RunnerComp;
};

UCLASS()
class RUNNINGHORSE_API URunnerCompDataTable : public UDataTable
{
	GENERATED_BODY()
	
};
