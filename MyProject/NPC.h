// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameObject.h"
#include "Components/BoxComponent.h"
#include "InventoryUserWidget.h"
#include "PlayerCharacter.h"
#include "NPC.generated.h"

UENUM()
enum RoleNPC
{
	Questgivers,
	Merchand,
	Banker
};

UCLASS()
class MYPROJECT_API ANPC : public AGameObject
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANPC();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UDataTable* ItemsTables = nullptr;

protected:
	UPROPERTY(EditAnywhere, Category = Inventory)
	TSubclassOf<UInventoryUserWidget> wInventoryUserWidget;

	UPROPERTY()
	UInventoryUserWidget* InventoryUserWidget;

	UFUNCTION()
	virtual void OnGameObject(AActor* Target, FKey ButtonPressed) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnyWhere, Category = NPC)
	TEnumAsByte<RoleNPC> RoleNPC;

	UPROPERTY(EditAnyWhere, Category=Shop)
	TArray<TEnumAsByte<ItemCategory>> CanSell;

protected:
	APlayerCharacter* PlayerInteract;
};
