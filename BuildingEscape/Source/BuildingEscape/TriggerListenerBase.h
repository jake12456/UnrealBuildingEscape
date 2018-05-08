// Copyright Jake Jeffery 2018

#pragma once

#include "CoreMinimal.h"
#include "Engine/EngineTypes.h"
#include "Components/ActorComponent.h"
#include "TriggerListenerBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTriggerEvent);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BUILDINGESCAPE_API UTriggerListenerBase : public UActorComponent
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	UTriggerListenerBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void CallTriggerReportEnter();
	virtual void CallTriggerReportExit();

private:

	UPROPERTY(BlueprintAssignable)
	FOnTriggerEvent OnTriggerReportEnter;

	UPROPERTY(BlueprintAssignable)
	FOnTriggerEvent OnTriggerReportExit;


};
