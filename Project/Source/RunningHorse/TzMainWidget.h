// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TzUserWidget.h"
#include "TzMainWidget.generated.h"

/**
 * 
 */
UCLASS()
class RUNNINGHORSE_API UTzMainWidget : public UTzUserWidget
{
	GENERATED_BODY()
	
public:
	virtual bool InitializeWidget() override;

};
