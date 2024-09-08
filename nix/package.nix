{ stdenv }:
let
  pname = "strlx";
  version = "2.0.2";
in
stdenv.mkDerivation {
  inherit pname version;
  src = ../.;

  installPhase = ''
    mkdir -p $out/bin
    cp strlx $out/bin/strlx
  '';

  meta = {
      description = "a fetch in C";
      homepage = "https://github.com/alexpkgs/strlx-port-for-nix"
      maintainers = with lib.maintainers; [alexpkgs];
      mainProgram = "strlx";
    };
  }
}
