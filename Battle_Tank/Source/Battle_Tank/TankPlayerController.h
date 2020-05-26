// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class ATank;

UCLASS()
class BATTLE_TANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	UFUNCTION(BlueprintCallable, Category = "Setup")
	ATank* GetControlledTank() const;

private:
		virtual void BeginPlay() override; ///make sure its override 

		virtual void Tick(float DeltaTime) override;

		void AimTowardsCrossHair();

		//return an OUT parameter, true if hit landscape
		bool GetSightRayHitLocation(FVector& HitLocation) const;

		bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;

		bool GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const;

		UPROPERTY(EditDefaultsOnly)
		float CrosshairXLocation = 0.5f;

		UPROPERTY(EditDefaultsOnly)
		float CrosshairYLocation = 0.3333f;

		UPROPERTY(EditDefaultsOnly)
		float LineTraceRange = 1000000.f; //1 million cm
	
};
