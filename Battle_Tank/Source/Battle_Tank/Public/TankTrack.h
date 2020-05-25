// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLE_TANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	//Sets the throttle between -1 and +1
	UFUNCTION(BlueprintCallable, Category = Input)
	void SetThrottle(float Throttle);

	/// Force = mass * acceleration (kg, m/s)
	// 0-60 in 10 sec is 2800 ms/s approx.
	//Tank mass = 40k kg

	// Max force per track, in Newtons
	UPROPERTY(EditDefaultsOnly)
	float TrackMaxDrivingForce = 40000000; 
};
