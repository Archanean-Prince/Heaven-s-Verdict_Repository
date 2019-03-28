// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class Heavens_VerdictTarget : TargetRules
{
	public Heavens_VerdictTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;

		ExtraModuleNames.AddRange( new string[] { "Heavens_Verdict" } );
	}
}
