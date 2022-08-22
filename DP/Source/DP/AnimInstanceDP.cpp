// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstanceDP.h"
#include "GameFramework/PawnMovementComponent.h"

void UAnimInstanceDP::UpdateAnimationProperties()
{
	PlayerRef = Cast<ADPCharacter>(TryGetPawnOwner());

	if(PlayerRef)
	{
		movementSpeed = PlayerRef->GetVelocity().Size();
		EnableJump = PlayerRef->GetMovementComponent()->IsFalling();
	}
}

	