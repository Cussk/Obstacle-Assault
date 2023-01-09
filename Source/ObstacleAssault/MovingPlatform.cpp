// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = GetActorLocation();
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MovePlatform(DeltaTime);
	RotatePlatform(DeltaTime);
}

void AMovingPlatform::MovePlatform(float DeltaTime)
{
	//move platform backwards if gone too far
	//check how far moved
	//reverse direction if gone too far
	if (ShouldPlatformReturn())
	{
		//FString ObjectName = GetName(); //FString for dynamic texts
		//float Overshoot = DistanceMoved - MoveDistance; //calculates distance platforms overshot end point, causing drift
		//UE_LOG(LogTemp, Display, TEXT("Object: %s overshot by: %f"), *ObjectName, Overshoot); // %char for specific types, *Variable for FString in Unreal
		FVector MoveDirection = PlatformVelocity.GetSafeNormal(); //gets a normalized vector distance
		StartLocation = StartLocation + (MoveDirection * MoveDistance); //calculates a more precise StartLocation
		SetActorLocation(StartLocation); //sets location of platform to newly defined start location
		PlatformVelocity = -PlatformVelocity; //reverses velocity of platform changing direction
	}
	else //Move platform forwards
	{
		//get current location
		FVector CurrentLocation = GetActorLocation();
		//add vector to location
		CurrentLocation = CurrentLocation + (PlatformVelocity * DeltaTime);
		//set location
		SetActorLocation(CurrentLocation);
	}
}

void AMovingPlatform::RotatePlatform(float DeltaTime)
{
	AddActorLocalRotation(RotationVelocity * DeltaTime);
	
}

bool AMovingPlatform::ShouldPlatformReturn() const
{
	return GetDistanceMoved() > MoveDistance;
}

float AMovingPlatform::GetDistanceMoved() const
{
	return FVector::Dist(StartLocation, GetActorLocation()); //checks how far move from starting location
}

