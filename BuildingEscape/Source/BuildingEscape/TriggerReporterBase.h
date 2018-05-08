// Copyright Jake Jeffery 2018

#pragma once

#include "CoreMinimal.h"
#include "Engine/EngineTypes.h"
#include "Components/ActorComponent.h"
#include "Components/BoxComponent.h"
#include "TriggerListenerBase.h"
#include "Engine/TriggerVolume.h"
#include "TriggerReporterBase.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BUILDINGESCAPE_API UTriggerReporterBase : public UActorComponent
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	UTriggerReporterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	//Virtual function for reporting trigger enter to object
	virtual void TriggerEnter();
	//Virtual function for reporting trigger exit to object
	virtual void TriggerExit();

	//Event to trigger enter on derived classes to report when an overlap occurs
	virtual void OnOverlapEventEnter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep);

	//Event to trigger exit on derived classes to report when an overlap occurs
	virtual void OnOverlapEventExit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	//Actor To Report To. If multiple are needed make a forwarder.
	UPROPERTY(EditAnywhere)
	AActor *ActorToTrigger = nullptr;
		
	UTriggerListenerBase *triggerListener = nullptr;
	
	//Listener for Overlap of PressurePlate
	UFUNCTION(BlueprintCallable, Category = "Custom Triggerable Nodes")
	void OverlapEventEnter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable, Category = "Custom Triggerable Nodes")
	void OverlapEventExit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
