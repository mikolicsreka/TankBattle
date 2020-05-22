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



void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	if (!Barrel) //protect Barrel pointer
	{
		return;
	}

	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(  //kiszámolja a forgatási szöget
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
		auto AimDirection = OutLaunchVelocity.GetSafeNormal(); //normalizáljuk a vektort
		MoveBarrelTowards(AimDirection);

		auto Time = GetWorld()->GetTimeSeconds();

	}
	else
	{
		auto Time = GetWorld()->GetTimeSeconds();

	}
	
	
	//Calculate the OutLaunchVelocity



}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	if (!BarrelToSet)
	{
		return;
	}
	Barrel = BarrelToSet;
}

void UTankAimingComponent::SetTurretReference(UTankTurret* TurretToSet)
{
	if (!TurretToSet)
	{
		return;
	}
	Turret = TurretToSet;
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	//Kikell számolni a különbséget a mostani rotation és AimDirection között
	auto BarrelRotator = Barrel->GetForwardVector().Rotation(); 
	auto AimAsRotator = AimDirection.Rotation();


	auto DeltaRotator = AimAsRotator - BarrelRotator; //The difference between rotations

	//Mozgatjuk a barrelt
	Barrel->Elevate(DeltaRotator.Pitch);
	Turret->Rotate(DeltaRotator.Yaw);
	//Given a max elevation speed, and the frame time
}

