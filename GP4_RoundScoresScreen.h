// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GP4_RoundScoresScreen.generated.h"

UENUM(BlueprintType)
enum class ECountingState : uint8
{
	ECountingState_TallyUp UMETA(DisplayName = "TallyUp"),
	ECountingState_MvpBonus UMETA(DisplayName = "MvpBonus"),
	ECountingState_MvpDeduction UMETA(DisplayName = "MvpDeduction"),
	ECountingState_NoCounting UMETA(DisplayName = "NoCounting"),
	ECountingState_Max UMETA(DisplayName = "Max"),
};

class UGP4_StatTrackingSubsystem;
UCLASS()
class FG21FT_GP4_TEAM05_API UGP4_RoundScoresScreen : public UUserWidget
{
	GENERATED_BODY()

public:
	
	UPROPERTY()
	UGP4_StatTrackingSubsystem* StatTrackingSystem;

	virtual void NativeConstruct() override;

	
	
};
