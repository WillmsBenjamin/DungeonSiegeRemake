// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DungeonSiegeRemakePlayerController.generated.h"

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

	void ProcessMouseHit(const FHitResult& Hit);
};


