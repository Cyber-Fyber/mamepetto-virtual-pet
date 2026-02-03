// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemSpawner.h"


AItemSpawner::AItemSpawner()
{
	PrimaryActorTick.bCanEverTick = true;
}


void AItemSpawner::BeginPlay()
{
	Super::BeginPlay();
}

void AItemSpawner::SpawnItems()
{
	SpawnPoint = FVector(FMath::RandRange(-300, 300), FMath::FRandRange(-300, 300), 300);

	SpawnParams.OverrideLevel = GetLevel();
	AItem* SpawnedItem = (AItem*)GetWorld()->SpawnActor(AItem::StaticClass(), &SpawnPoint, &SpawnRot, SpawnParams);
}


void AItemSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (FMath::RandRange(0, 500) == 1)
	{
		SpawnItems();
	}
}

