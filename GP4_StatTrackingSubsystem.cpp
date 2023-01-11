#include "GP4_StatTrackingSubsystem.h"

void UGP4_StatTrackingSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UGP4_StatTrackingSubsystem::SetUpPlayersData(const int Id)
{
	if (PlayerDataList[Id].bIsAssigned)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1,3,FColor::Yellow,	FString::Printf(TEXT("This player was already added")));
		}
		return;
	}
	PlayerDataList[Id].bIsAssigned = true;
	PlayerDataList[Id].PlayerID = Id;
	PlayerDataList[Id].Name.Append(" ");
	PlayerDataList[Id].Name.Append(FString::FromInt(PlayerDataList[Id].PlayerID + 1));
	ConnectedPlayersAmount++;
}

void UGP4_StatTrackingSubsystem::SetPlayerChoice(const int PlayerId, const int CharacterChoice)
{
	if (CheckIfIndexIsOutOfBounds(PlayerId))
	{
		return;
	}
	PlayerDataList[PlayerId].CharacterChoice = CharacterChoice;
}

FPlayerData& UGP4_StatTrackingSubsystem::GetPlayerData(const int PlayerId)
{
	if (CheckIfIndexIsOutOfBounds(PlayerId))
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1,3,FColor::Yellow,	FString::Printf(TEXT("Index out of bounds.")));
		}
	}
	return PlayerDataList[PlayerId];
}

void UGP4_StatTrackingSubsystem::UpdatePlayerRoundScore(const int PlayerId,int Score)
{
	if (CheckIfIndexIsOutOfBounds(PlayerId))
	{
		return;
	}
	if (PlayerDataList[PlayerId].bIsAssigned)
	{
		PlayerDataList[PlayerId].CurrentRoundScore += Score;
	}
}

void UGP4_StatTrackingSubsystem::AddAllPlayersRoundScoreToRound()
{
	for (int i = 0; i < ConnectedPlayersAmount; ++i)
	{
		PlayerDataList[i].RoundsScore.Add(PlayerDataList[i].CurrentRoundScore);
	}
}

void UGP4_StatTrackingSubsystem::ResetAllPlayersCurrentRoundScore()
{
	for (int i = 0; i < ConnectedPlayersAmount; ++i)
	{
		PlayerDataList[i].CurrentRoundScore = 0;
	}
}

void UGP4_StatTrackingSubsystem::UpdatePlayersTotalScore()
{
	for (int i = 0; i < ConnectedPlayersAmount; ++i)
	{
		PlayerDataList[i].PreviousTotalScore = PlayerDataList[i].TotalScore;
		int TotalScore = 0;
		for (int m = 0; m < PlayerDataList[i].RoundsScore.Num(); ++m)
		{
			TotalScore += PlayerDataList[i].RoundsScore[m];
		}
		PlayerDataList[i].TotalScore = TotalScore;
	}
}

void UGP4_StatTrackingSubsystem::UpdateScoreInOtherPlayersGoal(const int PlayerId, const int GoalId)
{
	if (CheckIfIndexIsOutOfBounds(PlayerId))
	{
		return;
	}
	if (PlayerDataList[GoalId].bIsAssigned)
	{
		PlayerDataList[PlayerId].ScoredOnOtherGoal += 1;
	}
}

void UGP4_StatTrackingSubsystem::UpdateTimesBumpedOtherPlayers(const int PlayerId)
{
	if (CheckIfIndexIsOutOfBounds(PlayerId))
	{
		return;
	}
	PlayerDataList[PlayerId].TimesBumpedOtherPlayers += 1;
}

void UGP4_StatTrackingSubsystem::UpdateTimesCordBroke(const int PlayerId)
{
	if (CheckIfIndexIsOutOfBounds(PlayerId))
	{
		return;
	}
	PlayerDataList[PlayerId].TimesCordBroke += 1;
}

int UGP4_StatTrackingSubsystem::GetWinningPlayerId()
{
	int WinnerId = 0;

	for (int i = 0; i < ConnectedPlayersAmount; ++i)
	{
		if (PlayerDataList[i].TotalScore > PlayerDataList[WinnerId].TotalScore)
		{
			WinnerId = PlayerDataList[i].PlayerID;
		}
	}
	return WinnerId;
}

void UGP4_StatTrackingSubsystem::UpdatePatientsKilled(const int PlayerId)
{
	if (CheckIfIndexIsOutOfBounds(PlayerId))
	{
		return;
	}
	PlayerDataList[PlayerId].PatientsKilled += 1;
}

void UGP4_StatTrackingSubsystem::UpdateHealthyPatientsRescued(const int PlayerId)
{
	if (CheckIfIndexIsOutOfBounds(PlayerId))
	{
		return;
	}
	PlayerDataList[PlayerId].HealthyPatientsRescued += 1;
}

void UGP4_StatTrackingSubsystem::ResetStatTracking()
{
	for (int i = 0; i < Max_Player_Amount; ++i)
	{
		PlayerDataList[i].bIsAssigned = false;
		PlayerDataList[i].Name = "Player";
		PlayerDataList[i].PlayerID = -1;
		PlayerDataList[i].CharacterChoice = 0;
		PlayerDataList[i].TotalScore = 0;
		PlayerDataList[i].CurrentRoundScore = 0;
		PlayerDataList[i].RoundsScore.Empty();
		PlayerDataList[i].ScoredOnOtherGoal = 0;
		PlayerDataList[i].TimesBumpedOtherPlayers = 0;
		PlayerDataList[i].TimesCordBroke = 0;
		PlayerDataList[i].PatientsKilled = 0;
		PlayerDataList[i].HealthyPatientsRescued = 0;
		PlayerDataList[i].PreviousTotalScore = 0;
		PlayerDataList[i].PatientsStolen = 0;
		PlayerDataList[i].TimeHoldingPatients = 0;
		PlayerDataList[i].BonusMvps.Empty();
		PlayerDataList[i].DeductionMvps.Empty();
	}
	ConnectedPlayersAmount = 0;
}

void UGP4_StatTrackingSubsystem::UpdatePatientsStolen(const int PlayerId)
{
	if (CheckIfIndexIsOutOfBounds(PlayerId))
	{
		return;
	}
	
	if (PlayerDataList[PlayerId].bIsAssigned)
	{
		PlayerDataList[PlayerId].PatientsStolen++;
	}
}

void UGP4_StatTrackingSubsystem::UpdateTimeHoldingPatient(const int PlayerId, int Time)
{
	if (CheckIfIndexIsOutOfBounds(PlayerId))
	{
		return;
	}
	
	if (PlayerDataList[PlayerId].bIsAssigned)
	{
		PlayerDataList[PlayerId].TimeHoldingPatients += Time;
	}
}

void UGP4_StatTrackingSubsystem::SetMvps()
{
	int AltruistId = 0;
	int SaboteurId = 0;
	int RecklessId = 0;
	int SaintId = 0;
	int ThiefId = 0;
	int AttachmentIssuesId = 0;
	
	for (int i = 0; i < ConnectedPlayersAmount; ++i)
	{
		//Player must have higher score and not be tied
		if (PlayerDataList[i].ScoredOnOtherGoal > PlayerDataList[AltruistId].ScoredOnOtherGoal
			&& PlayerDataList[i].ScoredOnOtherGoal != PlayerDataList[AltruistId].ScoredOnOtherGoal )
		{
			AltruistId = PlayerDataList[i].PlayerID;
		}

		if (PlayerDataList[i].TimesBumpedOtherPlayers > PlayerDataList[SaboteurId].TimesBumpedOtherPlayers
			&& PlayerDataList[i].TimesBumpedOtherPlayers != PlayerDataList[SaboteurId].TimesBumpedOtherPlayers)
		{
			SaboteurId = PlayerDataList[i].PlayerID;
		}

		if (PlayerDataList[i].PatientsKilled > PlayerDataList[RecklessId].PatientsKilled
			&& PlayerDataList[i].PatientsKilled != PlayerDataList[RecklessId].PatientsKilled)
		{
			RecklessId = PlayerDataList[i].PlayerID;
		}

		if (PlayerDataList[i].HealthyPatientsRescued > PlayerDataList[SaintId].HealthyPatientsRescued
			&& PlayerDataList[i].HealthyPatientsRescued != PlayerDataList[SaintId].HealthyPatientsRescued)
		{
			SaintId = PlayerDataList[i].PlayerID;
		}

		if (PlayerDataList[i].PatientsStolen > PlayerDataList[ThiefId].PatientsStolen
			&& PlayerDataList[i].PatientsStolen != PlayerDataList[ThiefId].PatientsStolen)
		{
			ThiefId = PlayerDataList[i].PlayerID;
		}

		if (PlayerDataList[i].TimeHoldingPatients > PlayerDataList[AttachmentIssuesId].TimeHoldingPatients
			&& PlayerDataList[i].TimeHoldingPatients != PlayerDataList[AttachmentIssuesId].TimeHoldingPatients)
		{
			AttachmentIssuesId = PlayerDataList[i].PlayerID;
		}
	}

	//Player only get mvp if they have score
	
	if (PlayerDataList[AltruistId].ScoredOnOtherGoal > 0)
	{
		PlayerDataList[AltruistId].DeductionMvps.AddUnique(EMVPS::EMVPS_Altruist); 
	}

	if (PlayerDataList[SaboteurId].TimesBumpedOtherPlayers > 0)
	{
		PlayerDataList[SaboteurId].BonusMvps.AddUnique(EMVPS::EMVPS_Saboteur);
	}

	if (PlayerDataList[RecklessId].PatientsKilled > 0)
	{
		PlayerDataList[RecklessId].DeductionMvps.AddUnique(EMVPS::EMVPS_Reckless);
	}

	if (PlayerDataList[SaintId].HealthyPatientsRescued > 0)
	{
		PlayerDataList[SaintId].BonusMvps.AddUnique(EMVPS::EMVPS_Saint);
	}

	if (PlayerDataList[ThiefId].PatientsStolen > 0)
	{
		PlayerDataList[ThiefId].BonusMvps.AddUnique(EMVPS::EMVPS_Thief);
	}

	if (PlayerDataList[AttachmentIssuesId].TimeHoldingPatients > 0)
	{
		PlayerDataList[AttachmentIssuesId].BonusMvps.AddUnique(EMVPS::EMVPS_AttachmentIssues);
	}
}

int UGP4_StatTrackingSubsystem::GetMvpStat(const int PlayerId, EMVPS Mvp)
{
	switch (Mvp)
	{
	case EMVPS::EMVPS_Altruist:
		return PlayerDataList[PlayerId].ScoredOnOtherGoal;

	case EMVPS::EMVPS_Saboteur:
		return PlayerDataList[PlayerId].TimesBumpedOtherPlayers;

	case EMVPS::EMVPS_Reckless:
		return PlayerDataList[PlayerId].PatientsKilled;

	case EMVPS::EMVPS_Saint:
		return PlayerDataList[PlayerId].HealthyPatientsRescued;

	case EMVPS::EMVPS_Thief:
		return PlayerDataList[PlayerId].PatientsStolen;

	case EMVPS::EMVPS_AttachmentIssues:
		return PlayerDataList[PlayerId].TimeHoldingPatients;
		
	default:
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1,3,	FColor::Yellow,FString::Printf(TEXT("No case for enum in stat tracking subsystem.")));
		};
		return -1;
	}
}

void UGP4_StatTrackingSubsystem::UpdateTotalScoreMvps(const int PlayerId, const int Score)
{
	PlayerDataList[PlayerId].TotalScore += Score;
}

bool UGP4_StatTrackingSubsystem::CheckIfIndexIsOutOfBounds(const int Index)
{
	if (Index < 0 || Index >= Max_Player_Amount )
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1,3,FColor::Yellow,	FString::Printf(TEXT("Index out of bounds.")));
		}
		return true;
	}
	return false;
}
