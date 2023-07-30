// Fill out your copyright notice in the Description page of Project Settings.


#include "MultiplayerSessionLobbyGamemode.h"

#include "GameFramework/GameStateBase.h"
#include "GameFramework/PlayerState.h"

void AMultiplayerSessionLobbyGamemode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	if (GameState)
	{
		int32 NumberOfPlayers = GameState.Get()->PlayerArray.Num();

		if (GEngine)
		{
				GEngine->AddOnScreenDebugMessage(1, 60.f, FColor::Orange, FString::Printf(TEXT("Number of players: %d"), NumberOfPlayers));

			if (auto PlayerState = NewPlayer->GetPlayerState<APlayerState>())
			{
				GEngine->AddOnScreenDebugMessage(1, 60.f, FColor::Orange, FString::Printf(TEXT("%ls has joined the game"), *PlayerState->GetPlayerName()));
			}
			
		}
	}
}

void AMultiplayerSessionLobbyGamemode::Logout(AController* Exiting)
{
	Super::Logout(Exiting);
	if (GameState)
	{
		int32 NumberOfPlayers = GameState.Get()->PlayerArray.Num();
					   
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(1, 60.f, FColor::Orange, FString::Printf(TEXT("Number of players: %d"), NumberOfPlayers - 1));
		   
			if (auto PlayerState = Exiting->GetPlayerState<APlayerState>())
			{
				GEngine->AddOnScreenDebugMessage(1, 60.f, FColor::Orange, FString::Printf(TEXT("%s has left the game"), *PlayerState->GetPlayerName()));
			}
								
		}
	}
}
