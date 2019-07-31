// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/Hazards/Pipe.h"

// Sets default values
APipe::APipe()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Initialise the pipe mesh.
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = GetMesh();
	GetMesh()->bCastDynamicShadow = false;
}

