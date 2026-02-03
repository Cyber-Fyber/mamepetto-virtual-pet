// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Peto.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemSpawner.h"

#include "Item.generated.h"



class APeto;

UCLASS()
class MAMEPETTO_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	

	AItem();

protected:

	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	class UStaticMeshComponent* ItemMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	class UMaterial* ItemMaterial;

	FVector ItemLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	APeto* Peto;

	void ItemFall(float DeltaTime);


private:

	float FoodValueHunger;
	int FoodValueTiredness;

public:	

	virtual void Tick(float DeltaTime) override;

	int HungerValue();
	int TirednessValue();
};
