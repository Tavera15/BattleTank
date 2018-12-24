// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet) {
	if (!BarrelToSet) { return; }
	Barrel = BarrelToSet;
}

void UTankAimingComponent::SetTurretReference(UTankTurret* TurretToSet) {
	if (!TurretToSet) { return; }
	Turret = TurretToSet;
}

void UTankAimingComponent::AimAt(FVector OUTHitLocation, float LaunchSpeed) {
	if (!Barrel) { return; }
	FVector OUTLaunchVelocity(0);
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	// Calculate OUTLaunchVelocity
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
	(
		this,
		OUTLaunchVelocity,
		StartLocation,
		OUTHitLocation,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);
	
	auto Time = GetWorld()->GetTimeSeconds();

	if (bHaveAimSolution) {
		auto AimDirection = OUTLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
		//MoveTurretTowards(AimDirection);

		//UE_LOG(LogTemp, Warning, TEXT(" %f: Aim solve found"), Time);

	}
	else {
		UE_LOG(LogTemp, Warning, TEXT(" %f: No aim solve found"), Time);

	}

}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection) {
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimRotator = AimDirection.Rotation();
	auto DeltaRotator = AimRotator - BarrelRotator;
	Barrel->Elevate(DeltaRotator.Pitch);
	Turret->RotateTurret(DeltaRotator.Yaw);
}

/*
void UTankAimingComponent::MoveTurretTowards(FVector AimDirection) {
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimRotator = AimDirection.Rotation();
	auto DeltaRotator = AimRotator - BarrelRotator;
	Turret->RotateTurret(DeltaRotator.Yaw);
}
*/
