// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemData.h"
#include "ItemBaseWidget.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API UItemBaseWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, category = Item)
	FTableRowInventory GetItemInfos()
	{ 
		return ItemInfos; 
	}

	UFUNCTION(BlueprintCallable, category = test)
	void SetItemInfos(const FTableRowInventory& NewItemInfos) { ItemInfos = NewItemInfos; }

	UFUNCTION(BlueprintCallable, category = Item)
	UTexture2D* GetSprite()
	{ 
		return ItemInfos.ItemData.sprite;
	}

	UFUNCTION(BlueprintCallable, category = Item)
	int32 GetQuantity()
	{
		return ItemInfos.Quantity;
	}

	UFUNCTION(BlueprintCallable, category = test)
	void SetQuantity(int32 NewQuantity) { ItemInfos.Quantity = NewQuantity; }

private:
	FTableRowInventory ItemInfos;
};
