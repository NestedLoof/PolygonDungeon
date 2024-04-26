// PW.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPP_BridgePlatform_PW.generated.h"


UCLASS()
class POLYGONDUNGEONS_API ACPP_BridgePlatform_PW : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACPP_BridgePlatform_PW();

	// Create a static mesh for the platform bridge lift
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Auto Movement")
	UStaticMeshComponent* staticMesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// keeps track of game running time and used for the movement calculation
	float RunningTime;

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
