// Copyright Jake Jeffery 2018

#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
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
	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
	// ...	
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (PressurePlate->IsOverlappingActor(ActorThatOpens))
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

