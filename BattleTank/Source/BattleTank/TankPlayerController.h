// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Public/Tank.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	ATank *GetControlledTank() const;

	//starts at initialziation
	virtual void BeginPlay() override;

	//ticks every frame
	virtual void Tick(float DeltaTime) override;

	//moving the barrel so shot would hit where crosshair intersects the world
	void AimAtCrosshair();

private:
	ATank *ControlledTank = NULL;
};
