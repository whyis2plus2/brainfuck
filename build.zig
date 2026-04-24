const std = @import("std");

pub fn build(b: *std.Build) void {
    const target = b.standardTargetOptions(.{});
    const mode   = b.standardOptimizeOption(.{});

    const module = b.addModule("main", .{
        .target = target,
        .optimize = mode,
        .link_libc = true,
    });

    module.addCSourceFiles(.{
        .files = &[_][]const u8{ "src/context.c", "src/errors.c", "src/main.c", "src/tokens.c" }
    });

    const exe = b.addExecutable(.{
        .name = "brainfuck",
        .root_module = module,
    });

    b.installArtifact(exe);
}
