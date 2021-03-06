// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"
#include "TankBarrel.h"
#include "Kismet/GameplayStatics.h"
#include "TankAimingComponent.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}



void UTankAimingComponent::AimAt(FVector HitLocation)
{
	if (!ensure(Barrel)) //protect Barrel pointer
	{
		return;
	}

	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	//Calculate the OutLaunchVelocity
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(  //kisz�molja a forgat�si sz�get
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);

	if (bHaveAimSolution)
	{
		auto AimDirection = OutLaunchVelocity.GetSafeNormal(); //normaliz�ljuk a vektort
		MoveBarrelTowards(AimDirection);

		auto Time = GetWorld()->GetTimeSeconds();

	}
	//if no solution do nothing
	
	
	



}

void UTankAimingComponent::Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	if (!ensure(BarrelToSet && TurretToSet))
	{
		return;
	}
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}


void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	if (!ensure(Barrel && Turret))
	{
		return;
	}

	//Kikell sz�molni a k�l�nbs�get a mostani rotation �s AimDirection k�z�tt
	auto BarrelRotator = Barrel->GetForwardVector().Rotation(); 
	auto AimAsRotator = AimDirection.Rotation();


	auto DeltaRotator = AimAsRotator - BarrelRotator; //The difference between rotations

	//Mozgatjuk a barrelt
	Barrel->Elevate(DeltaRotator.Pitch);

	if (FMath::Abs(DeltaRotator.Yaw) < 180)
	{
		Turret->Rotate(DeltaRotator.Yaw);
	}
	else // Avoid going the long-way round
	{
		Turret->Rotate(-DeltaRotator.Yaw);
	}
	//Given a max elevation speed, and the frame time
}
