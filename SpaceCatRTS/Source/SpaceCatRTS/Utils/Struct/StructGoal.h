#pragma once

#include "CoreMinimal.h"
#include "Utils/Struct/StructClientNeed.h"
#include "Utils/GameEnums.h"
#include "StructGoal.generated.h"

UENUM(BlueprintType)
enum class EGoalStatus : uint8
{
	FGC_HIDDEN UMETA(DisplayName = "Hidden"),
	FGC_ACTIVE UMETA(DisplayName = "Active"),
	FGC_MISSED UMETA(DisplayName = "Missed"),
	FGC_COMPLETED UMETA(DisplayName = "Completed")
};

/**
 *
 */
USTRUCT(BlueprintType)
struct FStructGoal
{
	GENERATED_USTRUCT_BODY()

public:
	FStructGoal() : GoalCompletion(EGoalStatus::FGC_HIDDEN) {}
	FStructGoal(float newTime, EAnimalBreed newBreed, float newGoalTimeToComplete, FStructClientNeed newClientNeed) :
		GoalCompletion(EGoalStatus::FGC_HIDDEN), TimeLeftWhenGoalAppears(newTime),
		Breed(newBreed), GoalTimeToComplete(newGoalTimeToComplete)
	{
		ClientNeeds.Add(newClientNeed);
	}
	FStructGoal(float newTime, EAnimalBreed newBreed, float newGoalTimeToComplete, TArray<FStructClientNeed> newClientNeeds) :
		GoalCompletion(EGoalStatus::FGC_HIDDEN), TimeLeftWhenGoalAppears(newTime),
		Breed(newBreed), GoalTimeToComplete(newGoalTimeToComplete), ClientNeeds(newClientNeeds)
	{
	}

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Goal")
		EGoalStatus GoalCompletion = EGoalStatus::FGC_HIDDEN;

	FORCEINLINE bool IsHidden() { return GoalCompletion == EGoalStatus::FGC_HIDDEN; }
	FORCEINLINE bool IsActive() { return GoalCompletion == EGoalStatus::FGC_ACTIVE; }
	FORCEINLINE bool IsMissed() { return GoalCompletion == EGoalStatus::FGC_MISSED; }
	FORCEINLINE bool IsCompleted() { return GoalCompletion == EGoalStatus::FGC_COMPLETED; }
	void SetActive() { GoalCompletion = EGoalStatus::FGC_ACTIVE; }
	void SetMissed() { GoalCompletion = EGoalStatus::FGC_MISSED; }
	void SetCompleted() { GoalCompletion = EGoalStatus::FGC_COMPLETED; }

	/**In seconds*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Goal")
		float TimeLeftWhenGoalAppears = 300.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Goal")
		EAnimalBreed Breed = EAnimalBreed::FAB_BEAR;

	/**In seconds*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Goal")
		float GoalTimeToComplete = 60.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Goal")
		TArray<FStructClientNeed> ClientNeeds;
};