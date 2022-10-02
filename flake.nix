{
  description = "Kaleidoscope keyboard firmware";

  inputs = {
    devshell.url = "github:numtide/devshell";
    flake-utils.url = "github:numtide/flake-utils";
    unstable.url = "github:nixos/nixpkgs/nixos-unstable";
  };

  outputs = { self, flake-utils, devshell, nixpkgs, unstable }:
    flake-utils.lib.eachDefaultSystem (system:
      let
        pkgs-unstable = import unstable {
          inherit system;
          overlays = [ devshell.overlays.default ];
        };
        pkgs = import nixpkgs {
          inherit system;
          overlays = [
            devshell.overlays.default
            (self: super: {
              inherit (pkgs-unstable) arduino-cli;
            })
          ];
        };
      in
      {
        devShell = pkgs.devshell.mkShell {
          env = [
            {
              name = "KALEIDOSCOPE_DIR";
              eval = "$PWD";
            }
          ];
          imports = [ (pkgs.devshell.importTOML ./devshell.toml) ];
        };
      });
}
