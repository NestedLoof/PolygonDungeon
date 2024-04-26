// Copyright 2024 - Luther Williamson

#include "HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// turned off tick for optimisation
	PrimaryComponentTick.bCanEverTick = false;

	// init health
	DefaultHealth = 100;
	Health = DefaultHealth;
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	AActor* Owner = GetOwner();
	if (Owner)
	{
		Owner->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::TakeDamage);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Owner is not set for %s"), *GetName());
	}
	
}

// Called when apply damage is triggered
void UHealthComponent::TakeDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
	if (Damage <= 0)
	{
		return;
	}

	Health = FMath::Clamp(Health - Damage, 0.0f, DefaultHealth);
	OnDamage.Broadcast(DamageCauser);

	UE_LOG(LogTemp, Warning, TEXT("Health: %s"), *FString::SanitizeFloat(Health));

}

