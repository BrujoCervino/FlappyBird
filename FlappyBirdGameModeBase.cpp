// Fill out your copyright notice in the Description page of Project Settings.

#include "FlappyBirdGameModeBase.h"
#include "UObject/ConstructorHelpers.h"

AFlappyBirdGameModeBase::AFlappyBirdGameModeBase()
{
	// Only once, find and store the FlappyBirdCharacter Blueprint archetype (the uninstantiated Blueprint class)
	static const TSubclassOf<APawn> PlayerPawnClass = 
		ConstructorHelpers::FClassFinder<APawn>(TEXT("/Game/Characters/BP_FlappyBirdCharacter")).Class;

	// If the PlayerPawnClass is valid,
	if( NULL != PlayerPawnClass )
	{
		// Set the default pawn class as the player pawn class
		DefaultPawnClass = PlayerPawnClass;
	}
}
