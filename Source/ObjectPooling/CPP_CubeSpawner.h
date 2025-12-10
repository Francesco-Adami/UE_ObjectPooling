// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPP_CubeSpawner.generated.h"

class UObjectPoolerSubsystem;

UCLASS()
class OBJECTPOOLING_API ACPP_CubeSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACPP_CubeSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	float Timer = 0.0f;

	UFUNCTION(BlueprintCallable, BlueprintType, Category = "CubeSpawner")
	void SpawnInRandomPos();
	UObjectPoolerSubsystem* PoolSys;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CubeSpawner")
	TSubclassOf<AActor> ActorToSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CubeSpawner")
	float SpawnPerSecond = 8.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CubeSpawner", meta=(MakeEditWidget))
	FTransform SpawnCenter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CubeSpawner")
	float SpawnRadius = 60.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CubeSpawner")
	int32 PoolSize = 1;

};
