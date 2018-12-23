// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TankAimingComponent.generated.h"

// Forward Declaration
class UTankBarrel;		


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BTGAME_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	// Sets default values for this component's properties
	UTankAimingComponent();
	
	void AimAt(FVector OUTHitLocation, float LaunchSpeed);

	void SetBarrelReference(UTankBarrel* BarrelToSet);


protected:
	
private:
	UTankBarrel* Barrel = nullptr;
	
	void MoveBarrelTowards(FVector);
};
