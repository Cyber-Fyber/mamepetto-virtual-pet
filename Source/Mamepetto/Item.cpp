// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"
#include "Peto.h"


AItem::AItem()
{

	PrimaryActorTick.bCanEverTick = true;

	FoodValueHunger = 100;
	FoodValueTiredness = 100;

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Item Mesh"));
	ItemMaterial = CreateDefaultSubobject<UMaterial>(TEXT("Item Material"));
	ItemMesh->SetWorldScale3D(FVector(5, 5, 5));

	RootComponent = ItemMesh;

	static ConstructorHelpers::FObjectFinder<UStaticMesh>ItemAsset(TEXT("/Game/Item_Content/item_apple/Red_Apple_Mesh"));
	static ConstructorHelpers::FObjectFinder<UMaterial>ItemAssetMaterial(TEXT("/Game/Item_Content/Item_Material"));

	if (ItemAsset.Succeeded())
	{
		ItemMesh->SetStaticMesh(ItemAsset.Object);
	}
	if (ItemAssetMaterial.Succeeded())
	{
		ItemMaterial = ItemAssetMaterial.Object;

		ItemMesh->SetMaterial(0, ItemMaterial);
	}
}


void AItem::BeginPlay()
{
	Super::BeginPlay();
}

void AItem::ItemFall(float DeltaTime)
{
	ItemLocation = GetActorLocation();
	
	if (ItemLocation.Z > 60)
	{
		ItemLocation.Z--;
	}

	SetActorLocation(ItemLocation);
}


void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	ItemFall(DeltaTime);
}

int AItem::HungerValue()
{
	return FoodValueHunger;
}

int AItem::TirednessValue()
{
	return FoodValueTiredness;
}

