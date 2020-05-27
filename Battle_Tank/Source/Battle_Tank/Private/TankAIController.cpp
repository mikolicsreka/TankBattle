// Fill out your copyright notice in the Description page of Project Settings.


#include "Engine/World.h"
#include "Engine.h"
#include "AIController.h"
#include "TankAIController.h"
#include "Battle_Tank/Tank.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}


void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	auto ControlledTank = Cast<ATank>(GetPawn());


	if (ensure(PlayerTank))
	{
		//Aim towards the player
		MoveToActor(PlayerTank,
			AcceptanceRadius  //mikor álljon meg, radius
			);


		///Aim towards player
		ControlledTank->AimAt(PlayerTank->GetActorLocation());

		//fire if ready
		ControlledTank->Fire();
	}
}
