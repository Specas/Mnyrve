workspace(name = "Mnyrve")

load("//tools/starlark:repository.bzl", "python_repository")

# gtest test archive
new_http_archive(
    name = "gtest",
    url = "https://github.com/google/googletest/archive/release-1.7.0.zip",
    sha256 = "b58cb7547a28b2c718d1e38aee18a3659c9e3ff52440297e965f5edffe34b6d0",
    build_file = "gtest.BUILD",
    strip_prefix = "googletest-release-1.7.0",
)

# glags repository
git_repository(
    name = "gflags_repo", 
    commit = "7e709881881c2663569cd49a93e5c8d9228d868e", 
    remote = "https://github.com/gflags/gflags.git",
)


# Python repository
python_repository(
    name = "python3_rep",
    version = "3",
)


