// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankPlayerController.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	auto ControlledTank = GetControlledTank();

	if (!ControlledTank) {
		UE_LOG(LogTemp, Warning, TEXT("TankPlayerController NOT possessing tank"))
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("TankPlayerController possessing tank: %s"), *(ControlledTank->GetName()))
	}
}


void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrossHair();

}

ATank* ATankPlayerController::GetControlledTank() const {
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrossHair() {
	if (!GetControlledTank()) { return; }

	FVector OUTHitLocation;		// OUT param

	// Has "side-effect" to line trace
	if (GetSightRayHitLocation(OUTHitLocation)) {
		GetControlledTank()->AimAt(OUTHitLocation);
	}


}

// Get world location of linetrace through crosshair
bool ATankPlayerController::GetSightRayHitLocation(FVector& OUTHitLocation) const{
	OUTHitLocation = FVector(1.0);

	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);

	auto ScreenLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);

	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection)) {		
		GetLookVectorHitLocation(LookDirection, OUTHitLocation);
	}

	return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const {
	FVector CameraWorldLocation;		// To be discarded

	return DeprojectScreenPositionToWorld(
		ScreenLocation.X, ScreenLocation.Y, 
		CameraWorldLocation, LookDirection);

}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& OUTHitLocation) const {
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);

	if (GetWorld()->LineTraceSingleByChannel(
		HitResult,
		StartLocation,
		EndLocation,
		ECollisionChannel::ECC_Visibility)
		) 
	{
		OUTHitLocation = HitResult.Location;
		return true;
	}
	OUTHitLocation = FVector(0);
	return false;
}