// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "PlayerCharacterAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API UPlayerCharacterAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:

	//Hitpoints. Self-explanatory.
	UPROPERTY(Category = "Wizard Attributes | Health", EditAnywhere, BlueprintReadWrite)
	FGameplayAttributeData Health;

public:

	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData &Data) override;
};
