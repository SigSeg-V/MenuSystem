// Fill out your copyright notice in the Description page of Project Settings.


#include "MultiplayerSessionsMenu.h"

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
}
