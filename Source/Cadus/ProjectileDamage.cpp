// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectileDamage.h"
#include "Engine/GameEngine.h"


// Sets default values for this component's properties
UProjectileDamage::UProjectileDamage()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	//Collider = CreateDefaultSubobject<USphereComponent>(TEXT("Collider"));
	//Collider->SetSimulatePhysics(true);
	//Collider->SetNotifyRigidBodyCollision(true);
	//Collider->BodyInstance.SetCollisionProfileName("BlockAllDynamic");
	//Collider->OnComponentHit.AddDynamic(this, &UProjectileDamage::OnCompHit);

	//Collider->SetupAttachment(GetOwner()->GetRootComponent());

	// ...
}


// Called when the game starts
void UProjectileDamage::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UProjectileDamage::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	
}

void UProjectileDamage::OnCompHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("I Hit: %s"), *OtherActor->GetName()));
	if ((OtherActor != NULL) && (OtherComp != NULL))
	{
		if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("I Hit: %s"), *OtherActor->GetName()));
	}
}