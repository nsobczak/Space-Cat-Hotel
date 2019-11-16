#pragma once

#include "CoreMinimal.h"
#include "StructLevelInfo.generated.h"


/**
 *
 */
USTRUCT(BlueprintType)
struct FStructLevelInfo
{
	GENERATED_USTRUCT_BODY()

public:
	FStructLevelInfo();
	FStructLevelInfo(float newXMin, float newXMax, float newYMin, float newYMax);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Level limit")
		float xMin = -1800.f ;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Level limit")
		float xMax = 1200.f ;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Level limit")
		float yMin = -1500.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Level limit")
		float yMax = 1500.f;

	/**In seconds*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Level timer")
		float LevelTimeLimit = 600.f;
};
