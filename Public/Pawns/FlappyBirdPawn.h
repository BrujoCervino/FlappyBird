// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UObject/ObjectMacros.h" // Avoided including CoreMinimal.h (only included what I need).
#include "GameFramework/Pawn.h"
#include "FlappyBirdPawn.generated.h"

class UCameraComponent;
class USphereComponent;

// The main pawn used by the player
UCLASS()
class FLAPPYBIRD_API AFlappyBirdPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AFlappyBirdPawn();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Returns Mesh
	inline UStaticMeshComponent* GetMesh() const { return Mesh; }

	// Returns Collider 
	inline USphereComponent* GetCollider() const { return Collider; }

	// Returns Camera
	inline UCameraComponent* GetCamera() const { return Camera; }

protected:

	// Propels the pawn into the air, on button press.
	virtual void Jump();
	
	// Called when the collider hits another actor. Use this for handling damage/death.
	UFUNCTION()
	virtual void OnColliderHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, 
		FVector NormalImpulse, const FHitResult & Hit);

	// Called when this pawn falls past the kill height, or into a KillZVolume
	virtual void FellOutOfWorld(const class UDamageType& dmgType) override;

	// How high the bird will jump 
	UPROPERTY(Category="FlappyBirdPawn|Gameplay", BlueprintReadOnly, EditAnywhere, meta = ( BlueprintProtected="True" ))
	float JumpHeight;

private:

	// The main mesh associated with this pawn
	UPROPERTY(Category = "FlappyBirdPawn|Appearance", BlueprintReadOnly, VisibleAnywhere, meta = ( AllowPrivateAccess = "True" ))
	UStaticMeshComponent* Mesh;
	
	// The sphere used to collide and overlap with other actors
	UPROPERTY(Category = "FlappyBirdPawn|Collision", BlueprintReadOnly, VisibleAnywhere, meta = ( AllowPrivateAccess = "True" ))
	USphereComponent* Collider;

	// The main camera associated with this pawn: used to view the game
	UPROPERTY(Category = "FlappyBirdPawn|Utility", BlueprintReadOnly, EditAnywhere, meta = ( AllowPrivateAccess = "True" ))
	UCameraComponent* Camera;	

};
