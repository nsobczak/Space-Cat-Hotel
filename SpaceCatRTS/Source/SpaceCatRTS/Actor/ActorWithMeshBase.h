#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ActorWithMeshBase.generated.h"

UCLASS()
class SPACECATRTS_API AActorWithMeshBase : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AActorWithMeshBase();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintPure, Category = "ActorMesh")
		FORCEINLINE class UStaticMeshComponent* GetBaseMesh() { return BaseMesh; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** Static mesh to represent the wall in the level*/
	UPROPERTY(VisibleAnywhere, Category = "ActorMesh")
		class UStaticMeshComponent* BaseMesh;
};
