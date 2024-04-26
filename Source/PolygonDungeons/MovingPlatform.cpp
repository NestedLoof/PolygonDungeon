// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Initialise the spline as the root component, then the platform moves relative to it
	MovementSpline = CreateDefaultSubobject<USplineComponent>(TEXT("Movement Spline"));
	SetRootComponent(MovementSpline);
	PlatformMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Platform Mesh"));
	PlatformMesh->SetupAttachment(MovementSpline);

}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	const FVector SplineLocation = MovementSpline->GetLocationAtSplinePoint(0, ESplineCoordinateSpace::World);
	PlatformMesh->SetWorldLocation(SplineLocation);

	PlayMovementTimeline();
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Move the platform along the spline each tick according to movement timeline
	if (MovementTimeline.IsPlaying())
	{
		MovementTimeline.TickTimeline(DeltaTime);
	}
	/*else
	{
		PlayMovementTimeline();
	}*/
}

void AMovingPlatform::PlayMovementTimeline()
{
	// Create progress function with movement curve
	FOnTimelineFloat ProgressFunction;
	ProgressFunction.BindUFunction(this, TEXT("ProcessMovementTimeline"));
	MovementTimeline.AddInterpFloat(MovementCurve, ProgressFunction);

	// Create finished function
	FOnTimelineEvent OnTimelineFinishedFunction;
	OnTimelineFinishedFunction.BindUFunction(this, TEXT("OnEndMovementTimeline"));
	MovementTimeline.SetTimelineFinishedFunc(OnTimelineFinishedFunction);

	// Play the timeline
	MovementTimeline.SetTimelineLengthMode(ETimelineLengthMode::TL_LastKeyFrame);
	MovementTimeline.PlayFromStart();

	bIsMovingForwards = true;
}

void AMovingPlatform::ReverseMovementTimeline()
{
	if (!MovementTimeline.IsReversing())
	{
		MovementTimeline.Reverse();
	}
}

void AMovingPlatform::ProcessMovementTimeline(float Value)
{
	const float SplineLength = MovementSpline->GetSplineLength();

	FVector CurrentSplineLocation = MovementSpline->GetLocationAtDistanceAlongSpline(Value * SplineLength, ESplineCoordinateSpace::World);
	FRotator CurrentSplineRotation = MovementSpline->GetRotationAtDistanceAlongSpline(Value * SplineLength, ESplineCoordinateSpace::World);

	CurrentSplineRotation.Pitch = 0.f;
	PlatformMesh ->SetWorldLocationAndRotation(CurrentSplineLocation, CurrentSplineRotation);
}

void AMovingPlatform::OnEndMovementTimeline()
{
	bIsMovingForwards = !bIsMovingForwards;
	if (!bIsMovingForwards)
	{
		MovementTimeline.Reverse();
	}
	else
	{
		MovementTimeline.Play();
	}
	
}

