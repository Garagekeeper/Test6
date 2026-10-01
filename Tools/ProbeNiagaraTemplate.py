import json
from pathlib import Path
import unreal

REG = unreal.ToolsetRegistry
TOOLSET = "NiagaraToolsets.NiagaraToolset_System"


def call(name, args):
    result = REG.execute_tool(TOOLSET, name, json.dumps(args))
    if result.get_editor_property("error"):
        raise RuntimeError(f"{name}: {result.get_editor_property('error')}")
    return json.loads(result.get_editor_property("value"))["returnValue"]


def ref(system, emitter="", renderer=-1):
    return {"system": {"refPath": system}, "emitterName": emitter,
            "scriptName": "", "moduleName": "", "rendererIndex": renderer,
            "inputNameStack": []}


systems = [
    "/Niagara/DefaultAssets/Templates/Systems/SimpleExplosion.SimpleExplosion",
    "/Niagara/DefaultAssets/Templates/Systems/RadialBurst.RadialBurst",
    "/Game/LevelPrototyping/Interactable/JumpPad/Assets/NS_JumpPad.NS_JumpPad",
]
result = {}
for path in systems:
    system = unreal.load_asset(path)
    summary = call("GetSystemSummary", {"system": {"refPath": path}})
    entry = {"summary": summary, "emitters": {}}
    for e in summary["emitters"]:
        name = e["emitterName"]
        er = ref(path, name)
        data = {"topology": call("GetEmitterTopology", {"emitterRef": er}),
                "values": call("GetEmitterInputValues", {"emitterRef": er}),
                "emitterData": call("GetEmitterData", {"emitterRef": er}),
                "renderers": []}
        for i in range(len(e["rendererClasses"])):
            data["renderers"].append(call("GetRendererData", {"rendererRef": ref(path, name, i)}))
        entry["emitters"][name] = data
    result[path] = entry

dest = Path(unreal.Paths.project_saved_dir(), "NiagaraTemplateProbe.json")
dest.write_text(json.dumps(result, indent=2), encoding="utf-8")
unreal.log(f"NIAGARA_PROBE_OK {dest}")
