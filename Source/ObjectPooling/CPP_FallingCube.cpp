// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_FallingCube.h"

#include "ObjectPoolerSubsystem.h"

// Sets default values
ACPP_FallingCube::ACPP_FallingCube()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACPP_FallingCube::BeginPlay()
{
	Super::BeginPlay();

	PoolSys = GetWorld()->GetGameInstance()->GetSubsystem<UObjectPoolerSubsystem>();
}

void ACPP_FallingCube::SetActive(bool Active)
{
	SetActorTickEnabled(Active);
	SetActorEnableCollision(Active);
	SetActorHiddenInGame(!Active);
}

// Called every frame
void ACPP_FallingCube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ActiveTimer += DeltaTime;
	
	if (ActiveTimer >= 4.0f)
	{
		FObjectPoolDeactivateData Data;
		NativeDeactivate(Data);
		ActiveTimer = 0.0f;
	}
}

void ACPP_FallingCube::NativeActivate(FObjectPoolActivateData Data)
{
	IObjectPoolInterface::NativeActivate(Data);

	FVector Location = Data.ObjectPoolTransform.GetLocation();
	FRotator Rotation = Data.ObjectPoolTransform.Rotator();
	
	SetActorLocationAndRotation(Location, Rotation);
	SetActorTickEnabled(true);
	// SetActive(true);
	
}

void ACPP_FallingCube::NativeDeactivate(FObjectPoolDeactivateData Data)
{
	IObjectPoolInterface::NativeDeactivate(Data);

	FVector Location = Data.ObjectPoolReturnTransform.GetLocation();
	FRotator Rotation = Data.ObjectPoolReturnTransform.Rotator();
	
	SetActorLocationAndRotation(Location, Rotation);

	// return to pool
	PoolSys->ReturnObjectToPool(GetClass(), this);
	SetActorTickEnabled(false);
	// SetActive(false);
}

void ACPP_FallingCube::BP_Activate_Implementation(FObjectPoolActivateData Data)
{
	IObjectPoolInterface::BP_Activate_Implementation(Data);
	
	// SetActive(true);
	SetActorTransform(Data.ObjectPoolTransform);
}

