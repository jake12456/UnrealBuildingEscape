// Copyright Jake Jeffery 2018

#include "TriggerReporterBase.h"


// Sets default values
UTriggerReporterBase::UTriggerReporterBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void UTriggerReporterBase::BeginPlay()
{
	Super::BeginPlay();
	triggerListener = Cast<UTriggerListenerBase>(ActorToTrigger->GetComponentByClass(UTriggerListenerBase::StaticClass()));
	if (!triggerListener)UE_LOG(LogTemp, Warning, TEXT("Actor Assigned To Trigger From %s, does not have a trigger listener"), *GetOwner()->GetName());
}

void UTriggerReporterBase::TriggerEnter()
{
	if (triggerListener) 
	{
		triggerListener->CallTriggerReportEnter();
	}
}
void UTriggerReporterBase::TriggerExit()
{
	if (triggerListener)
	{
		triggerListener->CallTriggerReportExit();
	}
}
void UTriggerReporterBase::OnOverlapEventEnter(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep)
{
	TriggerEnter();
}
void UTriggerReporterBase::OnOverlapEventExit(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	TriggerExit();
}
void UTriggerReporterBase::OverlapEventEnter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	OnOverlapEventEnter(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep);
}
void UTriggerReporterBase::OverlapEventExit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	OnOverlapEventExit(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);
}

// Called every frame
void UTriggerReporterBase::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)

{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

