// Copyright Jake Jeffery 2018

#include "Grabber.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Controller.h"
#include "Engine/World.h"
#include "DisplayDebugHelpers.h"
#include "DrawDebugHelpers.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	FindPhysicsHandleComonent();
	SetupInputComponent();
	World = GetWorld();
}

void UGrabber::SetupInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (!InputComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("No InputComponent Handle On : %s"), *GetOwner()->GetName());
	}
	else
	{
		InputComponent->BindAction("Grab", EInputEvent::IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", EInputEvent::IE_Released, this, &UGrabber::Release);
	}
}

void UGrabber::FindPhysicsHandleComonent()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (!PhysicsHandle)
	{
		UE_LOG(LogTemp, Error, TEXT("No Physics Handle On : %s"), *GetOwner()->GetName());
	}
}

void UGrabber::Grab()
{
	bool hit = false;
	FHitResult ResultOfLineTrace;
	if (GetFirstPhysicsBodyInReach(OUT ResultOfLineTrace))
	{
		auto ActorSelected = ResultOfLineTrace.GetActor();
		auto ComponentToGrab = ResultOfLineTrace.GetComponent();
		auto GrabLocation = ActorSelected->GetActorLocation();
		PhysicsHandle->GrabComponent(
			ComponentToGrab,
			NAME_None, 
			GrabLocation,
			true
		);
	}
}
bool UGrabber::GetFirstPhysicsBodyInReach(FHitResult &ResultOfLineTrace)
{
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());
	return World->LineTraceSingleByObjectType(
		OUT ResultOfLineTrace,
		PlayerViewPointLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters);
}
void UGrabber::Release() 
{
	PhysicsHandle->ReleaseComponent();
}
// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	UpdateWorldVars();
	if (PhysicsHandle->GrabbedComponent) 
	{
		PhysicsHandle->SetTargetLocation(LineTraceEnd);
	}
}

void UGrabber::UpdateWorldVars()
{
	World->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);
	LineTraceEnd = PlayerViewPointLocation + (PlayerViewPointRotation.Vector() * Reach);
}