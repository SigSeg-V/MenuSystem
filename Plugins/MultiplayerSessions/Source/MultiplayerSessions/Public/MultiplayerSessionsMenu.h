// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "MultiplayerSessionsMenu.generated.h"

class UMultiplayerSessionsSubsystem;
class UButton;
/**
 * 
 */
UCLASS()
class MULTIPLAYERSESSIONS_API UMultiplayerSessionsMenu : public UUserWidget
{
	GENERATED_BODY()

public:
	
	/**
	 * @brief Sets up the usual defaults for a menu, free cursor, input removed from actor etc.
	 */
	UFUNCTION(BlueprintCallable)
	void ShowMenu(int32 NumPublicConnections = 6, FString TypeOfMatch = "ffa");

protected:

	// Callbacks for the MPS delegates
	
	UFUNCTION()
	void OnMpsCreateSession(bool bWasSuccessful);
	
	void OnMpsFindSessions(const TArray<FOnlineSessionSearchResult>& SearchResults, bool bWasSuccessful);
	
	void OnMpsJoinSession(EOnJoinSessionCompleteResult::Type Result);

	UFUNCTION()
	void OnMpsStartSession(bool bWasSuccessful);

	UFUNCTION()
	void OnMpsDestroySession(bool bWasSuccessful);
private:

	UPROPERTY(meta = (BindWidget))
	UButton* HostButton;

	UPROPERTY(meta = (BindWidget))
	UButton* JoinButton;

	UFUNCTION()
	void HostButtonClicked();

	UFUNCTION()
	void JoinButtonClicked();

	void HideMenu();

	virtual bool Initialize() override;
	virtual void NativeDestruct() override;

	UPROPERTY()
	UMultiplayerSessionsSubsystem* MultiplayerSessionsSubsystem;

	int32 NumConnections{6};
	FString MatchType{"ffa"};
};
