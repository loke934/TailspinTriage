#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GP4_GameInstance.generated.h"

UCLASS()
class FG21FT_GP4_TEAM05_API UGP4_GameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintPure, Category = "Game|Game Instance", Meta = (DisplayName = "GetGameInstance", WorldContext = "WorldContext"))
	static UGP4_GameInstance* Get(UObject* WorldContext);

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	int CurrentRound = 0;
	
	UPROPERTY(BlueprintReadOnly)
	TArray<APawn*> PlayerList;

	UFUNCTION(BlueprintCallable)
	void AddPlayer(APawn* Player);
	
	
};


