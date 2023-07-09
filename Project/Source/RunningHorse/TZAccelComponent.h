// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RunnerActorComponent.h"
#include "TZAccelComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RUNNINGHORSE_API UTZAccelComponent : public URunnerActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTZAccelComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	virtual void ActivateBuff() override;
	virtual void DeactivateBuff() override;
};
