// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Avoided including CoreMinimal.h or any of its contained headers (only included what I need).
#include "GameFramework/GameModeBase.h"
#include "FlappyBirdGameModeBase.generated.h"

// The default game mode base for Flappy Bird Game
UCLASS()
class FLAPPYBIRD_API AFlappyBirdGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	// Default constructor
	AFlappyBirdGameModeBase();
	
};
