// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TzUserWidget.h"
#include "TzRankWidget.generated.h"

/**
 * 
 */
UCLASS()
class RUNNINGHORSE_API UTzRankWidget : public UTzUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintImplementableEvent)
	void BP_UpdateRank(int InRank);

public:
	UFUNCTION(BlueprintCallable)
	void SetRank(int InRank);
};
