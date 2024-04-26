// Copyright 2024 - Luther Williamson

#include "SpinningSaw.h"

// Sets default values
ASpinningSaw::ASpinningSaw()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	SetRootComponent(BaseMesh);
	SawMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Saw Mesh"));
	SawMesh->SetupAttachment(BaseMesh);

}

// Return true if the base mesh is not set
void ASpinningSaw::InitialiseBaseLength()
{
	if (BaseMesh)
	{
		BaseLength = BaseMesh->CalcLocalBounds().BoxExtent.Y;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("BaseMesh is not set for %s"), *GetName());
	}
}

// Return true if the saw mesh is not set
void ASpinningSaw::InitialiseStartLocation()
{
	if (SawMesh)
	{
		StartLocation = SawMesh->GetRelativeLocation();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("SawMesh is not set for %s"), *GetName());
	}
}

// Called when the game starts or when spawned
void ASpinningSaw::BeginPlay()
{
	Super::BeginPlay();

	InitialiseStartLocation();
	InitialiseBaseLength();
	
}

// Called every frame
void ASpinningSaw::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (ShouldMove)
	{
		MoveSaw(DeltaTime);
	}

	RotateSaw(DeltaTime);
}

void ASpinningSaw::MoveSaw(float DeltaTime)
{
	if (!SawMesh)
	{
		UE_LOG(LogTemp, Error, TEXT("SawMesh is not set for %s"), *GetName());
		return;
	}

	// change the current location of the saw based on the travel speed.
	FVector CurrentLocation = SawMesh->GetRelativeLocation();
	FVector TravelVelocity(0, TravelSpeed, 0);
	CurrentLocation += TravelVelocity * DeltaTime;
	SawMesh->SetRelativeLocation(CurrentLocation);

	if (ShouldSawReturn(CurrentLocation))
	{
		if (!BaseMesh)
		{
			UE_LOG(LogTemp, Error, TEXT("BaseMesh is not set for %s"), *GetName());
			return;
		}

		// Reset the start location to the intended target location
		FVector MoveDirection = TravelVelocity.GetSafeNormal();
		StartLocation += MoveDirection * BaseLength;
		SawMesh->SetRelativeLocation(StartLocation);
		
		// Reverse the direction of the saw
		TravelSpeed = -TravelSpeed;

		// Set a timer to stop the movement
		if (DelayTime > 0)
		{
			StopMovement();
		}
	}
}

void ASpinningSaw::RotateSaw(float DeltaTime)
{
	// rotate the blade
	const float DeltaRotationSpeed = RotationSpeed * DeltaTime;
	const FRotator DeltaRotation(0, 0, DeltaRotationSpeed);
	SawMesh->AddLocalRotation(DeltaRotation);
}

bool ASpinningSaw::ShouldSawReturn(FVector CurrentLocation) const
{
	return GetDistanceMoved(CurrentLocation) >= BaseLength;
}

float ASpinningSaw::GetDistanceMoved(FVector CurrentLocation) const
{
	return FVector::Distance(StartLocation, CurrentLocation);
}

void ASpinningSaw::StopMovement()
{
	ShouldMove = false;

	// Set a timer to allow the saw to move again after delay time
	// But first, clear the timer if it is already set
	if (MoveDelayTimerHandle.IsValid())
	{
		GetWorldTimerManager().ClearTimer(MoveDelayTimerHandle);
	}
	GetWorldTimerManager().SetTimer(MoveDelayTimerHandle, this, &ASpinningSaw::AllowMovement, DelayTime, false);
}

void ASpinningSaw::AllowMovement()
{
	ShouldMove = true;
	GetWorldTimerManager().ClearTimer(MoveDelayTimerHandle);
}
