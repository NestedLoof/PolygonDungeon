// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPP_StoneBridge_PW.generated.h"

UCLASS()
class POLYGONDUNGEONS_API ACPP_StoneBridge_PW : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACPP_StoneBridge_PW();

	// Create a static mesh for the platform bridge lift
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Auto Movement")
	UStaticMeshComponent* staticMesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	// To hold the X-Axis value
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Auto Movement")
	float XValue;

	// To hold the X-Axis value
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Auto Movement")
	float YValue;

	// To hold the X-Axis value
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Auto Movement")
	float ZValue;

};
