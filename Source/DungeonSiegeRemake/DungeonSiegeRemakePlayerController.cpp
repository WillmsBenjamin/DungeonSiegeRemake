// Copyright Epic Games, Inc. All Rights Reserved.

#include "DungeonSiegeRemakePlayerController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "DungeonSiegeRemakeCharacter.h"
#include "Engine/World.h"

namespace InputBindings
{
	const static FName GKSelect = "Select";
}

ADungeonSiegeRemakePlayerController::ADungeonSiegeRemakePlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}

void ADungeonSiegeRemakePlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
}

void ADungeonSiegeRemakePlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	InputComponent->BindAction(InputBindings::GKSelect, IE_Pressed, this, &ADungeonSiegeRemakePlayerController::OnSelectPressed);
}

void ADungeonSiegeRemakePlayerController::SetNewMoveDestination(const FVector DestLocation)
{
	const auto* MyPawn = GetPawn();
	if (IsValid(MyPawn))
	{
		float const Distance = FVector::Dist(DestLocation, MyPawn->GetActorLocation());

		// We need to issue move command only if far enough in order for walk animation to play correctly
		if ((Distance > 120.0f))
		{
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, DestLocation);
		}
	}
}

void ADungeonSiegeRemakePlayerController::OnSelectPressed()
{
	// Trace to see what is under the mouse cursor
	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Visibility, false, Hit);

	ProcessMouseHit(Hit);
}

void ADungeonSiegeRemakePlayerController::ProcessMouseHit(const FHitResult& Hit)
{
	if (!Hit.bBlockingHit)
	{
		return;
	}
	
	// We hit something, move there
	SetNewMoveDestination(Hit.ImpactPoint);
}
