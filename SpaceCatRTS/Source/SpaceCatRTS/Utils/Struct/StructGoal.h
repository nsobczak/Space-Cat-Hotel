#pragma once

#include "CoreMinimal.h"
#include "Utils/Struct/StructClientNeed.h"
#include "StructGoal.generated.h"

UENUM(BlueprintType)
enum class EGoalCompletion : uint8
{
	FGC_HIDDEN UMETA(DisplayName = "Hidden"),
	FGC_ACTIVE UMETA(DisplayName = "Active"),
	FGC_MISSED UMETA(DisplayName = "Missed"),
	FGC_COMPLETED UMETA(DisplayName = "Completed")
};

UENUM(BlueprintType)
enum class EAnimalBreed : uint8
{
	FAB_BEAR UMETA(DisplayName = "Flying bear"),
	FAB_COW UMETA(DisplayName = "Nuclear cow")
};

/**
 *
 */
USTRUCT(BlueprintType)
struct FStructGoal
{
	GENERATED_USTRUCT_BODY()

public:
	FStructGoal() : GoalCompletion(EGoalCompletion::FGC_HIDDEN) {}
	FStructGoal(float newTime, EAnimalBreed newBreed, float newGoalTimeToComplete, FStructClientNeed newClientNeed) :
		GoalCompletion(EGoalCompletion::FGC_HIDDEN), TimeLeftWhenGoalAppears(newTime),
		Breed(newBreed), GoalTimeToComplete(newGoalTimeToComplete)
	{
		ClientNeeds.Add(newClientNeed);
	}
	FStructGoal(float newTime, EAnimalBreed newBreed, float newGoalTimeToComplete, TArray<FStructClientNeed> newClientNeeds) :
		GoalCompletion(EGoalCompletion::FGC_HIDDEN), TimeLeftWhenGoalAppears(newTime),
		Breed(newBreed), GoalTimeToComplete(newGoalTimeToComplete), ClientNeeds(newClientNeeds)
	{
	}

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Goal")
		EGoalCompletion GoalCompletion = EGoalCompletion::FGC_HIDDEN;

	FORCEINLINE bool IsHidden() { return GoalCompletion == EGoalCompletion::FGC_HIDDEN; }
	FORCEINLINE bool IsActive() { return GoalCompletion == EGoalCompletion::FGC_ACTIVE; }
	FORCEINLINE bool IsMissed() { return GoalCompletion == EGoalCompletion::FGC_MISSED; }
	FORCEINLINE bool IsCompleted() { return GoalCompletion == EGoalCompletion::FGC_COMPLETED; }
	void SetActive() { GoalCompletion = EGoalCompletion::FGC_ACTIVE; }
	void SetMissed() { GoalCompletion = EGoalCompletion::FGC_MISSED; }
	void SetCompleted() { GoalCompletion = EGoalCompletion::FGC_COMPLETED; }

	/**In seconds*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Goal")
		float TimeLeftWhenGoalAppears = 300.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Goal")
		EAnimalBreed Breed;

	/**In seconds*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Goal")
		float GoalTimeToComplete = 60.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Goal")
		TArray<FStructClientNeed> ClientNeeds;
};