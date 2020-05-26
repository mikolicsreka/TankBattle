// Fill out your copyright notice in the Description page of Project Settings.

#include "Engine/World.h"
#include "Tank.h"
#include "TankPlayerController.h"
#include "Public/TankAimingComponent.h"

#define OUT

void ATankPlayerController::BeginPlay()
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
	
	
	auto AimingComponent = GetControlledTank()->FindComponentByClass<UTankAimingComponent>();
	if (AimingComponent)
	{
		FoundAimingComponent(AimingComponent);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Aiming component is missing!"));
	}
		

}


void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimTowardsCrossHair();


}

void ATankPlayerController::AimTowardsCrossHair()
{
	if (!GetControlledTank())
	{
		return;
	}

	FVector HitLocation;
	///If it hits the landscape
	if (GetSightRayHitLocation(HitLocation)) //Has side effect, is going to line trace
	{
		///Tell the controlled tank to aim at this point
		GetControlledTank()->AimAt(HitLocation);
			

	}
	


}
///Get World location if linetrace trough crosshair, true if hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	
	//Find the crosshair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);

	auto ScreenLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);

	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, OUT LookDirection))
	{
		//Line trace along that lookdirection, and see what we hit (up to max range)
		
		GetLookVectorHitLocation(LookDirection, OUT HitLocation);

		

	}


	
	//line trace along that LookDirection, and see what we hit (up to max range)

	return true;
}


bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);

	//if line trace succeeds
	if (GetWorld()->LineTraceSingleByChannel(
		HitResult,
		StartLocation,
		EndLocation,
		ECollisionChannel::ECC_Visibility) // hit anything which is visible
		)
	{
		HitLocation = HitResult.Location;
		return true;
	}

	///if line trace fails
	HitLocation = FVector(0);
	return false;
	
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{

	FVector CameraWorldLocation; ///to be discarded

	//"de-project" the screen position of the crosshair to a world direction	
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, OUT CameraWorldLocation, OUT LookDirection);

}



