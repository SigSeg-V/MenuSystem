// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "OnlineSessionSettings.h"
#include "MultiplayerSessionsSubsystem.generated.h"

/**
 * Handles all online session functionality including creating, joining, searching and destroying sessions.
 * This class is inherited from UGameInstanceSubsystem as such persists as long as the game is open.
 */
UCLASS()
class MULTIPLAYERSESSIONS_API UMultiplayerSessionsSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UMultiplayerSessionsSubsystem();

	/**
	 * @brief Creates a session as listener server with the following settings
	 * @param NumberPublicConnections Number of connections the server is
	 *                                expecting for the session
	 * @param MatchType The game mode for the session
	 */
	void CreateSession(int32 NumberPublicConnections, FString MatchType);

	/**
	 * @brief Search for a game session
	 * @param MaxSearchResults Maximum number of results to retrieve
	 */
	void FindSession(int32 MaxSearchResults);
	/**
	 * @brief Connect to the session provided by SessionSearchResult
	 * @param SessionSearchResult Session result to connect to
	 */
	void JoinSession(const FOnlineSessionSearchResult& SessionSearchResult);

	/**
	 * @brief Start the session configured by CreateSession()
	 */
	void StartSession();

	/**
	 * @brief Destroy the current session
	 */
	void DestroySession();
	
protected:

	// Callbacks bound to the online session interface
	void OnCreateSessionComplete(FName SessionName, bool bWasSuccessful);
	void OnFindSessionsComplete(bool bWasSuccessful);
	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);
	void OnStartSessionComplete(FName SessionName, bool bWasSuccessful);
	void OnDestroySessionComplete(FName SessionName, bool bWasSuccessful);
	
private:
	
	IOnlineSessionPtr OnlineSessionInterface;

	// Delegates for the public methods, and are bound to the fn callbacks
	FOnCreateSessionCompleteDelegate  CreateSessionCompleteDelegate;
	FOnFindSessionsCompleteDelegate   FindSessionsCompleteDelegate;
	FOnJoinSessionCompleteDelegate    JoinSessionCompleteDelegate;
	FOnStartSessionCompleteDelegate   StartSessionCompleteDelegate;
	FOnDestroySessionCompleteDelegate DestroySessionCompleteDelegate;

	// Handles for the created delegates 
	FDelegateHandle  CreateSessionCompleteDelegateHandle;
	FDelegateHandle  FindSessionsCompleteDelegateHandle;
	FDelegateHandle  JoinSessionCompleteDelegateHandle;
	FDelegateHandle  StartSessionCompleteDelegateHandle;
	FDelegateHandle  DestroySessionCompleteDelegateHandle;
};
