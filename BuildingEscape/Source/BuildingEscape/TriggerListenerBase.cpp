// Copyright Jake Jeffery 2018

#include "TriggerListenerBase.h"


// Sets default values
UTriggerListenerBase::UTriggerListenerBase()
{
}

// Called when the game starts or when spawned
void UTriggerListenerBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void UTriggerListenerBase::	TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UTriggerListenerBase::CallTriggerReportEnter()
{
	OnTriggerReportEnter.Broadcast();;
}

void UTriggerListenerBase::CallTriggerReportExit()
{
	OnTriggerReportExit.Broadcast();;
}

