// PW changes


#include "CPP_BridgePlatform_PW.h"

// Sets default values
ACPP_BridgePlatform_PW::ACPP_BridgePlatform_PW()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create a static mesh for the bridge platform lift
	staticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));

}

// Called when the game starts or when spawned
void ACPP_BridgePlatform_PW::BeginPlay()
{
	Super::BeginPlay();

	
}

// Called every frame
void ACPP_BridgePlatform_PW::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// on every tick, change the location to simulate a floating platform lift

	// Get the actor location
	FVector NewLocation = GetActorLocation();

	// Compute the delta distance using Sin function
	float DeltaHeight = (FMath::Sin(RunningTime + DeltaTime) - FMath::Sin(RunningTime));

	// Set the new coordinates
	NewLocation.X += DeltaHeight * XValue;
	NewLocation.Y += DeltaHeight * YValue;
	NewLocation.Z += DeltaHeight * ZValue;

	//Increment running time;
	RunningTime += DeltaTime;

	//set new location of the actor
	SetActorLocation(NewLocation);

}

