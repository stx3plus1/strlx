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
}
