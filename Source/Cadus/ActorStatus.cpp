// Fill out your copyright notice in the Description page of Project Settings.

#include "ActorStatus.h"


// Sets default values for this component's properties
UActorStatus::UActorStatus()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	CurrentHealth = Health;
	bIsDead = false;
}


// Called when the game starts
void UActorStatus::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UActorStatus::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UActorStatus::DamageActor(int Amount) {
	if (Amount - CurrentHealth) {
		CurrentHealth = 0;
		bIsDead = true;
	}

	CurrentHealth -= Amount;
}

