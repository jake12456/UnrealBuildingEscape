// Copyright Jake Jeffery 2018

#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "Components/PrimitiveComponent.h"
// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	owner = GetOwner();
	// ...	
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	float MassOnPressurePlate = GetTotalMassOfActorsOnPlate();
	if (MassOnPressurePlate > MassToOpenDoor)
	{
		OpenDoor(DeltaTime);
		if (!DoorOpening) {
			DoorOpening = true;
			LastDoorCloseTime = GetWorld()->GetTimeSeconds();
		}
	}
	else 
	{
		if (GetWorld()->GetTimeSeconds() - LastDoorCloseTime > DoorCloseDelay) 
		{
			DoorOpening = false;
			CloseDoor(DeltaTime);
		}
	}
	// ...
}

void UOpenDoor::OpenDoor(float DeltaTime)
{
	FRotator dir = owner->GetActorRotation();
	dir.Yaw = OpenAngle;
	owner->SetActorRotation(FMath::Lerp(owner->GetActorRotation(),dir,DeltaTime * DoorOpenSpeed));
	GetWorld()->GetTimeSeconds();
}
void UOpenDoor::CloseDoor(float DeltaTime)
{
	FRotator dir = owner->GetActorRotation();
	dir.Yaw = 0;
	owner->SetActorRotation(FMath::Lerp(owner->GetActorRotation(), dir, DeltaTime * DoorCloseSpeed));
}

float UOpenDoor::GetTotalMassOfActorsOnPlate()
{
	float ret = 0;
	TArray<AActor *>OverLappingActors;
	PressurePlate->GetOverlappingActors(OUT OverLappingActors);
	for (const auto * OverLappingActor : OverLappingActors) {
		ret += OverLappingActor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}
	return ret;
}