// Fill out your copyright notice in the Description page of Project Settings.

#include "MyProjectPlayerController.h"
#include "Engine.h"

bool AMyProjectPlayerController::MouseIsMoving()
{
	if (PlayerInput)
	{
		float DeltaX = PlayerInput->GetKeyValue(EKeys::MouseX);
		float DeltaY = PlayerInput->GetKeyValue(EKeys::MouseY);

		if (DeltaX != 0.0f || DeltaY != 0.0f)
		{
			return true;
		}
	}

	return false;
}