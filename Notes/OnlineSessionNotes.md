# Notes for Unreal Engine Online Sessions

This repo is using [Steam](https://docs.unrealengine.com/5.2/en-US/online-subsystem-steam-interface-in-unreal-engine/) for it's online subsystem.
to set up online sessions all you need to do is:
1. Add the following to your /Games/Config/DefaultEngine.ini:
```config

[/Script/Engine.GameEngine]
+NetDriverDefinitions=(DefName="GameNetDriver",DriverClassName="OnlineSubsystemSteam.SteamNetDriver",DriverClassNameFallback="OnlineSubsystemUtils.IpNetDriver")

[OnlineSubsystem]
DefaultPlatformService=Steam

[OnlineSubsystemSteam]
bEnabled=true
SteamDevAppId=480

; If using Sessions
bInitServerOnClient=true

[/Script/OnlineSubsystemSteam.SteamNetDriver]
NetConnectionClassName="OnlineSubsystemSteam.SteamNetConnection"
```
Note that the Sessions block is commented out in the online docs, 
this NEEDS to be uncommented or the game will crash when you try 
to create a session. 
When the game is ready for sale you need to change `SteamDevAppId` to the one
provided by Valve when they approve for sale.

2. Recompile the game with these settings and add the online subsystem
class.
```c++
	// Accessing the online subsystem
	if (const IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get())
	{
		// accessing session
		OnlineSessionInterface = OnlineSubsystem->GetSessionInterface();

		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(
				-1,
				15.f,
				FColor::Emerald,
				FString::Printf(TEXT("In online subsystem %ls!"), *OnlineSubsystem->GetSubsystemName().ToString()));
		}
	}
```

OnlineSessionInterface here is a pointer to the online session [IOnlineSessionPtr](https://docs.unrealengine.com/5.0/en-US/API/Plugins/OnlineSubsystem/Interfaces/IOnlineSessionPtr/).

You can set up a session using a delegate. FOnlineSessionSettings provides settings for the created session.
