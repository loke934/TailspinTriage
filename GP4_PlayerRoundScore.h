// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GP4_RoundScoresScreen.h"
#include "Components/TextBlock.h"
#include "GP4_PlayerRoundScore.generated.h"

class UGP4_GameInstance;
UCLASS()
class FG21FT_GP4_TEAM05_API UGP4_PlayerRoundScore : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	UGP4_GameInstance* GameInstance = nullptr;
	
	UPROPERTY()
	UGP4_StatTrackingSubsystem* StatTrackingSystem = nullptr;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	ECountingState CurrentState = ECountingState::ECountingState_NoCounting;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Count Up")
	int CountUpNumber = 100;
	
	UPROPERTY(VisibleAnywhere)
	int OwningPlayerId = -1;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	int CountScore = 0;

	UPROPERTY()
	int NumberOfRounds = 0;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	bool bTallyUpFinished;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	bool bMvpBonusFinished;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	bool bDeductionFinished;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UTextBlock* TallyUpText = nullptr;
	
	virtual void NativeConstruct() override;
	
	UFUNCTION(BlueprintCallable)
	void DoState();
	
	UFUNCTION(BlueprintCallable)
	void TallyUpScore();

	UFUNCTION(BlueprintCallable)
	void MvpBonusCounting();
	
	UFUNCTION(BlueprintCallable)
	void SetCountScore(int Score);

	UFUNCTION(BlueprintCallable)
	void SetUpHelperVariables(const int Id, const int Rounds);

	UFUNCTION(BlueprintCallable)
	void DeductionCounting();
	
};

class MyClassA
{
	
};

class MyClassB
{
	MyClassA MyClassARef;
};

