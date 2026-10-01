import unreal

for path in ("/Game/GAS/GE_Fireball_Projectile", "/Game/GAS/GE_Duration_Burn"):
    bp = unreal.EditorAssetLibrary.load_asset(path)
    unreal.log(f"FIREBALL_INSPECT {path} {bp.get_class().get_name()}")
    cls = bp.generated_class() if hasattr(bp, "generated_class") else bp.get_class()
    cdo = unreal.get_default_object(cls)
    for field in ("duration_policy", "duration_magnitude", "period", "gameplay_cues", "stacking_type", "stack_limit_count", "gameplay_effect_components"):
        try:
            unreal.log(f"FIREBALL_INSPECT {field}: {cdo.get_editor_property(field)}")
        except Exception as exc:
            unreal.log(f"FIREBALL_INSPECT {field}: ERROR {exc}")
