import unreal

tool = unreal.NiagaraToolset_System
unreal.log("NIAGARA_METHODS " + ", ".join(x for x in dir(tool) if any(k in x for k in ("summary", "topology", "input_values", "create_niagara", "renderer", "emitter"))))
unreal.log("NIAGARA_PY_CLASSES " + ", ".join(x for x in dir(unreal) if any(k in x for k in ("NiagaraSystemFactory", "NiagaraEditorLibrary", "GameplayCueNotify_Burst", "GameplayCueNotify_Looping", "NiagaraEmitterFactory"))))
unreal.log("NIAGARA_REGISTRY " + str(unreal.ToolsetRegistry.is_available()))
schema = unreal.ToolsetRegistry.get_toolset_json_schema(unreal.NiagaraToolset_System)
unreal.log("NIAGARA_SCHEMA_HEAD " + schema[:16000])
for path in (
    "/Niagara/DefaultAssets/Templates/Systems/SimpleExplosion",
    "/Niagara/DefaultAssets/Templates/Systems/RadialBurst",
    "/Niagara/DefaultAssets/Templates/Systems/DirectionalBurst",
    "/Niagara/DefaultAssets/Templates/Systems/FountainLightweight",
    "/Game/LevelPrototyping/Interactable/JumpPad/Assets/NS_JumpPad",
):
    asset = unreal.load_asset(path)
    unreal.log("NIAGARA_ASSET " + path + " " + str(asset))
    if asset:
        try:
            unreal.log("NIAGARA_SUMMARY " + str(tool.get_system_summary(asset)))
        except Exception as exc:
            unreal.log("NIAGARA_ERROR " + str(exc))
