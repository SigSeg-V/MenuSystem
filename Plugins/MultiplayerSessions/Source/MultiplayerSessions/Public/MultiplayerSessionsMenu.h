// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
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
	void MenuSetup();

private:

	UPROPERTY(meta = (BindWidget))
	UButton* HostButton;

	UPROPERTY(meta = (BindWidget))
	UButton* JoinButton;

	UFUNCTION()
	void HostButtonClicked();

	UFUNCTION()
	void JoinButtonClicked();

	virtual bool Initialize() override;

	UMultiplayerSessionsSubsystem* MultiplayerSessionsSubsystem;
};
