// Fill out your copyright notice in the Description page of Project Settings.


#include "Engine/World.h"
#include "Engine.h"
#include "AIController.h"
#include "TankAIController.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	auto ControlledTank = GetControlledTank();
	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Tank object missing!"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Tank: %s"), *(ControlledTank->GetName()));
	}

}


ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerPawn)
	{
		return nullptr;
	}
	
	return Cast<ATank>(PlayerPawn);

}