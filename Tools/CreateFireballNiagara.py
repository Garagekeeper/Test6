"""Create and tune the fireball Niagara systems with UE 5.8's Niagara toolset.

Run with UnrealEditor-Cmd -run=pythonscript -script=<this file>.
"""

import json
import unreal

REG = unreal.ToolsetRegistry
TOOLSET = "NiagaraToolsets.NiagaraToolset_System"
DEST = "/Game/Fireball/VFX"
TEMPLATE_IMPACT = "/Niagara/DefaultAssets/Templates/Systems/SimpleExplosion.SimpleExplosion"
TEMPLATE_BURN = "/Game/LevelPrototyping/Interactable/JumpPad/Assets/NS_JumpPad.NS_JumpPad"


def call(name, args):
    result = REG.execute_tool(TOOLSET, name, json.dumps(args))
    error = result.get_editor_property("error")
    if error:
        raise RuntimeError(f"{name}: {error}")
    value = result.get_editor_property("value")
    return json.loads(value).get("returnValue") if value else None


def sref(path):
    return {"refPath": path}


def ref(path, emitter="", script="", module="", renderer=-1, inputs=None):
    return {"system": sref(path), "emitterName": emitter, "scriptName": script,
            "moduleName": module, "rendererIndex": renderer,
            "inputNameStack": inputs or []}


def create(name, template):
    path = f"{DEST}/{name}.{name}"
    if not unreal.load_asset(path):
        result = call("CreateNiagaraSystem", {"assetName": name, "assetPath": DEST,
                                               "templateSystem": sref(template)})
        unreal.log(f"FIREBALL_NIAGARA_CREATED {name} {result}")
    if not unreal.load_asset(path):
        raise RuntimeError(f"System missing after creation: {path}")
    return path


def emitters(path):
    return [x["emitterName"] for x in call("GetSystemSummary", {"system": sref(path)})["emitters"]]


def keep_only(path, names):
    for name in emitters(path):
        if name not in names:
            call("RemoveEmitter", {"emitterToRemove": ref(path, name)})
    found = emitters(path)
    if found != names:
        raise RuntimeError(f"Unexpected emitters on {path}: {found}")


def material(path, emitter, material_path):
    call("SetRendererData", {"renderer": ref(path, emitter, renderer=0),
                             "rendererData": {"propertyValues": json.dumps({"Material": sref(material_path)})}})
    read = call("GetRendererData", {"rendererRef": ref(path, emitter, renderer=0)})
    actual = json.loads(read["propertyValues"])["Material"]["refPath"]
    if actual != material_path:
        raise RuntimeError(f"Renderer material did not stick: {actual}")


def input_value(path, emitter, script, module, input_name, value):
    r = ref(path, emitter, script, module, inputs=[input_name])
    old = call("GetStackInputData", {"stackInputRef": r})
    if not old or "struct" not in old:
        raise RuntimeError(f"Cannot read input {emitter}.{module}.{input_name}: {old}")
    old["value"] = value
    call("SetStackInputData", {"stackInputRef": r, "inputData": old})
    unreal.log(f"FIREBALL_NIAGARA_SET {emitter}.{module}.{input_name}={value}")


def f(path, emitter, script, module, name, number):
    input_value(path, emitter, script, module, name, {"value": number})


def save(path):
    asset = unreal.load_asset(path)
    if not unreal.EditorAssetLibrary.save_loaded_asset(asset):
        raise RuntimeError(f"Failed saving {path}")
    unreal.log(f"FIREBALL_NIAGARA_SAVED {path}")


impact = create("NS_FireballImpact", TEMPLATE_IMPACT)
keep_only(impact, ["OmnidirectionalBurst", "SimpleSpriteBurst"])
material(impact, "OmnidirectionalBurst", f"{DEST}/M_FireballFlame.M_FireballFlame")
material(impact, "SimpleSpriteBurst", f"{DEST}/M_FireballShock.M_FireballShock")
f(impact, "OmnidirectionalBurst", "EmitterUpdateScript", "SpawnBurst_Instantaneous", "Spawn Count", 45)
f(impact, "OmnidirectionalBurst", "ParticleSpawnScript", "InitializeParticle", "Lifetime Min", 0.25)
f(impact, "OmnidirectionalBurst", "ParticleSpawnScript", "InitializeParticle", "Lifetime Max", 0.65)
f(impact, "OmnidirectionalBurst", "ParticleSpawnScript", "InitializeParticle", "Uniform Sprite Size Min", 5)
f(impact, "OmnidirectionalBurst", "ParticleSpawnScript", "InitializeParticle", "Uniform Sprite Size Max", 16)
f(impact, "SimpleSpriteBurst", "EmitterUpdateScript", "SpawnBurst_Instantaneous", "Spawn Count", 1)
f(impact, "SimpleSpriteBurst", "ParticleSpawnScript", "InitializeParticle", "Uniform Sprite Size Min", 110)
f(impact, "SimpleSpriteBurst", "ParticleSpawnScript", "InitializeParticle", "Uniform Sprite Size Max", 110)
save(impact)

burn = create("NS_FireballBurn", TEMPLATE_BURN)
keep_only(burn, ["Spores"])
material(burn, "Spores", f"{DEST}/M_FireballFlame.M_FireballFlame")
f(burn, "Spores", "EmitterUpdateScript", "SpawnRate", "SpawnRate", 26)
f(burn, "Spores", "ParticleSpawnScript", "InitializeParticle", "Lifetime Min", 0.42)
f(burn, "Spores", "ParticleSpawnScript", "InitializeParticle", "Lifetime Max", 0.82)
f(burn, "Spores", "ParticleSpawnScript", "InitializeParticle", "Uniform Sprite Size Min", 23)
f(burn, "Spores", "ParticleSpawnScript", "InitializeParticle", "Uniform Sprite Size Max", 42)
f(burn, "Spores", "ParticleSpawnScript", "ShapeLocation", "Cylinder Radius", 28)
f(burn, "Spores", "ParticleUpdateScript", "GravityForce", "Gravity", {"x": 0, "y": 0, "z": 390})
save(burn)

for path in (impact, burn):
    state = call("GetSystemCompileState", {"system": sref(path)})
    issues = call("GetStackIssues", {"system": sref(path)})
    unreal.log(f"FIREBALL_NIAGARA_VERIFY {path} compile={state} issues={issues}")

unreal.log("FIREBALL_NIAGARA_COMPLETE")
