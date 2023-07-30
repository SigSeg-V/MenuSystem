// Fill out your copyright notice in the Description page of Project Settings.


#include "MultiplayerSessionsMenu.h"

#include "MultiplayerSessionsSubsystem.h"
#include "Components/Button.h"

void UMultiplayerSessionsMenu::MenuSetup()
{
	AddToViewport();
	SetVisibility(ESlateVisibility::Visible);
	SetIsFocusable(true);

	UWorld* World = GetWorld();
	if (World != nullptr)
	{
		auto Player = World->GetFirstPlayerController();
		if (Player)
		{
			// switching input to UI only
			FInputModeUIOnly InputModeData;
			InputModeData.SetWidgetToFocus(TakeWidget());
			InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
			Player->SetInputMode(InputModeData);

			Player->SetShowMouseCursor(true);
		}
	}
	// access the subsystem by the game instance
	const UGameInstance* GameInstance = GetGameInstance();
	if (GameInstance != nullptr)
	{
		MultiplayerSessionsSubsystem = GameInstance->GetSubsystem<UMultiplayerSessionsSubsystem>();
	}
}

void UMultiplayerSessionsMenu::HostButtonClicked()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(
			-1,
			15.f,
			FColor::Green,
			FString::Printf(TEXT("Clicked host button")));
	}

	if (MultiplayerSessionsSubsystem != nullptr)
	{
		MultiplayerSessionsSubsystem->CreateSession(6, "ffa");
	}
}

void UMultiplayerSessionsMenu::JoinButtonClicked()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(
			-1,
			15.f,
			FColor::Blue,
			FString::Printf(TEXT("Clicked join button")));
	}
}

bool UMultiplayerSessionsMenu::Initialize()
{
	if (!Super::Initialize())
	{
		return false;
	}

	// add callback methods to the buttons
	if (HostButton != nullptr)
	{
		HostButton->OnClicked.AddDynamic(this, &ThisClass::HostButtonClicked);
	}
	
	if (JoinButton != nullptr)
	{
		JoinButton->OnClicked.AddDynamic(this, &ThisClass::JoinButtonClicked);
	}
	
	return true;
}
