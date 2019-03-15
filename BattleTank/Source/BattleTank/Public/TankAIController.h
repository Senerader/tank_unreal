// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Public/Tank.h"
#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

class UTankAimingComponent;
/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
public:
	//starts at initialziation
	virtual void BeginPlay() override;

	//ticks every frame
	virtual void Tick(float DeltaTime) override;

protected:
	//how close can AI tank get to the player
	UPROPERTY(EditAnywhere)
	float AcceptanceRadius = 8000.f;

private:
	APawn *AITank = NULL;
	APawn *PlayerTank = NULL;
	FVector PlayerCoordinates;

	UTankAimingComponent* TankAimingComponent = nullptr;
};
