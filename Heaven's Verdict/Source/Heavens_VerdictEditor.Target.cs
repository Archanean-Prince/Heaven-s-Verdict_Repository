// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class Heavens_VerdictEditorTarget : TargetRules
{
	public Heavens_VerdictEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;

		ExtraModuleNames.AddRange( new string[] { "Heavens_Verdict" } );
	}
}
