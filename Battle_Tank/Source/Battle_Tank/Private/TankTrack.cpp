// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTrack.h"
#include "Components/PrimitiveComponent.h"


void UTankTrack::SetThrottle(float Throttle)
{
	UE_LOG(LogTemp, Warning, TEXT("throttle %f"), Throttle);

	
	// todo clamp actual throttle value, so player cant over drive
	auto ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();

	UE_LOG(LogTemp, Warning, TEXT("throttle %s"), *ForceLocation.ToString());
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied,ForceLocation);



}
