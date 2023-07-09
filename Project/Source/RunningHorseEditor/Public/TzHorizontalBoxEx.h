// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components\HorizontalBox.h"
#include "TzHorizontalBoxEx.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class RUNNINGHORSEEDITOR_API UTzHorizontalBoxEx : public UHorizontalBox
{
	GENERATED_UCLASS_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "UTzHorizontalBox|Panel")
	UPanelSlot* CustomInsertChildAt(int32 Index, UWidget* Content);

	UFUNCTION(BlueprintCallable, Category = "UTzHorizontalBox|Panel")
	void CustomShiftChild(int32 Index, UWidget* Child);
};
