// Copyright Jake Jeffery 2018

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	AActor* owner;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void OpenDoor(float DeltaTime);

	void CloseDoor(float DeltaTime);

		
private:
	UPROPERTY(EditAnywhere)
	float OpenAngle = -90.0f;

	UPROPERTY(EditAnywhere)
	ATriggerVolume *PressurePlate;

	AActor *ActorThatOpens;

	UPROPERTY(EditAnywhere)
	float DoorCloseDelay = 1.0f;

	UPROPERTY(EditAnywhere)
	float DoorOpenSpeed = 1.0f;

	UPROPERTY(EditAnywhere)
	float DoorCloseSpeed = 1.0f;

	float LastDoorCloseTime = 0;
	bool DoorOpening = false;

};
