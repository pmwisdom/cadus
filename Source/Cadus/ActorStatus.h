// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ActorStatus.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CADUS_API UActorStatus : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UActorStatus();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void DamageActor(int amount);

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int CurrentHealth;

	UPROPERTY(BlueprintReadOnly)
	bool bIsDead;


};
