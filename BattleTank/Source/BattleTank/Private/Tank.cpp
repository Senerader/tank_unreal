// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

float ATank::GetHealthPercent() const
{
	return (float)(CurrentHealth)/(float)(StartingHealth);
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = StartingHealth;
}

float ATank::TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser)
{
	int32 DamagePoints = FPlatformMath::RoundToInt(DamageAmount);
	int32 ClampedDamage = FMath::Clamp<int32>(DamagePoints, 0, CurrentHealth);
	
	CurrentHealth -= ClampedDamage;
	if (CurrentHealth <= 0)
	{
		OnTankDeath.Broadcast();
	}
	return ClampedDamage;
}

