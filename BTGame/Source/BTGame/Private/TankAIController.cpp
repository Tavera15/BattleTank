// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

}

void ATankAIController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	auto ControlledTank = Cast<ATank>(GetPawn());

	if (PlayerTank) {
		//TODO move towards player
		MoveToActor(PlayerTank, AcceptanceRadius);
		// Aim at the player
		ControlledTank->AimAt(PlayerTank->GetActorLocation());
	
		// TODO Shoot at the player but not every frame
		ControlledTank->Fire();
	}
	
}

