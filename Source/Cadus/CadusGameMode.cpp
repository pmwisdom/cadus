// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "CadusGameMode.h"
#include "CadusPawn.h"

ACadusGameMode::ACadusGameMode()
{
	// set default pawn class to our flying pawn
	DefaultPawnClass = ACadusPawn::StaticClass();
}
