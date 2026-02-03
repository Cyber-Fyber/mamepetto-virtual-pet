
#include "Peto.h"
#include "Item.h"
#include <Kismet/GameplayStatics.h>


APeto::APeto()
{
	PrimaryActorTick.bCanEverTick = true;

	MamepettoMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mame Mesh"));

	RootComponent = MamepettoMesh;

	Hunger = 50;
	Tiredness = 50;
	Toilet = 25;

	SubTick = 0;

	MoveSpeed = 150.0f;

	bCanSeeFood = false;
	bHasPlayedSoundEat = false;
}


void APeto::BeginPlay()
{
	Super::BeginPlay();
	
	PlaySoundBGM();
}

void APeto::PrintStats()
{
	if (GEngine != nullptr)
	{
		GEngine->AddOnScreenDebugMessage(2, 3.0f, FColor::Cyan, FString::Printf(TEXT("Hunger = %d"), Hunger));
		GEngine->AddOnScreenDebugMessage(3, 3.0f, FColor::Red, FString::Printf(TEXT("Tiredness = %d"), Tiredness));
		GEngine->AddOnScreenDebugMessage(4, 3.0f, FColor::Green, FString::Printf(TEXT("Toilet = %d"), Toilet));
	}
}

void APeto::UpdateStats(float DeltaTime)
{
	Hunger--;
	Tiredness--;
	Toilet--;
}

void APeto::PlaySoundBGM()
{
	UGameplayStatics::PlaySound2D(this, Sound2DBGM);
}

void APeto::PlaySoundFart()
{
	UGameplayStatics::PlaySound2D(this, Sound2DFart);
}

void APeto::PlaySoundEat()
{
	UGameplayStatics::PlaySound2D(this, Sound2DEat);

	bHasPlayedSoundEat = true;
}

void APeto::GoToilet()
{
	if (Toilet == 0)
	{
		PlaySoundFart();
		Toilet = 100;

		PoopSpawnPoint = GetActorLocation();
		PoopSpawnRot = FRotator::ZeroRotator;

		PoopSpawnParams.OverrideLevel = GetLevel();
		APoop* SpawnedItem = (APoop*)GetWorld()->SpawnActor(APoop::StaticClass(), &PoopSpawnPoint, &PoopSpawnRot, PoopSpawnParams);
	}
}

void APeto::CheckForFood()
{
	TSubclassOf<AActor> WorldClassObject = AItem::StaticClass();
	TArray<AActor*> FoodItems;

	UGameplayStatics::GetAllActorsOfClass(this, WorldClassObject, FoodItems);

	if (FoodItems.Num() > 0)
	{
		if (FoodItems.Num() == 1)
		{
			GEngine->AddOnScreenDebugMessage(6, 3.0f, FColor::Magenta, FString::Printf(TEXT("I can see %d apple!"), FoodItems.Num()));
			ItemTarget = Cast<AItem>(FoodItems[0]);
			FoodTarget = FoodItems[0]->GetActorLocation();
			bCanSeeFood = true;
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(6, 3.0f, FColor::Magenta, FString::Printf(TEXT("I can see %d apples!"), FoodItems.Num()));
			ItemTarget = Cast<AItem>(FoodItems[0]);
			FoodTarget = FoodItems[0]->GetActorLocation();
			bCanSeeFood = true;
		}
	}
	if (FoodItems.Num() < 1)
	{
		GEngine->AddOnScreenDebugMessage(6, 3.0f, FColor::Magenta, FString::Printf(TEXT("I can't see any apples:(")));
		bCanSeeFood = false;
	}
}

void APeto::Movement(float DeltaTime)
{
	FVector Location = GetActorLocation();

	FRotator NewRotation = FRotator(0.f, 45.0f, 0.f);

	int VectorDifference = 0;

	if (Location.X >= 300)
	{
		Direction = DirectionState::SOUTH;
	}
	else if (Location.X <= -300)
	{
		Direction = DirectionState::NORTH;
	}
	if (Location.Y >= 300)
	{
		Direction = DirectionState::WEST;
	}
	else if (Location.Y <= -300)
	{
		Direction = DirectionState::EAST;
	}
	if (bCanSeeFood == true)
	{
		if (Location.X > FoodTarget.X )
		{
			SetActorRotation(NewRotation);
			GEngine->AddOnScreenDebugMessage(1, 3.0f, FColor::Yellow, FString::Printf(TEXT("Time to eat :D")));
			Location.X -= MoveSpeed * DeltaTime;
			VectorDifference += Location.X - FoodTarget.X;
		}
		else if (Location.X < FoodTarget.X )
		{
			GEngine->AddOnScreenDebugMessage(1, 3.0f, FColor::Yellow, FString::Printf(TEXT("Time to eat :D")));
			Location.X += MoveSpeed * DeltaTime;
			VectorDifference += FoodTarget.X - Location.X;
		}
		if (Location.Y > FoodTarget.Y )
		{
			GEngine->AddOnScreenDebugMessage(1, 3.0f, FColor::Yellow, FString::Printf(TEXT("Time to eat :D")));
			Location.Y -= MoveSpeed * DeltaTime;
			VectorDifference += Location.Y - FoodTarget.Y;
		}
		else if (Location.Y < FoodTarget.Y)
		{
			GEngine->AddOnScreenDebugMessage(1, 3.0f, FColor::Yellow, FString::Printf(TEXT("Time to eat :D")));
			Location.Y += MoveSpeed * DeltaTime;
			VectorDifference += FoodTarget.Y - Location.Y;
		}


		if (VectorDifference < 20 && FoodTarget.Z <= 60)
		{
			Hunger = ItemTarget->HungerValue();
			Tiredness = ItemTarget->TirednessValue();
			ItemTarget->Destroy();
			GEngine->AddOnScreenDebugMessage(7, 0.3f, FColor::Orange, FString::Printf(TEXT("NOM")));

			if (ItemTarget->Destroy() && bHasPlayedSoundEat == false)
			{
				PlaySoundEat();
			}
		}

	}
	else
	{
		switch (Direction)
		{
		case DirectionState::IDLE:
			GEngine->AddOnScreenDebugMessage(1, 3.0f, FColor::Yellow, FString::Printf(TEXT("I am resting now!")));
			break;

		case DirectionState::NORTH:
			GEngine->AddOnScreenDebugMessage(1, 3.0f, FColor::Yellow, FString::Printf(TEXT("Lets head north")));
			Location.X += MoveSpeed * DeltaTime;
			break;

		case DirectionState::NORTHEAST:
			GEngine->AddOnScreenDebugMessage(1, 3.0f, FColor::Yellow, FString::Printf(TEXT("Lets head northeast")));
			Location.X += (MoveSpeed / 2) * DeltaTime;
			Location.Y += (MoveSpeed / 2) * DeltaTime;
			break;

		case DirectionState::EAST:
			GEngine->AddOnScreenDebugMessage(1, 3.0f, FColor::Yellow, FString::Printf(TEXT("Lets head east")));
			Location.Y += MoveSpeed * DeltaTime;
			break;

		case DirectionState::SOUTHEAST:
			GEngine->AddOnScreenDebugMessage(1, 3.0f, FColor::Yellow, FString::Printf(TEXT("Lets head southeast")));
			Location.X -= (MoveSpeed / 2) * DeltaTime;
			Location.Y += (MoveSpeed / 2) * DeltaTime;
			break;

		case DirectionState::SOUTH:
			GEngine->AddOnScreenDebugMessage(1, 3.0f, FColor::Yellow, FString::Printf(TEXT("Lets head south")));
			Location.X -= MoveSpeed * DeltaTime;
			break;

		case DirectionState::SOUTHWEST:
			GEngine->AddOnScreenDebugMessage(1, 3.0f, FColor::Yellow, FString::Printf(TEXT("Lets head southwest")));
			Location.X -= (MoveSpeed / 2) * DeltaTime;
			Location.Y -= (MoveSpeed / 2) * DeltaTime;
			break;

		case DirectionState::WEST:
			GEngine->AddOnScreenDebugMessage(1, 3.0f, FColor::Yellow, FString::Printf(TEXT("Lets head west")));
			Location.Y -= MoveSpeed * DeltaTime;
			break;

		case DirectionState::NORTHWEST:
			GEngine->AddOnScreenDebugMessage(1, 3.0f, FColor::Yellow, FString::Printf(TEXT("Lets head northwest")));
			Location.X += (MoveSpeed / 2) * DeltaTime;
			Location.Y -= (MoveSpeed / 2) * DeltaTime;
			break;
		}
	}

	SetActorLocation(Location);
}



void APeto::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FRotator CurrentRotation = GetActorRotation();
	FRotator NewRotation = FMath::RInterpTo(CurrentRotation, TargetRotation, DeltaTime, RotationSpeed);

	SetActorRotation(NewRotation);

	Movement(DeltaTime);

	if (SubTick > 75)
	{
		UpdateStats(DeltaTime);

		bHasPlayedSoundEat = false;

		GoToilet();

		PrintStats();
		Direction = DirectionState(FMath::RandRange(0, 8));
		CheckForFood();

		SubTick = 0;
	}

	SubTick++;
}




