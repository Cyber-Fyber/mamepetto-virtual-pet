// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.h"
#include "ItemSpawner.generated.h"

UCLASS()
class MAMEPETTO_API AItemSpawner : public AActor
{
	GENERATED_BODY()
	
public:	

	AItemSpawner();

protected:

	virtual void BeginPlay() override;

	FVector SpawnPoint;
	FRotator SpawnRot;
	FActorSpawnParameters SpawnParams;

	void SpawnItems();

public:	

	virtual void Tick(float DeltaTime) override;
};
