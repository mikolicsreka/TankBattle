// Fill out your copyright notice in the Description page of Project Settings.


#include "Engine/World.h"
#include "Engine.h"
#include "AIController.h"
#include "TankAIController.h"
#include "TankAimingComponent.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}


void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto ControlledTank = GetPawn();
	auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (!ensure(PlayerTank && PlayerTank && AimingComponent))
	{
		return;
	}
		//Aim towards the player
		MoveToActor(PlayerTank,
			AcceptanceRadius  //mikor álljon meg, radius
			);


		///Aim towards player
		AimingComponent->AimAt(PlayerTank->GetActorLocation());

		//fire if ready
		//ControlledTank->Fire();
	
}
