// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UObject/ObjectMacros.h" // Avoided including CoreMinimal.h (only included what I need).
#include "GameFramework/Actor.h"
#include "Pipe.generated.h"

// An obstacle into which the player crashes, ending the game. 
// I chose not to derive from AStaticMesh for this AActor, because the mesh is only part of the pipe,
//		and I don't want the actor to be used as an AStaticMesh.
UCLASS()
class FLAPPYBIRD_API APipe : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APipe();

public:	

	// Returns mesh
	inline UStaticMeshComponent* GetMesh() const { return Mesh; }
	
private:

	// The main mesh associated with this actor
	UPROPERTY(Category = "Pipe|Appearance", VisibleAnywhere, BlueprintReadOnly, meta = ( AllowPrivateAccess = "True" ))
	UStaticMeshComponent* Mesh;
};
