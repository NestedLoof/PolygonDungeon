// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SplineComponent.h"
#include "GameFramework/Actor.h"
#include "Components/TimelineComponent.h"
#include "MovingPlatform.generated.h"

UCLASS()
class POLYGONDUNGEONS_API AMovingPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMovingPlatform();

	// Timeline functions
	UFUNCTION()
	void ProcessMovementTimeline(float Value);
	UFUNCTION()
	void OnEndMovementTimeline();
	UFUNCTION()
	void PlayMovementTimeline();
	UFUNCTION()
	void ReverseMovementTimeline();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Components
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform")
	UStaticMeshComponent* PlatformMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform")
	USplineComponent* MovementSpline;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform")
	UCurveFloat* MovementCurve;


private:

	FTimeline MovementTimeline;
	bool bIsMovingForwards;
};
