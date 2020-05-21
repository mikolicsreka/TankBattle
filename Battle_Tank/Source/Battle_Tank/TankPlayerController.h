// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLE_TANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
		ATank* GetControlledTank() const;

		virtual void BeginPlay() override; ///make sure its override 

		virtual void Tick(float DeltaTime) override;

		void AimTowardsCrossHair();

		//return an OUT parameter, true if hit landscape
		bool GetSightRayHitLocation(FVector& HitLocation) const;

		bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;

		bool GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const;

		UPROPERTY(EditAnywhere)
		float CrosshairXLocation = 0.5f;

		UPROPERTY(EditAnywhere)
		float CrosshairYLocation = 0.3333f;

		UPROPERTY(EditAnywhere)
		float LineTraceRange = 1000000.f; //1 million cm
	
};
