// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TzUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class RUNNINGHORSE_API UTzUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual bool InitializeWidget() { return true; }
};
