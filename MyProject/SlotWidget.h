// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Blueprint/UserWidget.h"
#include "ItemBaseWidget.h"
#include "SlotWidget.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API USlotWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, category = testItemBase)
	UItemBaseWidget* GetItemDescription() 
	{ 
		return WidgetDescription; 
	}

	void SetItemDescription(UItemBaseWidget* NewItemDescription) { WidgetDescription = NewItemDescription; }

	UFUNCTION(BlueprintCallable, category = SlotWidget)
	UInventoryUserWidget* GetParentInventory() const
	{ 
		return ParentInventory; 
	}

	void SetParentInventory(UInventoryUserWidget* NewParentInventory) { ParentInventory = NewParentInventory; }

	UFUNCTION(BlueprintCallable, category = SlotWidget)
	int32 GetId() const
	{
		return Id;
	}

	void SetId(int32 NewId) { Id = NewId; }

	UFUNCTION(BlueprintCallable, category = SlotWidget)
	FTableRowInventory GetItemInfos() const
	{
		return ItemInfos;
	}

	UFUNCTION(BlueprintCallable, category = test)
	void SetItemInfos(const FTableRowInventory& NewItemInfos) { ItemInfos = NewItemInfos; }

private:
	UPROPERTY()
	UItemBaseWidget* WidgetDescription;

	UInventoryUserWidget* ParentInventory;

	FTableRowInventory ItemInfos;

	int32 Id;
};