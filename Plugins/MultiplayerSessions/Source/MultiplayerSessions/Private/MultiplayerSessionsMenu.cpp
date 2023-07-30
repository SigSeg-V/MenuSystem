// Fill out your copyright notice in the Description page of Project Settings.


#include "MultiplayerSessionsMenu.h"

#include "MultiplayerSessionsSubsystem.h"
#include "OnlineSubsystem.h"
#include "Components/Button.h"

void UMultiplayerSessionsMenu::ShowMenu(int32 NumPublicConnections, FString TypeOfMatch)
{
	AddToViewport();
	SetVisibility(ESlateVisibility::Visible);
	SetIsFocusable(true);

	NumConnections = NumPublicConnections;
	MatchType = TypeOfMatch;
	
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

	// binding the MPS delegate
	if (MultiplayerSessionsSubsystem)
	{
		MultiplayerSessionsSubsystem->MPSCreateSessionComplete.AddDynamic(this, &ThisClass::OnMpsCreateSession);
		MultiplayerSessionsSubsystem->MPSStartSessionComplete.AddDynamic(this, &ThisClass::OnMpsStartSession);
		MultiplayerSessionsSubsystem->MPSDestroySessionComplete.AddDynamic(this, &ThisClass::OnMpsDestroySession);
		MultiplayerSessionsSubsystem->MPSCreateSessionComplete.AddDynamic(this, &ThisClass::OnMpsCreateSession);
		MultiplayerSessionsSubsystem->MPSFindSessionsComplete.AddUObject(this, &ThisClass::OnMpsFindSessions);
		MultiplayerSessionsSubsystem->MPSJoinSessionComplete.AddUObject(this, &ThisClass::OnMpsJoinSession);
	}
}

void UMultiplayerSessionsMenu::OnMpsCreateSession(bool bWasSuccessful)
{
	if (bWasSuccessful)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Green, "Session successfully created!");
		}
	}
	else
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, "Session was not created!");
		}
	}
	
	if (UWorld* World = GetWorld())
	{
		World->ServerTravel("/Game/ThirdPerson/Maps/LobbyMap?listen");
	}
}

void UMultiplayerSessionsMenu::OnMpsFindSessions(const TArray<FOnlineSessionSearchResult>& SearchResults,
	bool bWasSuccessful)
{
	if (!bWasSuccessful)
	{
		return;
	}

	// find first of same match type and connect
	for (auto& Result : SearchResults)
	{
		FString FoundMatchType;
		Result.Session.SessionSettings.Get("match_type", FoundMatchType);

		if (MatchType == FoundMatchType)
		{
			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Green, "Found session!");
			}
			MultiplayerSessionsSubsystem->JoinSession(Result);
			break;
		}
	}
}

void UMultiplayerSessionsMenu::OnMpsJoinSession(EOnJoinSessionCompleteResult::Type Result)
{
	const IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get();
	if (Subsystem)
	{
		if (IOnlineSessionPtr SessionInterface = Subsystem->GetSessionInterface())
		{
			FString Addr;
			SessionInterface->GetResolvedConnectString(NAME_GameSession, Addr);

			auto Player = GetGameInstance()->GetFirstLocalPlayerController();
			if (Player)
			{
				Player->ClientTravel(Addr, TRAVEL_Absolute);
			}
		}
	}
}

void UMultiplayerSessionsMenu::OnMpsStartSession(bool bWasSuccessful)
{
}

void UMultiplayerSessionsMenu::OnMpsDestroySession(bool bWasSuccessful)
{
}

void UMultiplayerSessionsMenu::HideMenu()
{
	RemoveFromParent();
	if (UWorld* World = GetWorld())
	{
		if (auto Player = World->GetFirstPlayerController())
		{
			FInputModeGameOnly InputModeGameOnly;
			Player->SetInputMode(InputModeGameOnly);
			Player->SetShowMouseCursor(false);
		}
	}
}

void UMultiplayerSessionsMenu::HostButtonClicked()
{
	if (MultiplayerSessionsSubsystem != nullptr)
	{
		MultiplayerSessionsSubsystem->CreateSession(NumConnections, MatchType);
	}
}

void UMultiplayerSessionsMenu::JoinButtonClicked()
{
	if (MultiplayerSessionsSubsystem)
	{
		MultiplayerSessionsSubsystem->FindSession(10000);
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

void UMultiplayerSessionsMenu::NativeDestruct()
{
	Super::NativeDestruct();

	HideMenu();
}
