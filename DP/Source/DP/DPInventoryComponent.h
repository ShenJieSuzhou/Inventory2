// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DPInventoryComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryUpdated);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DP_API UDPInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDPInventoryComponent();

	// Called when the game starts
	virtual void BeginPlay() override;

	bool AddItem(class UItem* Item);
	bool RemoveItem(class UItem* Item);

	UPROPERTY(EditDefaultsOnly, Instanced)
	TArray<class UItem*> DefaultItems;

	UPROPERTY(EditDefaultsOnly, Category = "Inventory")
	int32 Capacity;

	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FOnInventoryUpdated OnInventoryUpdated;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Items")
	TArray<class UItem*> Items;
 
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
