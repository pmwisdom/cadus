// Fill out your copyright notice in the Description page of Project Settings.

#include "FlyingPawn.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Engine/World.h"
#include "Engine/StaticMesh.h"
#include "Engine/GameEngine.h"



// Sets default values
AFlyingPawn::AFlyingPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Structure to hold one-time initialization
	struct FConstructorStatics
	{
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> PlaneMesh;
		FConstructorStatics()
			: PlaneMesh(TEXT("/Game/Flying/Meshes/UFO.UFO"))
		{
		}
	};
	static FConstructorStatics ConstructorStatics;

	RootMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cube Mesh"));
	RootMesh->SetVisibility(false);
	RootComponent = RootMesh;

	// Create static mesh component
	PlaneMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlaneMesh0"));
	PlaneMesh->SetStaticMesh(ConstructorStatics.PlaneMesh.Get());	// Set static mesh
	PlaneMesh->SetupAttachment(RootComponent);

	// Create a spring arm component
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm0"));
	SpringArm->SetupAttachment(RootComponent);	// Attach SpringArm to RootComponent
	SpringArm->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	SpringArm->SocketOffset = FVector(0.f, 0.f, 60.f);
	SpringArm->bEnableCameraLag = false;	// Do not allow camera to lag
	SpringArm->CameraLagSpeed = 15.f;


	//Create the target Spring arm component
	//TargetSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm1"));
	//TargetSpringArm->SetupAttachment(RootComponent);	// Attach SpringArm to RootComponent
	//TargetSpringArm->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	//TargetSpringArm->SocketOffset = FVector(0.f, 0.f, 60.f);
	//TargetSpringArm->bEnableCameraLag = false;	// Do not allow camera to lag

	//TargetMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cube Mesh"));
	//TargetMesh->SetupAttachment(TargetSpringArm, USpringArmComponent::SocketName);	// Attach the camera

	// Create camera component 
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera0"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);	// Attach the camera
	Camera->bUsePawnControlRotation = false; // Don't rotate camera with controller

	ForwardSpeed = 2000.0f;
	StrafeSpeed = 1000.0f;
	PitchSpeed = 100.f;
	YawSpeed = 100.f;
	RotateSpeed = 1500.f;

}

// Called when the game starts or when spawned
void AFlyingPawn::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AFlyingPawn::Tick(float DeltaTime)
{
	const FVector LocalMove = FVector(ForwardSpeed * DeltaTime, 0.f, 0.f);

	// Move plane forwards (with sweep so we stop when we collide with things)
	AddActorLocalOffset(LocalMove, true);

	// Call any parent class Tick implementation
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AFlyingPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	// Check if PlayerInputComponent is valid (not NULL)
	check(PlayerInputComponent);

	// Bind our control axis' to callback functions
	// PlayerInputComponent->BindAxis("Thrust", this, &AFlyingPawn::ThrustInput);
	PlayerInputComponent->BindAxis("MoveUp", this, &AFlyingPawn::MoveUp);
	PlayerInputComponent->BindAxis("MoveRight", this, &AFlyingPawn::MoveRight);
}

void AFlyingPawn::MoveUp(float Val) {
	const FVector LocalMove = FVector(0.f, 0.f, Val * StrafeSpeed * GetWorld()->GetDeltaSeconds());
	const FRotator LocalRot = FRotator(Val * PitchSpeed * GetWorld()->GetDeltaSeconds(), 0.f, 0.f);

	// Move plane forwards (with sweep so we stop when we collide with things)
	AddActorLocalOffset(LocalMove, true);
	AddActorLocalRotation(LocalRot, true);
}

void AFlyingPawn::MoveRight(float Val) {
	bool bHasInput = !FMath::IsNearlyEqual(Val, 0.f);

	FRotator current = PlaneMesh->RelativeRotation;

	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Roll %F"), current.Roll));


	if (bHasInput) {
		const FVector LocalMove = FVector(0.f, Val * StrafeSpeed * GetWorld()->GetDeltaSeconds(), 0.f);
		const FRotator LocalRot = FRotator(0.f, Val * YawSpeed * GetWorld()->GetDeltaSeconds(), 0.f);


		// Move plane forwards (with sweep so we stop when we collide with things)
		AddActorLocalRotation(LocalRot, true);
		AddActorLocalOffset(LocalMove, true);

		if (current.Roll <= -60 || current.Roll >= 60) {
			return;
		}

		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, TEXT("ROTATE MESH"));


		RotateMesh(Val);
	}
	else {
		if (current.Roll >= -1.0f && current.Roll <= 1.0f) {
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("DONT ROTATE"));
			return;
		}

		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("ROTATE"));

		float Reverse = current.Roll < 0 ? 1.0f : -1.0f;

		RotateMesh(Reverse);
	}

}

void AFlyingPawn::RotateMesh(float Val) {
	FRotator rot = FRotator(0.f, 0.f, Val * (RotateSpeed / 1000));
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Rotate Mesh Value %F"), Val * (RotateSpeed / 1000)));


	PlaneMesh->AddLocalRotation(rot, true);

	//AddActorLocalRotation(rot, true);
}