// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ObjectPoolInterface.h"
#include "GameFramework/Actor.h"
#include "CPP_FallingCube.generated.h"

class UObjectPoolerSubsystem;

UCLASS()
class OBJECTPOOLING_API ACPP_FallingCube : public AActor, public IObjectPoolInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACPP_FallingCube();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void SetActive(bool Active);
	float ActiveTimer = 0.0f;

	UObjectPoolerSubsystem* PoolSys;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	

	virtual void NativeActivate(FObjectPoolActivateData Data) override;

	virtual void NativeDeactivate(FObjectPoolDeactivateData Data) override;

	virtual void BP_Activate_Implementation(FObjectPoolActivateData Data) override;

};
