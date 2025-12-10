// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_CubeSpawner.h"

#include "ObjectPoolerSubsystem.h"
#include "SAdvancedTransformInputBox.h"

// Sets default values
ACPP_CubeSpawner::ACPP_CubeSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACPP_CubeSpawner::BeginPlay()
{
	Super::BeginPlay();

	PoolSys = GetWorld()->GetGameInstance()->GetSubsystem<UObjectPoolerSubsystem>();
	PoolSys->AddPool(ActorToSpawn, PoolSize);
}

// Called every frame
void ACPP_CubeSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Timer += DeltaTime;
	if (Timer < 1 / SpawnPerSecond) return;
	
	Timer = 0.0f;
	SpawnInRandomPos();

}

void ACPP_CubeSpawner::SpawnInRandomPos()
{
	if (!ActorToSpawn || !PoolSys) return;

	FVector2D RandomPoint = FMath::RandPointInCircle(SpawnRadius);
	FVector LocalRandomOffset = FVector(RandomPoint.X, RandomPoint.Y, 0.0f);
	FVector RelativeLocation = SpawnCenter.GetLocation() + LocalRandomOffset;
    
	FVector WorldLocation = GetTransform().TransformPosition(RelativeLocation);
	FRotator SpawnRotation = GetActorRotation();

	TScriptInterface<IObjectPoolInterface> Spawned = PoolSys->GetObjectFromPool(ActorToSpawn);

	if (Spawned)
	{
		FObjectPoolActivateData Data;
		Data.ObjectPoolTransform = FTransform(SpawnRotation, WorldLocation, FVector::OneVector);

		// IObjectPoolInterface::Execute_BP_Activate(Spawned.GetObject(), Data);
		Spawned.GetInterface()->Activate(Data);
	}
}
