// Copyright 2024 - Luther Williamson

#include "SwingingAxe.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ASwingingAxe::ASwingingAxe()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	SetRootComponent(BaseMesh);
	AxeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Axe Mesh"));
	AxeMesh->SetupAttachment(BaseMesh);
}

// Called when the game starts or when spawned
void ASwingingAxe::BeginPlay()
{
	Super::BeginPlay();
	
	if (AxeMesh)
	{
		// Get the initial angle of the axe
		float AxeAngle = AxeMesh->GetRelativeRotation().Pitch;
		MaxAngle = FMath::Abs(AxeAngle);
		ReverseDirection = AxeAngle < 0;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("AxeMesh is not set for %s"), *GetName());
	}
}

// Called every frame
void ASwingingAxe::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float Time = UGameplayStatics::GetRealTimeSeconds(GetWorld());
	// Use Sine wave to make the axe swing back and forth over time
	float newAngle = MaxAngle * FMath::Sin(Time * 2 * PI / CycleTime);
	if (AxeMesh)
	{
		AxeMesh->SetRelativeRotation(FRotator(ReverseDirection ? -newAngle : newAngle, 0, 0));
	}
}

