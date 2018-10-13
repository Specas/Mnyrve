# -*- python -*-

load("//tools/starlark:utility.bzl", "custom_which")

def _impl(repository_ctx):

    python_config = custom_which(repository_ctx, "python3-config")
    python_headers = repository_ctx.execute([python_config, "--includes"])
    python_headers = python_headers.stdout.strip().split(" ")
    print("python3-config:", python_config)
    print("python3-headers:", python_headers) 

    root = repository_ctx.path("")
    root_len = len(str(root)) + 1
    base = root.get_child("include")

    includes = []


    for h in python_headers:
        source = repository_ctx.path(h[2:])
        destination = base.get_child(str(source).replace("/", "_"))
        include = str(destination)[root_len:]

        if include not in includes:
            repository_ctx.symlink(source, destination)
            includes += [include]
    
    file_content = """# -*- python -*-
  
headers = glob(
      ["include/*/*"],
      exclude_directories = 1,
)

cc_library(
      name = "python3_headers", 
      hdrs = headers, 
      includes = {}, 
      visibility = ["//visibility:public"],
)
    """.format(includes)

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
