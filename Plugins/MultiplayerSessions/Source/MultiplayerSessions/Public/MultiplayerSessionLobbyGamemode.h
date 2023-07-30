// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "MultiplayerSessionLobbyGamemode.generated.h"

/**
 * 
 */
UCLASS()
class MULTIPLAYERSESSIONS_API AMultiplayerSessionLobbyGamemode : public AGameMode
{
	GENERATED_BODY()

public:
	// overriding login and logout
	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void Logout(AController* Exiting) override;
};
