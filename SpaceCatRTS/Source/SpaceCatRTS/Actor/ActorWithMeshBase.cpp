#include "ActorWithMeshBase.h"
//#include "Components/StaticMeshComponent.h"

// Sets default values
AActorWithMeshBase::AActorWithMeshBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//create the static mesh component
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	RootComponent = (USceneComponent*)BaseMesh;
}

// Called when the game starts or when spawned
void AActorWithMeshBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AActorWithMeshBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

