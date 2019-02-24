// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NPC.h"
#include "NPCShop.generated.h"


/**
 * 
 */
UCLASS()
class MYPROJECT_API ANPCShop : public ANPC
{
	GENERATED_BODY()

	//UPROPERTY()
	//UShopUserWidget* ShopWidget;

	bool bInteract;

public:
	ANPCShop();

public:
	void OpenTheShop();

	void CloseTheShop();

protected:
	virtual void BeginPlay() override;

	virtual void OnGameObject(AActor* Target, FKey ButtonPressed) override;

private:
	TArray<FTableRowInventory*> GetItemsByCategory();

private:
	UPROPERTY(EditAnyWhere, Category = Shop)
	TArray<TEnumAsByte<ItemCategory>> TheCanSell;
};
