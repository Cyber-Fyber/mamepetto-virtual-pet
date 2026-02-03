
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.h"
#include "Poop.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundBase.h"

#include "Peto.generated.h"

UCLASS()
class MAMEPETTO_API APeto : public AActor
{
	GENERATED_BODY()
	
	enum class DirectionState : int8
	{
		IDLE,
		NORTH,
		NORTHEAST,
		EAST,
		SOUTHEAST,
		SOUTH,
		SOUTHWEST,
		WEST,
		NORTHWEST,
	};
	
public:	
	APeto();

protected:
	virtual void BeginPlay() override;

	void PrintStats();
	void UpdateStats(float DeltaTime);



	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh")
		class UStaticMeshComponent* MamepettoMesh;

		UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Tick")
		float MoveSpeed;

		class AItem* ItemTarget;

		class APoop* PoopTarget;


	FVector PoopSpawnPoint;
	FRotator PoopSpawnRot;
	FActorSpawnParameters PoopSpawnParams;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
		USoundBase* Sound2DEat;


		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
		USoundBase* Sound2DBGM;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	USoundBase* Sound2DFart;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotation")
		FRotator TargetRotation;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotation")
		float RotationSpeed = 2.f;

		void PlaySoundBGM();
		void PlaySoundFart();
		void PlaySoundEat();
		bool bHasPlayedSoundEat;

private:

	int Hunger;
	int Tiredness;
	int Toilet;
	int SubTick;

	FVector FoodTarget;

	bool bCanSeeFood;

	void GoToilet();

	DirectionState Direction;

	void CheckForFood();

	void Movement(float DeltaTime);

public:	

	virtual void Tick(float DeltaTime) override;
};
