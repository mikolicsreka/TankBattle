// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
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

	Barrel = FindComponentByClass<UTankBarrel>();

}



void ATank::Fire()
{
	if (!ensure(Barrel))
	{
		return;
	}
	bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;


	if (isReloaded)
	{
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, Barrel->GetSocketLocation("Projectile"), Barrel->GetSocketRotation("Projectile"));
		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
	}


}

