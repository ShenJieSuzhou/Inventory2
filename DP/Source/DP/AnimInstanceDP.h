// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "DPCharacter.h"
#include "AnimInstanceDP.generated.h"

/**
 * 
 */
UCLASS()
class DP_API UAnimInstanceDP : public UAnimInstance
{
	GENERATED_BODY()
	
	
public:
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float movementSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool EnableJump;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ADPCharacter* PlayerRef;


	UFUNCTION(BlueprintCallable, Category = "Animations")
	virtual void UpdateAnimationProperties();
};
