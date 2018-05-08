// Copyright Jake Jeffery 2018

#include "TriggerReporter_ObjectTrigger.h"

// Called when the game starts or when spawned
void UTriggerReporter_ObjectTrigger::BeginPlay()
{
	Super::BeginPlay();
}

void UTriggerReporter_ObjectTrigger::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime,TickType,ThisTickFunction);
	//get the actor being triggered
}

void UTriggerReporter_ObjectTrigger::OnOverlapEventEnter(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep)
{
	if (OtherActor == objectToTrigger) 
	{
		TriggerEnter();
	}
}
void UTriggerReporter_ObjectTrigger::OnOverlapEventExit(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor == objectToTrigger)
	{
		TriggerExit();
	}
}