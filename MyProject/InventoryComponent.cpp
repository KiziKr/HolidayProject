// Fill out your copyright notice in the Description page of Project Settings.

#include "InventoryComponent.h"
#include "Engine.h"
#include "Kismet/GameplayStatics.h"


UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	InventoryTable = nullptr;
}


void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
}


void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}


void UInventoryComponent::SortItemByName(const FTableRowInventory *item)
{
	/*if (!InventoryMap.Contains(item->ItemData.name))
	{
		FConversations test;
		test.Entries.Init(*item, 1);

		InventoryMap.Add(item->ItemData.name, test);
	}
	else
	{
		InventoryMap[item->ItemData.name].Entries.Add(*item);
	}*/
}


void UInventoryComponent::SortItemByStats(const FTableRowInventory *Item)
{

}


void UInventoryComponent::RemoveItem(const FItemData &item)
{

}