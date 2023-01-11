// Fill out your copyright notice in the Description page of Project Settings.


#include "GP4_PlayerRoundScore.h"
#include "GP4_GameInstance.h"
#include "GP4_StatTrackingSubsystem.h"
#include "Kismet/GameplayStatics.h"

void UGP4_PlayerRoundScore::NativeConstruct()
{
	Super::NativeConstruct();
	UGameInstance* GI = UGameplayStatics::GetGameInstance(GetWorld());
	GameInstance = Cast<UGP4_GameInstance>(GI);
	StatTrackingSystem = GameInstance->GetSubsystem<UGP4_StatTrackingSubsystem>(GameInstance);
	CurrentState = ECountingState::ECountingState_NoCounting;
}

void UGP4_PlayerRoundScore::DoState()
{
	switch (CurrentState)
	{
	case ECountingState::ECountingState_NoCounting:
		return;
	case ECountingState::ECountingState_TallyUp:
		TallyUpScore();
		break;
	case ECountingState::ECountingState_MvpBonus:
		MvpBonusCounting();
		break;
	case ECountingState::ECountingState_MvpDeduction:
		DeductionCounting();
		break;
	default:
		break;
	}
}

void UGP4_PlayerRoundScore::TallyUpScore()
{
	int RoundScore = StatTrackingSystem->GetPlayerData(OwningPlayerId).RoundsScore[GameInstance->CurrentRound-1];
	if (RoundScore <= 0)
	{
		bTallyUpFinished = true;
		FString String = FString::FromInt(StatTrackingSystem->GetPlayerData(OwningPlayerId).TotalScore);
		FText Text = FText::FromString(String);
		TallyUpText->SetText(Text);
		return;
	}

	if (CountScore < StatTrackingSystem->GetPlayerData(OwningPlayerId).TotalScore)
	{
		FString String = FString::FromInt(CountScore += CountUpNumber);
		FText Text = FText::FromString(String);
		TallyUpText->SetText(Text);
		return;
	}

	bTallyUpFinished = true;
}

void UGP4_PlayerRoundScore::MvpBonusCounting()
{
	if (CountScore < StatTrackingSystem->GetPlayerData(OwningPlayerId).TotalScore)
	{
		FString String = FString::FromInt(CountScore += CountUpNumber);
		FText Text = FText::FromString(String);
		TallyUpText->SetText(Text);
		return;
	}
	bMvpBonusFinished = true;
}

void UGP4_PlayerRoundScore::SetCountScore(int Score)
{
	CountScore = Score;
}

void UGP4_PlayerRoundScore::SetUpHelperVariables(const int Id, const int Rounds)
{
	OwningPlayerId = Id;
	NumberOfRounds = Rounds;
}

void UGP4_PlayerRoundScore::DeductionCounting()
{
	if (CountScore > StatTrackingSystem->GetPlayerData(OwningPlayerId).TotalScore)
	{
		FString String = FString::FromInt(CountScore -= CountUpNumber);
		FText Text = FText::FromString(String);
		TallyUpText->SetText(Text);
		return;
	}
	bDeductionFinished = true;
}
