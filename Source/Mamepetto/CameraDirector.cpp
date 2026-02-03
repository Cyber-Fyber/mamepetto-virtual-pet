// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraDirector.h"


// Sets default values
ACameraDirector::ACameraDirector()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//bMovedCamera = false;

	//CameraTimer = 0.f;

	//CameraSubtick = 0;

	//CameraRot1 = FRotator(-10.f, 0.f, 0.f);

	//CameraRot2 = FRotator(-20.0, 50.f, 0.f);

	//CameraPos1 = FVector(-800.0, -20.0, 380.0);

	//CameraPos2 = FVector(-400.0, -620.0, 400.0);


}



// Called when the game starts or when spawned
void ACameraDirector::BeginPlay()
{
	Super::BeginPlay();

	//PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	//
	//if (!PlayerController || !CameraOne) return;

	//PlayerController->SetViewTarget(CameraOne);

	//CameraOne->SetActorRotation(CameraRot2);
	//CameraOne->SetActorLocation(CameraPos2);
	
}



void ACameraDirector::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//if (!CameraOne || bMovedCamera) return;

	//CameraTimer += DeltaTime;

	//if (CameraTimer >= 3.f)
	//{
	//	CameraOne->SetActorRotation(CameraRot1);
	//	CameraOne->SetActorLocation(CameraPos1);

	//	bMovedCamera = true;
	//}

}
