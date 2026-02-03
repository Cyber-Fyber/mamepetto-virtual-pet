// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Poop.generated.h"





UCLASS()
class MAMEPETTO_API APoop : public AActor
{
	GENERATED_BODY()
	
public:	

	APoop();

protected:

	virtual void BeginPlay() override;


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh")
	class UStaticMeshComponent* PoopMesh;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	class UMaterial*PoopMaterial;




public:	

	virtual void Tick(float DeltaTime) override;


};
