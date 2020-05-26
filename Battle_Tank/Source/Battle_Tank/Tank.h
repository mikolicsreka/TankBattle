// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankBarrel; //Forward Declaration
class UTankAimingComponent;
class UTankTurret;
class AProjectile;
class UTankMovementComponent;

UCLASS()
class BATTLE_TANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = "Firing")
	void Fire();

protected:
	UPROPERTY(BlueprintReadOnly)
	UTankAimingComponent* TankAimingComponent = nullptr;

	UPROPERTY(BlueprintReadOnly)
	UTankMovementComponent* TankMovementComponent = nullptr;

private:
	// Sets default values for this pawn's properties
	ATank();

	UPROPERTY(EditDefaultsOnly, Category = "Firing") //EditDefaultsOnly: csak a blueprintbõl editelhetõ => az összes tankra egyszerre, nem lehet mindegyiknek más
	float ReloadTimeInSeconds = 3.f;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 4000; //Sensible starting value, 1000m/s

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBlueprint; //alternative: tsubclass https://docs.unrealengine.com/en-US/Programming/UnrealArchitecture/TSubclassOf/index.html



	//Local barrel reference for spawning projectile
	UTankBarrel* Barrel = nullptr;


	double LastFireTime = 0.0;
};
