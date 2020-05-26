// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "TankMovementComponent.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//no need to protect pointers as added at construction
	///hozzaadjuk a blueprintbe
	///TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
	///TankMovementComponent = CreateDefaultSubobject<UTankMovementComponent>(FName("Movement Component"));
}




void ATank::BeginPlay()
{
	Super::BeginPlay();


}

void ATank::AimAt(FVector HitLocation)
{
	if (!TankAimingComponent) { return; } //meg kell védeni mivel már nem a konstruktorba adjuk hozzá

	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);

}

void ATank::Fire()
{

	bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;


	if (Barrel && isReloaded)
	{
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, Barrel->GetSocketLocation("Projectile"), Barrel->GetSocketRotation("Projectile"));
		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
	}


}

