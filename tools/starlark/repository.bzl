# -*- python -*-

load("//tools/starlark:utility.bzl", "custom_which")

def _impl(repository_ctx):

    python_config = custom_which(repository_ctx, "python3-config")

    # Getting includes
    python_headers = repository_ctx.execute([python_config, "--includes"])
    python_headers = python_headers.stdout.strip().split(" ")
    python_headers = [python_header for python_header in python_headers if python_header]

    # Getting linkers
    python_linkers = repository_ctx.execute([python_config, "--ldflags"])
    python_linkers = python_linkers.stdout.strip().split(" ")
    python_linkers = [python_linker for python_linker in python_linkers if python_linker]

    print("python3-config:", python_config)
    print("python3-headers:", python_headers) 
    print("python3-linkers:", python_linkers)

    root = repository_ctx.path("")
    root_len = len(str(root)) + 1
    base = root.get_child("include")

    includes = []

    for h in python_headers:
        if h.startswith("-I"):
          source = repository_ctx.path(h[2:])
          destination = base.get_child(str(source).replace("/", "_"))
          include = str(destination)[root_len:]
  
          if include not in includes:
              repository_ctx.symlink(source, destination)
              includes += [include]

    for i in reversed(range(len(python_linkers))):
        if not python_linkers[i].startswith("-"):
            python_linkers[i-1] += " " + python_linkers.pop(i)

    python_linkers_direct_link = list(python_linkers)
    
    file_content = """# -*- python -*-
  
headers = glob(
    ["include/*/*"],
    exclude_directories = 1,
)

cc_library(
    name = "python3_headers", 
    hdrs = headers, 
    includes = {}, 
    visibility = ["//visibility:private"],
)

cc_library(
    name = "python3", 
    linkopts = {}, 
    deps = [":python3_headers"], 
    visibility = ["//visibility:public"],
)

    """.format(includes, python_linkers)

    repository_ctx.file(
            "BUILD.bazel", 
            content = file_content,
            executable = False, 
    )

    

python_repository = repository_rule(
    _impl, 
    attrs = {"version": attr.string(default = "3")},
    local = True,
)
