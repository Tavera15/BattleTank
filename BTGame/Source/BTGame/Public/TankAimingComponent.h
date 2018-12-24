// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/World.h"
#include "Components/ActorComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TankAimingComponent.generated.h"

// Forward Declaration
class UTankBarrel;
class UTankTurret;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BTGAME_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	// Sets default values for this component's properties
	UTankAimingComponent();
	
	void AimAt(FVector OUTHitLocation, float LaunchSpeed);

	void SetBarrelReference(UTankBarrel* BarrelToSet);
	void SetTurretReference(UTankTurret* TurretToSet);

protected:
	
private:
	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;
	
	void MoveBarrelTowards(FVector AimDirection);
	//void MoveTurretTowards(FVector AimDirection);
};
