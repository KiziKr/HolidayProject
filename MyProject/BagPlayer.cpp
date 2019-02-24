// Fill out your copyright notice in the Description page of Project Settings.

#include "BagPlayer.h"
#include "PlayerCharacter.h"
#include "Engine.h"

ABagPlayer::ABagPlayer()
{
	PrimaryActorTick.bCanEverTick = false;

	bIsOpen = false;
}

void ABagPlayer::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	if (PC && wInventoryUserWidget_0 && wInventoryUserWidget_1)
	{
		InventoryUserWidget_0 = CreateWidget<UInventoryUserWidget>(PC, wInventoryUserWidget_0);
		InventoryUserWidget_1 = CreateWidget<UInventoryUserWidget>(PC, wInventoryUserWidget_1);
	}
}

void ABagPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABagPlayer::OnPlayerEnterPickupBox(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnPlayerEnterPickupBox(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);


}

void ABagPlayer::SequenceBag()
{
	(bIsOpen == true) ? CloseBag() : OpenBag();
}

void ABagPlayer::OpenBag()
{
	if(InventoryUserWidget_0)
	{
		if (!bIsOpen)
		{
			InventoryUserWidget_0->ShowInventoryUniformInverse(InventoryBagPlayer, 5, 18);
			InventoryUserWidget_0->AddToViewport();
			bIsOpen = true;
		}
		else
		{
			RefreshBag();
		}
	}
}

void ABagPlayer::RefreshBag()
{
	if (InventoryUserWidget_0)
	{
		InventoryUserWidget_0->ShowInventoryUniformInverse(InventoryBagPlayer, 5, 18);
	}
}

void ABagPlayer::CloseBag()
{
	if (InventoryUserWidget_0 && bIsOpen)
	{
		InventoryUserWidget_0->RemoteInventory();
		bIsOpen = false;
	}
}

void ABagPlayer::InspectBag()
{
	if (InventoryUserWidget_1)
	{
		InventoryUserWidget_1->ShowInventoryInPanel<UScrollBox>(InventoryBagPlayer, FName("Inventory_Vertical"));
	}
}

FTableRowInventory* ABagPlayer::HasBrother(const FTableRowInventory &Item)
{
	for (FTableRowInventory& ItemBagPlayer : InventoryBagPlayer)
	{
		if (Item.ItemData.id != ItemBagPlayer.ItemData.id)
		{
			continue;
		}

		if (Item.ItemData.ItemStats.Agility != ItemBagPlayer.ItemData.ItemStats.Agility)
		{
			continue;
		}

		if (Item.ItemData.ItemStats.Intelligence != ItemBagPlayer.ItemData.ItemStats.Intelligence)
		{
			continue;
		}

		if (Item.ItemData.ItemStats.Strenght != ItemBagPlayer.ItemData.ItemStats.Strenght)
		{
			continue;
		}

		if (Item.ItemData.ItemStats.Vitality != ItemBagPlayer.ItemData.ItemStats.Vitality)
		{
			continue;
		}

		return &ItemBagPlayer;

	}
	return nullptr;
}

bool ABagPlayer::AddItem(const FTableRowInventory &Item, int32 Quantity)
{
	int32 CurrentWeight = Weight;
	Weight = (Item.ItemData.weight * Quantity) + Weight;

	if (Weight > MaxWeight)
	{
		Weight = CurrentWeight;
		return false;
	}

	if (FTableRowInventory* TempItem = HasBrother(Item))
	{
		TempItem->Quantity += Quantity;
		return true;
	}
	else if (NumberItemCategory(Item.ItemData.category) < MaxLimit)
	{
		FTableRowInventory NewItem = Item;
		NewItem.Quantity = Quantity;

		InventoryBagPlayer.Add(NewItem);
		return true;
	}

	Weight = CurrentWeight;
	return false;
}

FString ABagPlayer::ConvertCategoryString(TEnumAsByte<ItemCategory> category)
{
	const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("ItemCategory"), true);
	return EnumPtr->GetNameStringByValue(category.GetValue());
}

int32 ABagPlayer::NumberItemCategory(TEnumAsByte<ItemCategory> category)
{
	FString TheCategory = ConvertCategoryString(category);

	int32 Number = 0;
	for (FTableRowInventory ItemBagPlayer : InventoryBagPlayer)
	{
		if (ConvertCategoryString(ItemBagPlayer.ItemData.category) == TheCategory)
		{
			Number++;
		}
	}
	return Number;
}