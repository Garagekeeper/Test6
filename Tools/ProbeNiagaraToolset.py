import json
from pathlib import Path
import unreal

registry = unreal.ToolsetRegistry
schema = json.loads(registry.get_toolset_json_schema(unreal.NiagaraToolset_System))
Path(unreal.Paths.project_saved_dir(), "NiagaraToolsetSchema.json").write_text(json.dumps(schema, indent=2), encoding="utf-8")
unreal.log("NIAGARA_TOOL_NAMES " + ", ".join(x["name"].split(".")[-1] for x in schema["tools"]))
toolset_name = schema["name"]
tool_name = "GetSystemSummary"
params = {"system": {"refPath": "/Niagara/DefaultAssets/Templates/Systems/SimpleExplosion.SimpleExplosion"}}
result = registry.execute_tool(toolset_name, tool_name, json.dumps(params))
unreal.log("NIAGARA_RESULT_FIELDS " + ", ".join(x for x in dir(result) if any(k in x for k in ("complete", "error", "value"))))
unreal.log(f"NIAGARA_TOOL_RESULT error={result.get_editor_property('error')} value={result.get_editor_property('value')}")
