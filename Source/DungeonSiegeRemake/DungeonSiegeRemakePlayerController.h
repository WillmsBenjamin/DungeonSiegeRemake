// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DungeonSiegeRemakePlayerController.generated.h"

namespace InputBindings
{
	const static FName GKSelect = "Select";
}

UENUM()
enum class EMouseHoverState: uint8
{
	Invalid,
	Environment,
	Interactable
};

UCLASS()
class ADungeonSiegeRemakePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ADungeonSiegeRemakePlayerController();

protected:
	// Begin PlayerController interface
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;
	// End PlayerController interface
	
	/** Navigate player to the given world location. */
	void SetNewMoveDestination(const FVector DestLocation);

	/** Input handlers for SetDestination action. */
	void OnSelectPressed();

	static EMouseHoverState CalculateMouseHoverStatus(const FHitResult& Hit);

	void ProcessMouseHoverStateActions(const EMouseHoverState HoverState, const FHitResult& Hit);
	
	void ProcessMouseHoverStateCursor(const EMouseHoverState HoverState, const FHitResult& Hit);
	
private:
	UPROPERTY(Transient)
	FHitResult CurrentMouseHitResult;

	UPROPERTY(Transient)
	EMouseHoverState CurrentMouseHoverState = EMouseHoverState::Invalid;
};


