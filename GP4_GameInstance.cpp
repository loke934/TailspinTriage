#include "FG21FT_GP4_Team05\Public\GP4_GameInstance.h"


UGP4_GameInstance* UGP4_GameInstance::Get(UObject* WorldContext)
{
	UWorld* World = WorldContext->GetWorld();
	return World->GetGameInstance<UGP4_GameInstance>();
}

void UGP4_GameInstance::AddPlayer(APawn* Player)
{
	PlayerList.Add(Player);
}
