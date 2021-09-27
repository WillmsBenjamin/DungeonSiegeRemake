// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "DSInteractable.generated.h"

UENUM(BlueprintType)
enum class EInteractionType: uint8
{
	None,
	Talk,
	Attack,
	Action
};

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UDSInteractable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class DUNGEONSIEGEREMAKE_API IDSInteractable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual bool IsInteractable() const { return GetInteractionType() != EInteractionType::None; }
	
	virtual EInteractionType GetInteractionType() const { return EInteractionType::None; }
	
	virtual void Interact(APlayerController* InteractingController) PURE_VIRTUAL(IDSInteractable::Interact,);
};
