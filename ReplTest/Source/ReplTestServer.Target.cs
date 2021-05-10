// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

[SupportedPlatforms(UnrealPlatformClass.Server)]
public class ReplTestServerTarget : TargetRules
{
    public ReplTestServerTarget(TargetInfo Target) : base(Target)
    {
        Type = TargetType.Server;
        bUsesSteam = true;

        ExtraModuleNames.Add("ReplTest");
    }
}