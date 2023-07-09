// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LanePlace.generated.h"

UCLASS()
class RUNNINGHORSE_API ALanePlace : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALanePlace();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	FORCEINLINE int GetIndex() const { return Index; };

protected:
	UPROPERTY(EditAnywhere, Category = "RunningHorse")
	int Index;
};
