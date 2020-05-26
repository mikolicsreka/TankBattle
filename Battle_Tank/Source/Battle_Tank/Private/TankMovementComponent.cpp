  // Fill out your copyright notice in the Description page of Project Settings.


#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialize(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{

	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::IntendTurnRight(float Throttle)
{
	if (!LeftTrack || !RightTrack)
	{
		return;
	}

	LeftTrack->SetThrottle(-Throttle);
	RightTrack->SetThrottle(Throttle);
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	//No need to call super as we're replacing the functionality

	auto TankName = GetOwner()->GetName();
	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto AIForwardIntention = MoveVelocity.GetSafeNormal();

	auto ForwardThrow = FVector::DotProduct(TankForward, AIForwardIntention);
	IntendMoveForward(ForwardThrow);

	auto RightThrow = FVector::CrossProduct(TankForward, AIForwardIntention).Z; //skaláris szorzat i guess
	IntendTurnRight(RightThrow);

	UE_LOG(LogTemp, Warning, TEXT("%f forward, %f right"), ForwardThrow, RightThrow);
}

void UTankMovementComponent::IntendMoveForward(float Throttle)
{
	if (!LeftTrack || !RightTrack)
	{
		return;
	}

	
	LeftTrack->SetThrottle(Throttle);
	RightTrack->SetThrottle(Throttle);
}