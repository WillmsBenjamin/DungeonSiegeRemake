// Copyright Epic Games, Inc. All Rights Reserved.

#include "DungeonSiegeRemakePlayerController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "DungeonSiegeRemakeCharacter.h"
#include "Interaction/DSInteractable.h"

ADungeonSiegeRemakePlayerController::ADungeonSiegeRemakePlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
}

void ADungeonSiegeRemakePlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	
	GetHitResultUnderCursor(ECC_Visibility, false, CurrentMouseHitResult);
	CurrentMouseHoverState = CalculateMouseHoverStatus(CurrentMouseHitResult);
	
	ProcessMouseHoverStateCursor(CurrentMouseHoverState, CurrentMouseHitResult);
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
	const auto Status = CalculateMouseHoverStatus(CurrentMouseHitResult);
	ProcessMouseHoverStateActions(Status, CurrentMouseHitResult);
}

EMouseHoverState ADungeonSiegeRemakePlayerController::CalculateMouseHoverStatus(const FHitResult& Hit)
{
	if (!Hit.bBlockingHit)
	{
		return EMouseHoverState::Invalid;
	}

	auto* Interactable = Cast<IDSInteractable>(Hit.GetActor());
	if (Interactable != nullptr)
	{
		return (Interactable->IsInteractable()) ?
			EMouseHoverState::Interactable :
			EMouseHoverState::Invalid;
	}
	
	return EMouseHoverState::Environment;
}

void ADungeonSiegeRemakePlayerController::ProcessMouseHoverStateActions(const EMouseHoverState HoverState,
	const FHitResult& Hit)
{
	switch (HoverState)
	{
		case EMouseHoverState::Environment:
			{
				SetNewMoveDestination(Hit.ImpactPoint);
				break;
			}
		case EMouseHoverState::Interactable:
			{
				auto* Interactable = Cast<IDSInteractable>(Hit.GetActor());
				Interactable->Interact(this);
				break;
			}
		default:
			{
				break;
			}
	}
}

void ADungeonSiegeRemakePlayerController::ProcessMouseHoverStateCursor(const EMouseHoverState HoverState,
	const FHitResult& Hit)
{
	switch (HoverState)
	{
	case EMouseHoverState::Environment:
		{
			CurrentMouseCursor = EMouseCursor::Default;
			break;
		}
	case EMouseHoverState::Interactable:
		{
			CurrentMouseCursor = EMouseCursor::GrabHand;
			break;
		}
	default:
		{
			CurrentMouseCursor = EMouseCursor::SlashedCircle;
			break;
		}
	}
}
