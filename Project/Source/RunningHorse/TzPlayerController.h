// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TzPlayerController.generated.h"

/**
 * 
 */
class UTzUserWidget;
enum class ERunningState : uint8;

UCLASS()
class RUNNINGHORSE_API ATzPlayerController : public APlayerController
{
	GENERATED_BODY()


	ATzPlayerController(const FObjectInitializer& ObjectInitializer);

public:
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintImplementableEvent)
	void BP_OnChanged_RunningState(ERunningState InRunningState);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TWeakObjectPtr<UTzUserWidget> CachedMainWidget;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TWeakObjectPtr<UTzUserWidget> CachedResultWidget;

public:
	UFUNCTION()
	void OnChanged_RunningState(ERunningState InRunningState);
};
