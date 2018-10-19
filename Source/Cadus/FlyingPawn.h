// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "FlyingPawn.generated.h"

UCLASS()
class CADUS_API AFlyingPawn : public APawn
{
	GENERATED_BODY()


public:
	// Sets default values for this pawn's properties
	AFlyingPawn();

	/** StaticMesh component that will be the visuals for our flying pawn */
	UPROPERTY(Category = Mesh, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* PlaneMesh;

	UPROPERTY(Category = Mesh, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* RootMesh;


	/** Spring arm that will offset the camera */
	UPROPERTY(Category = Camera, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* SpringArm;

	/** Camera component that will be our viewpoint */
	UPROPERTY(Category = Camera, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* Camera;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/** Bound to the vertical axis */
	void MoveUp(float Val);

	/** Bound to the horizontal axis */
	void MoveRight(float Val);

private:
	/** Current forward speed */
	float ForwardSpeed;

	/** Current forward speed */
	float StrafeRightSpeed;

	float StrafeUpSpeed;

	float YawSpeed;

	float PitchSpeed;

	float RotateSpeed;

	bool bIsRotating;

	/* Rotate mesh without rotating root */
	void RotateMesh(float Val);

	
	
};
