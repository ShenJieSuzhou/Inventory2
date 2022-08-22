// Fill out your copyright notice in the Description page of Project Settings.


#include "DPInventoryComponent.h"
#include "Item.h"

// Sets default values for this component's properties
UDPInventoryComponent::UDPInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...

	Capacity = 20;
}


// Called when the game starts
void UDPInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	for(auto& Item : DefaultItems)
	{
		AddItem(Item);
	}
}


bool UDPInventoryComponent::AddItem(class UItem* Item)
{
	if(Items.Num() >= Capacity || !Item)
	{
		return false;
	}

	Item->OwningInventory = this;
	Item->World = GetWorld();
	Items.Add(Item);

	// Update UI
	OnInventoryUpdated.Broadcast(); 

	return true;
}

bool UDPInventoryComponent::RemoveItem(class UItem* Item)
{
	if (Item)
	{
		Item->OwningInventory = nullptr;
		Item->World = nullptr;
		Items.RemoveSingle(Item);
		OnInventoryUpdated.Broadcast();
		return true;
	}
	return false;
}

// Called every frame
void UDPInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

