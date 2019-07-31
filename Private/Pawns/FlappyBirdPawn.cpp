// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/Pawns/FlappyBirdPawn.h"
#include "Camera/CameraComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AFlappyBirdPawn::AFlappyBirdPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create the collider subobject
	Collider = CreateDefaultSubobject<USphereComponent>(TEXT("Collider"));
	RootComponent = GetCollider(); // Make the collider the root component
	GetCollider()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics); // Let the collider handle both overlaps and hits.
#if WITH_EDITOR // If we're using the editor, 
	GetCollider()->bHiddenInGame = false; // Unhide the collider, for testing
#endif
	GetCollider()->SetSimulatePhysics(true);
	GetCollider()->SetNotifyRigidBodyCollision(true); // Ensure the mesh generates hit events
	GetCollider()->SetComponentTickEnabled(false); // Disable component ticking: we'll use actor ticking instead

	// Set up the collider's events															   
	// Bind the OnColliderHit function to the collider's OnComponentHit event
	GetCollider()->OnComponentHit.AddDynamic(this, &AFlappyBirdPawn::OnColliderHit); 
	
	// Create the mesh subobject
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	GetMesh()->SetupAttachment(GetRootComponent()); // Attach the mesh to root (the collider)
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision); // The collider handles collision, not the mesh.
	GetMesh()->SetComponentTickEnabled(false); // Disable component ticking: we'll use actor ticking instead

	// Create the camera
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera")); 
	// Attach the camera to nothing, because we want the camera to be static
	GetCamera()->SetMobility(EComponentMobility::Static); // The camera will be unable to move.
	GetCamera()->SetComponentTickEnabled(false); // Disable component ticking: we'll use actor ticking instead

	// General defaults
	JumpHeight = 20.0f;
}

// Called every frame
void AFlappyBirdPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// #TODO: Reduce velocity
	static FVector const FallingVelocity = FVector::UpVector * -1; // Store (only once) a downward velocity
	AddActorLocalOffset(FallingVelocity); // Push the character constantly downwards

}

// Called to bind functionality to input
void AFlappyBirdPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Bind the jump event to the jump button
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AFlappyBirdPawn::Jump);

}

void AFlappyBirdPawn::Jump()
{
	// Stop simulating physics, so we can add our own velocity
	GetCollider()->SetSimulatePhysics(false);
	// Add upward velocity to the player
	FVector const JumpVelocity = FVector::UpVector * JumpHeight;
	AddActorLocalOffset(JumpVelocity, true);
	// Recommence simulating physics, so this pawn starts to fall again
	GetCollider()->SetSimulatePhysics(true);

	// #TODO: The character should rot lerp from beak-rightward to beak-downward

}

void AFlappyBirdPawn::OnColliderHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// #TODO: Check tags then die

	// Reset the level
	FName const CurrentLevelName = *UGameplayStatics::GetCurrentLevelName(this);
	UGameplayStatics::OpenLevel(this, CurrentLevelName);
}

void AFlappyBirdPawn::FellOutOfWorld(const UDamageType & dmgType)
{
	// Reset the level
	FName const CurrentLevelName = *UGameplayStatics::GetCurrentLevelName(this);
	UGameplayStatics::OpenLevel(this, CurrentLevelName);
}
