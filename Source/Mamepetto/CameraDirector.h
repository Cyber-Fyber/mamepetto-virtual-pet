// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "CameraDirector.generated.h"

UCLASS()
class MAMEPETTO_API ACameraDirector : public AActor
{
	GENERATED_BODY()
	
public:	

	ACameraDirector();

protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	AActor* CameraOne;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	AActor* CameraTwo;


	FVector CameraPos1;
	FVector CameraPos2;
	FVector CameraPos3;

	FRotator CameraRot1;
	FRotator CameraRot2;
	FRotator CameraRot3;
	
	bool bMovedCamera;


	APlayerController* PlayerController;

	FVector CamSpawnPoint;
	FRotator CamSpawnRot;
	FActorSpawnParameters CamSpawnParams;

	float CameraTimer;
	
	int CameraSubtick;

public:	

	virtual void Tick(float DeltaTime) override;

};
