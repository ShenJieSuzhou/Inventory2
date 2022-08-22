// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "MyItemPickup.generated.h"

UCLASS()
class DP_API AMyItemPickup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyItemPickup();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Interacted();

	bool GetActive();

private:
	UPROPERTY()
	bool active;

	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	class UStaticMeshComponent* mesh; 
};
