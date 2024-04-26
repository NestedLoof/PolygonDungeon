// Copyright 2024 - Luther Williamson

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SwingingAxe.generated.h"

UCLASS()
class POLYGONDUNGEONS_API ASwingingAxe : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASwingingAxe();

	// Meshes
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base")
	UStaticMeshComponent* BaseMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Axe")
	UStaticMeshComponent* AxeMesh;

	// Swinging variables
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Axe")
	float CycleTime = 2;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	// Swinging variables
	float MaxAngle = 0;
	bool ReverseDirection = false;

};
