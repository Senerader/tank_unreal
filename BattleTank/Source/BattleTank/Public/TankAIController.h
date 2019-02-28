// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Public/Tank.h"
#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

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
private:
	ATank *GetAITank() const;
	ATank *GetPlayerTank() const;
	
	ATank *AITank = NULL;
	ATank *PlayerTank = NULL;
};
