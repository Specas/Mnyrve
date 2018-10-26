# -*- python -*-

def custom_which(repository_ctx, file_name, default = None):

    result = repository_ctx.which(file_name)
    if not result:
        return default
    else:
        return repository_ctx.which(file_name)
