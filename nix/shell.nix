{ mkShell, gnumake, strlx }:
mkShell {
  name = "strlx Developer Environment";
  inputsFrom = [
    strlx
  ];
  packages = [
    gnumake
  ];
}
