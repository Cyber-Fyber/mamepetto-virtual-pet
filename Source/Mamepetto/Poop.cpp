// Fill out your copyright notice in the Description page of Project Settings.


#include "Poop.h"
#include "Peto.h"


APoop::APoop()
{
	PrimaryActorTick.bCanEverTick = false;


	PoopMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Poop Mesh"));
	PoopMaterial = CreateDefaultSubobject<UMaterial>(TEXT("Poop Material"));
	PoopMesh->SetWorldScale3D(FVector(0.5, 0.5, 0.5));

	static ConstructorHelpers::FObjectFinder<UStaticMesh>ItemAsset(TEXT("/Game/Item_Content/Poop_Mesh"));
	static ConstructorHelpers::FObjectFinder<UMaterial>ItemAssetMaterial(TEXT("/Game/Item_Content/Poop_Material"));


	if (ItemAsset.Succeeded())
	{
		PoopMesh->SetStaticMesh(ItemAsset.Object);
	}
	if (ItemAssetMaterial.Succeeded())
	{
		PoopMaterial = ItemAssetMaterial.Object;

		PoopMesh->SetMaterial(0, PoopMaterial);

	}
}


void APoop::BeginPlay()
{
	Super::BeginPlay();
}



void APoop::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


