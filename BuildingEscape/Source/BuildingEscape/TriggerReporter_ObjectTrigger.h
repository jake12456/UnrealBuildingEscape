// Copyright Jake Jeffery 2018

#pragma once

#include "CoreMinimal.h"
#include "TriggerReporterBase.h"
#include "TriggerReporter_ObjectTrigger.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BUILDINGESCAPE_API UTriggerReporter_ObjectTrigger : public UTriggerReporterBase
{
	GENERATED_BODY()

public:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void OnOverlapEventEnter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep) override;
	virtual void OnOverlapEventExit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;


	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

	//if this object is what overlapped with us, then call trigger is hit
	UPROPERTY(EditAnywhere)
	AActor * objectToTrigger;
};
