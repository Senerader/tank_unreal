// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TankAimingComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Classes/Components/StaticMeshComponent.h"
#include "Tank.generated.h"

//Forward declarations
class AProjectile;
class UTankBarrel;
class UTankAimingComponent;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	void AimAt(FVector AimHitLocation);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void Fire();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly)
	UTankAimingComponent *TankAimingComponent = nullptr;


private:	
	// Sets default values for this pawn's properties
	ATank();

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float ReloadTimeSec = 3.f;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float LaunchSpeed = 40000; //sensible starting value

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	TSubclassOf<AProjectile> ProjectileBP;

	UTankBarrel *LocaLBarrel = nullptr;

	float LastFireTime = 0;
};
