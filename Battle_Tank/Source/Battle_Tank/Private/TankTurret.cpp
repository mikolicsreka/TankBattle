// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTurret.h"

void UTankTurret::Rotate(float RelativeSpeed)
{
	///Move the turret the right amount this frame
	//Given a max elevation speed and the frame time
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);

	UE_LOG(LogTemp, Warning, TEXT("location: %f"), USceneComponent::GetRelativeRotation().Yaw);
	auto RotationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto NewRotation = GetRelativeRotation().Yaw + RotationChange;
	SetRelativeRotation(FRotator(0, NewRotation, 0));
}
