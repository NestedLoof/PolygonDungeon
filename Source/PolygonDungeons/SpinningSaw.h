// Copyright 2024 - Luther Williamson

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpinningSaw.generated.h"

UCLASS()
class POLYGONDUNGEONS_API ASpinningSaw : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpinningSaw();

	// meshes
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base")
	UStaticMeshComponent* BaseMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpinningSaw")
	UStaticMeshComponent* SawMesh;

	// saw movement variables
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpinningSaw")
	float RotationSpeed = 300;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpinningSaw")
	float TravelSpeed = 100;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpinningSaw")
	float DelayTime = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpinningSaw")
	bool ShouldMove = true;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	FVector StartLocation;
	float BaseLength = 0;
	FTimerHandle MoveDelayTimerHandle;

	void InitialiseBaseLength();
	void InitialiseStartLocation();
	void MoveSaw(float DeltaTime);
	void RotateSaw(float DeltaTime);
	bool ShouldSawReturn(FVector CurrentLocation) const;
	float GetDistanceMoved(FVector CurrentLocation) const;
	void StopMovement();
	void AllowMovement();
};
